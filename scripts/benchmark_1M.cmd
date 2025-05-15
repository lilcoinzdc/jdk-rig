@echo off
cd /d "%~dp0"
jdkrig.exe --bench=1M --submit
pause
