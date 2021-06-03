#pragma once

#define VERSION_STRING "0.1.0"
#define DEBUG_OPTION_LIST_SIZE 4

class Debug
{
public:
	Debug(const Debug&) = delete;
	class Log;
	class Timer;
	class Callback;

	static Debug& GetInstance();

	static void Init(int _argc, char** _argv);

	static const char* GetVersionString();
	static bool GetOption(int _index);

private:
	Debug() {}
	bool b_options[DEBUG_OPTION_LIST_SIZE] = { 0,0,0,0 };

	void InternalInit(int _argc, char** _argv);
};