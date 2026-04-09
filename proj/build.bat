@echo off
REM cria a pasta build se não existir
if not exist build mkdir build
REM apaga o exe antigo
del build\main.exe /f /q
echo Compilando projeto...

gcc -Iinclude -I"C:/raylib/inlcude" src/main.c -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o build\main.exe
REM verifica se compilacao deu erro

if ERRORLEVEL 1 goto erro
echo Compilacao concluida!
echo Rodando o programa...
build\main.exe
pause
goto :fim
:erro
echo Houve um erro na compilacao
pause
:fim