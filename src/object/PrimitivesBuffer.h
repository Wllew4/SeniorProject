#pragma once

#include "object/Primitive.h"

#include <vector>

class PrimitiveBuffer {
public:
	PrimitiveBuffer();

	void AddPrimitive(const PrimitiveType _type, double _num,			std::string& _name);
	void AddPrimitive(const PrimitiveType _type, std::string _string,	std::string& _name);
	void AddPrimitive(const PrimitiveType _type, bool _bool,			std::string& _name);

	void IncreaseScope();
	void DescreaseScope();

	Primitive& GetByName(std::string& _name);

private:
	std::vector<std::vector<Primitive>> m_buffer;
	unsigned int m_currentScope;
};