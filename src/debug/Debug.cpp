#include "debug/Log.h"
#include "debug/Debug.h"
#include "ast/lexing/Lexer.h"
#include <string.h>
#include <algorithm>

Debug& Debug::GetInstance()
{
    static Debug s_instance;
    return s_instance;
}

void Debug::Init(int _argc, char** _argv)
{
    GetInstance().InternalInit(_argc, _argv);
}

const char* Debug::GetVersionString()
{
    return VERSION_STRING;
}

bool Debug::GetOption(int _index)
{
    _index = std::clamp(_index, 0, DEBUG_OPTION_LIST_SIZE);
    return GetInstance().b_options[_index];
}

void Debug::InternalInit(int _argc, char** _argv)
{
    if (_argc == 1)
    {
        Debug::Log::Crash(113) << "No file name or arguments provided\n";
        exit(113);
    }
    for(int i = 1; i < _argc; i++)
    {
        if(_argv[i][0] == '-')
        {
            if(strcmp(_argv[i], "--verify") == 0)
                Debug::Log::Print() << "Janelle Interpreter version " << VERSION_STRING << '\n';
            if(strcmp(_argv[i], "--debug-printfile") == 0)
                b_options[0] = true;
            if(strcmp(_argv[i], "--debug-printtokens") == 0)
                b_options[1] = true;
            if(strcmp(_argv[i], "--debug-printstatements") == 0)
                b_options[2] = true;
            if (strcmp(_argv[i], "--debug-stopwatch") == 0)
                b_options[3] = true;
        }
    }

    int enabledDebuggerC = 0;
    for(bool i : b_options)
        if(i)
            enabledDebuggerC++;

    if (enabledDebuggerC > 0)
    {
        Debug::Log::Print() << "Janelle Interpreter version " << VERSION_STRING << '\n';
        Debug::Log::Print() << "Running Debugger"
            << (enabledDebuggerC > 1 ? "s:" : ":")
            << (b_options[0] ? " Print Source" : "")
            << (b_options[1] ? " Print Tokens" : "")
            << (b_options[2] ? " Print Statements" : "")
            << (b_options[3] ? " Stopwatch" : "")
            << "\n\n";
    }
}