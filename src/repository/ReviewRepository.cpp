#include "ReviewRepository.h"

#include <iostream>

ReviewRepository::ReviewRepository()
{
}

std::optional<long long> ReviewRepository::createReview(
    long long productId,
    long long userId,
    int rating,
    const std::string& comment)
{
    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return std::nullopt;
    }

    try
    {
        auto result = db->execSqlSync(
            "INSERT INTO reviews "
            "(product_id, user_id, rating, comment) "
            "VALUES ($1, $2, $3, $4) "
            "RETURNING id",
            productId,
            userId,
            rating,
            comment
        );

        if (result.empty())
        {
            return std::nullopt;
        }

        return result[0]["id"].as<long long>();
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "REVIEW DATABASE ERROR: "
            << e.what()
            << std::endl;

        return std::nullopt;
    }
}

std::vector<Review>
ReviewRepository::getReviewsByProduct(
    long long productId)
{
    std::vector<Review> reviews;

    auto db =
        drogon::app().getDbClient("default");

    if (!db)
    {
        return reviews;
    }

    try
    {
        auto result = db->execSqlSync(
            "SELECT id, product_id, user_id, "
            "rating, comment, created_at "
            "FROM reviews "
            "WHERE product_id = $1 "
            "ORDER BY created_at DESC",
            productId
        );

        for (const auto& row : result)
        {
            Review review;

            review.id =
                row["id"].as<long long>();

            review.productId =
                row["product_id"].as<long long>();

            review.userId =
                row["user_id"].as<long long>();

            review.rating =
                row["rating"].as<int>();

            if (row["comment"].isNull())
            {
                review.comment = "";
            }
            else
            {
                review.comment =
                    row["comment"].as<std::string>();
            }

            review.createdAt =
                row["created_at"].as<std::string>();

            reviews.push_back(review);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "REVIEW DATABASE ERROR: "
            << e.what()
            << std::endl;
    }

    return reviews;
}