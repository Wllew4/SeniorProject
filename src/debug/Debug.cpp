#include "debug/Log.h"
#include <string.h>
#include <stdlib.h>
#include <chrono>

const char* version_string = "0.1.0";
bool options[4] = {0,0,0,0};

std::chrono::time_point<std::chrono::high_resolution_clock> s;

void parseArgs(int argc, char** argv){
    if(argc == 1){ Log::Error(1,"No file name or arguments provided"); exit(1); }
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
            if(strcmp(argv[i], "--debug-printstatements") == 0){
                options[2] = true;
            }
            if (strcmp(argv[i], "--debug-stopwatch") == 0) {
                options[3] = true;
                s = std::chrono::high_resolution_clock::now();
            }
        }
    }

    #pragma region printDebugOptions
    int enabledDebuggerC = 0;
    for(bool i : options){
        if(i) enabledDebuggerC++;
    }
    if(enabledDebuggerC > 0){
        Log::Print(3, "version ", version_string, "\n");
        Log::Print(6, "Running Debugger",
            enabledDebuggerC > 1 ? "s:" : ":",
            options[0] ? " Print Source" : "",
            options[1] ? " Print Tokens" : "",
            options[2] ? " Print Statements" : "",
            "\n\n");
    }
    #pragma endregion
}

void DebugEnd()
{
    if (options[3])
    {
        auto e = std::chrono::high_resolution_clock::now();
        double dur = std::chrono::duration<double, std::milli>(e - s).count();
        Log::Print(3, "Completed in ", std::to_string(dur).c_str(), "ms");
    }
}