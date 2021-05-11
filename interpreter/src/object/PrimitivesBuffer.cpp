#include "object/PrimitivesBuffer.h"
#include "util/Log.h"
#include <algorithm>
#include <string.h>
#include <iostream>

PrimitiveBuffer::PrimitiveBuffer()
{
	currentScope = 0;
	buffer.resize(1);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE* type, double n, const char* name)
{
	buffer.at(currentScope).emplace_back(type, n, name);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE* type, const char* s, const char* name)
{
	buffer.at(currentScope).emplace_back(type, s, name);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE* type, bool b, const char* name)
{
	buffer.at(currentScope).emplace_back(type, b, name);
}

// void PrimitiveBuffer::RemovePrimitive(Primitive* item)
// {
// 	buffer.erase(
// 		std::remove_if(
// 			buffer.begin(),
// 			buffer.end(),
// 			[&](Primitive* i){
// 				if(i == item){
// 					delete i;
// 					return true;
// 				}
// 				return false;
// 			}),
// 		buffer.end());
// }

// void PrimitiveBuffer::RemovePrimitives(std::vector<Primitive> items)
// {
// 	buffer.erase(
// 		std::remove_if(
// 			buffer.begin(),
// 			buffer.end(),
// 			[&](Primitive* i){
// 				for(auto j : items){
// 					if(i == j){
// 						delete i;
// 						return true;
// 					}
// 				}
// 				return false;
// 			}),
// 		buffer.end());
// }

void PrimitiveBuffer::IncreaseScope()
{
	buffer.emplace_back();
	currentScope++;
}

void PrimitiveBuffer::DescreaseScope()
{
	buffer.pop_back();
	currentScope--;
}

Primitive* PrimitiveBuffer::GetByName(const char* name)
{
	for(int i = 0; i < buffer.size(); i++)
		for(int j = 0; j < buffer.at(i).size(); j++)
			if(strcmp(buffer.at(i).at(j).getName(), name) == 0)
				return &buffer.at(i).at(j);

	//Log::UnrecognizedIdentifier(name);
	return nullptr;
}