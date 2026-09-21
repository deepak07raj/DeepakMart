#pragma once

#include <drogon/HttpController.h>

#include "../service/AdminService.h"

class AdminController
    : public drogon::HttpController<AdminController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        AdminController::getAllUsers,
        "/api/admin/users",
        drogon::Get
    );

    ADD_METHOD_TO(
        AdminController::getAllOrders,
        "/api/admin/orders",
        drogon::Get
    );

    ADD_METHOD_TO(
        AdminController::deleteProduct,
        "/api/admin/products/{1}",
        drogon::Delete
    );

    METHOD_LIST_END

    void getAllUsers(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getAllOrders(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void deleteProduct(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long productId);
};