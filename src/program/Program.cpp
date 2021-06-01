#include "program/Program.h"

void Program::Execute(char* main)
{
	m_mainFile.Load(main);
	m_mainFile.Execute();
}

PrimitiveBuffer& Program::GetBuffer()
{
	return m_objectBuffer;
}