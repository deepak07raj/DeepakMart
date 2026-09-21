#include "ReviewService.h"

ReviewService::ReviewService()
{
}

std::optional<long long>
ReviewService::createReview(
    long long productId,
    long long userId,
    int rating,
    const std::string& comment)
{
    if (productId <= 0)
    {
        return std::nullopt;
    }

    if (userId <= 0)
    {
        return std::nullopt;
    }

    if (rating < 1 || rating > 5)
    {
        return std::nullopt;
    }

    if (comment.length() > 2000)
    {
        return std::nullopt;
    }

    return reviewRepository.createReview(
        productId,
        userId,
        rating,
        comment
    );
}

std::vector<Review>
ReviewService::getReviewsByProduct(
    long long productId)
{
    if (productId <= 0)
    {
        return {};
    }

    return reviewRepository.getReviewsByProduct(
        productId
    );
}