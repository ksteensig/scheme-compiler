%{
#include "ast.hpp"
extern int yylex(); 
int yyerror(std::string s);
%}

%union{
  char Ch;
  char Di;

  Identifier *Id;
  char Initial;
  std::deque<char> *Subsequent;
  char Subsequent_;
  
  Program *Prog;
  Format *Form;
  Definition *Def;
  Expression *Expr;

  Number *Num;
  int64_t Signed_int;
  uint64_t Unsigned_int;
  double Float;
};

%token<Ch> LETTER
%token<Di> DIGIT
%token PLUS
%token MINUS
%token DOT
%token LEFT_PAREN
%token RIGHT_PAREN
%token DEFINE
%token EOL
 /*
%type<Prog> program
%type<Form> form
%type<Def> definition
%type<Expr> expression

%type<Id> parameter_name
 */
%type<Id> identifier
%type<Initial> initial
%type<Subsequent> subsequent
%type<Subsequent_> subsequent_

 /*
%type<Num> number;
%type<Signed_int> signed_int
%type<Unsigned_int> unsigned_int
%type<Float> float_val
 */

%%
 
program: { $$ = new Program(); }
| program form { $1->push_back(std::make_shared<Format>(*$2)); $$ = $1; }
;

form:
definition { $$ = (Format *)$1; }
| expression { $$ = (Format *)$1; }
;

definition:
;

expression:
;

parameter_name: identifier
;

identifier: initial subsequent { $2->push_front($1); $$ = new Identifier(std::string($2->begin(), $2->end())); delete $2; }
| PLUS {$$ = new Identifier("+"); }
| MINUS {$$ = new Identifier("-"); }
| DOT {$$ = new Identifier("."); }
;

initial: LETTER { $$ = $1; }
;

subsequent: /* empty */ { $$ = new deque<char>(); }
| subsequent subsequent_ { $1->push_back($2); $$ = $1; }
;

subsequent_:
initial { $$ = $1; }
| DIGIT { $$ = $1; }
| PLUS { $$ = '+'; }
| MINUS { $$ = '-'; }
| DOT { $$ = '.'; }
;

number:
MINUS integer_ {std::make_shared<int64_t>()}
| integer_
;

integer: integer digit {}


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
