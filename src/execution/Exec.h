#include "ast/parsing/StmtNode.h"

namespace Exec
{
	void Init(char* file);

	void Execute(std::shared_ptr<StmtNode> statement);
}