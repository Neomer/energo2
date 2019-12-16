//
// Created by kir on 15.12.2019.
//

#include <stdexcept>
#include "Version_Tests.h"

using namespace std;
using namespace energo::types;

TEST_F(Version_Tests, IntegerValueMustBeMajorOnlyVersion) {
    auto version = Version::Parse("10");
    EXPECT_TRUE(version.getMajor() == 10 && version.getMinor() == 0 && version.getPatch() == 0 && version.getBuild() == 0);
}

TEST_F(Version_Tests, IntDotIntValueMustBeMajorAndMinorVersion) {
    auto version = Version::Parse("10.12");
    EXPECT_TRUE(version.getMajor() == 10 && version.getMinor() == 12 && version.getPatch() == 0 && version.getBuild() == 0);
}

TEST_F(Version_Tests, IntDotIntDotIntValueMustBeMajorMinorPatchVersion) {
    auto version = Version::Parse("10.12.54");
    EXPECT_TRUE(version.getMajor() == 10 && version.getMinor() == 12 && version.getPatch() == 54 && version.getBuild() == 0);
}

TEST_F(Version_Tests, IntDotIntDotIntSpaceIntValueMustBeMajorMinorPatchBuildVersion) {
    auto version = Version::Parse("10.12.54 454");
    EXPECT_TRUE(version.getMajor() == 10 && version.getMinor() == 12 && version.getPatch() == 54 && version.getBuild() == 454);
}

TEST_F(Version_Tests, NonExpectedSymbolMustThrowsInvalidArgumentException) {
    EXPECT_THROW(Version::Parse("1f0.12.54"), invalid_argument);
    EXPECT_THROW(Version::Parse("10..12.54"), invalid_argument);
    EXPECT_THROW(Version::Parse("10.12...54"), invalid_argument);
    EXPECT_THROW(Version::Parse("10 12.54"), invalid_argument);
}

TEST_F(Version_Tests, NonExpectedSymbolMustReturnsFalse) {
    Version v;
    EXPECT_FALSE(Version::TryParse("1f0.12.54", v));
}

TEST_F(Version_Tests, EmptyConstructorMustSetMajorToOne) {
    Version version;
    EXPECT_TRUE(version.getMajor() == 1 && version.getMinor() == 0 && version.getPatch() == 0 && version.getBuild() == 0);
}

TEST_F(Version_Tests, MultipleSpacesBeforeBuildShouldBeSkipped) {
    Version version;
    EXPECT_TRUE(Version::TryParse("1.4.3    3", version));
    EXPECT_TRUE(version.getMajor() == 1 && version.getMinor() == 4 && version.getPatch() == 3 && version.getBuild() == 3);
}

TEST_F(Version_Tests, FirstAndLastSpacesShouldBeSkipped) {
    Version version;
    EXPECT_TRUE(Version::TryParse("   1.4.3 3   ", version));
    EXPECT_TRUE(version.getMajor() == 1 && version.getMinor() == 4 && version.getPatch() == 3 && version.getBuild() == 3);
}

TEST_F(Version_Tests, StringifyWithoutBuildMustBeTrippleInt) {
    Version version;
    EXPECT_EQ(version.toString(), "1.0.0");
}


TEST_F(Version_Tests, StringifyWIthBuild) {
    Version version{5, 3, 5, 56};
    EXPECT_EQ(version.toString(), "5.3.5 56");
}

