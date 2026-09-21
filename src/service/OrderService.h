#pragma once

#include "../model/Order.h"
#include "../model/OrderItem.h"
#include "../repository/OrderRepository.h"

#include <optional>
#include <vector>

class OrderService
{
private:
    OrderRepository orderRepository;

public:
    OrderService();

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

    std::optional<Order> getOrderById(
        long long orderId,
        long long buyerId);

    bool checkout(
        long long buyerId);
};