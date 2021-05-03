#pragma once

enum TYPE_PRIMITIVE {
	TYPE_NUM,
	TYPE_STRING,
	TYPE_BOOL
};

union Data {
	double* num;
	const char* string;
	bool* boolean;
};

class Primitive {
	private:
		const TYPE_PRIMITIVE* m_type;
		Data m_data;
		const char* m_name;
	public:
		Primitive(const TYPE_PRIMITIVE* type, double* n, const char* name);
		Primitive(const TYPE_PRIMITIVE* type, const char* s, const char* name);
		Primitive(const TYPE_PRIMITIVE* type, bool* b, const char* name);
		~Primitive();
		const char* asString();
		double* asNum();
		bool* asBool();
		void setValue(double* val);
		void setValue(const char* val);
		void setValue(bool* val);
		const char* getName();
		const TYPE_PRIMITIVE* getType();
		Data* getData();
};