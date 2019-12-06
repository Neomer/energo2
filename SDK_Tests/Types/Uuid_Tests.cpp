//
// Created by vinokurov on 05.12.2019.
//

#include <random>
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

TEST_F(Uuid_Tests, CorrectStringFormat) {
    Uuid uid(14486695158647617595u, 17669454269604863270u);
    EXPECT_EQ(uid.toString(), "c90b147e-348f-f83b-3600-830a9ace9d26");
    EXPECT_EQ(Uuid::Empty().toString(), "00000000-0000-0000-0000-000000000000");
}