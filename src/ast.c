#include "ast.h"

lisp_expr_t *lisp_list_new()
{
  lisp_list_t *list = malloc(sizeof(lisp_list_t));
  list->expressions = malloc(2 * sizeof(lisp_expr_t *));
  list->parent.type = LISP_LIST;
  list->length = 2;

  return (lisp_expr_t *)list;
}

void lisp_list_append(lisp_expr_t *list, lisp_expr_t *expr)
{
  lisp_list_t *l = (lisp_list_t *)list;

  if (l->elements == l->length)
    {
      lisp_expr_t **new = malloc(sizeof(lisp_expr_t *) * l->length * 2);
      memcpy(new, l->expressions, sizeof(lisp_expr_t *) * l->elements);
      free(l->expressions);
      l->expressions = new;
      l->length = l->length * 2;
    }

  l->expressions[l->elements++] = expr;
}

lisp_expr_t *lisp_number_new(int number)
{
  lisp_num_t *n = malloc(sizeof(lisp_num_t));
  n->number = number;
  return (lisp_expr_t *)n;
}

lisp_expr_t *lisp_addop_new()
{
  lisp_addop_t *a = malloc(sizeof(lisp_addop_t));
  return (lisp_expr_t *)a;
}
