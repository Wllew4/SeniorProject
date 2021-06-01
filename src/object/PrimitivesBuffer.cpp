#include "object/PrimitivesBuffer.h"
#include "debug/Log.h"
#include "ast/lexing/Lexer.h"

PrimitiveBuffer::PrimitiveBuffer()
{
	m_currentScope = 0;
	m_buffer.resize(1);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, double n, std::string& name)
{
	m_buffer.at(m_currentScope).emplace_back(type, n, name);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, std::string s, std::string& name)
{
	m_buffer.at(m_currentScope).emplace_back(type, s, name);
}

void PrimitiveBuffer::AddPrimitive(const TYPE_PRIMITIVE type, bool b, std::string& name)
{
	m_buffer.at(m_currentScope).emplace_back(type, b, name);
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

Primitive& PrimitiveBuffer::GetByName(std::string& name)
{
	for (unsigned int i = m_buffer.size() - 1; i >= 0; i--)
	{
		for (unsigned int j = 0; j < m_buffer.at(i).size(); j++)
			if (m_buffer.at(i).at(j).getName() == name)
				return m_buffer.at(i).at(j);
	}

	Debug::Log::UnhandledException(201)
		<< "Unrecognized identifier: "
		<< name << '\n';
}