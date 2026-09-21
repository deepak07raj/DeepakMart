#pragma once

#include "../model/Review.h"

#include <drogon/drogon.h>

#include <vector>
#include <optional>

class ReviewRepository
{
public:
    ReviewRepository();

    std::optional<long long> createReview(
        long long productId,
        long long userId,
        int rating,
        const std::string& comment);

    std::vector<Review> getReviewsByProduct(
        long long productId);
};