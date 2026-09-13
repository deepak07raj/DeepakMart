#include "HomeController.h"

void HomeController::home(
    const drogon::HttpRequestPtr&,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto db = drogon::app().getDbClient("default");

    if (!db)
    {
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k500InternalServerError);
        response->setBody("Database client is not available.");
        callback(response);
        return;
    }

    try
    {
        auto result = db->execSqlSync("SELECT 1");

        auto response = drogon::HttpResponse::newHttpResponse();
        response->setBody("DeepakMart API + PostgreSQL Connected Successfully!");
        callback(response);
    }
    catch (const std::exception& e)
    {
        auto response = drogon::HttpResponse::newHttpResponse();
        response->setStatusCode(drogon::k500InternalServerError);
        response->setBody(
            std::string("PostgreSQL Error: ") + e.what()
        );
        callback(response);
    }
}