#ifndef _JAY_GLISTC
#define _JAY_GLISTC
#include "list.h"

struct _list_node *__linit__()
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

	if(index < 0)
	{
		JAY_ERRNO = 15;
		return 0;
	}

	if((*target)->value == NULL)
	{
		(*target)->value = value;
		(*target)->next = NULL;
		return 1;
	}

	if(index >= list_size(target))
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

int removeAt(list target, int index)
{
	if(target == NULL)
	{
		JAY_ERRNO = 16;
		return 0;
	}

	if(index < 0)
	{
		JAY_ERRNO = 15;
		return 0;
	}

	if (index >= list_size(target))
	{
		JAY_ERRNO = 14;
		return 0;
	}

	int where = 0;
	struct _list_node *walk = *target;
	struct _list_node *prev = NULL;
	while(walk->next != NULL && where < index)
	{
		prev = walk;
		walk = walk->next;
		where++;
	}

	struct _list_node *tmp;
	if(prev == NULL)
	{
		tmp = *target;
		*target = walk->next;
		free(tmp);
		return 1;
	}
	if(walk->next == NULL)
	{
		tmp = walk;
		prev->next = NULL;
		free(tmp);
		return 1;
	}

	tmp = walk;
	prev->next = walk->next;
	free(tmp);
	return 1;
}

int remove_elem(list target, _list_node_type *value, int same(_list_node_type *, _list_node_type *))
{
	int index = indexof(target, value, same);
	if(index < 0)
	{
		JAY_ERRNO = 13;
		return 0;
	}
	return removeAt(target, index);
}

int list_size(list target)
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

_list_node_type *at_index(list target, int index)
{
	if(index < 0) { JAY_ERRNO = 15; return NULL; }
	if(index >= list_size(target)) { JAY_ERRNO = 14; return NULL; }

	struct _list_node *walk = *target;
	int curr = 0;
	while(walk->next != NULL && curr < index)
	{
		walk = walk->next;
		curr++;
	}

	if(walk == NULL) { JAY_ERRNO = 13;  return NULL; }
	return walk->value;
}

int batch_append(list target, _list_node_type *values[], int amount)
{
	int res = 0;
	for(int i = 0; i < amount; i++) { res += append(target, values[i]); }
	return (res - amount) + 1;
}

int batch_insertAt(list target, _list_node_type *values[], int amount, int firstind)
{
	int res = 0;
	for(int i = 0; i < amount; i++)
	{
		res += insert_at(target, values[i], firstind + res);
	}
	return (res - amount) + 1;
}

int batch_insort(list target, _list_node_type *values[], int amount, int order(_list_node_type *, _list_node_type *))
{
	int res = 0;
	for(int i = 0; i < amount; i++) { res += insort(target, values[i], order); }
	return (res - amount) + 1;
}

int sort(list target, int order(_list_node_type *, _list_node_type *))
{
	if(target == NULL)
	{
		JAY_ERRNO = 17;
		return 0;
	}
	if((*target)->next == NULL)
	{
		JAY_ERRNO = 18;
		return 0;
	}

	struct _list_node *newl = __linit__();
	struct _list_node *walk = *target;
	struct _list_node *rm = NULL;
	while(walk != NULL)
	{
		if( !insort(&newl, walk->value, order)) { __ldestroy__(&newl); return 0; }
		walk = walk->next;
	}
	fprintf(stderr, "Finished sorting\n");
	walk = *target;
	fprintf(stderr, "Freeing disposable nodes\n");
	while (walk != NULL)
	{
		rm = walk;
		walk = walk->next;
		free(rm);
	}
	*target = newl;
	return 1;
}

int stalin_sort(list target, int order(_list_node_type *, _list_node_type *))
{
	if(target == NULL)
	{
		JAY_ERRNO = 17;
		return 0;
	}
	if((*target)->next == NULL)
	{
		JAY_ERRNO = 18;
		return 0;
	}

	struct _list_node *walker = *target;
	int index = 0;
	while(walker->next != NULL)
	{
		if(order(walker->value, walker->next->value) < 0)
		{
                        walker = walker->next;
                        index++;
		}
		else
		{
			walker = walker->next;
			if(!removeAt(target, index))
			{
				JAY_ERRNO = 19;
				return 0;
			}
		}
	}

	return 1;
}

int batch_removeAt(list target, int indexes[], int amount)
{
	int res = 0;
	for(int i = 0; i < amount; i++) { res += removeAt(target, indexes[i] - res); }
	return (res - amount) + 1;
}

int batch_remove_elem(list target, _list_node_type *values[], int amount, int same(_list_node_type *, _list_node_type *))
{
	int res = 0;
	for (int i = 0; i < amount; i++) { res += remove_elem(target, values[i], same); }
	return (res - amount + 1);
}

int __ldestroy__(list target)
{
	while(*target != NULL)
	{
		if(!removeAt(target, 0)) return 0;
	}
	free(*target);
	return 1;
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
