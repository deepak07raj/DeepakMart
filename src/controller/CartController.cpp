#include "CartController.h"

void CartController::addItem(
    const drogon::HttpRequestPtr& req,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();

    if (!json)
    {
        Json::Value result;

        result["error"] =
            "Invalid JSON";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                result
            );

        response->setStatusCode(
            drogon::k400BadRequest
        );

        callback(response);
        return;
    }

    if (!json->isMember("user_id") ||
        !json->isMember("product_id") ||
        !json->isMember("quantity"))
    {
        Json::Value result;

        result["error"] =
            "user_id, product_id and quantity are required";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                result
            );

        response->setStatusCode(
            drogon::k400BadRequest
        );

        callback(response);
        return;
    }

    long long userId =
        (*json)["user_id"].asInt64();

    long long productId =
        (*json)["product_id"].asInt64();

    int quantity =
        (*json)["quantity"].asInt();

    CartService cartService;

    if (!cartService.addItem(
            userId,
            productId,
            quantity))
    {
        Json::Value result;

        result["error"] =
            "Failed to add item to cart";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                result
            );

        response->setStatusCode(
            drogon::k400BadRequest
        );

        callback(response);
        return;
    }

    Json::Value result;

    result["message"] =
        "Item added to cart successfully";

    result["user_id"] =
        static_cast<Json::Int64>(
            userId
        );

    result["product_id"] =
        static_cast<Json::Int64>(
            productId
        );

    result["quantity"] =
        quantity;

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            result
        );

    response->setStatusCode(
        drogon::k201Created
    );

    callback(response);
}

void CartController::getCart(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long userId)
{
    CartService cartService;

    auto items =
        cartService.getCart(
            userId
        );

    Json::Value result(
        Json::arrayValue
    );

    for (const auto& item : items)
    {
        Json::Value cartItem;

        cartItem["id"] =
            static_cast<Json::Int64>(
                item.id
            );

        cartItem["user_id"] =
            static_cast<Json::Int64>(
                item.userId
            );

        cartItem["product_id"] =
            static_cast<Json::Int64>(
                item.productId
            );

        cartItem["quantity"] =
            item.quantity;

        result.append(cartItem);
    }

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            result
        );

    response->setStatusCode(
        drogon::k200OK
    );

    callback(response);
}

void CartController::updateQuantity(
    const drogon::HttpRequestPtr& req,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long userId,
    long long productId)
{
    auto json = req->getJsonObject();

    if (!json)
    {
        Json::Value result;

        result["error"] =
            "Invalid JSON";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                result
            );

        response->setStatusCode(
            drogon::k400BadRequest
        );

        callback(response);
        return;
    }

    if (!json->isMember("quantity"))
    {
        Json::Value result;

        result["error"] =
            "quantity is required";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                result
            );

        response->setStatusCode(
            drogon::k400BadRequest
        );

        callback(response);
        return;
    }

    int quantity =
        (*json)["quantity"].asInt();

    CartService cartService;

    if (!cartService.updateQuantity(
            userId,
            productId,
            quantity))
    {
        Json::Value result;

        result["error"] =
            "Failed to update cart quantity";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                result
            );

        response->setStatusCode(
            drogon::k400BadRequest
        );

        callback(response);
        return;
    }

    Json::Value result;

    result["message"] =
        "Cart quantity updated successfully";

    result["user_id"] =
        static_cast<Json::Int64>(
            userId
        );

    result["product_id"] =
        static_cast<Json::Int64>(
            productId
        );

    result["quantity"] =
        quantity;

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            result
        );

    response->setStatusCode(
        drogon::k200OK
    );

    callback(response);
}

void CartController::removeItem(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long userId,
    long long productId)
{
    CartService cartService;

    if (!cartService.removeItem(
            userId,
            productId))
    {
        Json::Value result;

        result["error"] =
            "Failed to remove item from cart";

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
        "Item removed from cart successfully";

    result["user_id"] =
        static_cast<Json::Int64>(
            userId
        );

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