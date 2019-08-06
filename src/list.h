#pragma once

typedef struct
{
  node_type_t type;
} node_t;

typedef struct {
  uint32_t length;
  uint32_t elements;
  node_t **nodes;
} list_t;


list_t *list_new()
{
  list_t *list = malloc(sizeof(list_t));
  list->nodes = malloc(2 * sizeof(node_t *));
  list->length = 2;
  list->elements = 0;

  return list;
}

void list_append(list_t *list, node_t *node)
{
  if (list->elements == list->length)
    {
      void **new = malloc(sizeof(node_t *) * list->length * 2);
      memcpy(new, list->nodes, sizeof(node_t *) * list->elements);
      free(list->expressions);
      list->expressions = new;
      list->length = list->length * 2;
    }

  list->nodes[list->elements++] = node;
}
