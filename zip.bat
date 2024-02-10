@echo off

set VERSION=1.0

set ARC=7z
set ARCFLAGS=u -mx5
set FILES=*
set EXFILES=-x!*.zip
set OUT=Xdv-%VERSION%.zip

set COMMAND=%ARC% %ARCFLAGS% %EXFILES% %OUT% %FILES%

echo Running '%COMMAND%'...
%COMMAND%
