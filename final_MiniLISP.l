%{
#include "main.hh"
#include "yacc.tab.h"
using namespace std;

extern "C"
{
    int yywrap(void);
    int yylex(void);
}
bool stb(string in){
    if(in == "#t") return true;
    if(in == "#f") return false;
}
%}
seperator   [\t\n\r' ']
letter      [a-z]
digit       [0-9]
Boolean     #[tf]
Number      0|[1-9]{digit}*|-[1-9]{digit}*
ID          {letter}({letter}|{digit}|\-)*

%%
{seperator} {}
"+"         {return ADD;}
"-"         {return SUB;}
"*"         {return MUL;}
"/"         {return DIV;}
"mod"       {return MOD;}
">"         {return GRT;}
"<"         {return SML;}
"="         {return EQL;}
"and"       {return AND;}
"or"        {return OR;}
"not"       {return NOT;}
"print-num" {return PRINT_NUM;}
"print-bool" {return PRINT_BOOL;}
"if"        {return IF;}
"define"    {return DEF;}
"lambda"    {return FUN;}
{Boolean}   {yylval.indata = new inData{0, stb(yytext), "\0"};return BOOL;}
{Number}    {yylval.indata = new inData{atoi(yytext), true, "\0"};return INT;}
{ID}        {yylval.indata = new inData{0, true, strdup(yytext)};return ID;}
.           {return yytext[0];}
%%
int yywrap(void)
{
    return 1;
}

