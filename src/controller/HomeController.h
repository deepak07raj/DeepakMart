#pragma once

#include <drogon/HttpController.h>

class HomeController
    : public drogon::HttpController<HomeController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        HomeController::health,
        "/api/v1/health",
        drogon::Get
    );

    ADD_METHOD_TO(
        HomeController::health,
        "/api/health",
        drogon::Get
    );

    METHOD_LIST_END

    void health(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);
};