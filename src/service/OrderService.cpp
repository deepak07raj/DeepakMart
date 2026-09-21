#include "OrderService.h"

OrderService::OrderService()
{
}

std::optional<long long>
OrderService::createOrder(
    long long buyerId,
    long long totalAmountCents)
{
    if (buyerId <= 0)
    {
        return std::nullopt;
    }

    if (totalAmountCents < 0)
    {
        return std::nullopt;
    }

    return orderRepository.createOrder(
        buyerId,
        totalAmountCents
    );
}

bool OrderService::addOrderItem(
    long long orderId,
    long long productId,
    int quantity,
    long long unitPriceCents)
{
    if (orderId <= 0)
    {
        return false;
    }

    if (productId <= 0)
    {
        return false;
    }

    if (quantity <= 0)
    {
        return false;
    }

    if (unitPriceCents < 0)
    {
        return false;
    }

    return orderRepository.addOrderItem(
        orderId,
        productId,
        quantity,
        unitPriceCents
    );
}

std::vector<Order>
OrderService::getOrdersByBuyer(
    long long buyerId)
{
    if (buyerId <= 0)
    {
        return {};
    }

    return orderRepository.getOrdersByBuyer(
        buyerId
    );
}

std::vector<Order>
OrderService::getOrdersBySeller(
    long long sellerId)
{
    if (sellerId <= 0)
    {
        return {};
    }

    return orderRepository.getOrdersBySeller(
        sellerId
    );
}

std::vector<OrderItem>
OrderService::getOrderItems(
    long long orderId)
{
    if (orderId <= 0)
    {
        return {};
    }

    return orderRepository.getOrderItems(
        orderId
    );
}

std::optional<Order>
OrderService::getOrderById(
    long long orderId,
    long long buyerId)
{
    if (orderId <= 0 ||
        buyerId <= 0)
    {
        return std::nullopt;
    }

    return orderRepository.findOrderById(
        orderId,
        buyerId
    );
}

bool OrderService::checkout(
    long long buyerId)
{
    if (buyerId <= 0)
    {
        return false;
    }

    return orderRepository.checkout(
        buyerId
    );
}