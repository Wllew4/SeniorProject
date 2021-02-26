#pragma once
#include <vector>

#include "Token.h"

enum NodeType {
    N_PRINT,
    N_PRINTLN
};

struct Node {
    std::vector<Token> tokens;
    NodeType type;

    void parseNode (){
        switch(type){

        }
    }
};