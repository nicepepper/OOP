@echo off

SET PROGRAM="%~1"
SET OUT="%TEMP%\output.bin"

REM missing input file 
%PROGRAM% pack Test1.bin %OUT% && goto err
echo Test 1 passed

REM mode set incorrectly
%PROGRAM% p Test.bin %OUT% && goto err
echo Test 2 passed

REM empty command line options
%PROGRAM% "" "" "" && goto err
echo Test 3 passed

REM wrong number of command line options
%PROGRAM% pack Test.bin %OUT% 10 && goto err
echo Test 4 passed

REM first encoding mode test (AAAAAAAAAA)
%PROGRAM% pack Test.bin %OUT% || goto err
fc Test-out.bin %OUT% > nul || goto err
echo Test 5 passed

REM first decoding mode test (0A 41)
%PROGRAM% unpack Test-out.bin %OUT% || goto err
fc Test.bin %OUT% > nul || goto err
echo Test 6 passed

REM empty file (encoding + decoding)
%PROGRAM% pack Test7.bin %OUT% || goto err
fc Test7-out.bin %OUT% > nul || goto err
%PROGRAM% unpack Test7-out.bin %OUT% ||got err
fc Test7.bin %OUT% > nul || goto err
echo  Test 7 passed

REM 255A, 256B, 257C - encoding
%PROGRAM% pack Test8.bin %OUT% || goto err
fc Test8-out.bin %OUT% > nul ||goto err
echo Test 8 passed

REM 255A, 256B, 257C - decoding
%PROGRAM% unpack Test8-out.bin %OUT% || goto err
fc Test8.bin %OUT% > nul ||goto err
echo Test 9 passed

REM odd length of encoded file (9 byte)
%PROGRAM% unpack Test10.bin %OUT% && goto err
echo Test 10 passed

REM zero character repetition
%PROGRAM% unpack Test11.bin %OUT% && goto err
echo Test 11 passed

REM File containing characters code 255 (0xFF)
%PROGRAM% unpack Test12.bin %OUT% || goto err
fc Test12-out.bin %OUT% > nul ||goto err
echo Test 12 passed



REM I successfully tested the tests
echo All tests passed successfuly
exit /B 0

REM We will get here in case of an error
:err
echo Test Failed
exit /B 1