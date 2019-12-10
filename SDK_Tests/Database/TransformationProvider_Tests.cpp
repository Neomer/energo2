#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by vinokurov on 10.12.2019.
//

#include "TransformationProvider_Tests.h"

using namespace std;
using namespace energo::db;

TEST_F(TransformationProvider_Tests, TransformationProviderShouldQuoteFieldName) {
    EXPECT_EQ("\"SomeField\"", TransformationProvider::EscapeFieldNameIfNeeded("SomeField"));
}
#pragma clang diagnostic pop