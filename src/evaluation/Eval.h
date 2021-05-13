#pragma once

#include "ast/parsing/ExprNode.h"
#include "object/Primitive.h"
#include "program/Program.h"

namespace Eval {
    double      EvalNumExpr     (ExprNode* node);
    std::string EvalStringExpr  (ExprNode* node);
    bool        EvalBoolExpr    (ExprNode* node);

    std::string toString        (Primitive* val);
    bool        toBool          (Primitive* val);

    namespace {
        PrimitiveBuffer* buffer = program.GetBuffer();
    }
};