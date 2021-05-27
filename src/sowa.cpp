#include <unistd.h>
#include "include/sowa.h"
#include "lexer.cpp"
#include "parser.cpp"
#include "as_frontend.cpp"

char *sh(const char *cmd)
{
    char *output = (char *)calloc(1, sizeof(char));
    output[0] = '\0';

    FILE *fp;
    char path[1035];

    fp = popen(cmd, "r");

    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL)
    {
        output = (char *)realloc(output, (strlen(output) + strlen(path) + 1) * sizeof(char));
        strcat(output, path);
    }

    pclose(fp);

    return output;
}

void sowa_compile(string src)
{
    Lexer *lexer = new Lexer(src);
    Parser *parser = new Parser(lexer);
    SyntaxTree *root = parser->parser_parse();

    string s = as_f_root(root);

    fstream out;
    out.open("test.s", ios::out);
    if (out.good())
    {
        out << s;
        out.close();
    }
    else
    {
        cout << "Error" << endl;
    }

    sh("as test.s -o test.o");
    sh("ld test.o -o test.out");

    // Token *token = 0;

    // while((token = lexer->lexer_next_token())->getType() != TOKEN_END_OF_FILE)
    // {
    //     cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
    // }
    //   cout<<"Token("<<token->getValue()<<") ("<<token->getType()<<")"<<endl;
}