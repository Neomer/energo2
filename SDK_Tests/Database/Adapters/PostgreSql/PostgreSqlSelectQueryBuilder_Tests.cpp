//
// Created by kir on 10.12.2019.
//

#include "PostgreSqlSelectQueryBuilder_Tests.h"

using namespace std;
using namespace energo::db::adapters;

TEST_F(PostgreSqlSelectQueryBuilder_Tests, SimpleSelectAllRecordsFromTable) {
    PostgreSqlSelectQueryBuilder builder(*provider, "SomeTable");
    EXPECT_EQ(builder.build(), "select * from \"SomeTable\";");
}

TEST_F(PostgreSqlSelectQueryBuilder_Tests, SelectSomeFieldsGivenByString) {
    PostgreSqlSelectQueryBuilder builder(*provider, "SomeTable");
    builder.fields("f1, f2 as ff");
    EXPECT_EQ(builder.build(), "select f1, f2 as ff  from \"SomeTable\";");
}
