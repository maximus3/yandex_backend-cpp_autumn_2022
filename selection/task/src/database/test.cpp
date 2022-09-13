#include "test.h"
#include "database.h"

void Test::TestDB()
{
    Database db;
    db.ExecuteSQL(
            "CREATE TABLE IF NOT EXISTS system_item("
            "uid SERIAL PRIMARY KEY,"
            "id VARCHAR(255) NOT NULL UNIQUE,"
            "url VARCHAR(255),"
            "date VARCHAR(255) NOT NULL,"
            "dt_date TIMESTAMP NOT NULL,"
            "parentId VARCHAR(255) REFERENCES system_item (id),"
            "type VARCHAR(255) NOT NULL,"
            "size BIGINT"
            ");"
    );
}