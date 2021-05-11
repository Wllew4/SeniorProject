#pragma once

#include <string>

enum TYPE_PRIMITIVE {
	TYPE_NUM,
	TYPE_STRING,
	TYPE_BOOL
};

union Data {
	Data(){}
	~Data(){}
	double num;
	std::string string;
	bool boolean;
};

class Primitive {
	private:
		const TYPE_PRIMITIVE* m_type;
		Data m_data;
		std::string m_name;
	public:
		Primitive(const TYPE_PRIMITIVE* type, double n, 	const char* name);
		Primitive(const TYPE_PRIMITIVE* type, const char* s,const char* name);
		Primitive(const TYPE_PRIMITIVE* type, bool b, 		const char* name);
		Primitive(const Primitive& r);
		~Primitive();
		const char* asString();
		double asNum();
		bool asBool();
		void setValue(double val);
		void setValue(std::string val);
		void setValue(bool val);
		std::string& getName();
		const TYPE_PRIMITIVE* getType();
		Data& getData();
};