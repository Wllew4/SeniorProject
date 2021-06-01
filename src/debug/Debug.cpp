#include "debug/Log.h"
#include "debug/Debug.h"
#include "ast/lexing/Lexer.h"
#include <string.h>
#include <stdlib.h>
#include <chrono>

const char* version_string = "0.1.0";
bool options[4] = {0,0,0,0};

void Debug::parseArgs(int argc, char** argv){
    //if(argc == 1){ Log::Error(1,"No file name or arguments provided"); exit(1); }
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(strcmp(argv[i], "--verify") == 0){
                //Log::Print(3,"Janelle Intepreter version ", version_string, "\n");
            }
            if(strcmp(argv[i], "--debug-printfile") == 0){
                options[0] = true;
            }
            if(strcmp(argv[i], "--debug-printtokens") == 0){
                options[1] = true;
            }
            if(strcmp(argv[i], "--debug-printstatements") == 0){
                options[2] = true;
            }
            if (strcmp(argv[i], "--debug-stopwatch") == 0) {
                options[3] = true;
            }
        }
    }

    int enabledDebuggerC = 0;
    for(bool i : options){
        if(i) enabledDebuggerC++;
    }
    if(enabledDebuggerC > 0){
        //Log::Print(3, "version ", version_string, "\n");
        //Log::Print(7, "Running Debugger",
            // enabledDebuggerC > 1 ? "s:" : ":",
            // options[0] ? " Print Source" : "",
            // options[1] ? " Print Tokens" : "",
            // options[2] ? " Print Statements" : "",
            // options[3] ? " Stopwatch" : "",
            // "\n\n");
    }
}

void Debug::callbackNewToken(Token& t)
{
	if(options[1])
		Print << t.toString() << '\n';
}