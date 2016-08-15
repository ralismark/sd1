@echo off

if "%done-setup%" == "" (
	set "done-setup=1"
	set "path=%path%;%~dp0\bin"
	echo Setup done
) else (
	echo Already done setup
)
