#pragma once

#include <string>

struct Product
{
    long long id;
    long long sellerId;

    std::string name;
    std::string description;

    long long priceCents;
    int stockQty;

    std::string category;
    std::string imageUrl;
};