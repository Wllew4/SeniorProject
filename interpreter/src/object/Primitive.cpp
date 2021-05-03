#include "object/Primitive.h"
#include "executor/Eval.h"
#include "util/Log.h"

Primitive::Primitive(const TYPE_PRIMITIVE* type, double* n, const char* name)
	: m_type(type), m_name(name)
{
	m_data.num = n;
}

Primitive::Primitive(const TYPE_PRIMITIVE* type, const char* s, const char* name)
	: m_type(type), m_name(name)
{
	m_data.string = s;
}

Primitive::Primitive(const TYPE_PRIMITIVE* type, bool* b, const char* name)
	: m_type(type), m_name(name)
{
	m_data.boolean = b;
}

Primitive::~Primitive()
{
	delete m_type;
	delete m_name;
	delete this;
}

double* Primitive::asNum()
{
	if(*m_type == TYPE_PRIMITIVE::TYPE_NUM)
		return m_data.num;
	else Log::CannotImplicitlyConvert(*m_type, TYPE_PRIMITIVE::TYPE_NUM);
	return nullptr;
}

const char* Primitive::asString()
{
	return Eval::toString(this);
}

bool* Primitive::asBool()
{
	return Eval::toBool(this);
}

void Primitive::setValue(double* val)
{
	delete m_data.num;
	m_data.num = val;
}

void Primitive::setValue(const char* val)
{
	delete m_data.string;
	m_data.string = val;
}

void Primitive::setValue(bool* val)
{
	delete m_data.boolean;
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

Data* Primitive::getData()
{
	return &m_data;
}