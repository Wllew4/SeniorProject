#include "debug/Timer.h"
#include "program/Program.h"

Program::Program()
	: m_mainFile(m_objectBuffer) {}

void Program::Execute(char* _main)
{
	Debug::Timer timer = "Total Program Execution";
	m_mainFile.Load(_main);
	m_mainFile.Execute();
}

PrimitiveBuffer& Program::GetBuffer()
{
	return m_objectBuffer;
}