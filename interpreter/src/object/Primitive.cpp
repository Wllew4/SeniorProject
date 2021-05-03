#include "object/Primitive.h"

Primitive::Primitive(TYPE_PRIMITIVE type, Data* data, const char* name)
	: m_type(type), m_data(data), m_name(name)
{
	
}

const char* Primitive::asString()
{
	return Eval::toString(&m_data);
}

double* Primitive::asNum()
{
	return Eval::toNum(&m_data);
}

bool* Primitive::asBool()
{
	return Eval::toBool(&m_data);
}

void setValue(Data* val)
{
	switch(m_type){
		case TYPE_NUM:
			m_data.num = Eval::toNum(val);
			break;
			case TYPE_STRING:
			m_data.string = Eval::toString(val);
			break;
		case TYPE_BOOL:
			m_data.boolean = Eval::toBool(val);
			break;
	}
}

const char* getName()
{
	return m_name;
}