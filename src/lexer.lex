%{
   #include "parser.tab.h"
%}

%%
[0-9]+     { yylval.number = lisp_number_new(atoi(yytext)); return NUMBER; }
"("        { return LEFT_PAREN; }
")"        { return RIGHT_PAREN; }
"+"        { return ADD; }
" "        {}
"\n"       { return EOL; }
%%
