#pragma once

#include "execution/Execution.h"

class File
{
public:
	File(PrimitiveBuffer& _program);
	~File();
    void Load(char* _file);
    void Execute();

private:
	char* m_file;
	Exec m_exe;
};