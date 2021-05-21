#include "object/PrimitivesBuffer.h"
#include "debug/Log.h"
#include <algorithm>
#include <string.h>
#include <iostream>

PrimitiveBuffer::PrimitiveBuffer()
{
	currentScope = 0;
	buffer.resize(1);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, double n, std::string& name)
{
	buffer.at(currentScope).emplace_back(type, n, name);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, std::string s, std::string& name)
{
	buffer.at(currentScope).emplace_back(type, s, name);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, bool b, std::string& name)
{
	buffer.at(currentScope).emplace_back(type, b, name);
}

void PrimitiveBuffer::IncreaseScope()
{
	buffer.emplace_back();
	currentScope++;
}

void PrimitiveBuffer::DescreaseScope()
{
	buffer.pop_back();
	buffer.shrink_to_fit();
	currentScope--;
}

Primitive* PrimitiveBuffer::GetByName(std::string& name)
{
	for(unsigned int i = 0; i < buffer.size(); i++)
		for (unsigned int j = 0; j < buffer.at(i).size(); j++) {
			if (buffer.at(i).at(j).getName() == name)
				return &buffer.at(i).at(j);
		}
	//Log::UnrecognizedIdentifier(name);
	return nullptr;
}