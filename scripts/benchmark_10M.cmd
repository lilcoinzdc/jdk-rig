@echo off
cd /d "%~dp0"
jdkrig.exe --bench=10M --submit
pause
