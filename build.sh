sourcefile=examples/helloworld.jan
flags=--debug-printtokens

output=interpreter/bin/janelle.exe
includepaths=interpreter/src

#		Build intermediates
i=0
mkdir intermediates
for f in interpreter/src/*.cpp interpreter/src/**/*.cpp; do
		echo $f
    i=$[i+1]
    g++ -c $f -I $includepaths -o intermediates/$i.o
done

#		Compile executable
[ ! -d "intermediates/bin" ]; mkdir interpreter/bin
g++ intermediates/*.o -o $output

#		Clean up intermediates
rm -r intermediates

#		Execute
$output $sourcefile $flags