#include "UserController.h"

void UserController::registerUser(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();

    if (!json)
    {
        Json::Value result;
        result["error"] = "Invalid JSON";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    User user;

    user.name = (*json)["name"].asString();
    user.email = (*json)["email"].asString();
    user.password = (*json)["password"].asString();
    user.role = "BUYER";

    UserService userService;

    if (!userService.registerUser(user))
    {
        Json::Value result;
        result["error"] = "User registration failed";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    Json::Value result;
    result["message"] = "User registered successfully";
    result["name"] = user.name;
    result["email"] = user.email;
    result["role"] = user.role;

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(result);

    response->setStatusCode(drogon::k201Created);
    callback(response);
}


void UserController::loginUser(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();

    if (!json)
    {
        Json::Value result;
        result["error"] = "Invalid JSON";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    std::string email = (*json)["email"].asString();
    std::string password = (*json)["password"].asString();

    UserService userService;

    auto user = userService.loginUser(email, password);

    if (!user.has_value())
    {
        Json::Value result;
        result["error"] = "Invalid email or password";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k401Unauthorized);
        callback(response);
        return;
    }

    Json::Value result;
    result["message"] = "Login successful";
    result["id"] = static_cast<Json::Int64>(user->id);
    result["name"] = user->name;
    result["email"] = user->email;
    result["role"] = user->role;

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(result);

    response->setStatusCode(drogon::k200OK);
    callback(response);
}