#include "HomeController.h"

void HomeController::health(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value result;

    result["status"] = "UP";
    result["db"] = "DOWN";

    try
    {
        auto db =
            drogon::app().getDbClient("default");

        if (db)
        {
            db->execSqlSync("SELECT 1");
            result["db"] = "UP";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Health check DB exception: " << e.what() << std::endl;
        result["db"] = "DOWN";
    }
    catch (...)
    {
        std::cerr << "Health check DB unknown exception" << std::endl;
        result["db"] = "DOWN";
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