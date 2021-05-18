#include<iostream>
#include "include/syntaxTree.h"
using namespace std;

string as_f_compound(SyntaxTree *st){
    string value = "";
    for(int i = 0; i < (int) st->getChildren()->getSize(); i++){
        SyntaxTree *child = (SyntaxTree*) st->getChildren()->getItems(i);
        string next_value = as_f(child);
        value += next_value;
    }
    return value;
}

string as_f_assignment(SyntaxTree *st){
    const string example = "mov $128, \%eax";
    string s = example;

    return s;
}

string as_f_variable(SyntaxTree *st){

}

string as_f_call(SyntaxTree *st){

}

string as_f_int(SyntaxTree *st){

}

string as_f(SyntaxTree *st){
    string value = "";
    string next_value = "";

    switch(st->getType()){
        case ST_COMPOUND: next_value = as_f_compound(st); break;
        case ST_ASSIGNMENT: next_value = as_f_assignment(st); break;
        case ST_VARIABLE: next_value = as_f_variable(st); break;
        case ST_CALL: next_value = as_f_call(st); break;
        case ST_INT: next_value = as_f_int(st); break;
        default: {
            cout<<"[As frontend]: No frontend for ST of type "<<st->getType()<<endl;
            exit(1);
            break;
        }
    }

    value += next_value;

    return value;
}