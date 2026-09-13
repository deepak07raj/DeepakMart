#include "UserRepository.h"

#include <iostream>

UserRepository::UserRepository()
{
}

bool UserRepository::createUser(const User& user)
{
    auto db = drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        db->execSqlSync(
            "INSERT INTO users (name, email, password_hash, role) "
            "VALUES ($1, $2, $3, $4)",
            user.name,
            user.email,
            user.password,
            user.role
        );

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "DATABASE ERROR: " << e.what() << std::endl;
        return false;
    }
}

std::optional<User> UserRepository::findByEmail(
    const std::string& email)
{
    auto db = drogon::app().getDbClient("default");

    if (!db)
    {
        return std::nullopt;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT id, name, email, password_hash, role "
            "FROM users "
            "WHERE email = $1",
            email
        );

        if (result.empty())
        {
            return std::nullopt;
        }

        User user;

        user.id = result[0]["id"].as<long long>();
        user.name = result[0]["name"].as<std::string>();
        user.email = result[0]["email"].as<std::string>();
        user.password = result[0]["password_hash"].as<std::string>();
        user.role = result[0]["role"].as<std::string>();

        return user;
    }
    catch (const std::exception& e)
    {
        std::cerr << "DATABASE ERROR: " << e.what() << std::endl;
        return std::nullopt;
    }
}