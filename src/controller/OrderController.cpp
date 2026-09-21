#include "OrderController.h"

void OrderController::checkout(
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

    long long buyerId =
        (*json)["buyer_id"].asInt64();

    OrderService orderService;

    if (!orderService.checkout(buyerId))
    {
        Json::Value result;

        result["error"] =
            "Checkout failed";

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
        "Checkout successful";

    result["buyer_id"] =
        static_cast<Json::Int64>(
            buyerId
        );

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            result
        );

    response->setStatusCode(
        drogon::k201Created
    );

    callback(response);
}

void OrderController::getOrdersByBuyer(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long buyerId)
{
    OrderService orderService;

    auto orders =
        orderService.getOrdersByBuyer(
            buyerId
        );

    Json::Value result(
        Json::arrayValue
    );

    for (const auto& order : orders)
    {
        Json::Value item;

        item["id"] =
            static_cast<Json::Int64>(
                order.id
            );

        item["buyer_id"] =
            static_cast<Json::Int64>(
                order.buyerId
            );

        item["status"] =
            order.status;

        item["total_amount_cents"] =
            static_cast<Json::Int64>(
                order.totalAmountCents
            );

        result.append(item);
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

void OrderController::getOrderById(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long buyerId,
    long long orderId)
{
    OrderService orderService;

    auto order =
        orderService.getOrderById(
            orderId,
            buyerId
        );

    if (!order.has_value())
    {
        Json::Value result;

        result["error"] =
            "Order not found";

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

    auto orderItems =
        orderService.getOrderItems(
            orderId
        );

    Json::Value result;

    result["id"] =
        static_cast<Json::Int64>(
            order->id
        );

    result["buyer_id"] =
        static_cast<Json::Int64>(
            order->buyerId
        );

    result["status"] =
        order->status;

    result["total_amount_cents"] =
        static_cast<Json::Int64>(
            order->totalAmountCents
        );

    Json::Value items(
        Json::arrayValue
    );

    for (const auto& item : orderItems)
    {
        Json::Value orderItem;

        orderItem["id"] =
            static_cast<Json::Int64>(
                item.id
            );

        orderItem["order_id"] =
            static_cast<Json::Int64>(
                item.orderId
            );

        orderItem["product_id"] =
            static_cast<Json::Int64>(
                item.productId
            );

        orderItem["quantity"] =
            item.quantity;

        orderItem["unit_price_cents"] =
            static_cast<Json::Int64>(
                item.unitPriceCents
            );

        items.append(orderItem);
    }

    result["items"] =
        items;

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(
            result
        );

    response->setStatusCode(
        drogon::k200OK
    );

    callback(response);
}