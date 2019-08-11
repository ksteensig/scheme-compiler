%{
#include "ast.hpp"
extern int yylex(); 
int yyerror(std::string s);
%}

%union{
  String *Ch;
  String *Di;

  Identifier *Id;
  std::string *Initial;
  std::string *Subsequent;

  
};

%token<Ch> LETTER
%token<Di> DIGIT
%token PLUS
%token MINUS
%token DOT
%token LEFT_PAREN
%token RIGHT_PAREN
%token EOL


%type<Id> identifier_start
%type<Id> identifier
%type<Initial> initial
%type<Subsequent> subsequent_start
%type<Subsequent> subsequent

%%
identifier_start: identifier EOL
;

identifier: initial subsequent_start { *$1 = *$1 + *$2; $$ = (Identifier*)$1; delete $2; }
| PLUS {$$ = new Identifier("+"); }
| MINUS {$$ = new Identifier("-"); }
| DOT {$$ = new Identifier("."); }
;

initial: LETTER { $$ = $1; }
;

subsequent_start: /* empty */ { $$ = new std::string(""); }
| subsequent_start subsequent { *$1 = *$1 + *$2; $$ = $1; delete $2; }
;

subsequent:
initial { $$ = $1; }
| DIGIT { $$ = $1; }
| PLUS { $$ = new std::string("+"); }
| MINUS { $$ = new std::string("-"); }
| DOT { $$ = new std::string("."); }
;
%%

int main(int argc, char *argv[])
{
  yyparse();
  
  return 0;
}

int yyerror(std::string s)
{
  printf("error: %s\n", s.c_str());
  return 0;
}
