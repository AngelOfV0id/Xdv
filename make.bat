@echo off

set VERSION=\"1.1\"

set CC=tcc
set DEFINES=-DVERSION=%VERSION%
set ARCH=-m32
set LIBS=-lshell32
set CCFLAGS=%ARCH% %LIBS% %DEFINES%
set SOURCE=Xdv.c
set OUT=Xdv.exe

set COMMAND=%CC% %SOURCE% %CCFLAGS% -o %OUT%

echo Running '%COMMAND%'...
%COMMAND%
