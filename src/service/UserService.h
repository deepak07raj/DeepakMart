#pragma once

#include "../model/User.h"
#include "../repository/UserRepository.h"

#include <optional>

class UserService
{
private:
    UserRepository userRepository;

public:
    UserService();

    bool registerUser(User& user);

    std::optional<User> loginUser(
        const std::string& email,
        const std::string& password);
};