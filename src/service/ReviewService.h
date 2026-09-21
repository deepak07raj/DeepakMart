#pragma once

#include "../model/Review.h"
#include "../repository/ReviewRepository.h"

#include <optional>
#include <string>
#include <vector>

class ReviewService
{
private:
    ReviewRepository reviewRepository;

public:
    ReviewService();

    std::optional<long long> createReview(
        long long productId,
        long long userId,
        int rating,
        const std::string& comment);

    std::vector<Review> getReviewsByProduct(
        long long productId);
};