@echo off
setlocal enabledelayedexpansion

:: Output file
set "OUTFILE=sources.inc"

echo # Automatically generated source/object lists for Atlas > %OUTFILE%

set "SRCS="
set "OBJS="

:: Scan the source directory for .cpp files
for %%f in (source\*.cpp) do (
    set "SRCS=!SRCS! %%f"
    set "OBJS=!OBJS! build\obj\%%~nf.obj"
)

:: Write variables to the include file
echo SRCS = !SRCS! >> %OUTFILE%
echo OBJS = !OBJS! >> %OUTFILE%

echo File list generated in %OUTFILE%