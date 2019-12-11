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
#endif
