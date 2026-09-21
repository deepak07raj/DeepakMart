#include "ReviewController.h"

void ReviewController::createReview(
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

    if (!json->isMember("product_id") ||
        !json->isMember("user_id") ||
        !json->isMember("rating"))
    {
        Json::Value result;

        result["error"] =
            "product_id, user_id and rating are required";

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

    long long productId =
        (*json)["product_id"].asInt64();

    long long userId =
        (*json)["user_id"].asInt64();

    int rating =
        (*json)["rating"].asInt();

    std::string comment;

    if (json->isMember("comment") &&
        !(*json)["comment"].isNull())
    {
        comment =
            (*json)["comment"].asString();
    }

    ReviewService reviewService;

    auto reviewId =
        reviewService.createReview(
            productId,
            userId,
            rating,
            comment
        );

    if (!reviewId.has_value())
    {
        Json::Value result;

        result["error"] =
            "Failed to create review";

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
        "Review created successfully";

    result["review_id"] =
        static_cast<Json::Int64>(
            reviewId.value()
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

void ReviewController::getReviewsByProduct(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long productId)
{
    ReviewService reviewService;

    auto reviews =
        reviewService.getReviewsByProduct(
            productId
        );

    Json::Value result(
        Json::arrayValue
    );

    for (const auto& review : reviews)
    {
        Json::Value item;

        item["id"] =
            static_cast<Json::Int64>(
                review.id
            );

        item["product_id"] =
            static_cast<Json::Int64>(
                review.productId
            );

        item["user_id"] =
            static_cast<Json::Int64>(
                review.userId
            );

        item["rating"] =
            review.rating;

        item["comment"] =
            review.comment;

        item["created_at"] =
            review.createdAt;

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