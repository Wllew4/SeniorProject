#pragma once

#define DebugOptionListSize 4

class Debug
{
public:
	Debug(const Debug&) = delete;
	class Log;
	class Timer;
	class Callback;

	static Debug& GetInstance();

	static void Init(int argc, char** argv);

	static const char* GetVersionString();
	static bool GetOption(int index);

private:
	Debug() {}
	const char* version_string = "0.1.0";
	bool b_options[DebugOptionListSize] = { 0,0,0,0 };

	void InternalInit(int argc, char** argv);
};