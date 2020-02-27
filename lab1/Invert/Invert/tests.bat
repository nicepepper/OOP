@echo off

SET PROGRAM="%~1"
SET OUT="%TEMP%\output.txt"

REM как устранить знак - в -0.000 ????; надо ли проверять корректность данных в файле ?;

REM det != 0
%PROGRAM% test1.txt > %OUT% || goto err
fc test1-out.txt %OUT% > nul || goto err
echo Test 1 passed

REM det = 0
%PROGRAM% test2.txt && goto err
echo Test 2 passed

REM not paramets
%PROGRAM% && goto err
echo Test 3 passed

REM if output file is not specified, program must fail
%PROGRAM% MissingFile.txt && goto err
echo Test 4 passed

REM det != 0
%PROGRAM% test5.txt > %OUT% || goto err
fc test5-out.txt %OUT% > nul || goto err
echo Test 5 passed

REM I successfully tested the tests
echo All tests passed successfuly
exit /B 0

REM We will get here in case of an error
:err
echo Test failed
exit /B 1