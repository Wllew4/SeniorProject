#include "Exec.h"
#include <iostream>

void Exec(StmtNode* statement){
    switch(statement->type){
        case StmtNodeType::STMT_PRINT:
            std::cout << statement->val.print.expr_string->val.string.value;
            return;
        case StmtNodeType::STMT_PRINTLN:
            std::cout << statement->val.print.expr_string->val.string.value << std::endl;
            return;
    }
}