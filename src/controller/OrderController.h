#pragma once

#include <drogon/HttpController.h>

#include "../service/OrderService.h"

class OrderController
    : public drogon::HttpController<OrderController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        OrderController::checkout,
        "/api/checkout",
        drogon::Post
    );

    ADD_METHOD_TO(
        OrderController::getOrdersByBuyer,
        "/api/orders/{1}",
        drogon::Get
    );

    ADD_METHOD_TO(
        OrderController::getOrderById,
        "/api/orders/{1}/{2}",
        drogon::Get
    );

    ADD_METHOD_TO(
        OrderController::getOrdersBySeller,
        "/api/seller/orders/{1}",
        drogon::Get
    );

    METHOD_LIST_END

    void checkout(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getOrdersByBuyer(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long buyerId);

    void getOrderById(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long buyerId,
        long long orderId);

    void getOrdersBySeller(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long sellerId);
};