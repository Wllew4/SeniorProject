#include "object/PrimitiveBuffer.h"

Primitive* PrimitiveBuffer::AddPrimitive(TYPE_PRIMITIVE type, Data* val, const char* name)
{
	Primitive* newPrimitive = new Primitive(type, val, name);
	buffer.push_back(newPrimitive);
	return newPrimitive;
}

void PrimitiveBuffer::RemovePrimitive(Primitive* item)
{
	
}

void PrimitiveBuffer::RemovePrimitives(std::vector<Primitive*> items);
Primitive* PrimitiveBuffer::GetByName(const char* name);