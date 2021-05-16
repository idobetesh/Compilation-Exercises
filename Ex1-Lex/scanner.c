#include <stdio.h>
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern char *yytext;

// [-+]?[0-9]*\.[1-9]*e?[+-]?[1-9] FLOAT
// [+]?[0-9]*-[0-9]*-[0-9]*-?[0-9]* PHONE
// [a-zA-Z]*@[a-zA-Z]*\.[a-zA-Z]*\.?[a-zA-Z]* EMAIL

char *names[] = {NULL, "number", "float", "email", "phone", "address"};

int main(void)
{
    int ntoken, vtoken;

    ntoken = yylex();
    while (ntoken)
    {
        printf("\n");
        if (yylex() != COLON)
        {
            printf("Syntax error in line %d, Expected a ':' but found %s\n", yylineno, yytext);
            return 1;
        }

        vtoken = yylex();
        switch (ntoken)
        {
        case NUMBER:
            if (vtoken != OP && vtoken != INTEGER)
            {
                printf("Syntax error in line %d, Expected an integer but found %s\n", yylineno, yytext);
                return 1;
            }
            printf("%s is set to %s\n", names[ntoken], yytext);
            break;

        case FLOAT:
            if (vtoken != FLOATING)
            {
                printf("Syntax error in line %d, Expected an integer but found %s\n", yylineno, yytext);
                return 1;
            }
            printf("%s is set to %s\n", names[ntoken], yytext);
            break;

        case EMAIL:
            if (vtoken != EMAIL_ADD)
            {
                printf("Syntax error in line %d, Expected an identifier but found %s\n", yylineno, yytext);
                return 1;
            }
            printf("%s is set to %s\n", names[ntoken], yytext);
            break;

        case PHONE:
            if (vtoken != PHONE_NUM)
            {
                printf("Syntax error in line %d, Expected an identifier but found %s\n", yylineno, yytext);
                return 1;
            }
            printf("%s is set to %s\n", names[ntoken], yytext);
            break;

        default:
            printf("Syntax error in line %d\n", yylineno);
        }

        ntoken = yylex();
    }
    return 0;
}