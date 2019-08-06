#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  node_t parent;
  list_t forms;
} lisp_program_t;

typedef struct {
  node_t parent;
  node_t *identifier; // lisp_identifier_t
  node_t *datum;
} lisp_definition_var_t;

typedef struct {
  node_t parent;
  node_t *identifier; // lisp_identifier_t
  list_t parameter_names;
  list_t body;        // body = list of expressions
} lisp_definition_fun_t;


typedef struct {
  node_t parent;
  node_t *identifier; // lisp_identifier_t
} lisp_parameter_name_t;


typedef struct {
  node_t parent;
  list_t expressions;
} lisp_body_t;


typedef struct {
  node_t parent;
  node_t *identifier; // lisp_identifier_t
  list_t datums;
} lisp_expression_application_t;


typedef struct {
  node_t parent;
  list_t datums;
} lisp_expression_quote_t;


typedef struct {
  node_t parent;
  node_t *datum;  // a single datum
} lisp_expression_datum_t;


typedef struct {
  node_t parent;
  int64_t number;
} lisp_int_t;


typedef struct {
  node_t parent;
  double number;
} lisp_float_t;

typedef struct {
  node_t parent;
  char *string;
} lisp_string_t;


typedef struct {
  node_t parent;
  bool value;
} lisp_boolean_t;


typedef struct {
  node_t parent;
  char *identifier;
} lisp_identifier_t;
