#pragma once

#include <vector>
#include "object/ObjectBuffer.h"
#include "program/File.h"

class Program {
	private:
		std::vector<Primitive*> PrimitivesBuffer;
		File mainFile;

	public:
		void execute(char* main);
		std::vector<Primitive*>* GetBuffer();
};