#pragma once

#include "../model/Order.h"
#include "../model/OrderItem.h"

#include <drogon/drogon.h>

#include <vector>
#include <optional>

class OrderRepository
{
public:
    OrderRepository();

    std::optional<long long> createOrder(
        long long buyerId,
        long long totalAmountCents);

    bool addOrderItem(
        long long orderId,
        long long productId,
        int quantity,
        long long unitPriceCents);

    std::vector<Order> getOrdersByBuyer(
        long long buyerId);

    std::vector<Order> getOrdersBySeller(
        long long sellerId);

    std::vector<OrderItem> getOrderItems(
        long long orderId);

    std::optional<Order> findOrderById(
        long long orderId,
        long long buyerId);

    bool checkout(
        long long buyerId);
};