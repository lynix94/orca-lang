
if "%1" == "" goto exit
if "%2" == "" goto exit

set OUT_DIR=%1
set DEST_DIR=%2
set SRC_DIR=%OUT_DIR%\..\..\src
set SRC_LIB_DIR=%OUT_DIR%\..\..\lib
set SRC_TEST_DIR=%OUT_DIR%\..\..\tests
set SRC_EXT_DIR=%OUT_DIR%\..\..\external\lib

set BIN_DIR=%DEST_DIR%
set LIB_DIR=%DEST_DIR%\lib
set INC_DIR=%DEST_DIR%\include\orca
set TEST_DIR=%DEST_DIR%\tests

mkdir %DEST_DIR%
mkdir %BIN_DIR%
mkdir %LIB_DIR%
mkdir %DEST_DIR%\include
mkdir %INC_DIR%
mkdir %TEST_DIR%

copy %SRC_DIR%\..\vscompile.bat   %BIN_DIR%
copy %OUT_DIR%\*.lib %BIN_DIR%
copy %OUT_DIR%\*.dll %BIN_DIR%
copy %OUT_DIR%\*.exe %BIN_DIR%
copy %SRC_EXT_DIR%\*.*   %BIN_DIR%

copy %SRC_DIR%\include\*.h   %INC_DIR%
copy %SRC_DIR%\vm\*.h   %INC_DIR%
copy %SRC_DIR%\parser\*.h   %INC_DIR%
copy %SRC_DIR%\corelib\*.h   %INC_DIR%
copy %SRC_DIR%\primitive\*.h   %INC_DIR%

copy %SRC_LIB_DIR%\*.*   %LIB_DIR%
copy %SRC_TEST_DIR%\*.*   %TEST_DIR%


:EXIT

