#pragma once

#include <vector>
#include "object/ObjectBuffer.h"
#include "program/File.h"

class Program {
	private:
		std::vector<ObjectBuffer> ObjectBufferBuffer;
		File mainFile;

	public:
		Program(char* main);
};