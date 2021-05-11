#include "object/Primitive.h"
#include "executor/Eval.h"
#include "util/Log.h"

Primitive::Primitive(const TYPE_PRIMITIVE* type, double n, const char* name)
	: m_type(type), m_name(name)
{
	m_data.num = n;
}

Primitive::Primitive(const TYPE_PRIMITIVE* type, const char* s, const char* name)
	: m_type(type), m_name(name)
{
	m_data.string = s;
}

Primitive::Primitive(const TYPE_PRIMITIVE* type, bool b, const char* name)
	: m_type(type), m_name(name)
{
	m_data.boolean = b;
}

Primitive::Primitive(const Primitive& r)
	: m_type(r.m_type), m_name(r.m_name)
{
	switch(*r.m_type)
	{
		case TYPE_PRIMITIVE::TYPE_NUM:
			m_data.num = r.m_data.num;
			break;
		case TYPE_PRIMITIVE::TYPE_STRING:
			m_data.string = r.m_data.string;
			break;
		case TYPE_PRIMITIVE::TYPE_BOOL:
			m_data.boolean = r.m_data.boolean;
			break;
	}
}

Primitive::~Primitive()
{
	delete m_type;
	delete m_name;
}

double Primitive::asNum()
{
	if(*m_type == TYPE_PRIMITIVE::TYPE_NUM)
		return m_data.num;
	else Log::CannotImplicitlyConvert(*m_type, TYPE_PRIMITIVE::TYPE_NUM);
	return 0;
}

const char* Primitive::asString()
{
	return Eval::toString(this);
}

bool Primitive::asBool()
{
	return Eval::toBool(this);
}

void Primitive::setValue(double val)
{
	m_data.num = val;
}

void Primitive::setValue(const char* val)
{
	m_data.string = val;
	delete val;
}

void Primitive::setValue(bool val)
{
	m_data.boolean = val;
}

const char* Primitive::getName()
{
	return m_name;
}

const TYPE_PRIMITIVE* Primitive::getType()
{
	return m_type;
}

Data& Primitive::getData()
{
	return m_data;
}