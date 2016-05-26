
if "%1" == "" goto exit

set DEST_DIR=%1

rmdir %DEST_DIR% /s/q

:EXIT

