#pragma once

#include "execution/Execution.h"

class File
{
private:
		char* m_file;
		Exec m_exe;

public:
	~File();
    void Load(char* file);
    void Execute();
};