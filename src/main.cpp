#include <drogon/drogon.h>

#include <cstdlib>
#include <iostream>
#include <string>

std::string getEnv(
    const char* name,
    const std::string& defaultValue = "")
{
    const char* value = std::getenv(name);

    if (value == nullptr)
    {
        return defaultValue;
    }

    return std::string(value);
}

int main()
{
    const std::string dbHost =
        getEnv("DB_HOST");

    const std::string dbPortString =
        getEnv("DB_PORT", "5432");

    const std::string dbName =
        getEnv("DB_NAME");

    const std::string dbUser =
        getEnv("DB_USER");

    const std::string dbPassword =
        getEnv("DB_PASSWORD");

    const std::string portString =
        getEnv("PORT", "10000");

    if (dbHost.empty() ||
        dbName.empty() ||
        dbUser.empty() ||
        dbPassword.empty())
    {
        std::cerr
            << "ERROR: Database environment variables are missing."
            << std::endl;

        return 1;
    }

    unsigned short dbPort =
        static_cast<unsigned short>(
            std::stoi(dbPortString));

    unsigned short serverPort =
        static_cast<unsigned short>(
            std::stoi(portString));

    drogon::orm::PostgresConfig dbConfig;

    dbConfig.host = dbHost;
    dbConfig.port = dbPort;
    dbConfig.databaseName = dbName;
    dbConfig.username = dbUser;
    dbConfig.password = dbPassword;
    dbConfig.connectionNumber = 2;
    dbConfig.name = "default";
    dbConfig.isFast = false;
    dbConfig.timeout = 10.0;


    drogon::app()
        .addDbClient(dbConfig)
        .addListener(
            "0.0.0.0",
            serverPort)
        .setDocumentRoot("frontend")
        .run();

    return 0;
}