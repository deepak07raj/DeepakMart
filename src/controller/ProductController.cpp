#include "ProductController.h"

#include <string>

void ProductController::createProduct(
    const drogon::HttpRequestPtr& req,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
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

    if (!json->isMember("seller_id") ||
        !json->isMember("name") ||
        !json->isMember("price_cents") ||
        !json->isMember("stock_qty") ||
        !json->isMember("category"))
    {
        Json::Value result;
        result["error"] =
            "seller_id, name, price_cents, stock_qty and category are required";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    Product product;

    product.sellerId =
        (*json)["seller_id"].asInt64();

    product.name =
        (*json)["name"].asString();

    product.description =
        json->isMember("description")
            ? (*json)["description"].asString()
            : "";

    product.priceCents =
        (*json)["price_cents"].asInt64();

    product.stockQty =
        (*json)["stock_qty"].asInt();

    product.category =
        (*json)["category"].asString();

    product.imageUrl =
        json->isMember("image_url")
            ? (*json)["image_url"].asString()
            : "";

    ProductService productService;

    if (!productService.createProduct(product))
    {
        Json::Value result;
        result["error"] = "Product creation failed";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    Json::Value result;
    result["message"] = "Product created successfully";
    result["name"] = product.name;
    result["category"] = product.category;
    result["price_cents"] =
        static_cast<Json::Int64>(product.priceCents);
    result["stock_qty"] = product.stockQty;
    result["image_url"] = product.imageUrl;

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(result);

    response->setStatusCode(drogon::k201Created);
    callback(response);
}

void ProductController::getAllProducts(
    const drogon::HttpRequestPtr& req,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    std::string keyword =
        req->getParameter("keyword");

    std::string category =
        req->getParameter("category");

    ProductService productService;

    auto products =
        productService.getAllProducts(
            keyword,
            category);

    Json::Value result(
        Json::arrayValue);

    for (const auto& product : products)
    {
        Json::Value item;

        item["id"] =
            static_cast<Json::Int64>(product.id);

        item["seller_id"] =
            static_cast<Json::Int64>(product.sellerId);

        item["name"] = product.name;
        item["description"] = product.description;

        item["price_cents"] =
            static_cast<Json::Int64>(product.priceCents);

        item["stock_qty"] = product.stockQty;
        item["category"] = product.category;
        item["image_url"] = product.imageUrl;

        result.append(item);
    }

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(result);

    response->setStatusCode(drogon::k200OK);
    callback(response);
}

void ProductController::getProductById(
    const drogon::HttpRequestPtr&,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long productId)
{
    ProductService productService;

    auto product =
        productService.getProductById(productId);

    if (!product.has_value())
    {
        Json::Value result;
        result["error"] = "Product not found";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k404NotFound);
        callback(response);
        return;
    }

    Json::Value result;

    result["id"] =
        static_cast<Json::Int64>(product->id);

    result["seller_id"] =
        static_cast<Json::Int64>(product->sellerId);

    result["name"] = product->name;
    result["description"] = product->description;

    result["price_cents"] =
        static_cast<Json::Int64>(product->priceCents);

    result["stock_qty"] = product->stockQty;
    result["category"] = product->category;
    result["image_url"] = product->imageUrl;

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(result);

    response->setStatusCode(drogon::k200OK);
    callback(response);
}

void ProductController::updateProduct(
    const drogon::HttpRequestPtr& req,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long productId)
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

    if (!json->isMember("seller_id") ||
        !json->isMember("name") ||
        !json->isMember("price_cents") ||
        !json->isMember("stock_qty") ||
        !json->isMember("category"))
    {
        Json::Value result;
        result["error"] =
            "seller_id, name, price_cents, stock_qty and category are required";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    Product product;

    product.id = productId;

    product.sellerId =
        (*json)["seller_id"].asInt64();

    product.name =
        (*json)["name"].asString();

    product.description =
        json->isMember("description")
            ? (*json)["description"].asString()
            : "";

    product.priceCents =
        (*json)["price_cents"].asInt64();

    product.stockQty =
        (*json)["stock_qty"].asInt();

    product.category =
        (*json)["category"].asString();

    product.imageUrl =
        json->isMember("image_url")
            ? (*json)["image_url"].asString()
            : "";

    ProductService productService;

    if (!productService.updateProduct(product))
    {
        Json::Value result;
        result["error"] = "Product update failed";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    Json::Value result;
    result["message"] = "Product updated successfully";

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(result);

    response->setStatusCode(drogon::k200OK);
    callback(response);
}

void ProductController::deleteProduct(
    const drogon::HttpRequestPtr& req,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback,
    long long productId)
{
    const std::string sellerParameter =
        req->getParameter("seller_id");

    if (sellerParameter.empty())
    {
        Json::Value result;
        result["error"] =
            "seller_id query parameter is required";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    long long sellerId = 0;

    try
    {
        sellerId = std::stoll(sellerParameter);
    }
    catch (...)
    {
        Json::Value result;
        result["error"] = "Invalid seller_id";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    ProductService productService;

    if (!productService.deleteProduct(productId, sellerId))
    {
        Json::Value result;
        result["error"] =
            "Product not found or seller does not own this listing";

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(result);

        response->setStatusCode(drogon::k404NotFound);
        callback(response);
        return;
    }

    Json::Value result;
    result["message"] = "Product deleted successfully";
    result["product_id"] =
        static_cast<Json::Int64>(productId);

    auto response =
        drogon::HttpResponse::newHttpJsonResponse(result);

    response->setStatusCode(drogon::k200OK);
    callback(response);
}
