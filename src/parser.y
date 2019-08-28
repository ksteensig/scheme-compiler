%{
#include "ast.hpp"
extern int yylex(); 
int yyerror(std::string s);
%}

%union{
  Program *Prog;
  Format *Form;
  Definition *Def;
  Expression *Expr;

  char Ch;
  char Di;

  vector<Datum> *DatumList;
  
  Identifier *Id;
  char Initial;
  std::deque<char> *Subsequent;
  char Subsequent_;

  Datum *Dat;

  char *Str;

  Number *Num;
  vector<char> *Integer;
  int64_t Signed_int;
  uint64_t Unsigned_int;
  double Float;

  bool Bool;

  List *ActualList;
  List *List_;
};

%token<Ch> LETTER
%token<Di> DIGIT
%token<Str> STRING
%token PLUS
%token MINUS
%token DOT
%token TRUE
%token FALSE
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

%type<DatumList> datum_list

%type<Id> identifier
%type<Initial> initial
%type<Subsequent> subsequent
%type<Subsequent_> subsequent_

%type<Dat> datum
 
%type<Num> number
%type<Integer> integer
%type<Signed_int> signed_int
%type<Unsigned_int> unsigned_int
%type<Float> float_val

%type<Bool> boolean

%type<ActualList> list
%type<List_> list_
%%
 /*
program: { $$ = new Program(); }
| program form { $1->push_back(*$2); delete $2; $$ = $1; }
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
 */

 /*expression:
LEFT_PAREN identifier datum_list RIGHT_PAREN {  } 
| LEFT_PAREN datum_list RIGHT_PAREN {}
;*/

datum_list:
/* empty */ { $$ = new vector<Datum>(); }
| datum_list datum { $1->push_back(*$2); $$ = $1; delete $2; }
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

datum:
number { $$ = new Datum(*$1); delete $1; }
| STRING { $$ = new Datum(new String($1)); delete $1; }
| boolean { $$ = new Datum($1); }
| identifier { $$ = new Datum(*$1); }
| list {
  auto l = List{};
  l.datum = std::move($1->datum);
  $$ = new Datum(l); }
;

number:
MINUS integer { $$ = new Number(-1 * std::stoi(std::string($2->begin(), $2->end()))); delete $2; }
| integer { $$ = new Number(std::stoi(std::string($1->begin(), $1->end()))); delete $1; }
| integer DOT integer {
  auto int_part = std::stoi(std::string($1->begin(), $1->end()))); delete $1;
  auto dot = ".";
  auto decimal_part = std::stoi(std::string($3->begin(), $3->end()))); delete $3;
  $$ = new Number(std::stof(int_part + dot + decimal_part)); }
| MINUS integer DOT integer {
  auto int_part = std::stoi(std::string($2->begin(), $2->end()))); delete $2;
  auto dot = ".";
  auto decimal_part = std::stoi(std::string($4->begin(), $4->end()))); delete $4;
  $$ = new Number(-1 * std::stof(int_part + dot + decimal_part)); }
;

integer:
/* empty */ { $$ = new vector<char>(); }
| integer DIGIT { $1->push_back($2); $$ = $1; }
;

boolean:
TRUE { $$ = true; }
| FALSE { $$ = false; }
;

list:
LEFT_PAREN list_ RIGHT_PAREN { $$ = (List *)$2; }
;

list_:
/* empty */ { $$ = new List(); }
| list_ datum { $1->datum.push_back(*$2); $$ = $1; delete *$2; }
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
