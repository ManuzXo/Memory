@echo off
setlocal enabledelayedexpansion

rem --- DEFAULTS ---
set ARCH=x64
set BUILD_TYPE=Debug
set PROJECT_NAME=Memory
set BUILD_DIR=build

rem --- PARSING ARGOMENTI ---
:parse_args
if "%~1"=="" goto args_done

if /I "%~1"=="-a" (
    set ARCH=%~2
    shift
    shift
    goto parse_args
)
if /I "%~1"=="-t" (
    set BUILD_TYPE=%~2
    shift
    shift
    goto parse_args
)
if /I "%~1"=="-c" (
    echo Cleaning build directory...
    rmdir /s /q "%BUILD_DIR%"
    exit /b 0
)
echo Argomento sconosciuto: %1
exit /b 1

:args_done

rem --- MAPPATURA ARCHITETTURA ---
if /I "%ARCH%"=="x86" (
    set PLATFORM=Win32
) else if /I "%ARCH%"=="x64" (
    set PLATFORM=x64
) else (
    echo Architettura non valida: %ARCH%
    exit /b 1
)

echo Configurazione: %PLATFORM% / %BUILD_TYPE%

rem --- Configurazione CMake ---
cmake -G "Visual Studio 17 2022" -A %PLATFORM% -S . -B %BUILD_DIR% ^
    -DCMAKE_CONFIGURATION_TYPES="Debug;Release" ^
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG="%CD%\bin\Debug" ^
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE="%CD%\bin\Release"

if errorlevel 1 (
    echo Errore nella configurazione CMake.
    exit /b 1
)

rem --- Compilazione ---
cmake --build %BUILD_DIR% --config %BUILD_TYPE%

if errorlevel 1 (
    echo Compilazione fallita.
    exit /b 1
)

echo Build completata! Eseguibile: bin\%BUILD_TYPE%\%PROJECT_NAME%.exe

endlocal
