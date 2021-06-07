#include <iostream>
// #include<format>
#include "include/as_frontend.h"
using namespace std;

string section_data = ".data\n";
int string_counter = 1;
string section_bss = ".bss\n";
string constants = "";

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
    string s = "";

    string var_name = st->getName();
    string value = ((SyntaxTree *)st->getValue()->getChildren()->getItems(0))->getName();

    string assign_string = var_name + ": .ascii \"" + value + "\"\n" + var_name + "_len = .- " + var_name + "\n";

    section_data += assign_string;

    return s;
}

string as_f_variable(SyntaxTree *st)
{
    string s = "";

    string value = st->getName();

    string var_declaration = value + ": .space " + value + "_len\n";

    section_bss += var_declaration;

    constants += value + "_len = 200\n";

    return s;
}

string as_f_call(SyntaxTree *st)
{
    string s = "";
    if (st->getName() == "return")
    {
        // SyntaxTree *first_arg = nullptr;
        // if(st->getValue()->getChildren()->getSize()) first_arg = (SyntaxTree*)st->getValue()->getChildren()->getItems(0);
        SyntaxTree *first_arg = (SyntaxTree *)(st->getValue()->getChildren()->getSize() ? st->getValue()->getChildren()->getItems(0) : nullptr);

        const string temp = "mov $" + to_string(first_arg ? first_arg->getIntValue() : 0) + ", \%eax\n";

        s += temp;
        return s;
    }

    if (st->getName() == "print")
    {
        int num_of_arg = ((SyntaxTree *)st->getValue()->getChildren()->getItems(0))->getChildren()->getSize();

        for (int i = 0; i < num_of_arg; i++)
        {

            SyntaxTree *print_arg = ((SyntaxTree *)((SyntaxTree *)st->getValue()->getChildren()->getItems(0))->getChildren()->getItems(i));

            if (print_arg->getType() == ST_STRING)
            {
                string value = ((SyntaxTree *)((SyntaxTree *)st->getValue()->getChildren()->getItems(0))->getChildren()->getItems(i))->getName();

                string define = "text" + to_string(string_counter) + ": .ascii \"" + value + "\"\n"
                                                                                             "text" +
                                to_string(string_counter) + "_len = .- text" + to_string(string_counter) + "\n";

                const string print = "mov $4, %eax\n"
                                     "mov $1, %ebx\n"
                                     "mov $text" +
                                     to_string(string_counter) + ", %ecx\n"
                                                                 "mov $text" +
                                     to_string(string_counter) + "_len, %edx\n"
                                                                 "int $0x80\n";

                string_counter++;

                s += print;
                section_data += define;
            }
            else if (print_arg->getType() == ST_VARIABLE)
            {
                string var_name = print_arg->getName();
                const string print = "mov $4, %eax\n"
                                     "mov $1, %ebx\n"
                                     "mov $" +
                                     var_name + ", %ecx\n"
                                                "mov $" +
                                     var_name + "_len, %edx\n"
                                                "int $0x80\n";

                s += print;
            }
        }

        return s;
    }

    if (st->getName() == "scan")
    {
        SyntaxTree *print_arg = ((SyntaxTree *)((SyntaxTree *)st->getValue()->getChildren()->getItems(0))->getChildren()->getItems(0));
        if (print_arg->getType() == ST_VARIABLE)
        {
            string var_name = print_arg->getName();
            const string scan = "mov $3, %eax\n"
                                "mov $0, %ebx\n"
                                "mov $" +
                                var_name + ", %ecx\n"
                                           "mov $" +
                                var_name + "_len, %edx\n"
                                           "int $0x80\n";

            s += scan;
        }

        return s;
    }

    s += "call " + st->getName() + "\n";

    return s;
}

string as_f_function(SyntaxTree *st)
{
    string s;

    if (st->getValue()->getType() == ST_CALL)
    {
        string call_func = as_f_call(st);
        return call_func;
    }

    const string temp = ".global " + st->getName() + "\n" + st->getName() + ":\n";

    s = temp;

    SyntaxTree *as_val = st->getValue();

    string as_val_val = as_f(as_val->getValue());

    s += as_val_val;
    s += "ret\n";

    return s;
}

string as_f_int(SyntaxTree *st)
{
    return "";
}

string as_f_root(SyntaxTree *st)
{
    const string section_text = ".text\n"
                                ".global _start\n"
                                "_start:\n"
                                "call main\n"
                                "mov \%eax, \%ebx\n"
                                "mov $1, \%eax\n"
                                "int $0x80\n\n";

    string value = section_text;

    string next_value = as_f(st);
    value += next_value;
    string result = "";
    result += constants;
    result += section_data;
    result += section_bss;
    result += value;
    return result;
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
        break;
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