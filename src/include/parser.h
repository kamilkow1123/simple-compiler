#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include "syntaxTree.h"

class Parser{
private:
    Lexer *lexer;
    Token *token;

public:
    Parser(Lexer *lexer);
    Token *parser_eat(Type type);
    SyntaxTree *parser_parse();
    SyntaxTree *parser_parse_id();
    SyntaxTree *parser_parse_block();
    SyntaxTree *parser_parse_list();
    SyntaxTree *parser_parse_int();
    SyntaxTree *parser_parse_expression();
    SyntaxTree *parser_parse_compound();
};

#endif