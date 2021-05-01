sourcefile=examples/FizzBuzz.jan
#flags=--debug-printtokens

output=interpreter/bin/janelle.exe
includepaths=interpreter/src
sources=$(find ./interpreter/src -type f -iname *.cpp)

g++ -o $output $sources -I $includepaths
$output $sourcefile $flags