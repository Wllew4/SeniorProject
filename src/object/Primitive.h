#pragma once

#include <string>

enum PrimitiveType {
	Num,
	String,
	Bool
};

union Data {
	Data(){}
	~Data(){}
	double num;
	std::string string;
	bool boolean;
};

class Primitive {
public:
	Primitive(const Primitive& _result);
	~Primitive();

	Primitive(const PrimitiveType _type, double _num, std::string _name);
	Primitive(const PrimitiveType _type, std::string _string, std::string _name);
	Primitive(const PrimitiveType _type, bool _bool, std::string _name);

	std::string AsString();
	double		AsNum();
	bool		AsBool();

	void SetValue(double _val);
	void SetValue(std::string _val);
	void SetValue(bool _val);

	std::string&		GetName();
	const PrimitiveType GetType();
	Data&				GetData();

private:
	const PrimitiveType m_type;
	Data m_data;
	std::string m_name;
};