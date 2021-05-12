#include "include/parser.h"
#include "types.cpp"

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
    return this->parser_parse_compound();
}

SyntaxTree *Parser::parser_parse_id(){
    string value = this->token->getValue();
    this->parser_eat(TOKEN_ID);

    if(this->token->getType() == TOKEN_EQUALS){
        this->parser_eat(TOKEN_EQUALS);
        SyntaxTree *st = new SyntaxTree(ST_ASSIGNMENT);
        st->setName(value);
        cout<<st->getName()<<endl;
        st->setValue(this->parser_parse_expression());
        // cout << (st->getValue())->getName();
        return st;
    }
    
    SyntaxTree *st = new SyntaxTree(ST_VARIABLE);
    st->setName(value);
    
    if(this->token->getType() == TOKEN_COLON)
    {
        this->parser_eat(TOKEN_COLON);
        st->setDataType(typename_to_int(this->token->getValue()));
        
        this->parser_eat(TOKEN_ID);
    }

    return st;
}

SyntaxTree *Parser::parser_parse_list(){
    this->parser_eat(TOKEN_LEFT_PAREN);

    SyntaxTree *compound = new SyntaxTree(ST_COMPOUND);

    (compound->getChildren())->list_push(this->parser_parse_expression());

    while(this->token->getType() == TOKEN_COMMA){
        this->parser_eat(TOKEN_COMMA);
        (compound->getChildren())->list_push(this->parser_parse_expression());
    }

    this->parser_eat(TOKEN_RIGHT_PAREN);

    return compound;
}

SyntaxTree *Parser::parser_parse_expression(){
    switch(this->token->getType()){
        case TOKEN_ID: return this->parser_parse_id();
        case TOKEN_LEFT_PAREN: return this->parser_parse_list();
        default: {
            cout<<"[Parser]: Unexpected token: '"<<this->token->getValue()<<"'"<<endl;
            exit(1);
        }
    }
}

SyntaxTree *Parser::parser_parse_compound(){
    SyntaxTree *compound = new SyntaxTree(ST_COMPOUND);

    while(this->token->getType() != TOKEN_END_OF_FILE){
        (compound->getChildren())->list_push(this->parser_parse_expression());
    }

    size_t i = (compound->getChildren())->getSize();
    cout<<i<<endl;
    while (i > 0)
    {
        cout<<((compound->getChildren())->getItems(i));
        i--;
    }

    return compound;
}
