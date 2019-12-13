#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by vinokurov on 13.12.2019.
//

#include "PostgreSqlInsertQueryBuilder_Tests.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;

TEST_F(PostgreSqlInsertQueryBuilder_Tests, EmptySql) {
    PostgreSqlInsertQueryBuilder builder(*transformationProvider, "SomeTable");
    EXPECT_EQ(builder.build(), R"(insert into "public"."SomeTable" values ();)");
}

TEST_F(PostgreSqlInsertQueryBuilder_Tests, ValuesWithoutFields) {
    PostgreSqlInsertQueryBuilder builder(*transformationProvider, "SomeTable");
    builder.values({
        transformationProvider->formatValue(4),
        transformationProvider->formatValue(4.3),
        transformationProvider->formatValue("fgg"),
    });
    EXPECT_EQ(builder.build(), R"(insert into "public"."SomeTable" values (4, 4.3, 'fgg');)");
}

TEST_F(PostgreSqlInsertQueryBuilder_Tests, ValuesWithFields) {
    PostgreSqlInsertQueryBuilder builder(*transformationProvider, "SomeTable");
    builder.fields({"a", "b", "c"});
    builder.values({
           transformationProvider->formatValue(4),
           transformationProvider->formatValue(4.3),
           transformationProvider->formatValue("fgg"),
    });
    EXPECT_EQ(builder.build(), R"(insert into "public"."SomeTable" ("a", "b", "c") values (4, 4.3, 'fgg');)");
}

TEST_F(PostgreSqlInsertQueryBuilder_Tests, WithReturnsIdAndSchema) {
    PostgreSqlInsertQueryBuilder builder(*transformationProvider, "SomeTable");
    builder.fields({"a", "b", "c"})
           .values({
                   transformationProvider->formatValue(4),
                   transformationProvider->formatValue(4.3),
                   transformationProvider->formatValue("fgg"),
           })
           .schema("other")
           .returns({ "Id" });
    EXPECT_EQ(builder.build(), R"(insert into "other"."SomeTable" ("a", "b", "c") values (4, 4.3, 'fgg') returns "Id";)");
}


#pragma clang diagnostic pop