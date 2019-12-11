@echo off
echo =====================================
echo #   Generation makefiles...
echo =====================================
cmake -S ./ -B ./cmake-build-release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

echo =====================================
echo #   Building...
echo =====================================
cmake --build ./cmake-build-release --target all -j 4

echo =====================================
echo #   Running tests...
echo =====================================
call "./cmake-build-release/SDK_Tests/SDK_Tests.exe" --gtest_color=yes
pause