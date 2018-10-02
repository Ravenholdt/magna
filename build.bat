@echo off

IF NOT EXIST "build/" (
    mkdir build
)

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"

cd build
cmake -G "NMake Makefiles" ..
nmake

cd ..