#include "object/Num.h"
#include <string>

std::string Num::getString(){
    return std::to_string(*this->getValue());
}