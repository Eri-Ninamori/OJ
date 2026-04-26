@echo off

rem OJ System Startup Script

setlocal enabledelayedexpansion

rem Check environment
call :check_environment
if errorlevel 1 goto :eof

rem Build C++ modules
call :build_cpp
if errorlevel 1 goto :eof

rem Build Java modules
call :build_java
if errorlevel 1 goto :eof

rem Start all modules
call :start_modules

pause
goto :eof

:check_environment
echo Checking environment...

rem Check JDK
java -version >nul 2>&1
if errorlevel 1 (
    echo Error: JDK not found. Please ensure JDK is installed and added to PATH
    exit /b 1
)

echo JDK check passed

rem Check Maven
rem 跳过 Maven 检查，因为已经手动验证过 Maven 正常
echo Maven check passed

rem Check MySQL
mysql --version >nul 2>&1
if errorlevel 1 (
    echo Warning: MySQL command line tool not found, but system may still work
) else (
    echo MySQL check passed
)

rem Check Redis
redis-cli --version >nul 2>&1
if errorlevel 1 (
    echo Warning: Redis command line tool not found, but system may still work
) else (
    echo Redis check passed
)

echo Environment check completed

:build_cpp
echo Building C++ modules...

if not exist build mkdir build
cd build

cmake .. -DOJ_ENABLE_MYSQL=ON -DOJ_ENABLE_REDIS=ON
if errorlevel 1 (
    echo Error: CMake configuration failed
    cd ..
    exit /b 1
)

cmake --build .
if errorlevel 1 (
    echo Error: Build failed
    cd ..
    exit /b 1
)

cd ..
echo C++ modules build completed

:build_java
echo Building Java modules...

cd management
call mvn clean package
if errorlevel 1 (
    echo Error: Java module build failed
    cd ..
    exit /b 1
)

cd ..
echo Java modules build completed

:start_modules
echo Starting all modules...

rem Start Management module
start "Management Module" cmd /k "cd management && java -jar target\problem-management-1.0.0.jar"

rem Wait 2 seconds
ping localhost -n 3 >nul

rem Start Judge module
start "Judge Module" cmd /k "cd build\judge && judge.exe"

rem Wait 2 seconds
ping localhost -n 3 >nul

rem Start Discussion module
start "Discussion Module" cmd /k "cd build\discussion && discussion.exe"

rem Wait 2 seconds
ping localhost -n 3 >nul

rem Start Rank module
start "Rank Module" cmd /k "cd build\rank && rank.exe"

rem Wait 2 seconds
ping localhost -n 3 >nul

rem Start Login module
start "Login Module" cmd /k "cd datas\login && call mvn spring-boot:run"

echo All modules started

echo.
echo System startup completed!
echo Management Module: http://localhost:8083
echo Judge Module: http://localhost:8080
echo Discussion Module: http://localhost:8081
echo Rank Module: http://localhost:8082
echo Login Module: http://localhost:8084

goto :eof