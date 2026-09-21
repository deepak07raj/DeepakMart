#pragma once

#include "../model/CartItem.h"
#include "../repository/CartRepository.h"

#include <vector>

class CartService
{
private:
    CartRepository cartRepository;

public:
    CartService();

    bool addItem(
        long long userId,
        long long productId,
        int quantity);

    std::vector<CartItem> getCart(
        long long userId);

    bool updateQuantity(
        long long userId,
        long long productId,
        int quantity);

    bool removeItem(
        long long userId,
        long long productId);
};