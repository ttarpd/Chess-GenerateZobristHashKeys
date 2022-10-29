@echo off

REM locale dependent - this is for UK
For /f "tokens=1-3 delims=/ " %%a in ('date /t') do (set mydate=%%c%%b%%a)
For /f "tokens=1-2 delims=/:" %%a in ('time /t') do (set mytime=%%a%%b)
set mydatetime=%mydate%_%mytime%

.\GenerateZobristHashKeys.exe 1>zobrist_%mydatetime%.log
