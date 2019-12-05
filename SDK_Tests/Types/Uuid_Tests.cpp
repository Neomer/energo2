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
    ASSERT_EQ(uid, Uuid::Empty());
}

TEST_F(Uuid_Tests, UuidRandomMustReturnsDifferentValues) {
    random_device rd;
    ASSERT_FALSE(Uuid::Random(rd) == Uuid::Random(rd));
}

TEST_F(Uuid_Tests, UuidRandomMustNotBeEmpty) {
    random_device rd;
    ASSERT_FALSE(Uuid::Random(rd) == Uuid::Empty());
}