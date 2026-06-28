@echo off

if "%1" == "build" goto :build
if "%1" == "run" goto :run
if "%1" == "compdb" goto :compdb
if "%1" == "clean" goto :clean
if "%1" == "vs" goto :vs

echo Commands:
echo   learnopengl build       - configure + build (Debug) with the msvc preset
echo   learnopengl run [id]    - build + run, optionally an exercise id (e.g. run 3)
echo   learnopengl compdb      - configure with Ninja and copy compile_commands.json to root
echo   learnopengl clean       - delete build
echo   learnopengl vs          - open the Visual Studio solution
exit /b

:build
cmake --preset msvc || exit /b 1
cmake --build --preset debug || exit /b 1
exit /b

:run
cmake --preset msvc || exit /b 1
cmake --build --preset debug || exit /b 1
build\msvc\Debug\learnopengl.exe %2
exit /b

:compdb
:: Ninja needs the MSVC compiler (and ninja itself) on PATH at configure time.
call "D:\Visual Studio\VC\Auxiliary\Build\vcvarsall.bat" x64
:: Wipe any prior cache so CMake doesn't refuse to switch generators, then use
:: the vcpkg toolchain so the database matches the real build. Ninja only emits
:: compile_commands.json when EXPORT is ON.
if exist "build\ninja" rmdir /s /q "build\ninja"
cmake -S . -B build\ninja -G Ninja ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
  -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ^
  -DCMAKE_TOOLCHAIN_FILE="C:/Users/ayode/vcpkg/scripts/buildsystems/vcpkg.cmake" ^
  -DVCPKG_TARGET_TRIPLET=x64-windows || exit /b 1
if not exist "build\ninja\compile_commands.json" (
    echo ERROR: compile_commands.json was not generated in build\ninja.
    exit /b 1
)
copy /y "build\ninja\compile_commands.json" "compile_commands.json" >nul || exit /b 1
echo Copied compile_commands.json to repo root.
exit /b

:clean
if exist "build" rmdir /s /q "build"
exit /b

:vs
start "" "build\msvc\LearnOpenGL.slnx"
exit /b
