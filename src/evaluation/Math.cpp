#include "Math.h"

const Math& Math::GetInstance()
{
    static Math s_instance;
    return s_instance;
}

double Math::Modulus (double x, double y){
    double r = x < 0 ? -x : x;
    while (r >= y) r = r - y;
    if(x < 0) return -r;
    return r;
}