#include "ProductRepository.h"

#include <iostream>

ProductRepository::ProductRepository()
{
}

bool ProductRepository::createProduct(
    const Product& product)
{
    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        db->execSqlSync(
            "INSERT INTO products "
            "(seller_id, name, description, price_cents, "
            "stock_qty, category, image_url) "
            "VALUES ($1, $2, $3, $4, $5, $6, $7)",
            product.sellerId,
            product.name,
            product.description,
            product.priceCents,
            product.stockQty,
            product.category,
            product.imageUrl
        );

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "PRODUCT DATABASE ERROR: "
            << e.what()
            << std::endl;

        return false;
    }
}

std::vector<Product>
ProductRepository::getAllProducts(
    const std::string& keyword,
    const std::string& category)
{
    std::vector<Product> products;

    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return products;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT id, seller_id, name, description, "
            "price_cents, stock_qty, category, image_url "
            "FROM products "
            "WHERE "
            "($1 = '' OR "
            "LOWER(name) LIKE LOWER('%' || $1 || '%') "
            "OR LOWER(description) LIKE LOWER('%' || $1 || '%')) "
            "AND "
            "($2 = '' OR LOWER(category) = LOWER($2)) "
            "ORDER BY id DESC",
            keyword,
            category
        );

        for (const auto& row : result)
        {
            Product product;

            product.id =
                row["id"].as<long long>();

            product.sellerId =
                row["seller_id"].as<long long>();

            product.name =
                row["name"].as<std::string>();

            product.description =
                row["description"].isNull()
                    ? ""
                    : row["description"].as<std::string>();

            product.priceCents =
                row["price_cents"].as<long long>();

            product.stockQty =
                row["stock_qty"].as<int>();

            product.category =
                row["category"].as<std::string>();

            product.imageUrl =
                row["image_url"].isNull()
                    ? ""
                    : row["image_url"].as<std::string>();

            products.push_back(product);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "PRODUCT DATABASE ERROR: "
            << e.what()
            << std::endl;
    }

    return products;
}

std::optional<Product>
ProductRepository::findById(
    long long productId)
{
    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return std::nullopt;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT id, seller_id, name, description, "
            "price_cents, stock_qty, category, image_url "
            "FROM products "
            "WHERE id = $1",
            productId
        );

        if (result.empty())
        {
            return std::nullopt;
        }

        Product product;

        product.id =
            result[0]["id"].as<long long>();

        product.sellerId =
            result[0]["seller_id"].as<long long>();

        product.name =
            result[0]["name"].as<std::string>();

        product.description =
            result[0]["description"].isNull()
                ? ""
                : result[0]["description"].as<std::string>();

        product.priceCents =
            result[0]["price_cents"].as<long long>();

        product.stockQty =
            result[0]["stock_qty"].as<int>();

        product.category =
            result[0]["category"].as<std::string>();

        product.imageUrl =
            result[0]["image_url"].isNull()
                ? ""
                : result[0]["image_url"].as<std::string>();

        return product;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "PRODUCT DATABASE ERROR: "
            << e.what()
            << std::endl;

        return std::nullopt;
    }
}

bool ProductRepository::updateProduct(
    const Product& product)
{
    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        auto result = db->execSqlSync(
            "UPDATE products "
            "SET name = $1, "
            "description = $2, "
            "price_cents = $3, "
            "stock_qty = $4, "
            "category = $5, "
            "image_url = $6 "
            "WHERE id = $7 "
            "AND seller_id = $8",
            product.name,
            product.description,
            product.priceCents,
            product.stockQty,
            product.category,
            product.imageUrl,
            product.id,
            product.sellerId
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "PRODUCT DATABASE ERROR: "
            << e.what()
            << std::endl;

        return false;
    }
}

bool ProductRepository::deleteProduct(
    long long productId,
    long long sellerId)
{
    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        auto result = db->execSqlSync(
            "DELETE FROM products "
            "WHERE id = $1 "
            "AND seller_id = $2",
            productId,
            sellerId
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "PRODUCT DATABASE ERROR: "
            << e.what()
            << std::endl;

        return false;
    }
}