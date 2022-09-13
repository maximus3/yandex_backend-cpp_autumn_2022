#include "server/server.h"
#include "database/database.h"
#include "database/test.h"

int main(int argc, char** argv)
{
    //
    Test::TestDB();
    //
    App app;

    return app.run(argc, argv);
}
