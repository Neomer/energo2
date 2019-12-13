#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by kir on 10.12.2019.
//

#include <fmt/format.h>
#include <os.h>
#include "PostgreSqlTransformationProvider_Tests.h"

using namespace std;
using namespace energo::types;
using namespace energo::db::adapters;

TEST_F(PostgreSqlTransformationProvider_Tests, TableNameMustBeQuoted) {
    EXPECT_EQ(provider->escapeTableNameIfNeeded("SomeName"), "\"SomeName\"");
}


TEST_F(PostgreSqlTransformationProvider_Tests, FieldNameMustBeQuoted) {
    EXPECT_EQ(provider->escapeTableNameIfNeeded("SomeName"), "\"SomeName\"");
}

TEST_F(PostgreSqlTransformationProvider_Tests, ZeroValueSholdBeAsIs) {
    EXPECT_EQ(provider->formatValue(static_cast<uint8_t>(0)), "0");
    EXPECT_EQ(provider->formatValue(static_cast<uint16_t>(0)), "0");
    EXPECT_EQ(provider->formatValue(static_cast<uint32_t>(0)), "0");
    EXPECT_EQ(provider->formatValue(static_cast<int8_t>(0)), "0");
    EXPECT_EQ(provider->formatValue(static_cast<int16_t>(0)), "0");
    EXPECT_EQ(provider->formatValue(static_cast<int32_t>(0)), "0");
#ifdef ENVIRONMENT64
    EXPECT_EQ(provider->formatValue(static_cast<uint64_t>(0)), "0");
    EXPECT_EQ(provider->formatValue(static_cast<int64_t>(0)), "0");
#endif
    EXPECT_EQ(provider->formatValue(static_cast<double>(0)), "0.0");
    EXPECT_EQ(provider->formatValue(static_cast<float>(0)), "0.0");
}

TEST_F(PostgreSqlTransformationProvider_Tests, UuidMustBeSingleQuoted) {
    auto uid = Uuid::Random(rd);
    EXPECT_EQ(provider->formatValue(uid), fmt::format("'{0}'", uid.toString()));
}

TEST_F(PostgreSqlTransformationProvider_Tests, StringMustBeSingleQuoted) {
    EXPECT_EQ(provider->formatValue("dfvdfsvdfdfsv"), "'dfvdfsvdfdfsv'");
}

TEST_F(PostgreSqlTransformationProvider_Tests, RealValuesMustBeDottedWithoutQuotes) {
    EXPECT_EQ(provider->formatValue(1.251f), "1.251");
    EXPECT_EQ(provider->formatValue(1.251), "1.251");
}

TEST_F(PostgreSqlTransformationProvider_Tests, HighPressisionRealValuesMustBeDottedWithoutQuotes) {
    EXPECT_EQ(provider->formatValue(1.25112312333213231232f), "1.2511231");
    EXPECT_EQ(provider->formatValue(1.25112312333213231232f), "1.2511231");
}


#pragma clang diagnostic pop