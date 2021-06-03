#include "object/Primitive.h"

#include "debug/Log.h"
#include "evaluation/Eval.h"

#include <iostream>

Primitive::Primitive(const PrimitiveType _type, double _num, std::string _name)
	: m_type(_type), m_name(_name)
{
	m_data.num = _num;
}

Primitive::Primitive(const PrimitiveType _type, std::string _string, std::string _name)
	: m_type(_type), m_name(_name)
{
	m_data.string = _string;
}

Primitive::Primitive(const PrimitiveType _type, bool _bool, std::string _name)
	: m_type(_type), m_name(_name)
{
	m_data.boolean = _bool;
}

Primitive::Primitive(const Primitive& _result)
	: m_type(_result.m_type), m_name(_result.m_name)
{
	switch(_result.m_type)
	{
		case PrimitiveType::Num:
			m_data.num = _result.m_data.num;
			break;
		case PrimitiveType::String:
			m_data.string = _result.m_data.string;
			break;
		case PrimitiveType::Bool:
			m_data.boolean = _result.m_data.boolean;
			break;
	}
}

Primitive::~Primitive()
{
}

double Primitive::AsNum()
{
	if(m_type == PrimitiveType::Num)
		return m_data.num;
	else
	{
		Debug::Log::UnhandledException(202)
			<< "Could not implicity convert object of type "
			<< m_type
			<< " to Num";
		exit(202);
	}
	return 0;
}

std::string Primitive::AsString()
{
	return Eval::ToString(this);
}

bool Primitive::AsBool()
{
	return Eval::ToBool(this);
}

void Primitive::SetValue(double val)
{
	m_data.num = val;
}

void Primitive::SetValue(std::string val)
{
	m_data.string = val;
}

void Primitive::SetValue(bool val)
{
	m_data.boolean = val;
}

std::string& Primitive::GetName()
{
	return m_name;
}

const PrimitiveType Primitive::GetType()
{
	return m_type;
}

Data& Primitive::GetData()
{
	return m_data;
}