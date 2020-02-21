@echo off

REM The path to the program under test is passed through the 1st argument of the command line 
SET MyProgram="%~1"

REM Protection against starting without an argument specifying the path to the program
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy non-empty file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Copy missing file shoild fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM if output file is not specified, program must fail
%MyProgram% MissingFile.txt && goto err
echo Test 4 passed

REM if input and output file is not specified, program must fail
%MyProgram% && goto err
echo Test 5 passed

REM I successfully tested the tests
echo All tests passed successfuly
exit /B 0

REM We will get here in case of an error
:err
echo Test failed
exit /B 1