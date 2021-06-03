#pragma once

#include "ast/parsing/Parser.h"
#include "ast/parsing/StmtNode.h"
#include "evaluation/Eval.h"

class Exec
{
public:
	Exec(PrimitiveBuffer& _program);
	void Init(char* _file);

private:
	Parser m_parser;
	Eval m_eval;
	void Execute(std::shared_ptr<StmtNode> _statement);
};