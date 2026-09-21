#pragma once

#include <drogon/HttpController.h>

#include "../service/CartService.h"

class CartController
    : public drogon::HttpController<CartController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        CartController::addItem,
        "/api/cart",
        drogon::Post
    );

    ADD_METHOD_TO(
        CartController::getCart,
        "/api/cart/{1}",
        drogon::Get
    );

    ADD_METHOD_TO(
        CartController::updateQuantity,
        "/api/cart/{1}/{2}",
        drogon::Put
    );

    ADD_METHOD_TO(
        CartController::removeItem,
        "/api/cart/{1}/{2}",
        drogon::Delete
    );

    METHOD_LIST_END

    void addItem(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getCart(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long userId);

    void updateQuantity(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long userId,
        long long productId);

    void removeItem(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long userId,
        long long productId);
};