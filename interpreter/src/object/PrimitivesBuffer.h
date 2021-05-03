#pragma once
#include "object/Primitive.h"
#include <vector>

class PrimitiveBuffer {
	private:
		std::vector<Primitive*> buffer;
	public:
		Primitive* AddPrimitive(const TYPE_PRIMITIVE* type, double* n, const char* name);
		Primitive* AddPrimitive(const TYPE_PRIMITIVE* type, const char* s, const char* name);
		Primitive* AddPrimitive(const TYPE_PRIMITIVE* type, bool* b, const char* name);
		void RemovePrimitive(Primitive* item);
		void RemovePrimitives(std::vector<Primitive*> items);
		Primitive* GetByName(const char* name);
};