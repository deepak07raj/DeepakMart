#pragma once

#include "../model/User.h"
#include <drogon/drogon.h>
#include <optional>

class UserRepository
{
public:
    UserRepository();

    bool createUser(User& user);

    std::optional<User> findByEmail(const std::string& email);
};