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
		const TYPE_PRIMITIVE m_type;
		Data m_data;
		std::string m_name;
	public:
		Primitive(const TYPE_PRIMITIVE type, double n,		std::string name);
		Primitive(const TYPE_PRIMITIVE type, std::string s,std::string name);
		Primitive(const TYPE_PRIMITIVE type, bool b,		std::string name);
		Primitive(const Primitive& r);
		~Primitive();
		std::string asString();
		double asNum();
		bool asBool();
		void setValue(double val);
		void setValue(std::string val);
		void setValue(bool val);
		std::string& getName();
		const TYPE_PRIMITIVE getType();
		Data& getData();
};