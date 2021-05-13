#include "include/syntaxTree.h"

SyntaxTree::SyntaxTree(SyntaxType type){
    this->type = type;

    if(type == ST_COMPOUND){
        this->children = new List(sizeof(SyntaxTree*));
    }
}

void SyntaxTree::setName(string name){
    this->name = name;
}

string SyntaxTree::getName(){
    return this->name;
}

void SyntaxTree::setValue(SyntaxTree *value){
    this->value = value;
}

SyntaxTree *SyntaxTree::getValue(){
    return this->value;
}

void SyntaxTree::setDataType(int data){
    this->data_type = data;
}

int SyntaxTree::getDataType(){
    return this->data_type;
}

SyntaxType SyntaxTree::getType(){
    return this->type;
}

void SyntaxTree::setType(SyntaxType type){
    this->type = type;
}

void SyntaxTree::setIntValue(int int_value){
    this->int_value = int_value;
}