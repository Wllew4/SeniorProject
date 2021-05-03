#pragma once

enum TYPE_PRIMITIVE {
	TYPE_NUM,
	TYPE_STRING,
	TYPE_BOOL
}

union Data {
	double* num;
	const char* string;
	bool* boolean;
}

class Primitive {
	private:
		TYPE_PRIMITIVE m_type;
		Data m_data;
		const char* m_name;
	public:
		Primitive(TYPE_PRIMITIVE type, Data* data, const char* name);
		const char* asString();
		double* asNum();
		bool* asBool();
		void setValue(Data* val);
		const char* getName();
};