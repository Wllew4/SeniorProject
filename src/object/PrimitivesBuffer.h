#pragma once
#include "object/Primitive.h"
#include <vector>

class PrimitiveBuffer {
	private:
		std::vector<std::vector<Primitive>> m_buffer;
		int m_currentScope;
	public:
		PrimitiveBuffer();
		void AddPrimitive(const TYPE_PRIMITIVE type, double n, std::string& name);
		void AddPrimitive(const TYPE_PRIMITIVE type, std::string s, std::string& name);
		void AddPrimitive(const TYPE_PRIMITIVE type, bool b, std::string& name);
		void IncreaseScope();
		void DescreaseScope();
		Primitive& GetByName(std::string& name);
};