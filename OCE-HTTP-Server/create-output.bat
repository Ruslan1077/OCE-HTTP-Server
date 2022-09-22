@echo off
rem options
set "out_dir_x64=Win_http_compiled\x64"
set "out_dir_x32=Win_http_compiled\x32"

set "win_64=bin\x64\Release"
set "win_32=bin\Win32\Release"



@echo Create output for Win_x64
rem create out dirs
mkdir %out_dir_x64%
mkdir %out_dir_x64%\pdb

rem create output with server
copy %win_64%\http_server.exe %out_dir_x64%\OCE-HTTP-Server.exe /y
copy %win_64%\lua.dll %out_dir_x64%\lua.dll /y

rem create output with pdbs
copy %win_64%\config_lib.pdb %out_dir_x64%\pdb\config_lib.pdb /y
copy %win_64%\http_server.pdb %out_dir_x64%\pdb\http_server.pdb /y
copy %win_64%\http_server_lib.pdb %out_dir_x64%\pdb\http_server_lib.pdb /y
copy %win_64%\connection_handler_lib.pdb %out_dir_x64%\pdb\connection_handler_lib.pdb /y



@echo Create output for Win_x32
rem create out dirs
mkdir %out_dir_x32%
mkdir %out_dir_x32%\pdb

rem create output with server
copy %win_32%\http_server.exe %out_dir_x32%\OCE-HTTP-Server.exe /y
copy %win_32%\lua.dll %out_dir_x32%\lua.dll /y

rem create output with pdbs
copy %win_32%\config_lib.pdb %out_dir_x32%\pdb\config_lib.pdb /y
copy %win_32%\http_server.pdb %out_dir_x32%\pdb\http_server.pdb /y
copy %win_32%\http_server_lib.pdb %out_dir_x32%\pdb\http_server_lib.pdb /y
copy %win_32%\connection_handler_lib.pdb %out_dir_x32%\pdb\connection_handler_lib.pdb /y
