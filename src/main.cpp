#include <drogon/drogon.h>

int main()
{
    drogon::app()
        .loadConfigFile("config.json")
        .setDocumentRoot("frontend")
        .run();

    return 0;
}