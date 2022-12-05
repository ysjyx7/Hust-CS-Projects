@echo off

set appname="SR.exe"
set inputname="input.txt"
set outputname="output.txt"
set resultname="SR.txt"

for /l %%i in (1,1,10) do (
    echo Test %appname% %%i:
    %appname% > %resultname% 2>&1
    fc /N %inputname% %outputname%
)
pause