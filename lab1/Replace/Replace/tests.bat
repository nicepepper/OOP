@echo off

REM The path to the program under test is passed through the 1st argument of the command line 
SET MyProgram="%~1"

REM Protection against starting without an argument specifying the path to the program
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" "a" "b" || goto err
fc Empty-output.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1-Empty passed

REM search for dogs and replacement with a cat
%MyProgram% fox.txt "%TEMP%\output.txt" "dog" "cat"|| goto err
fc fox-replace-dog-with-cat.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2-fox passed

REM replacement of the substring 1231234 inside the text 12312312345
%MyProgram% numbers.txt "%TEMP%\output.txt" "1231234" "0"
fc numbers-output.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3-numbers passed

REM mo replace with momo
%MyProgram% mom.txt "%TEMP%\output.txt" "mo" "momo"|| goto err
fc mom-output.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4-mom passed

REM uppercase
%MyProgram% uppercase.txt "%TEMP%\output.txt" e E || goto err
fc uppercase-output.txt "%TEMP%\output.txt" > nul || goto err
echo test 5-uppercase passed


REM Copy missing file shoild fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" a b && goto err
echo Test 6-missing passed

REM if input and output file is not specified, program must fail
%MyProgram% && goto err
echo Test 6-input-output passed



REM I successfully tested the tests
echo All tests passed successfuly
exit /B 0

REM We will get here in case of an error
:err
echo Test failed
exit /B 1