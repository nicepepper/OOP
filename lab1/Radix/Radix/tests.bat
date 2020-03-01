@echo off

SET PROGRAM="%~1"
SET OUT="%TEMP%\out.txt"

REM 234(8) = 156(10)
%PROGRAM% "8" "10" "234" > %OUT% || goto err
fc Test1.txt %OUT% > nul || goto err
echo Test 1 passed

REM not paramets
%PROGRAM% && goto err
echo Test 2 passed

REM empty paramets
%PROGRAM% "" "" "" && goto err
echo Test 3 passed

REM the first parameter is bad
%PROGRAM% "37" "10" "P" && goto err
echo Test 4 passed

REM P(36) = 25(10)
%PROGRAM% "36" "10" "P" > %OUT% || goto err
fc Test5.txt %OUT% > nul  || goto err
echo Test 5 passed

REM the second parameter is bad
%PROGRAM% "34" "1" "RF" && goto err
echo Test 6 passed

REM RF(34) = 1110100101(2)
%PROGRAM% "34" "2" "RF" > %OUT% || goto err
fc Test7.txt %OUT% > nul  || goto err
echo Test 7 passed

REM 7FFFFFFF(16) = 2147483647(10)
%PROGRAM% 16 10 7FFFFFFF > %OUT% || goto err
fc Test8.txt %OUT% > nul || goto err
echo Test 8 passed

REM 80000000(16) = 2147483647(10)
%PROGRAM% 16 10 80000000 && goto err
echo Test 9 passed

REM -80000000(16) = -2147483648(10)
%PROGRAM% 16 10 -80000000 > %OUT% || goto err
fc Test10.txt %OUT% > nul || goto err
echo Test 10 passed

REM -80000001(16) = -2147483648(10)
%PROGRAM% 16 10 -80000001 && goto err
echo Test 11 passed

REM проверка на 0
%PROGRAM% "8" "10" "0" > %OUT% || goto err
fc Test12.txt %OUT% > nul || goto err
echo Test 12 passed

REM third parameter is bad
%PROGRAM% "2" "10" "-" && goto err
echo Test 13 passed

REM third parameter is bad
%PROGRAM% "2" "10" "--10" && goto err
echo Test 14 passed


REM I successfully tested the tests
echo All tests passed successfuly
exit /B 0

REM We will get here in case of an error
:err
echo Test failed
exit /B 1