#pragma once

#include "../model/Product.h"
#include "../repository/ProductRepository.h"

#include <optional>
#include <vector>
#include <string>

class ProductService
{
private:
    ProductRepository productRepository;

public:
    ProductService();

    bool createProduct(
        const Product& product);

    std::vector<Product> getAllProducts(
        const std::string& keyword = "",
        const std::string& category = "");

    std::optional<Product> getProductById(
        long long productId);

    bool updateProduct(
        const Product& product);

    bool deleteProduct(
        long long productId,
        long long sellerId);
};