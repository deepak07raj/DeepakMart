#include "UserService.h"
#include "../util/PasswordUtil.h"

UserService::UserService()
{
}

bool UserService::registerUser(User& user)
{
    if (user.name.empty() ||
        user.email.empty() ||
        user.password.empty())
    {
        return false;
    }

    if (user.role.empty())
    {
        user.role = "BUYER";
    }

    User userToSave = user;

    userToSave.password =
        PasswordUtil::hashPassword(user.password);

    bool ok = userRepository.createUser(userToSave);
    if (ok)
    {
        user.id = userToSave.id;
        user.password = userToSave.password;
    }

    return ok;
}

std::optional<User> UserService::loginUser(
    const std::string& email,
    const std::string& password)
{
    if (email.empty() || password.empty())
    {
        return std::nullopt;
    }

    auto user = userRepository.findByEmail(email);

    if (!user.has_value())
    {
        return std::nullopt;
    }

    bool passwordCorrect =
        PasswordUtil::verifyPassword(
            password,
            user->password
        );

    if (!passwordCorrect)
    {
        return std::nullopt;
    }

    return user;
}