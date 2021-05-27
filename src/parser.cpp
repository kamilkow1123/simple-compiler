#include "include/parser.h"
#include <string>
#include "types.cpp"

Parser::Parser(Lexer *lexer)
{
    this->lexer = lexer;
    this->token = lexer->lexer_next_token();
}

Token *Parser::parser_eat(Type type)
{

    if (this->token->getType() != type)
    {
        cout << "[Parser]: Unexpected token: " << this->token->getType() << endl;
        exit(1);
    }

    this->token = this->lexer->lexer_next_token();
    return this->token;
}

SyntaxTree *Parser::parser_parse()
{
    return this->parser_parse_compound();
}

SyntaxTree *Parser::parser_parse_id()
{
    string value = this->token->getValue();
    this->parser_eat(TOKEN_ID);

    if (this->token->getType() == TOKEN_EQUALS)
    {
        this->parser_eat(TOKEN_EQUALS);
        SyntaxTree *st = new SyntaxTree(ST_ASSIGNMENT);
        st->setName(value);
        // cout<<st->getName()<<endl;
        st->setValue(this->parser_parse_expression());
        // cout << (st->getValue())->getName();
        return st;
    }

    SyntaxTree *st = new SyntaxTree(ST_VARIABLE);
    st->setName(value);

    if (this->token->getType() == TOKEN_COLON)
    {
        this->parser_eat(TOKEN_COLON);

        while (this->token->getType() == TOKEN_ID)
        {
            st->setDataType(typename_to_int(this->token->getValue()));
            this->parser_eat(TOKEN_ID);

            if (this->token->getType() == TOKEN_LT)
            {
                this->parser_eat(TOKEN_LT);
                st->setDataType(st->getDataType() + typename_to_int(this->token->getValue()));
                this->parser_eat(TOKEN_ID);
                this->parser_eat(TOKEN_GT);
            }
        }
    }
    else
    {
        if (this->token->getType() == TOKEN_LEFT_PAREN)
        {
            st->setType(ST_CALL);
            st->setValue(this->parser_parse_list());
        }
    }

    return st;
}

SyntaxTree *Parser::parser_parse_block()
{
    this->parser_eat(TOKEN_LEFT_BRACE);
    SyntaxTree *st = new SyntaxTree(ST_COMPOUND);

    while (this->token->getType() != TOKEN_RIGHT_BRACE)
    {
        (st->getChildren())->list_push(this->parser_parse_expression());
    }

    this->parser_eat(TOKEN_RIGHT_BRACE);

    return st;
}

SyntaxTree *Parser::parser_parse_list()
{
    this->parser_eat(TOKEN_LEFT_PAREN);

    SyntaxTree *st = new SyntaxTree(ST_COMPOUND);

    (st->getChildren())->list_push(this->parser_parse_expression());

    while (this->token->getType() == TOKEN_COMMA)
    {
        this->parser_eat(TOKEN_COMMA);
        (st->getChildren())->list_push(this->parser_parse_expression());
    }

    this->parser_eat(TOKEN_RIGHT_PAREN);

    if (this->token->getType() == TOKEN_COLON)
    {
        this->parser_eat(TOKEN_COLON);

        while (this->token->getType() == TOKEN_ID)
        {
            st->setDataType(typename_to_int(this->token->getValue()));
            this->parser_eat(TOKEN_ID);

            if (this->token->getType() == TOKEN_LT)
            {
                this->parser_eat(TOKEN_LT);
                st->setDataType(st->getDataType() + typename_to_int(this->token->getValue()));
                this->parser_eat(TOKEN_ID);
                this->parser_eat(TOKEN_GT);
            }
        }
    }

    if (this->token->getType() == TOKEN_ARROW_RIGHT)
    {
        this->parser_eat(TOKEN_ARROW_RIGHT);
        st->setType(ST_FUNCTION);
        st->setValue(this->parser_parse_compound());
    }

    return st;
}

SyntaxTree *Parser::parser_parse_int()
{
    int int_value = stoi(this->token->getValue());
    this->parser_eat(TOKEN_INT);

    SyntaxTree *st = new SyntaxTree(ST_INT);
    st->setIntValue(int_value);

    return st;
}

SyntaxTree *Parser::parser_parse_expression()
{
    switch (this->token->getType())
    {
    case TOKEN_ID:
        return this->parser_parse_id();
    case TOKEN_LEFT_PAREN:
        return this->parser_parse_list();
    case TOKEN_INT:
        return this->parser_parse_int();
    default:
    {
        cout << "[Parser]: Unexpected token: '" << this->token->getValue() << "'" << endl;
        exit(1);
    }
    }
}

SyntaxTree *Parser::parser_parse_compound()
{
    bool should_close = false;

    if (this->token->getType() == TOKEN_LEFT_BRACE)
    {
        this->parser_eat(TOKEN_LEFT_BRACE);
        should_close = true;
    }

    SyntaxTree *compound = new SyntaxTree(ST_COMPOUND);

    while (this->token->getType() != TOKEN_END_OF_FILE && this->token->getType() != TOKEN_RIGHT_BRACE)
    {
        (compound->getChildren())->list_push(this->parser_parse_expression());

        if (this->token->getType() == TOKEN_SEMICOLON)
        {
            this->parser_eat(TOKEN_SEMICOLON);
        }
    }

    if (should_close)
    {
        this->parser_eat(TOKEN_RIGHT_BRACE);
    }

    return compound;
}
