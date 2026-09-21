#include "CartRepository.h"

#include <iostream>

CartRepository::CartRepository()
{
}

bool CartRepository::addItem(
    long long userId,
    long long productId,
    int quantity)
{
    auto db = drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        db->execSqlSync(
            "INSERT INTO cart_items "
            "(user_id, product_id, quantity) "
            "VALUES ($1, $2, $3) "
            "ON CONFLICT (user_id, product_id) "
            "DO UPDATE SET quantity = "
            "cart_items.quantity + EXCLUDED.quantity",
            userId,
            productId,
            quantity
        );

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "CART DATABASE ERROR: "
                  << e.what()
                  << std::endl;

        return false;
    }
}

std::vector<CartItem> CartRepository::getCart(
    long long userId)
{
    std::vector<CartItem> items;

    auto db = drogon::app().getDbClient("default");

    if (!db)
    {
        return items;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT id, user_id, product_id, quantity "
            "FROM cart_items "
            "WHERE user_id = $1 "
            "ORDER BY id",
            userId
        );

        for (const auto& row : result)
        {
            CartItem item;

            item.id =
                row["id"].as<long long>();

            item.userId =
                row["user_id"].as<long long>();

            item.productId =
                row["product_id"].as<long long>();

            item.quantity =
                row["quantity"].as<int>();

            items.push_back(item);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "CART DATABASE ERROR: "
                  << e.what()
                  << std::endl;
    }

    return items;
}

bool CartRepository::updateQuantity(
    long long userId,
    long long productId,
    int quantity)
{
    auto db = drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        auto result = db->execSqlSync(
            "UPDATE cart_items "
            "SET quantity = $1 "
            "WHERE user_id = $2 "
            "AND product_id = $3",
            quantity,
            userId,
            productId
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "CART DATABASE ERROR: "
                  << e.what()
                  << std::endl;

        return false;
    }
}

bool CartRepository::removeItem(
    long long userId,
    long long productId)
{
    auto db = drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        auto result = db->execSqlSync(
            "DELETE FROM cart_items "
            "WHERE user_id = $1 "
            "AND product_id = $2",
            userId,
            productId
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "CART DATABASE ERROR: "
                  << e.what()
                  << std::endl;

        return false;
    }
}