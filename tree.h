#ifndef _JAY_GNTREE
#define _JAY_GNTREE

#include "const.h"
#include <stdlib.h>
#include <stdio.h>

//change char to allow for other types as node data
typedef char _ntree_node_type;
//change NTREE_AMOUNT in ./const.h to allow for other amounts of child nodes

struct _ntree_node {
	_ntree_node_type *value;
	struct _ntree_node *parent;
	struct _ntree_node *children[NTREE_AMOUNT];
	int lastchild; //child to set next
};

typedef struct _ntree_node **ntree;

struct _ntree_node *__ntinit__();
int append_left(ntree target, _ntree_node_type *value);
int append_position(ntree target, int directions[], _ntree_node_type *value, int amount);

int printntreeto(ntree target, FILE * restrict stream, const char *tostring(_ntree_node_type *), int sorted);
#endif
