#pragma once

#include "../model/Product.h"

#include <drogon/drogon.h>

#include <vector>
#include <optional>
#include <string>

class ProductRepository
{
public:
    ProductRepository();

    bool createProduct(
        const Product& product);

    std::vector<Product> getAllProducts(
        const std::string& keyword = "",
        const std::string& category = "");

    std::optional<Product> findById(
        long long productId);

    bool updateProduct(
        const Product& product);

    bool deleteProduct(
        long long productId,
        long long sellerId);
};