#pragma once

#include "ast/parsing/StmtNode.h"
#include "ast/parsing/Parser.h"

class Exec
{
	public:
	void Init(char* file);

	private:
	Parser p;
	void Execute(std::shared_ptr<StmtNode> statement);
};