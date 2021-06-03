#pragma once

class Math
{
public:
	Math(const Math&) = delete;
	const Math& GetInstance();

	static double Modulus(double x, double y);

private:
	Math() {}
};