#include "include/sowa.h"
// #include "include/lexer.h"
#include "lexer.cpp"

void sowa_compile(string src){
  Lexer *lexer = new Lexer(src);
  Token *token = 0;

  while((token = lexer->lexer_next_token())->getType() != TOKEN_END_OF_FILE)
  {
    cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
  }
  // cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
}