#pragma once

#include "execution/Exec.h"

class File {
	private:
		char* m_file;
		Exec exe;
	public:
    void load(char* file);
    void execute();
};