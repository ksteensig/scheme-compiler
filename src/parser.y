%code requires {
#include "ast.h"
}

%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
extern int yylex(); 
int yyerror(char* msg);
lisp_expr_t *top;
%}

%union{
  lisp_expr_t *number;
  lisp_expr_t *atomic;
  lisp_expr_t *list;
  lisp_expr_t *addop;
  lisp_expr_t *expr;
};

%token LETTER
%token ADD
%token LEFT_PAREN
%token RIGHT_PAREN
%token EOL
%type <expr> expression
%type <list> list_start
%type <atomic> atom

%%
list_start:
LEFT_PAREN expression RIGHT_PAREN EOL { $$ = lisp_list_new($2); top = $$; }
;

atom:
ADD { $$ = $1; }
| NUMBER { $$ = $1; }
;

expression:
atom { $$ = $1; }
| expression atom {lisp_list_append($$, $1); lisp_list_append($$, $2);}
| expression LEFT_PAREN expression RIGHT_PAREN {lisp_expr_t *nl = lisp_list_new();
                                                lisp_list_append(nl, $1);
						lisp_list_append($$, nl);}
;

%%

int main(int argc, char **argv[])
{
  yyparse();
  lisp_expr_t *l = top;

  printf("%d\n", l->type);
  
  return 0;
}

int yyerror(char *s)
{
  printf("error: %s\n", s);
  return 0;
}
