#include "CartService.h"

CartService::CartService()
{
}

bool CartService::addItem(
    long long userId,
    long long productId,
    int quantity)
{
    if (userId <= 0)
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

    return cartRepository.addItem(
        userId,
        productId,
        quantity
    );
}

std::vector<CartItem> CartService::getCart(
    long long userId)
{
    if (userId <= 0)
    {
        return {};
    }

    return cartRepository.getCart(userId);
}

bool CartService::updateQuantity(
    long long userId,
    long long productId,
    int quantity)
{
    if (userId <= 0)
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

    return cartRepository.updateQuantity(
        userId,
        productId,
        quantity
    );
}

bool CartService::removeItem(
    long long userId,
    long long productId)
{
    if (userId <= 0)
    {
        return false;
    }

    if (productId <= 0)
    {
        return false;
    }

    return cartRepository.removeItem(
        userId,
        productId
    );
}