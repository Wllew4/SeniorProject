#include "object/PrimitivesBuffer.h"

#include "ast/lexing/Lexer.h"
#include "debug/Log.h"

PrimitiveBuffer::PrimitiveBuffer()
{
	m_currentScope = 0;
	m_buffer.resize(1);
}

void PrimitiveBuffer::AddPrimitive(const PrimitiveType _type, double _num, std::string& _name)
{
	m_buffer.at(m_currentScope).emplace_back(_type, _num, _name);
}

void PrimitiveBuffer::AddPrimitive(const PrimitiveType _type, std::string _string, std::string& _name)
{
	m_buffer.at(m_currentScope).emplace_back(_type, _string, _name);
}

void PrimitiveBuffer::AddPrimitive(const PrimitiveType _type, bool _bool, std::string& _name)
{
	m_buffer.at(m_currentScope).emplace_back(_type, _bool, _name);
}

void PrimitiveBuffer::IncreaseScope()
{
	m_buffer.emplace_back();
	m_currentScope++;
}

void PrimitiveBuffer::DescreaseScope()
{
	m_buffer.pop_back();
	m_buffer.shrink_to_fit();
	m_currentScope--;
}

Primitive& PrimitiveBuffer::GetByName(std::string& _name)
{
	for (unsigned int i = m_buffer.size() - 1; i >= 0; i--)
	{
		for (unsigned int j = 0; j < m_buffer.at(i).size(); j++)
			if (m_buffer.at(i).at(j).GetName() == _name)
				return m_buffer.at(i).at(j);
	}

	Debug::Log::UnhandledException(201)
		<< "Unrecognized identifier: "
		<< _name << '\n';
	exit(201);
}