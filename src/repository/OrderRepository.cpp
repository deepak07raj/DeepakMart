#include "OrderRepository.h"

#include <iostream>

OrderRepository::OrderRepository()
{
}

std::optional<long long>
OrderRepository::createOrder(
    long long buyerId,
    long long totalAmountCents)
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
            "INSERT INTO orders "
            "(buyer_id, status, total_amount_cents) "
            "VALUES ($1, 'PENDING', $2) "
            "RETURNING id",
            buyerId,
            totalAmountCents
        );

        if (result.empty())
        {
            return std::nullopt;
        }

        return result[0]["id"].as<long long>();
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ORDER DATABASE ERROR: "
            << e.what()
            << std::endl;

        return std::nullopt;
    }
}

bool OrderRepository::addOrderItem(
    long long orderId,
    long long productId,
    int quantity,
    long long unitPriceCents)
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
            "INSERT INTO order_items "
            "(order_id, product_id, quantity, unit_price_cents) "
            "VALUES ($1, $2, $3, $4)",
            orderId,
            productId,
            quantity,
            unitPriceCents
        );

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ORDER ITEM DATABASE ERROR: "
            << e.what()
            << std::endl;

        return false;
    }
}

std::vector<Order>
OrderRepository::getOrdersByBuyer(
    long long buyerId)
{
    std::vector<Order> orders;

    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return orders;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT id, buyer_id, status, "
            "total_amount_cents "
            "FROM orders "
            "WHERE buyer_id = $1 "
            "ORDER BY id DESC",
            buyerId
        );

        for (const auto& row : result)
        {
            Order order;

            order.id =
                row["id"].as<long long>();

            order.buyerId =
                row["buyer_id"].as<long long>();

            order.status =
                row["status"].as<std::string>();

            order.totalAmountCents =
                row["total_amount_cents"]
                    .as<long long>();

            orders.push_back(order);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ORDER DATABASE ERROR: "
            << e.what()
            << std::endl;
    }

    return orders;
}

std::vector<Order>
OrderRepository::getOrdersBySeller(
    long long sellerId)
{
    std::vector<Order> orders;

    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return orders;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT DISTINCT "
            "o.id, "
            "o.buyer_id, "
            "o.status, "
            "o.total_amount_cents "
            "FROM orders o "
            "JOIN order_items oi "
            "ON o.id = oi.order_id "
            "JOIN products p "
            "ON oi.product_id = p.id "
            "WHERE p.seller_id = $1 "
            "ORDER BY o.id DESC",
            sellerId
        );

        for (const auto& row : result)
        {
            Order order;

            order.id =
                row["id"].as<long long>();

            order.buyerId =
                row["buyer_id"].as<long long>();

            order.status =
                row["status"].as<std::string>();

            order.totalAmountCents =
                row["total_amount_cents"]
                    .as<long long>();

            orders.push_back(order);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "SELLER ORDER DATABASE ERROR: "
            << e.what()
            << std::endl;
    }

    return orders;
}

std::vector<OrderItem>
OrderRepository::getOrderItems(
    long long orderId)
{
    std::vector<OrderItem> items;

    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return items;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT id, order_id, product_id, "
            "quantity, unit_price_cents "
            "FROM order_items "
            "WHERE order_id = $1 "
            "ORDER BY id",
            orderId
        );

        for (const auto& row : result)
        {
            OrderItem item;

            item.id =
                row["id"].as<long long>();

            item.orderId =
                row["order_id"].as<long long>();

            item.productId =
                row["product_id"].as<long long>();

            item.quantity =
                row["quantity"].as<int>();

            item.unitPriceCents =
                row["unit_price_cents"]
                    .as<long long>();

            items.push_back(item);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ORDER ITEM DATABASE ERROR: "
            << e.what()
            << std::endl;
    }

    return items;
}

std::optional<Order>
OrderRepository::findOrderById(
    long long orderId,
    long long buyerId)
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
            "SELECT id, buyer_id, status, "
            "total_amount_cents "
            "FROM orders "
            "WHERE id = $1 "
            "AND buyer_id = $2",
            orderId,
            buyerId
        );

        if (result.empty())
        {
            return std::nullopt;
        }

        Order order;

        order.id =
            result[0]["id"].as<long long>();

        order.buyerId =
            result[0]["buyer_id"].as<long long>();

        order.status =
            result[0]["status"].as<std::string>();

        order.totalAmountCents =
            result[0]["total_amount_cents"]
                .as<long long>();

        return order;
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ORDER DATABASE ERROR: "
            << e.what()
            << std::endl;

        return std::nullopt;
    }
}

bool OrderRepository::checkout(
    long long buyerId)
{
    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return false;
    }

    try
    {
        db->execSqlSync("BEGIN");

        auto cart = db->execSqlSync(
            "SELECT ci.product_id, "
            "ci.quantity, "
            "p.price_cents, "
            "p.stock_qty "
            "FROM cart_items ci "
            "JOIN products p "
            "ON ci.product_id = p.id "
            "WHERE ci.user_id = $1",
            buyerId
        );

        if (cart.empty())
        {
            db->execSqlSync("ROLLBACK");
            return false;
        }

        long long totalAmountCents = 0;

        for (const auto& row : cart)
        {
            int quantity =
                row["quantity"].as<int>();

            int stockQty =
                row["stock_qty"].as<int>();

            long long priceCents =
                row["price_cents"].as<long long>();

            if (quantity <= 0)
            {
                db->execSqlSync("ROLLBACK");
                return false;
            }

            if (quantity > stockQty)
            {
                db->execSqlSync("ROLLBACK");
                return false;
            }

            totalAmountCents +=
                priceCents * quantity;
        }

        auto orderResult =
            db->execSqlSync(
                "INSERT INTO orders "
                "(buyer_id, status, total_amount_cents) "
                "VALUES ($1, 'CONFIRMED', $2) "
                "RETURNING id",
                buyerId,
                totalAmountCents
            );

        if (orderResult.empty())
        {
            db->execSqlSync("ROLLBACK");
            return false;
        }

        long long orderId =
            orderResult[0]["id"]
                .as<long long>();

        for (const auto& row : cart)
        {
            long long productId =
                row["product_id"]
                    .as<long long>();

            int quantity =
                row["quantity"].as<int>();

            long long priceCents =
                row["price_cents"]
                    .as<long long>();

            db->execSqlSync(
                "INSERT INTO order_items "
                "(order_id, product_id, "
                "quantity, unit_price_cents) "
                "VALUES ($1, $2, $3, $4)",
                orderId,
                productId,
                quantity,
                priceCents
            );

            auto stockResult =
                db->execSqlSync(
                    "UPDATE products "
                    "SET stock_qty = stock_qty - $1 "
                    "WHERE id = $2 "
                    "AND stock_qty >= $1",
                    quantity,
                    productId
                );

            if (stockResult.affectedRows() == 0)
            {
                db->execSqlSync("ROLLBACK");
                return false;
            }
        }

        db->execSqlSync(
            "DELETE FROM cart_items "
            "WHERE user_id = $1",
            buyerId
        );

        db->execSqlSync("COMMIT");

        return true;
    }
    catch (const std::exception& e)
    {
        try
        {
            db->execSqlSync("ROLLBACK");
        }
        catch (...)
        {
        }

        std::cerr
            << "CHECKOUT DATABASE ERROR: "
            << e.what()
            << std::endl;

        return false;
    }
}