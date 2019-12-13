#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
    //
// Created by vinokurov on 13.12.2019.
//

#include "PostgreSqlDeleteQueryBuilder_Tests.h"

using namespace std;
using namespace energo::db;
using namespace energo::types;
using namespace energo::db::adapters;

TEST_F(PostgreSqlDeleteQueryBuilder_Tests, DeleteAll) {
    PostgreSqlDeleteQueryBuilder builder(*transformationProvider, "SomeTable");
    EXPECT_EQ(builder.build(), R"(delete from "public"."SomeTable";)");
}

TEST_F(PostgreSqlDeleteQueryBuilder_Tests, DeleteWithLimit) {
    PostgreSqlDeleteQueryBuilder builder(*transformationProvider, "SomeTable");
    builder.limit(5);
    EXPECT_EQ(builder.build(), R"(delete from "public"."SomeTable" limit 5;)");
}

TEST_F(PostgreSqlDeleteQueryBuilder_Tests, DeleteWithConditionAndSchema) {
    PostgreSqlDeleteQueryBuilder builder(*transformationProvider, "SomeTable");
    builder
        .schema("other")
        .where(
            SqlConditionBuilder::Ge(transformationProvider->escapeFieldNameIfNeeded("a"), transformationProvider->formatValue(5))
        );
    EXPECT_EQ(builder.build(), R"(delete from "other"."SomeTable" where "a">=5;)");
}
#pragma clang diagnostic pop