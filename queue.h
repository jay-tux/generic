#ifndef _JAY_GQUEUE
#define _JAY_GQUEUE
#include "const.h"
#include <stdlib.h>
#include <stdio.h>
//change char to allow for other types as node data
typedef char _queue_node_type;

struct _queue_node {
	_queue_node_type *value;
	struct _queue_node *next;
};

typedef struct _queue_node **queue;

struct _queue_node *__qinit__();
int enqueue(queue target, _queue_node_type *value);
int batch_enqueue(queue target, _queue_node_type *values[], int amount);
_queue_node_type *dequeue(queue target);
_queue_node_type *peek(queue target);
int batch_dequeue(queue target, _queue_node_type *out[], int amount);
int queue_size(queue target);
int printqueueto(queue target, FILE * restrict stream, const char *tostring(_queue_node_type *));
int __qdestroy__(queue target);
#endif
