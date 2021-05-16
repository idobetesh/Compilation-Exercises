%{
#include "scanner.h"
%}

%option nounput yylineno

%%
:																	return COLON;
"number"															return NUMBER;
"float"																return FLOAT;
"email"																return EMAIL;
"phone"																return PHONE;
"address"															return ADDRESS;
"C_key_word"														return C_KEYWORD;

[a-zA-Z][_a-zA-Z0-9]*												return IDENTIFIER;
[1-9][0-9]*															return INTEGER;
[-+]?[1-9][0-9]*													return OP;
[-+]?[0-9]*\.[1-9]*e?[+-]?[1-9] 									return FLOATING;
[a-zA-Z]*@[a-zA-Z]*\.[a-zA-Z]*\.?[a-zA-Z]* 							return EMAIL_ADD;
[+]?[0-9]*-[0-9]*-[0-9]*-?[0-9]* 									return PHONE_NUM;
[1-9][0-9]*[a-zA-Z]*[, ]?[a-zA-Z.]*,[a-zA-Z-]*,[a-zA-Z]*,[a-zA-Z]* 	return HOME_ADDRESS;
if|while|'for'|'switch'|'case'|'break'|'continue'		 			return KEYWORD;
[ \t\n]																;
.																	printf("unexpected character\n");
%%

//In order to stop the lexer after a single run
int yywrap(void)
{
	return 1;
}
