#include "./include/lexer.h"
#include<string.h>
#include<ctype.h>
#include<algorithm>
#include "token.cpp"

int min(int a, int b){
  return (a<b) ? a : b ;
}

Lexer::Lexer(string src){
  this->src = src;
  this->i = 0;
  this->src_size = src.length();
  this->c = src[this->i];
}

void Lexer::lexer_advance()
{
    if(this->i < this->src_size && this->c != '\0')
    {
        this->i+=1;
        this->c = this->src[this->i];
    }
}

Token *Lexer::lexer_advance_with(Token *token){
	this->lexer_advance();
	return token;
}

Token *Lexer::lexer_advance_current(Type type){
	string value = "";
	value += this->c;
	Token *token = new Token(value, type);
	this->lexer_advance();
	return token;
}

void Lexer::lexer_skip_whitespace()
{
	while(this->c == 13 || this->c == 10 || this->c == ' ' || this->c =='\t')
		this->lexer_advance();
}

char Lexer::lexer_peek(int next_char){
  return this->src[min(this->i + next_char, this->src_size)];
}


// As long as the src fragment is an alphanumeric string read it, and at the end create token as TOKEN_ID with name
// RETURN EXAMPLE: ("main", 0)
Token *Lexer::lexer_parse_id(){ 
    string value = "";

    while(isalpha(this->c)){
        value += this->c;
        this->lexer_advance();
    }

    Token *token = nullptr;
    if(value == "if"){
        token = new Token(value, TOKEN_IF);
    }
    else if(value == "while"){
        token = new Token(value, TOKEN_WHILE);
    }
    else if(value == "let"){
        token = new Token(value, TOKEN_LET);
    }
    else if(value == "return"){
        token = new Token(value, TOKEN_RETURN);
    }
    else{
        token = new Token(value, TOKEN_ID);
    }

    return token;
}

Token *Lexer::lexer_parse_number(){
  string value = "";

  while(isdigit(this->c)){
    value += this->c;
    this->lexer_advance();
  }
  Token *token = new Token(value, TOKEN_INT);
  return token;
}

Token *Lexer::lexer_next_token(){
  while(this->c != '\0')
  {
    this->lexer_skip_whitespace();
    if(isalpha(this->c))
      return this->lexer_parse_id();

    if(isdigit(this->c))
      return this->lexer_parse_number();

    switch(this->c){
		case '(': return this->lexer_advance_current(TOKEN_LEFT_PAREN);
		case ')': return this->lexer_advance_current(TOKEN_RIGHT_PAREN);
		case '[': return this->lexer_advance_current(TOKEN_LEFT_BRACKET);
		case ']': return this->lexer_advance_current(TOKEN_RIGHT_BRACKET);
		case '{': return this->lexer_advance_current(TOKEN_LEFT_BRACE);
		case '}': return this->lexer_advance_current(TOKEN_RIGHT_BRACE);
		case ',': return this->lexer_advance_current(TOKEN_COMMA);
		case ';': return this->lexer_advance_current(TOKEN_SEMICOLON);
		case ':': return this->lexer_advance_current(TOKEN_COLON);
		case '+': return this->lexer_advance_current(TOKEN_PLUS);
		case '-': return this->lexer_advance_current(TOKEN_MINUS);
		case '*': return this->lexer_advance_current(TOKEN_ASTERISK);
		case '&': 
			if(this->lexer_peek(1) == '&')
			return this->lexer_advance_with(this->lexer_advance_with(new Token("&&", TOKEN_AND)));
			return this->lexer_advance_with(new Token("&", TOKEN_AMPERSAND));
		case '=': 
			if(this->lexer_peek(1) == '=')
			return this->lexer_advance_with(this->lexer_advance_with(new Token("==", TOKEN_DOUBLE_EQUAL)));
			return this->lexer_advance_with(new Token("=", TOKEN_EQUALS));
		case '!': 
			if(this->lexer_peek(1) == '=')
			return this->lexer_advance_with(this->lexer_advance_with(new Token("!=", TOKEN_NOT_EQUAL)));
			return this->lexer_advance_with(new Token("!", TOKEN_EXCLAMATION));
		case '|': 
			if(this->lexer_peek(1) == '|')
			return this->lexer_advance_with(this->lexer_advance_with(new Token("||", TOKEN_OR)));
			break;
		case '\0': break;
		default: 
			cout<<"[Lexer]: Unexpected character "<<this->c<<endl;
			exit(1);
			break;
    }
  }
  
  return new Token("0", TOKEN_END_OF_FILE);
}