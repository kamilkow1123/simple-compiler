#include "include/sowa.h"
#include "include/lexer.h"
#include "include/parser.h"

void sowa_compile(string src){
  Lexer *lexer = new Lexer(src);
  Parser *parser = new Parser(lexer);
  SyntaxTree *root = parser->parser_parse();

    cout<<endl<<root<<endl;

//   Token *token = 0;

//   while((token = lexer->lexer_next_token())->getType() != TOKEN_END_OF_FILE)
//   {
//     cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
//   }
  // cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
}