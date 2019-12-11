#ifndef _JAY_GLISTC
#define _JAY_GLISTC
#include "list.h"

struct _list_node *__init__();
int append(list target, _list_node_type *value);
int insert_at(list target, _list_node_type *value, int index);
int insort(list target, _list_node_type *value, int order(_list_node_type *, _list_node_type *));
int size(list target);
int indexof(list target, _list_node_type *value, int same(_list_node_type *, _list_node_type *));
int printlistto(list target, FILE * restrict stream, const char *tostring(_list_node_type *));

struct _list_node *__init__()
{
	struct _list_node *root = (struct _list_node *)malloc(sizeof(struct _list_node));
	if(root == NULL) 
	{
		JAY_ERRNO = 10; 
		return NULL;
	}

	root->next= NULL;
	root->value = NULL;
	return (root);
}

int append(list target, _list_node_type *value)
{
	if(target == NULL)
	{
		JAY_ERRNO = 11;
		return 0;
	}

	if((*target)->value == NULL)
	{
		(*target)->value = value;
		(*target)->next = NULL;
		return 1;
	}

	struct _list_node *walk = *target;
	while(walk->next != NULL)
	{
		walk = walk->next;
	}
	struct _list_node *newt = (struct _list_node *)malloc(sizeof(struct _list_node));
	newt->value = value;
	newt->next = NULL;
	walk->next = newt;
	return 1;
}

int insert_at(list target, _list_node_type *value, int index)
{
	if(target == NULL)
	{
		JAY_ERRNO = 11;
		return 0;
	}

	if((*target)->value == NULL)
	{
		(*target)->value = value;
		(*target)->next = NULL;
		return 1;
	}

	if(index >= size(target))
	{
		JAY_ERRNO = 14;
		return 0;
	}

	int where = 0;
	struct _list_node *walk = *target;
	struct _list_node *prev = NULL;
	while(walk != NULL && where < index)
	{
		prev = walk;
		walk = walk->next;
		where++;
	}

	struct _list_node *newnode = (struct _list_node *)malloc(sizeof(struct _list_node));
	newnode->value = value;

	if(prev == NULL)
	{
		newnode->next = *target;
		*target = newnode;
		return 1;
	}

	newnode->next = walk;
	prev->next = newnode;
	return 1;
}

int insort(list target, _list_node_type *value, int order(_list_node_type *, _list_node_type *))
{
	if(target == NULL)
        {
                JAY_ERRNO = 11;
                return 0;
        }

        if((*target)->value == NULL)
        {
                (*target)->value = value;
                (*target)->next = NULL;
                return 1;
        }

        struct _list_node *walk = *target;
        struct _list_node *prev = NULL;
        while(walk != NULL && order(walk->value, value) < 0)
        {
                prev = walk;
                walk = walk->next;
        }

        struct _list_node *newnode = (struct _list_node *)malloc(sizeof(struct _list_node));
        newnode->value = value;

        if(prev == NULL)
        {
                newnode->next = *target;
                *target = newnode;
                return 1;
        }

        newnode->next = walk;
        prev->next = newnode;
        return 1;
}

int size(list target)
{
	if(target == NULL || (*target)->value == NULL)
	{
		 return 0;
	}

	int count = 0;
	struct _list_node *walk = *target;
	while(walk != NULL)
	{
		count++;
		walk = walk->next;
	}
	return count;
}

int indexof(list target, _list_node_type *tofind, int same(_list_node_type *, _list_node_type *))
{
	if(target == NULL || (*target)->value == NULL)
	{
		JAY_ERRNO = 12;
		return -1;
	}

	int ind = 0;
	struct _list_node *walk = *target;
	while(walk != NULL && !same(walk->value, tofind))
	{
		walk = walk->next;
		ind++;
	}

	if(walk == NULL)
	{
		JAY_ERRNO = 13;
		return -1;
	}
	return ind;
}

int printlistto(list target, FILE * restrict stream, const char *tostring(_list_node_type *))
{
	struct _list_node *walk = *target;
	while(walk != NULL)
	{
		const char *string = tostring(walk->value);
		fprintf(stream, "%s --> ", string);
		walk = walk->next;
	}
	fprintf(stream, "NULL.");
	return 1;
}

#endif
