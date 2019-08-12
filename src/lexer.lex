%option noyywrap

%{
#include <ast.hpp>
#include <parser.tab.hpp>
%}

%%
[0-9]      { yylval.Di = yytext[0]; return DIGIT; }
[a-z]      { yylval.Ch = yytext[0]; return LETTER; }
"define"   { return DEFINE; }
"("        { return LEFT_PAREN; }
")"        { return RIGHT_PAREN; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"."        { return DOT; }
" "        {}
"\n"       { return EOL; }
%%
