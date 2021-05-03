#pragma once
#include "object/Primitive.h"
#include <vector>

class PrimitiveBuffer {
	private:
		std::vector<Primitive*> buffer;
	public:
		Primitive* AddPrimitive(Data* val, const char* name);
		void RemovePrimitive(Primitive* item);
		void RemovePrimitives(std::vector<Primitive*> items);
		Primitive* GetByName(const char* name);
};