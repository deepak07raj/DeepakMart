#include "PasswordUtil.h"

#include <argon2.h>
#include <openssl/rand.h>

#include <stdexcept>
#include <vector>

std::string PasswordUtil::hashPassword(const std::string& password)
{
    const uint32_t timeCost = 3;
    const uint32_t memoryCost = 65536;
    const uint32_t parallelism = 2;

    const size_t saltLength = 16;
    const size_t hashLength = 32;

    unsigned char salt[saltLength];

    if (RAND_bytes(salt, saltLength) != 1)
    {
        throw std::runtime_error("Failed to generate secure password salt");
    }

    const size_t encodedLength =
        argon2_encodedlen(
            timeCost,
            memoryCost,
            parallelism,
            saltLength,
            hashLength,
            Argon2_id
        );

    std::vector<char> encoded(encodedLength);

    int result = argon2id_hash_encoded(
        timeCost,
        memoryCost,
        parallelism,
        password.data(),
        password.size(),
        salt,
        saltLength,
        hashLength,
        encoded.data(),
        encoded.size()
    );

    if (result != ARGON2_OK)
    {
        throw std::runtime_error(
            std::string("Password hashing failed: ") +
            argon2_error_message(result)
        );
    }

    return std::string(encoded.data());
}

bool PasswordUtil::verifyPassword(
    const std::string& password,
    const std::string& hash)
{
    int result = argon2id_verify(
        hash.c_str(),
        password.data(),
        password.size()
    );

    return result == ARGON2_OK;
}