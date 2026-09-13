#pragma once

#include <drogon/HttpController.h>

class HomeController : public drogon::HttpController<HomeController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(HomeController::home, "/", drogon::Get);

    METHOD_LIST_END

    void home(
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};