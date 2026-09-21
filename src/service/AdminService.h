#pragma once

#include "../repository/AdminRepository.h"

#include <string>

class AdminService
{
private:
    AdminRepository adminRepository;

public:
    AdminService();

    Json::Value getAllUsers();

    Json::Value getAllOrders();

    bool deleteProduct(long long productId);
};