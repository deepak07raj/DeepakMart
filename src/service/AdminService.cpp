#include "AdminService.h"

AdminService::AdminService()
{
}

Json::Value AdminService::getAllUsers()
{
    return adminRepository.getAllUsers();
}

Json::Value AdminService::getAllOrders()
{
    return adminRepository.getAllOrders();
}

bool AdminService::deleteProduct(
    long long productId)
{
    if (productId <= 0)
    {
        return false;
    }

    return adminRepository.deleteProduct(
        productId
    );
}