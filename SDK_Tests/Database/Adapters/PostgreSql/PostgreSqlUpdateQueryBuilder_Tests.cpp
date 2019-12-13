#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by vinokurov on 13.12.2019.
//

#include <Database/SqlConditionBuilder.h>
#include "PostgreSqlUpdateQueryBuilder_Tests.h"

using namespace std;
using namespace energo::db;
using namespace energo::types;
using namespace energo::db::adapters;


TEST_F(PostgreSqlUpdateQueryBuilder_Tests, UpdateOneNumericField) {
    PostgreSqlUpdateQueryBuilder builder(*transformationProvider, "SomeTable");
    builder.values({
                           { "a", transformationProvider->formatValue(5)}
    });
    EXPECT_EQ(builder.build(), R"(update "public"."SomeTable" set "a"=5;)");
}

TEST_F(PostgreSqlUpdateQueryBuilder_Tests, UpdateOneNumericFieldWithWhereClauseAndSchema) {
    PostgreSqlUpdateQueryBuilder builder(*transformationProvider, "SomeTable");
    builder
        .schema("other")
        .values({
            { "a", transformationProvider->formatValue(5)}
        })
        .where(
                SqlConditionBuilder::Eq(
                        transformationProvider->escapeFieldNameIfNeeded("a"),
                        transformationProvider->formatValue(4)));
    EXPECT_EQ(builder.build(), R"(update "other"."SomeTable" set "a"=5 where "a"=4;)");
}

#pragma clang diagnostic pop