#pragma once

#include "object/PrimitivesBuffer.h"
#include "program/File.h"

class Program
{
public:
	Program();

	void Execute(char* _main);
	PrimitiveBuffer& GetBuffer();

private:
	File m_mainFile;
	PrimitiveBuffer m_objectBuffer;
};