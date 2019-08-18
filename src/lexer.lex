%option noyywrap

%{
#include <ast.hpp>
#include <parser.tab.hpp>
%}

%%
[0-9]      { yylval.Di = yytext[0]; return DIGIT; }
[a-zA-Z]   { yylval.Ch = yytext[0]; return LETTER; }
"define"   { return DEFINE; }
"("        { return LEFT_PAREN; }
")"        { return RIGHT_PAREN; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"."        { return DOT; }
#t|#T      { return TRUE; }
#f|#F      { return FALSE; }
" "        { }
"\n"       { return EOL; }
\"[^\\\"]*\" { yylval.Str = yytext; return STRING; }
%%
