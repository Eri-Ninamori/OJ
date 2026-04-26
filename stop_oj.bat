@echo off

rem OJ System Stop Script

echo Stopping OJ system modules...

rem Stop Java processes
taskkill /f /im java.exe 2>nul

rem Stop C++ processes
taskkill /f /im judge.exe 2>nul
taskkill /f /im discussion.exe 2>nul
taskkill /f /im rank.exe 2>nul

echo OJ system stopped

pause