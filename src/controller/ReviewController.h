#pragma once

#include <drogon/HttpController.h>

#include "../service/ReviewService.h"

class ReviewController
    : public drogon::HttpController<ReviewController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        ReviewController::createReview,
        "/api/reviews",
        drogon::Post
    );

    ADD_METHOD_TO(
        ReviewController::getReviewsByProduct,
        "/api/products/{1}/reviews",
        drogon::Get
    );

    METHOD_LIST_END

    void createReview(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getReviewsByProduct(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long productId);
};