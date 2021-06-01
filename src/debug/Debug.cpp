#include "debug/Log.h"
#include "debug/Debug.h"
#include "ast/lexing/Lexer.h"
#include <string.h>
#include <algorithm>

Debug& Debug::GetInstance()
{
    static Debug instance;
    return instance;
}

void Debug::Init(int argc, char** argv)
{
    GetInstance().InternalInit(argc, argv);
}

const char* Debug::GetVersionString()
{
    return GetInstance().version_string;
}

bool Debug::GetOption(int index)
{
    index = std::clamp(index, 0, DebugOptionListSize);
    return GetInstance().b_options[index];
}

void Debug::InternalInit(int argc, char** argv)
{
    if (argc == 1)
    {
        Debug::Log::Crash(113) << "No file name or arguments provided\n";
        exit(113);
    }
    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            if(strcmp(argv[i], "--verify") == 0)
                Print << "Janelle Interpreter version " << version_string << '\n';
            if(strcmp(argv[i], "--debug-printfile") == 0)
                b_options[0] = true;
            if(strcmp(argv[i], "--debug-printtokens") == 0)
                b_options[1] = true;
            if(strcmp(argv[i], "--debug-printstatements") == 0)
                b_options[2] = true;
            if (strcmp(argv[i], "--debug-stopwatch") == 0)
                b_options[3] = true;
        }
    }

    int enabledDebuggerC = 0;
    for(bool i : b_options)
        if(i)
            enabledDebuggerC++;

    if(enabledDebuggerC > 0)
        Print << "Running Debugger "
            << (enabledDebuggerC > 1 ? "s:" : ":")
            << (b_options[0] ? " Print Source" : "")
            << (b_options[1] ? " Print Tokens" : "")
            << (b_options[2] ? " Print Statements" : "")
            << (b_options[3] ? " Stopwatch" : "")
            << "\n\n";
}
