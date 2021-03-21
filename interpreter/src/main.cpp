/*      Janelle Interpreter
 *      Created by William Janelle
 *      Bedford High School Senior Project
 * 
 *      TO-DO:
 *          - Conditionals
 *          - Recursion
 *          - Math
 *          - Rendering
 */

const char* version_string = "0.1.0";


#include <string.h>
#include <string>

#include "util/Log.h"
#include "parser/Parser.h"
#include "config.h"

bool options[2] = {0,0};

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

    #pragma region printDebugOptions
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
    #pragma endregion

    Parser::parse(*fileArg);
}