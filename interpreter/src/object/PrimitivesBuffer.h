#pragma once
#include "object/Primitive.h"
#include <vector>

class PrimitiveBuffer {
	private:
		std::vector<std::vector<Primitive>> buffer;
		int currentScope;
	public:
		PrimitiveBuffer();
		void AddPrimitive(const TYPE_PRIMITIVE* type, double n, const char* name);
		void AddPrimitive(const TYPE_PRIMITIVE* type, const char* s, const char* name);
		void AddPrimitive(const TYPE_PRIMITIVE* type, bool b, const char* name);
		void IncreaseScope();
		void DescreaseScope();
		Primitive* GetByName(const char* name);
};