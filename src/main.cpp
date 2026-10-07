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
    // ---------------------------------------------------------
    // Read environment variables
    // ---------------------------------------------------------

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

    // ---------------------------------------------------------
    // Validate required database settings
    // ---------------------------------------------------------

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

    // ---------------------------------------------------------
    // Convert ports
    // ---------------------------------------------------------

    const unsigned short dbPort =
        static_cast<unsigned short>(
            std::stoi(dbPortString));

    const unsigned short serverPort =
        static_cast<unsigned short>(
            std::stoi(portString));

    // ---------------------------------------------------------
    // Build Drogon configuration dynamically
    // ---------------------------------------------------------

    Json::Value config;

    // ---------------------------------------------------------
    // PostgreSQL / Neon configuration
    // ---------------------------------------------------------

    Json::Value dbClient;

    dbClient["name"] = "default";
    dbClient["rdbms"] = "postgresql";

    dbClient["host"] = dbHost;
    dbClient["port"] = dbPort;
    dbClient["dbname"] = dbName;

    dbClient["user"] = dbUser;
    dbClient["passwd"] = dbPassword;

    dbClient["is_fast"] = false;
    dbClient["number_of_connections"] = 2;
    dbClient["timeout"] = 10.0;
    dbClient["auto_batch"] = false;

    // Neon PostgreSQL requires SSL.
    dbClient["connect_options"]["sslmode"] = "require";

    config["db_clients"].append(dbClient);

    // ---------------------------------------------------------
    // Render HTTP listener
    // ---------------------------------------------------------

    Json::Value listener;

    listener["address"] = "0.0.0.0";
    listener["port"] = serverPort;
    listener["https"] = false;

    config["listeners"].append(listener);

    // ---------------------------------------------------------
    // Frontend configuration
    // ---------------------------------------------------------

    config["app"]["document_root"] = "frontend";
    config["app"]["home_page"] = "index.html";

    // ---------------------------------------------------------
    // Start Drogon
    // ---------------------------------------------------------

    try
    {
        drogon::app()
            .loadConfigJson(config)
            .run();
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "ERROR: Failed to start DeepakMart."
            << std::endl
            << e.what()
            << std::endl;

        return 1;
    }

    return 0;
}