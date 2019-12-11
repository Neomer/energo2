#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by kir on 10.12.2019.
//

#include "PostgreSqlSelectQueryBuilder_Tests.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;

TEST_F(PostgreSqlSelectQueryBuilder_Tests, SimpleSelectAllRecordsFromTable) {
    PostgreSqlSelectQueryBuilder builder(*provider, "SomeTable");
    EXPECT_EQ(builder.build(), "select * from \"public\".\"SomeTable\";");
}

TEST_F(PostgreSqlSelectQueryBuilder_Tests, SelectSomeFieldsGivenByString) {
    PostgreSqlSelectQueryBuilder builder(*provider, "SomeTable");
    builder.fields("f1, f2 as f_alias");
    EXPECT_EQ(builder.build(), "select f1, f2 as f_alias from \"public\".\"SomeTable\";");
}

TEST_F(PostgreSqlSelectQueryBuilder_Tests, SelectSomeFieldsGivenByVector) {
    PostgreSqlSelectQueryBuilder builder(*provider, "SomeTable");
    builder.fields({
        {"f1", nullopt },
        {"f2", "f_alias"}
    });
    EXPECT_EQ(builder.build(), "select \"f1\", \"f2\" as \"f_alias\" from \"public\".\"SomeTable\";");
}

TEST_F(PostgreSqlSelectQueryBuilder_Tests, SelectSomeFieldsGivenByVectorWithLimitAndOffset) {
    PostgreSqlSelectQueryBuilder builder(*provider, "SomeTable");
    builder
        .fields({
                               {"f1", nullopt },
                               {"f2", "f_alias"}
                       })
        .limit(15)
        .offset(5);
    EXPECT_EQ(builder.build(), "select \"f1\", \"f2\" as \"f_alias\" from \"public\".\"SomeTable\" limit 15 offset 5;");
}

TEST_F(PostgreSqlSelectQueryBuilder_Tests, WhereClauseByString) {
    PostgreSqlSelectQueryBuilder builder(*provider, "SomeTable");
    builder.where("a > 4");
    EXPECT_EQ(builder.build(), "select * from \"public\".\"SomeTable\" where a > 4;");
}

#pragma clang diagnostic pop