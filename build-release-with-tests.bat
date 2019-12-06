@echo off

echo Generation makefiles...
cmake -S ./ -B ./cmake-build-release -G "MinGW Makefiles"

echo 
echo Building...
cmake --build ./cmake-build-release --target all -j 4


@echo on
echo
echo Running tests...
call "./cmake-build-release/SDK_Tests/SDK_Tests.exe" --gtest_color=no
pause