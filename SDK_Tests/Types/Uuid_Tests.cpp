#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by vinokurov on 05.12.2019.
//

#include <random>
#include <stdexcept>
#include "Uuid_Tests.h"

using namespace std;
using namespace testing;
using namespace energo::types;

TEST_F(Uuid_Tests, UuidDefaultConstructorShouldInitializeEmptyUuid) {
    Uuid uid;
    EXPECT_EQ(uid, Uuid::Empty());
}

TEST_F(Uuid_Tests, UuidRandomMustReturnsDifferentValues) {
    random_device rd;
    EXPECT_FALSE(Uuid::Random(rd) == Uuid::Random(rd));
}

TEST_F(Uuid_Tests, UuidRandomMustNotBeEmpty) {
    random_device rd;
    EXPECT_FALSE(Uuid::Random(rd) == Uuid::Empty());
}

TEST_F(Uuid_Tests, EmptyUuidsMustBeEquals) {
    EXPECT_EQ(Uuid::Empty(), Uuid::Empty());
}

TEST_F(Uuid_Tests, ToStringTest) {
    Uuid uid(14486695158647617595u, 17669454269604863270u);
    EXPECT_EQ(uid.toString(), "c90b147e-348f-f83b-f536-830a9ace9d26");
}

TEST_F(Uuid_Tests, ToStringEmptyUuid) {
    EXPECT_EQ(Uuid::Empty().toString(), "00000000-0000-0000-0000-000000000000");
}

TEST_F(Uuid_Tests, ParseEmptyUuidString) {
    Uuid uid;
    EXPECT_TRUE(Uuid::TryParse("00000000-0000-0000-0000-000000000000", uid));
    EXPECT_EQ(Uuid::Empty(), uid);
}

TEST_F(Uuid_Tests, IsEmptyCheck) {
    Uuid uid;
    EXPECT_TRUE( uid.isEmpty());
}

TEST_F(Uuid_Tests, ParseAndToStringBackEquals) {
    Uuid uid;
    EXPECT_TRUE(Uuid::TryParse("12345678-1234-1234-1234-000000054321", uid));
    EXPECT_EQ(uid.toString(), "12345678-1234-1234-1234-000000054321");
}

TEST_F(Uuid_Tests, ParsingIncorrectStringMustThrowsInvalidArgumentException) {
    EXPECT_THROW(Uuid::Parse("00000000-0000-0000-0000-00000000000g"), invalid_argument);
    EXPECT_THROW(Uuid::Parse("00asdfa0-0000-0000-0000-00000000000g"), invalid_argument);
    EXPECT_THROW(Uuid::Parse("00000000+0000-0000-0000-000000000000"), invalid_argument);
    EXPECT_THROW(Uuid::Parse("000000000000-0000-0000-000000000000"), invalid_argument);
    EXPECT_THROW(Uuid::Parse(""), invalid_argument);
}

TEST_F(Uuid_Tests, TryParsingIncorrectStringMustReturnFalse) {
    Uuid uid;
    EXPECT_FALSE(Uuid::TryParse("00000000-0000-0000-0000-00000000000g", uid));
    EXPECT_FALSE(Uuid::TryParse("00asdfa0-0000-0000-0000-00000000000g", uid));
    EXPECT_FALSE(Uuid::TryParse("00000000+0000-0000-0000-000000000000", uid));
    EXPECT_FALSE(Uuid::TryParse("000000000000-0000-0000-000000000000", uid));
    EXPECT_FALSE(Uuid::TryParse("", uid));
}
#pragma clang diagnostic pop