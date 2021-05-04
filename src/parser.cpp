#include "include/parser.h"

Parser::Parser(Lexer *lexer){
    this->lexer = lexer;
    this->token = lexer->lexer_next_token();
}

Token *Parser::parser_eat(Type type){

    if(this->token->getType() != type){
        cout<<"[Parser]: Unexpected token: "<<this->token->getType()<<endl;
        exit(1);
    }

    this->token = this->lexer->lexer_next_token();
    return this->token;
}

SyntaxTree *Parser::parser_parse(){
    return new SyntaxTree(ST_NOOP);
}

SyntaxTree *Parser::parser_parse_expression(){
    SyntaxTree *expression = new SyntaxTree(ST_EXPRESSION);

    while(this->token->getType() != TOKEN_END_OF_FILE){
        SyntaxTree *child = parser_parse();
    }

    return new SyntaxTree(ST_NOOP);
}
