
call "%VS90COMNTOOLS%"\vsvars32.bat
cl %1%2".cpp" /DWINDOWS /I%ORCA_PATH%\include\orca /I%BOOST_PATH% /I%ORCA_PATH%\external\include liborca.lib /LD %4 %5
copy %3 %1

