#pragma once

#include "program/File.h"
#include "object/PrimitivesBuffer.h"

class Program {
	private:
		PrimitiveBuffer objbuffer;
		File mainFile;

	public:
		void execute(char* main);
		PrimitiveBuffer* GetBuffer();
};

extern Program program;