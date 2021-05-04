#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_

enum SyntaxType
{
    ST_EXPRESSION,
    ST_FUNCTION_DEFINITION,
    ST_CALL,
    ST_VARIABLE,
    ST_STATEMENT_RETURN,
    ST_NOOP, // No operation
};

class SyntaxTree
{
private:
    SyntaxType type;
public:
    SyntaxTree(SyntaxType);
};

#endif