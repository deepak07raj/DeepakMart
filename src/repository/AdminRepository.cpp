#include "AdminRepository.h"

#include <iostream>

AdminRepository::AdminRepository()
{
}

Json::Value AdminRepository::getAllUsers()
{
    Json::Value result(
        Json::arrayValue
    );

    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return result;
    }

    try
    {
        auto rows = db->execSqlSync(
            "SELECT id, name, email, role, created_at "
            "FROM users "
            "ORDER BY id DESC"
        );

        for (const auto& row : rows)
        {
            Json::Value user;

            user["id"] =
                static_cast<Json::Int64>(
                    row["id"].as<long long>()
                );

            user["name"] =
                row["name"].as<std::string>();

            user["email"] =
                row["email"].as<std::string>();

            user["role"] =
                row["role"].as<std::string>();

            user["created_at"] =
                row["created_at"].as<std::string>();

            result.append(user);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ADMIN USERS DATABASE ERROR: "
            << e.what()
            << std::endl;
    }

    return result;
}

Json::Value AdminRepository::getAllOrders()
{
    Json::Value result(
        Json::arrayValue
    );

    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return result;
    }

    try
    {
        auto rows = db->execSqlSync(
            "SELECT id, buyer_id, status, "
            "total_amount_cents, created_at "
            "FROM orders "
            "ORDER BY id DESC"
        );

        for (const auto& row : rows)
        {
            Json::Value order;

            long long orderId =
                row["id"].as<long long>();

            order["order_id"] =
                static_cast<Json::Int64>(
                    orderId
                );

            order["buyer_id"] =
                static_cast<Json::Int64>(
                    row["buyer_id"].as<long long>()
                );

            order["status"] =
                row["status"].as<std::string>();

            order["total_amount_cents"] =
                static_cast<Json::Int64>(
                    row["total_amount_cents"]
                        .as<long long>()
                );

            order["created_at"] =
                row["created_at"].as<std::string>();

            Json::Value items(
                Json::arrayValue
            );

            auto itemRows = db->execSqlSync(
                "SELECT id, product_id, quantity, "
                "unit_price_cents "
                "FROM order_items "
                "WHERE order_id = $1 "
                "ORDER BY id",
                orderId
            );

            for (const auto& itemRow : itemRows)
            {
                Json::Value item;

                item["id"] =
                    static_cast<Json::Int64>(
                        itemRow["id"]
                            .as<long long>()
                    );

                item["product_id"] =
                    static_cast<Json::Int64>(
                        itemRow["product_id"]
                            .as<long long>()
                    );

                item["quantity"] =
                    itemRow["quantity"]
                        .as<int>();

                item["unit_price_cents"] =
                    static_cast<Json::Int64>(
                        itemRow["unit_price_cents"]
                            .as<long long>()
                    );

                items.append(item);
            }

            order["items"] = items;

            result.append(order);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ADMIN ORDERS DATABASE ERROR: "
            << e.what()
            << std::endl;
    }

    return result;
}

bool AdminRepository::deleteProduct(
    long long productId)
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
            "WHERE id = $1",
            productId
        );

        return result.affectedRows() > 0;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ADMIN PRODUCT DELETE DATABASE ERROR: "
            << e.what()
            << std::endl;

        return false;
    }
}