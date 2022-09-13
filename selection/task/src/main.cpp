#include "server/server.h"
#include "database/database.h"
#include "database/database_creator.h"

int main(int argc, char** argv)
{
    //
    DatabaseCreator::Create();
    //
    App app;

    return app.run(argc, argv);
}
