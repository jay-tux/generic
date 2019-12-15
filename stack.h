#ifndef _JAY_GSTACK
#define _JAY_GSTACK
#include "const.h"
#include <stdlib.h>
#include <stdio.h>
//change char to allow for other types as node data
typedef char _stack_node_type;

struct _stack_node {
	_stack_node_type *value;
	struct _stack_node *next;
};

typedef struct _stack_node **stack;

struct _stack_node *__sinit__();
int push(stack target, _stack_node_type *value);
int batch_push(stack target, _stack_node_type *values[], int amount);
_stack_node_type *pop(stack target);
_stack_node_type *peek(stack target);
int batch_pop(stack target, _stack_node_type *out[], int amount);
int stack_size(stack target);
int printstackto(stack target, FILE * restrict stream, const char *tostring(_stack_node_type *));
int __sdestroy__(stack target);
#endif
