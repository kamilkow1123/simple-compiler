#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_
#include "../list.cpp"

enum SyntaxType
{
    ST_COMPOUND,
    ST_FUNCTION,
    ST_ASSIGNMENT,
    ST_CALL,
    ST_VARIABLE,
    ST_STATEMENT_RETURN,
    ST_NOOP, // No operation
};

class SyntaxTree
{
private:
    SyntaxType type;
    List *children;
    string name;
    SyntaxTree *value;
    int data_type;
public:
    SyntaxTree(SyntaxType);
    void setName(string);
    string getName();
    void setValue(SyntaxTree*);
    SyntaxTree *getValue();
    void setDataType(int);
    List* getChildren() {return this->children;}
};

#endif