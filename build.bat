@echo off
setlocal EnableDelayedExpansion

goto :main
goto :eof



:main

	set "tmpfile=%tmp%\-out-build-"
	if "%1" == "force" (
		shift /1
		goto :force
	)

	goto :build

goto :eof



:build

	( tup || goto :fail ) > %tmpfile%1
	type %tmpfile%1 | findstr /L /C:"<<" | sed "s/.*<<\(.*\)>>.*/\1/g" > %tmpfile%2

	echo:Build done:

	set cnt=0
	for /F %%f in (%tmpfile%2) do (
		set /A cnt += 1
		echo: !cnt!^) output %%f
		for /F "usebackq" %%d in (`stat -c "%%Y" "%~dp0%%f"`) do (
			sqlite3 "%~dp0.tup\db" "update node set mtime=%%d where type=4 and name='%%~nxf'"
		)
	)

	if %cnt% == 0 (
		echo: -^) no output files
		echo:
		echo:nothing happened...
		goto :eof
	)

goto :eof



:fail

	echo:Build failed!
	exit /b 1

goto :eof



:force

	echo:Force rebuilding
	for /R %%i in ("%~dp0*.?pp") do @touch "%%i"
	echo:

	goto :build

goto :eof
