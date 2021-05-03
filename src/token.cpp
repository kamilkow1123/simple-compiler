#include "include/token.h"

Token::Token(string value, Type type){
  this->value = value;
  this->type = type;
}

Type Token::getType()
{
  return this->type;
}

string Token::getValue()
{
  return this->value;
}