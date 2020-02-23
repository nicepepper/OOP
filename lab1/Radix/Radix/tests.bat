@echo off

SET PROGRAM="%~1"

SET OUT="%TEMP%\out.txt"

REM 234(8) = 156(10)
%PROGRAM% "8" "10" "234" > %OUT%
fc Test1.txt %OUT% > nul || goto err
echo Test 1 passed


REM I successfully tested the tests
echo All tests passed successfuly
exit /B 0

REM We will get here in case of an error
:err
echo Test failed
exit /B 1