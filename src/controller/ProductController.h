#pragma once

#include <drogon/HttpController.h>

#include "../service/ProductService.h"

class ProductController
    : public drogon::HttpController<ProductController>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(
        ProductController::createProduct,
        "/api/products",
        drogon::Post
    );

    ADD_METHOD_TO(
        ProductController::getAllProducts,
        "/api/products",
        drogon::Get
    );

    ADD_METHOD_TO(
        ProductController::getProductById,
        "/api/products/{1}",
        drogon::Get
    );

    ADD_METHOD_TO(
        ProductController::updateProduct,
        "/api/products/{1}",
        drogon::Put
    );

    ADD_METHOD_TO(
        ProductController::deleteProduct,
        "/api/products/{1}",
        drogon::Delete
    );

    METHOD_LIST_END

    void createProduct(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getAllProducts(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback);

    void getProductById(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long productId);

    void updateProduct(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long productId);

    void deleteProduct(
        const drogon::HttpRequestPtr& req,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback,
        long long productId);
};
