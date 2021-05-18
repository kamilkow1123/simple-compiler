#include "include/sowa.h"
#include "lexer.cpp"
#include "parser.cpp"
#include "as_frontend.cpp"

void sowa_compile(string src){
    Lexer *lexer = new Lexer(src);
    Parser *parser = new Parser(lexer);
    SyntaxTree *root = parser->parser_parse();

    string s = as_f(root);

    cout<<s<<endl;

    Token *token = 0;

    while((token = lexer->lexer_next_token())->getType() != TOKEN_END_OF_FILE)
    {
        cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
    }
//   cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
}