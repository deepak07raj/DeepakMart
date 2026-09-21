#include "AdminController.h"

void AdminController::getAllUsers(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    AdminService adminService;

    Json::Value users =
        adminService.getAllUsers();

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            users
        );

    response->setStatusCode(
        drogon::k200OK
    );

    callback(response);
}

void AdminController::getAllOrders(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    AdminService adminService;

    Json::Value orders =
        adminService.getAllOrders();

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            orders
        );

    response->setStatusCode(
        drogon::k200OK
    );

    callback(response);
}

void AdminController::deleteProduct(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long productId)
{
    AdminService adminService;

    if (!adminService.deleteProduct(productId))
    {
        Json::Value result;

        result["error"] =
            "Product not found or could not be removed";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                result
            );

        response->setStatusCode(
            drogon::k404NotFound
        );

        callback(response);
        return;
    }

    Json::Value result;

    result["message"] =
        "Product removed successfully";

    result["product_id"] =
        static_cast<Json::Int64>(
            productId
        );

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            result
        );

    response->setStatusCode(
        drogon::k200OK
    );

    callback(response);
}