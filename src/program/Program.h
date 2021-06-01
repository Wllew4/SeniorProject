#pragma once

#include "program/File.h"
#include "object/PrimitivesBuffer.h"

class Program
{
	private:
		PrimitiveBuffer m_objectBuffer;
		File m_mainFile;

	public:
		void Execute(char* main);
		PrimitiveBuffer& GetBuffer();
};