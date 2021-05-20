#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_
#include<iostream>
#include "../list.cpp"
using namespace std;

enum SyntaxType
{
    ST_COMPOUND,
    ST_FUNCTION,
    ST_CALL,
    ST_ASSIGNMENT,
    ST_DEFINITION_TYPE,
    ST_VARIABLE,
    ST_STATEMENT,
    ST_INT,
    ST_NOOP, // No operation
};

class SyntaxTree
{
private:
    SyntaxType type;
    List *children;
    string name;
    SyntaxTree *value;
    int int_value;
    int data_type;
public:
    SyntaxTree(SyntaxType);
    void setName(string);
    string getName();
    void setValue(SyntaxTree*);
    SyntaxTree *getValue();
    void setDataType(int);
    int getDataType();
    SyntaxType getType();
    void setType(SyntaxType);
    List* getChildren() {return this->children;}
    void setIntValue(int);
    int getIntValue(){return this->int_value;};
};

#endif