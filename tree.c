#ifndef _JAY_GNTREEC
#define _JAY_GNTREEC
#include "tree.h"

struct _ntree_node *__ntinit__()
{
	struct _ntree_node *root = (struct _ntree_node *)malloc(sizeof(struct _ntree_node));
	if(root == NULL) { JAY_ERRNO = 40; return NULL; }
	root->value = NULL;
	for(int i = 0; i < NTREE_AMOUNT; i++)
	{
		root->children[i] = NULL;
	}
	root->lastchild = 0;
	root->parent = NULL;
	return root;
}

int append_position(ntree target, int direction[], _ntree_node_type *value, int amount)
{
	if(target == NULL) { JAY_ERRNO = 41; return 0; }
        struct _ntree_node *newnode = (struct _ntree_node *)malloc(sizeof(struct _ntree_node));
        if(newnode == NULL) { JAY_ERRNO = 42; return 0; }
	newnode->value = value;
	newnode->lastchild = 0;
	for(int i = 0; i < NTREE_AMOUNT; i++)
	{
		newnode->children[i] = NULL;
	}

	if((*target)->value == NULL)
	{
		*target = newnode;
		return 1;
	}

	struct _ntree_node *walk = *target;
	for(int i = 0; i < amount; i++)
	{
		if(direction[i] > NTREE_AMOUNT)
		{
			JAY_ERRNO = 44;
			free(newnode);
			return 0;
		}

		if(walk->children[direction[i]] == NULL)
		{
			walk->children[direction[i]] = newnode;
			newnode->parent = walk;
			return 1;
		}
		else
		{
			walk = walk->children[direction[i]];
		}
	}
	JAY_ERRNO = 43; return 0;
}

void printsubtreeto(struct _ntree_node *target, FILE * restrict stream, 
		const char *tostring(_ntree_node_type *), int indent, int sorted)
{
	for(int i = 0; i < indent; i++) { fprintf(stream, " "); }
	if(target == NULL || target->value == NULL)
	{
		fprintf(stream, "{ NULL node }\n");
		return;
	}
	else
	{
		if(sorted)
		{
			fprintf(stream, "{ Value: %s; %d of %d children set }\n", 
				tostring(target->value), target->lastchild, NTREE_AMOUNT);
		}
		else
		{
			int set = 0;
			for(int i = 0; i < NTREE_AMOUNT; i++)
			{
				set += (target->children[i] != NULL);
			}
			fprintf(stream, "{ Value: %s; %d of %d children set }\n",
				tostring(target->value), set, NTREE_AMOUNT);
		}
	}
	for(int i = 0; i < NTREE_AMOUNT; i++)
	{
		printsubtreeto(target->children[i], stream, tostring, indent + 4, sorted);
	}
}

int printntreeto(ntree target, FILE * restrict stream, 
		const char *tostring(_ntree_node_type *), int sorted)
{
	fprintf(stream, "ROOT: ");
	printsubtreeto(*target, stream, tostring, 0, sorted);
	return 1;
}
#endif
