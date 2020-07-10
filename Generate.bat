@ECHO OFF

RMDIR /Q /S Build
MKDIR Build
PUSHD Build

conan install ../conanfile_windows.txt
cmake .. -G "Visual Studio 16"
REM cmake --build . --config Debug
POPD
