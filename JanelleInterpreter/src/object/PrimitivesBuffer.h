#pragma once
#include "object/Primitive.h"
#include <vector>

class PrimitiveBuffer {
	private:
		std::vector<std::vector<Primitive>> buffer;
		int currentScope;
	public:
		PrimitiveBuffer();
		void AddPrimitive(const TYPE_PRIMITIVE* type, double n, std::string& name);
		void AddPrimitive(const TYPE_PRIMITIVE* type, const char* s, std::string& name);
		void AddPrimitive(const TYPE_PRIMITIVE* type, bool b, std::string& name);
		void IncreaseScope();
		void DescreaseScope();
		Primitive* GetByName(std::string& name);
};