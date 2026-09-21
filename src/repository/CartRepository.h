#pragma once

#include "../model/CartItem.h"

#include <drogon/drogon.h>
#include <vector>
#include <optional>

class CartRepository
{
public:
    CartRepository();

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