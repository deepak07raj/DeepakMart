#pragma once

#include <drogon/drogon.h>

#include <optional>

class AdminRepository
{
public:
    AdminRepository();

    Json::Value getAllUsers();

    Json::Value getAllOrders();

    bool deleteProduct(long long productId);
};