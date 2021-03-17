@echo off

set sourcefile=examples/helloworld.jan

set sourcepaths=interpreter\src\*.cpp interpreter\src\util\*.cpp interpreter\src\parser\*.cpp
set output=.\interpreter\bin\janelle.exe
set includepaths=interpreter/src

::  Compile
g++ %sourcepaths% -o %output% -I %includepaths%

::  Execute
%output% %sourcefile%