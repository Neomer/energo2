//
// Created by kir on 08.12.2019.
//

#include <stdexcept>
#include "SqlValue_Tests.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
using namespace std;
using namespace energo::db;
using namespace energo::types;

TEST_F(SqlValue_Tests, IntegerValue) {
    SqlValue value("12");
    EXPECT_EQ(value.asInt8(), 12);
    EXPECT_EQ(value.asInt16(), 12);
    EXPECT_EQ(value.asInt32(), 12);
    EXPECT_EQ(value.asUInt8(), 12);
    EXPECT_EQ(value.asUInt16(), 12);
    EXPECT_EQ(value.asUInt32(), 12);

#ifdef ENVIRONMENT64
    EXPECT_EQ(value.asInt64(), 12);
    EXPECT_EQ(value.asUInt16(), 12);
#endif
    
    EXPECT_EQ(value.asFloat(), 12.0f);
    EXPECT_EQ(value.asDouble(), 12.0);
    auto s = value.asString();
    EXPECT_EQ(s, "12");
    EXPECT_THROW(value.asUuid(), invalid_argument);
    EXPECT_FALSE(value.asBool());
}

TEST_F(SqlValue_Tests, DoubleValue) {
    SqlValue value("12.5");
    EXPECT_THROW(value.asInt8(), invalid_argument);
    EXPECT_THROW(value.asInt16(), invalid_argument);
    EXPECT_THROW(value.asInt32(), invalid_argument);
    EXPECT_THROW(value.asUInt8(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
    EXPECT_THROW(value.asUInt32(), invalid_argument);

#ifdef ENVIRONMENT64
    EXPECT_THROW(value.asInt64(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
#endif
    
    EXPECT_EQ(value.asFloat(), 12.5f);
    EXPECT_EQ(value.asDouble(), 12.5);
    auto s = value.asString();
    EXPECT_EQ(s, "12.5");
    EXPECT_THROW(value.asUuid(), invalid_argument);
    EXPECT_FALSE(value.asBool());
}


TEST_F(SqlValue_Tests, StringTrue) {
    SqlValue value("trUe");
    EXPECT_THROW(value.asInt8(), invalid_argument);
    EXPECT_THROW(value.asInt16(), invalid_argument);
    EXPECT_THROW(value.asInt32(), invalid_argument);
    EXPECT_THROW(value.asUInt8(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
    EXPECT_THROW(value.asUInt32(), invalid_argument);

#ifdef ENVIRONMENT64
    EXPECT_THROW(value.asInt64(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
#endif
    
    EXPECT_THROW(value.asFloat(), invalid_argument);
    EXPECT_THROW(value.asDouble(), invalid_argument);
    auto s = value.asString();
    EXPECT_EQ(s, "trUe");
    EXPECT_THROW(value.asUuid(), invalid_argument);
    EXPECT_TRUE(value.asBool());
}

TEST_F(SqlValue_Tests, ShortStringTrue) {
    SqlValue value("t");
    EXPECT_THROW(value.asInt8(), invalid_argument);
    EXPECT_THROW(value.asInt16(), invalid_argument);
    EXPECT_THROW(value.asInt32(), invalid_argument);
    EXPECT_THROW(value.asUInt8(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
    EXPECT_THROW(value.asUInt32(), invalid_argument);

#ifdef ENVIRONMENT64
    EXPECT_THROW(value.asInt64(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
#endif
    
    EXPECT_THROW(value.asFloat(), invalid_argument);
    EXPECT_THROW(value.asDouble(), invalid_argument);
    auto s = value.asString();
    EXPECT_EQ(s, "t");
    EXPECT_THROW(value.asUuid(), invalid_argument);
    EXPECT_TRUE(value.asBool());
}

TEST_F(SqlValue_Tests, NumberOneMustBeTrue) {
    SqlValue value("1");
    EXPECT_TRUE(value.asBool());
}


TEST_F(SqlValue_Tests, UuidString) {
    random_device rd;
    auto uid = Uuid::Random(rd);
    SqlValue value(uid.toString().c_str());
    EXPECT_THROW(value.asInt8(), invalid_argument);
    EXPECT_THROW(value.asInt16(), invalid_argument);
    EXPECT_THROW(value.asInt32(), invalid_argument);
    EXPECT_THROW(value.asUInt8(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
    EXPECT_THROW(value.asUInt32(), invalid_argument);

#ifdef ENVIRONMENT64
    EXPECT_THROW(value.asInt64(), invalid_argument);
    EXPECT_THROW(value.asUInt16(), invalid_argument);
#endif
    
    EXPECT_THROW(value.asFloat(), invalid_argument);
    EXPECT_THROW(value.asDouble(), invalid_argument);
    auto s = value.asString();
    EXPECT_EQ(s, uid.toString());
    EXPECT_EQ(value.asUuid(), uid);
    EXPECT_FALSE(value.asBool());
}


#pragma clang diagnostic pop