/*      Janelle Interpreter
 *      Created by William Janelle
 *      Bedford High School Senior Project
 */

const char* version_string = "0.1.0";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/Log.h"

struct {
    bool printfile = false;
} options;

const char* readFile(char* file){
    FILE* f = fopen(file, "r");

    if(f){
        fseek(f, 0, SEEK_END);
        int bufsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char* buffer = (char*)malloc(sizeof(char) * (bufsize + 1));
        buffer[bufsize] = '\0';

        int readsize = fread(buffer, sizeof(char), bufsize, f);
        if(bufsize != readsize){
            free(buffer);
            printf("Could not allocate memory for file " + *file);
            exit(1);
        }
        fclose(f);
        if(options.printfile){
            Log::Print("DEBUG Print source file: ");
            Log::AddOn(file);
            Log::AddOn("\n");
            printf(buffer);
            
        }

        return buffer;
    } else {
        printf("Could not find file %s", file);
        exit(1);
    }
}

int main(int argc, char** argv){
    if(argc == 1){ Log::Error("No file name or arguments provided"); exit(1); }
    char** fileArg;
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(strcmp(argv[i], "--verify") == 0){
                Log::Print("Janelle Intepreter version ");
                Log::AddOn(version_string);
                Log::AddOn("\n");
            }
            if(strcmp(argv[i], "--debug-printfile") == 0){  //  <-- Doing weird stuff when file has line breaks
                options.printfile = true;
            }
        }
        else {
            fileArg = &argv[i];
        }
    }
    readFile(*fileArg);
}