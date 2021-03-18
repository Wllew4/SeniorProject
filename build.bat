@echo off
setlocal enabledelayedexpansion

set sourcefile=examples/helloworld.jan

set output=.\interpreter\bin\janelle.exe
set includepaths=interpreter/src

::  Build intermediates
set /A i=0
mkdir intermediates
for /R "interpreter\src\" %%f in ("*.cpp") DO (
    set /A i+=1
    g++ -c %%f -I %includepaths% -o intermediates\!i!.o
)

::  Compile executable
g++ intermediates\*.o -o %output%

::  Clean up intermediates
del /Q intermediates
rmdir /Q intermediates

::  Execute
%output% %sourcefile%