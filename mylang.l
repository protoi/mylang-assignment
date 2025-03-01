%{
	#include <stdlib.h>
	#include "mylang.h"
	#include "mylang.tab.h"
	#include <stdbool.h>

void yyerror(char*);
int calculateIndex(char*, char);
%}
%option noyywrap

%%
"~"						return UMINUS;
">=" 					return GE;
"<=" 					return LE;
"==" 					return EQ;
"!=" 					return NE;
"while" 				return WHILE;
"if" 					return IF;
"else" 					return ELSE;
"display" 				return DISPLAY;

[a-n][0-9][0-9]			{
							yylval.sIndex = calculateIndex(yytext, 'a');
							return SIVAR;
						}
[o-z][0-9][0-9]			{
							yylval.sIndex = calculateIndex(yytext, 'o');
							return FPVAR;
						}
([0-9]+[.][0-9]+)		{

							yylval.fvalue = atof(yytext);
							printf("\t\tTOKEN READ: %lf\n", yylval.fvalue);
							return FLOATIE;
						}
[0-9]+					{
							yylval.ivalue = atoi(yytext);
							printf("\t\tTOKEN READ: %d\n", yylval.ivalue);
							return INTEGER;
						}
[-\(\)<>\{\}+=\*/^;] 	{
							printf("\t\t\t\tTOKEN READ: %c\n", yytext[0]);
							return yytext[0];
						}
[ \t\n]+ 				; /* ignore whitespaces, tabs and line breaks */
.						{
							yyerror("Unknown character encountered\n");
						}
%%

int calculateIndex(char *c, char x)
{
	return (c[0] - x) * 100 + (c[1] - '0') * 10 + (c[2] - '0') * 1;
} 