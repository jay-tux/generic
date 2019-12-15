#ifndef _JAY_GLIST
#define _JAY_GLIST
#include "const.h"
#include <stdlib.h>
#include <stdio.h>
//change char to allow for other types as node data
typedef char _list_node_type;

struct _list_node {
	_list_node_type *value;
	struct _list_node *next;
};

typedef struct _list_node **list;

//INIT
struct _list_node *__linit__();

//ADD 1
int append(list target, _list_node_type *value);
int insert_at(list target, _list_node_type *value, int index);
int insort(list target, _list_node_type *value, int order(_list_node_type *, _list_node_type *));

//REMOVE 1
int removeAt(list target, int index);
int remove_elem(list target, _list_node_type *value, int same(_list_node_type *, _list_node_type *));

//GET
int list_size(list target);
int indexof(list target, _list_node_type *value, int same(_list_node_type *, _list_node_type *));
_list_node_type *at_index(list target, int index);

//ADD BATCH
int batch_append(list target, _list_node_type *values[], int amount);
int batch_insertAt(list target, _list_node_type *values[], int amount, int firstind);
int batch_insort(list target, _list_node_type *values[], int amount, int order(_list_node_type *, _list_node_type *));
int sort(list target, int order(_list_node_type *, _list_node_type *));
int stalin_sort(list target, int order(_list_node_type *, _list_node_type *));

//REMOVE BATCH
int batch_removeAt(list target, int indexes[], int amount);
int batch_remove_elem(list target, _list_node_type *values[], int amount, int same(_list_node_type *, _list_node_type *));
int __ldestroy__(list target);

//PRINT
int printlistto(list target, FILE * restrict stream, const char *tostring(_list_node_type *));
#endif
