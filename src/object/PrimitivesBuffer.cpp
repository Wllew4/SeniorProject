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
	buffer.at(currentScope).emplace_back(type, n, name.c_str());
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, std::string s, std::string& name)
{
	buffer.at(currentScope).emplace_back(type, s, name.c_str());
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, bool b, std::string& name)
{
	buffer.at(currentScope).emplace_back(type, b, name.c_str());
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

Primitive* PrimitiveBuffer::GetByName(std::string& name)
{
	//std::cout << name;
	for(int i = 0; i < buffer.size(); i++)
		for (int j = 0; j < buffer.at(i).size(); j++) {
			//std::cout << buffer.at(i).at(j).getName();
			if (buffer.at(i).at(j).getName() == name)
				return &buffer.at(i).at(j);
		}
			

	std::cout << "no luckj";
	//Log::UnrecognizedIdentifier(name);
	return nullptr;
}