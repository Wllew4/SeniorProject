#include "object/PrimitivesBuffer.h"
#include "util/Log.h"
#include <algorithm>
#include <string.h>

Primitive* PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE* type, double* n, const char* name)
{
	Primitive* newPrimitive = new Primitive(type, n, name);
	buffer.push_back(newPrimitive);
	return newPrimitive;
}

Primitive* PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE* type, const char* s, const char* name)
{
	Primitive* newPrimitive = new Primitive(type, s, name);
	buffer.push_back(newPrimitive);
	return newPrimitive;
}

Primitive* PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE* type, bool* b, const char* name)
{
	Primitive* newPrimitive = new Primitive(type, b, name);
	buffer.push_back(newPrimitive);
	return newPrimitive;
}

void PrimitiveBuffer::RemovePrimitive(Primitive* item)
{
	buffer.erase(
		std::remove_if(
			buffer.begin(),
			buffer.end(),
			[&](Primitive* i){
				if(i == item){
					delete i;
					return true;
				}
				return false;
			}),
		buffer.end());
}

void PrimitiveBuffer::RemovePrimitives(std::vector<Primitive*> items)
{
	buffer.erase(
		std::remove_if(
			buffer.begin(),
			buffer.end(),
			[&](Primitive* i){
				for(auto j : items){
					if(i == j){
						delete i;
						return true;
					}
				}
				return false;
			}),
		buffer.end());
}

Primitive* PrimitiveBuffer::GetByName(const char* name)
{
	for(auto item : buffer)
		if(strcmp(item->getName(), name) == 0)
			return item;
	
	Log::UnrecognizedIdentifier(name);
	return nullptr;
}