#include <iostream>
// #include<format>
#include "include/as_frontend.h"
using namespace std;

string as_f_compound(SyntaxTree *st)
{
    string value = "";
    for (int i = 0; i < (int)st->getChildren()->getSize(); i++)
    {
        SyntaxTree *child = (SyntaxTree *)st->getChildren()->getItems(i);
        string next_value = as_f(child);
        value += next_value;
    }
    return value;
}

string as_f_assignment(SyntaxTree *st)
{
    string s;
    if (st->getValue()->getType() == ST_FUNCTION)
    {
        const string temp = ".global " + st->getName() + "\n" + st->getName() + ":\n";

        s = temp;

        SyntaxTree *as_val = st->getValue();

        string as_val_val = as_f(as_val->getValue());

        s += as_val_val;
    }

    return s;
}

string as_f_function(SyntaxTree *st)
{
    string s;
    const string temp = ".global " + st->getName() + "\n" + st->getName() + ":\n";

    s = temp;

    SyntaxTree *as_val = st->getValue();

    string as_val_val = as_f(as_val->getValue());

    s += as_val_val;

    return s;
}

string as_f_variable(SyntaxTree *st)
{
    return "";
}

string as_f_call(SyntaxTree *st)
{
    string s = "";

    if (st->getName() == "return")
    {
        // SyntaxTree *first_arg = nullptr;
        // if(st->getValue()->getChildren()->getSize()) first_arg = (SyntaxTree*)st->getValue()->getChildren()->getItems(0);
        SyntaxTree *first_arg = (SyntaxTree *)(st->getValue()->getChildren()->getSize() ? st->getValue()->getChildren()->getItems(0) : nullptr);

        const string temp = "mov $" + to_string(first_arg ? first_arg->getIntValue() : 0) + ", \%eax\n"
                                                                                            "ret\n";

        s += temp;
    }

    return s;
}

string as_f_int(SyntaxTree *st)
{
    return "";
}

string as_f_root(SyntaxTree *st)
{
    const string section_text = ".section .text\n"
                                ".global _start\n"
                                "_start:\n"
                                "call main\n"
                                "mov \%eax, \%ebx\n"
                                "mov $1, \%eax\n"
                                "int $0x80\n\n";

    string value = section_text;

    string next_value = as_f(st);
    value += next_value;
    return value;
}

string as_f(SyntaxTree *st)
{
    string value = "";
    string next_value = "";
    switch (st->getType())
    {
    case ST_COMPOUND:
        next_value = as_f_compound(st);
        break;
    case ST_ASSIGNMENT:
        next_value = as_f_assignment(st);
        break;
    case ST_VARIABLE:
        next_value = as_f_variable(st);
        break;
    case ST_CALL:
        next_value = as_f_call(st);
        break;
    case ST_INT:
        next_value = as_f_int(st);
        break;
    case ST_FUNCTION:
        next_value = as_f_function(st);
    default:
    {
        cout << "[As frontend]: No frontend for ST of type " << st->getType() << endl;
        exit(1);
        break;
    }
    }

    value += next_value;

    return value;
}