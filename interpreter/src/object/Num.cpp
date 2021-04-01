#include "object/Num.h"
#include "object/ObjectBuffer.h"
#include "util/Math.h"
#include "executor/Eval.h"

#include <string>
#include <vector>

extern ObjectBuffer ProgramBuffer;

std::string Num::getString(){
    return std::to_string(this->getValue());
}

void Num::setValue(double x){
    m_value = x;
}

double Num::getValue(){
    return m_value;
}