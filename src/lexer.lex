%option noyywrap

%{
#include <ast.hpp>
#include <parser.tab.hpp>
%}

%%
[0-9]      { yylval.Di = new std::string(yytext); return DIGIT; }
[a-z]      { yylval.Ch = new std::string(yytext); return LETTER; }
"("        { return LEFT_PAREN; }
")"        { return RIGHT_PAREN; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"."        { return DOT; }
" "        {}
"\n"       { return EOL; }
%%
