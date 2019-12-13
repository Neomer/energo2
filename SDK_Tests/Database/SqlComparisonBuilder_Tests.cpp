#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by vinokurov on 13.12.2019.
//

#include <Types/Uuid.h>
#include "SqlComparisonBuilder_Tests.h"

using namespace energo::types;
using namespace energo::db;

TEST_F(SqlComparisonBuilder_Tests, SimpleEquals) {
    EXPECT_EQ(SqlComparisonBuilder::Eq("a", "4"), "a=4");
}

TEST_F(SqlComparisonBuilder_Tests, SimpleGreat) {
    EXPECT_EQ(SqlComparisonBuilder::Gr("a", "4"), "a>4");
}

TEST_F(SqlComparisonBuilder_Tests, SimpleGreatEquals) {
    EXPECT_EQ(SqlComparisonBuilder::Ge("a", "4"), "a>=4");
}

TEST_F(SqlComparisonBuilder_Tests, SimpleLess) {
    EXPECT_EQ(SqlComparisonBuilder::Ls("a", "4"), "a<4");
}

TEST_F(SqlComparisonBuilder_Tests, SimpleLike) {
    EXPECT_EQ(SqlComparisonBuilder::Like("a", "%'dfvdfv'"), "a like %'dfvdfv'");
}

TEST_F(SqlComparisonBuilder_Tests, SimpleAnd) {
    EXPECT_EQ(SqlComparisonBuilder::And("a>2", "a<4"), "(a>2) AND (a<4)");
}

TEST_F(SqlComparisonBuilder_Tests, SimpleOr) {
    EXPECT_EQ(SqlComparisonBuilder::Or("a<4", "a>10"), "(a<4) OR (a>10)");
}

TEST_F(SqlComparisonBuilder_Tests, SimpleNot) {
    EXPECT_EQ(SqlComparisonBuilder::Not("a>2"), "NOT(a>2)");
}

TEST_F(SqlComparisonBuilder_Tests, SomeCollectionOfComparsion) {
    auto comp = SqlComparisonBuilder::Or(
            SqlComparisonBuilder::Not(SqlComparisonBuilder::Gr("a", "4")),
            SqlComparisonBuilder::And(
                    SqlComparisonBuilder::Ge("a", "0"),
                    SqlComparisonBuilder::Le("a", "10")));

    EXPECT_EQ(comp, "(NOT(a>4)) OR ((a>=0) AND (a<=10))");
}

#pragma clang diagnostic pop