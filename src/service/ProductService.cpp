#include "ProductService.h"

ProductService::ProductService()
{
}

bool ProductService::createProduct(
    const Product& product)
{
    if (product.sellerId <= 0)
    {
        return false;
    }

    if (product.name.empty())
    {
        return false;
    }

    if (product.name.length() > 200)
    {
        return false;
    }

    if (product.category.empty())
    {
        return false;
    }

    if (product.category.length() > 100)
    {
        return false;
    }

    if (product.priceCents < 0)
    {
        return false;
    }

    if (product.stockQty < 0)
    {
        return false;
    }

    return productRepository.createProduct(
        product
    );
}

std::vector<Product>
ProductService::getAllProducts(
    const std::string& keyword,
    const std::string& category)
{
    if (keyword.length() > 100)
    {
        return {};
    }

    if (category.length() > 100)
    {
        return {};
    }

    return productRepository.getAllProducts(
        keyword,
        category
    );
}

std::optional<Product>
ProductService::getProductById(
    long long productId)
{
    if (productId <= 0)
    {
        return std::nullopt;
    }

    return productRepository.findById(
        productId
    );
}

bool ProductService::updateProduct(
    const Product& product)
{
    if (product.id <= 0)
    {
        return false;
    }

    if (product.sellerId <= 0)
    {
        return false;
    }

    if (product.name.empty())
    {
        return false;
    }

    if (product.name.length() > 200)
    {
        return false;
    }

    if (product.category.empty())
    {
        return false;
    }

    if (product.category.length() > 100)
    {
        return false;
    }

    if (product.priceCents < 0)
    {
        return false;
    }

    if (product.stockQty < 0)
    {
        return false;
    }

    return productRepository.updateProduct(
        product
    );
}

bool ProductService::deleteProduct(
    long long productId,
    long long sellerId)
{
    if (productId <= 0 ||
        sellerId <= 0)
    {
        return false;
    }

    return productRepository.deleteProduct(
        productId,
        sellerId
    );
}