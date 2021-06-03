#pragma once

#include "ast/parsing/ExprNode.h"
#include "object/PrimitivesBuffer.h"

class Eval
{
public:
    Eval(PrimitiveBuffer& _program);

    PrimitiveBuffer& GetBuffer();

    double      EvalNumExpr     (ExprNode* _node);
    std::string EvalStringExpr  (ExprNode* _node);
    bool        EvalBoolExpr    (ExprNode* _node);

    static std::string ToString (Primitive* _val);
    static bool        ToBool   (Primitive* _val);

private:
    PrimitiveBuffer& m_buffer;
};