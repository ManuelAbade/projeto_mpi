@echo off
taskkill /f /im game.exe
title Compilador do Jogo

taskkill /f /im game.exe > nul 2>&1
timeout /t 1 /nobreak > nul

REM Vai para a pasta raiz do projeto
cd /d "%~dp0"

REM ============================================
REM CONFIGURACAO DO AMBIENTE
REM ============================================
set AMBIENTE=1

if "%AMBIENTE%"=="1" (
    set RAYLIB_PATH=C:/raylib
    echo Ambiente: PC Principal
) else (
    set RAYLIB_PATH=C:/msys64/ucrt64
    echo Ambiente: Portatil
)

set RAYLIB_INCLUDE=-I%RAYLIB_PATH%/include
set RAYLIB_LIB=-L%RAYLIB_PATH%/lib

:menu
cls
echo ========================================
echo        COMPILADOR DO JOGO
echo ========================================
echo.
echo Ambiente atual: %RAYLIB_PATH%
echo Pasta atual: %CD%
echo.
echo ========================================
echo Opcoes:
echo ========================================
echo 1 - Desenvolvimento (com consola)
echo 2 - Teste (sem consola)
echo 3 - Build Final
echo 4 - Build Final + ZIP
echo 5 - Limpar
echo 6 - Trocar ambiente
echo 0 - Sair
echo.
set /p env="Escolha: "

if "%env%"=="1" goto dev
if "%env%"=="2" goto test
if "%env%"=="3" goto final
if "%env%"=="4" goto final_zip
if "%env%"=="5" goto clean
if "%env%"=="6" goto trocar
if "%env%"=="0" exit
goto menu

:trocar
echo.
if "%AMBIENTE%"=="1" (
    set AMBIENTE=2
    set RAYLIB_PATH=C:/msys64/ucrt64
    echo Agora: Portatil
) else (
    set AMBIENTE=1
    set RAYLIB_PATH=C:/raylib
    echo Agora: PC Principal
)
set RAYLIB_INCLUDE=-I%RAYLIB_PATH%/include
set RAYLIB_LIB=-L%RAYLIB_PATH%/lib
pause
goto menu

REM ============================================
REM DEV MODE
REM ============================================
:dev
echo.
echo Modo Desenvolvimento...

if not exist build mkdir build

gcc src/*.c -Iinclude %RAYLIB_INCLUDE% %RAYLIB_LIB% ^
-lraylib -lglfw3 -lopengl32 -lgdi32 -lwinmm ^
-DDEV ^
-o build/game.exe

if errorlevel 1 goto erro

REM Copiar assets (IMPORTANTE)
if exist assets xcopy /E /I /Y assets build\assets > nul

echo Executando...
cd build
game.exe
cd ..

pause
goto menu

REM ============================================
REM TEST MODE
REM ============================================
:test
echo.
echo Modo Teste (sem consola)...

if not exist build mkdir build

gcc src/*.c -Iinclude %RAYLIB_INCLUDE% %RAYLIB_LIB% ^
-lraylib -lglfw3 -lopengl32 -lgdi32 -lwinmm ^
-mwindows ^
-o build/game.exe

if errorlevel 1 goto erro

REM Copiar assets
if exist assets xcopy /E /I /Y assets build\assets > nul

echo Executando...
cd build
start game.exe
cd ..

pause
goto menu

REM ============================================
REM FINAL BUILD
REM ============================================
:final
echo.
echo BUILD FINAL...

if not exist build mkdir build
if not exist build\release mkdir build\release

gcc src/*.c -Iinclude %RAYLIB_INCLUDE% %RAYLIB_LIB% ^
-lraylib -lglfw3 -lopengl32 -lgdi32 -lwinmm ^
-O2 -s -mwindows ^
-o build/release/game.exe

if errorlevel 1 goto erro

echo Copiando assets...
if exist assets xcopy /E /I /Y assets build\release\assets > nul

REM Copia para teste rapido
copy build\release\game.exe build\ > nul

echo.
echo BUILD CONCLUIDA!
echo Pasta: build\release\
pause
goto menu

REM ============================================
REM FINAL + ZIP
REM ============================================
:final_zip
call :final

where 7z > nul 2> nul
if not errorlevel 1 (
    cd build
    7z a -tzip release.zip release\* > nul
    cd ..
    echo ZIP criado!
) else (
    echo 7zip nao encontrado
)

pause
goto menu

REM ============================================
REM CLEAN
REM ============================================
:clean
echo Limpando...
if exist build rmdir /S /Q build
echo OK
pause
goto menu

REM ============================================
REM ERRO
REM ============================================
:erro
echo.
echo ERRO na compilacao!
pause
goto menu