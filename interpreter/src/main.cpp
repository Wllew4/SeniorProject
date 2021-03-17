/*      Janelle Interpreter
 *      Created by William Janelle
 *      Bedford High School Senior Project
 * 
 *      TO-DO:
 *          - Variables (weakly typed or strings/numbers)
 *          - Conditionals
 *          - Recursion
 *          - Math
 *          - Rendering
 */

const char* version_string = "0.1.0";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "util/Log.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "config.h"

bool options[2] = {0,0};

char* readFile(char* file){
    FILE* f = fopen(file, "rb");

    if(f){
        fseek(f, 0, SEEK_END);
        int bufsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        char* buffer = new char[bufsize + 1];
        buffer[bufsize] = '\0';

        int readsize = fread(buffer, sizeof(char), bufsize, f);
        if(bufsize != readsize){
            free(buffer);
            Log::Error(3,"Could not allocate memory for file ", file, "\n");
            exit(1);
        }
        fclose(f);
        if(options[0]){
            Log::Print(5,"DEBUG Print source file: ", file, "\n", buffer, "\n\n");
        }

        return buffer;
    } else {
        Log::Error(3,"Could not find file ", file, "\n");
        exit(1);
    }
}

int main(int argc, char** argv){
    setbuf(stdout, NULL);
    if(argc == 1){ Log::Error(1,"No file name or arguments provided"); exit(1); }
    char** fileArg;
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(strcmp(argv[i], "--verify") == 0){
                Log::Print(3,"Janelle Intepreter version ", version_string, "\n");
            }
            if(strcmp(argv[i], "--debug-printfile") == 0){
                options[0] = true;
            }
            if(strcmp(argv[i], "--debug-printtokens") == 0){
                
                options[1] = true;
            }
        }
        else {
            fileArg = &argv[i];
        }
    }

    int enabledDebuggerC = 0;
    for(bool i : options){
        if(i) enabledDebuggerC++;
    }
    if(enabledDebuggerC > 0){
        Log::Print(3, "version ", version_string, "\n");
        Log::Print(5, "Running Debugger",
            enabledDebuggerC > 1 ? "s:" : ":",
            options[0] ? " Print Source" : "",
            options[1] ? " Print Tokens" : "",
            "\n\n");
    }

    Lexer::Init(readFile(*fileArg));
    Parser::parse();
}