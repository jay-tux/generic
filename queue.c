#ifndef _JAY_GQUEUEC
#define _JAY_GQUEUEC
#include "queue.h"

struct _queue_node *__qinit__()
{
	struct _queue_node *root = (struct _queue_node *)malloc(sizeof(struct _queue_node));
	if (root == NULL)
	{
		JAY_ERRNO = 30;
		return NULL;
	}

	root->next = NULL;
	root->value = NULL;
	return root;
}

int enqueue(queue target, _queue_node_type *value)
{
	if(target == NULL)
	{
		JAY_ERRNO = 31;
		return 0;
	}

	if((*target)->value == NULL)
	{
		(*target)->value = value;
		(*target)->next = NULL;
		return 1;
	}

	struct _queue_node *walker = *target;
	while(walker->next != NULL)
	{
		walker = walker->next;
	}
	struct _queue_node *newn = (struct _queue_node *)malloc(sizeof(struct _queue_node));
	newn->value = value;
	newn->next = NULL;
	walker->next = newn;
	return 1;
}

int batch_enqueue(queue target, _queue_node_type *values[], int amount)
{
	int res = 0;
	for(int i = 0; i < amount; i++)
	{
		res += enqueue(target, values[i]);
	}
	return (amount - res) + 1;
}

_queue_node_type *dequeue(queue target)
{
	if(target == NULL || (*target)->value == NULL)
	{
		JAY_ERRNO = 32;
		return NULL;
	}

	struct _queue_node *tmp = *target;
	_queue_node_type *out = (tmp->value);
	*target = tmp->next;
	free(tmp);
	return out;
}

_queue_node_type *peek(queue target)
{
	if(target == NULL || (*target)->value == NULL)
        {
                JAY_ERRNO = 33;
                return NULL;
        }

        return ((*target)->value);
}

int batch_dequeue(queue target, _queue_node_type *out[], int amount)
{
	int res = 0;
	if(amount > queue_size(target)) 
	{
		JAY_ERRNO = 34;
		return 0;
	}

	for(int i = 0; i < amount; i++)
	{
		out[i] = dequeue(target);
		res += (out[i] != NULL);
	}
	return (amount - res) + 1;
}

int queue_size(queue target)
{
	if(target == NULL || (*target)->value == NULL)
        {
		JAY_ERRNO = 35;
                return 0;
        }

        int count = 0;
        struct _queue_node *walk = *target;
        while(walk != NULL)
        {
                count++;
                walk = walk->next;
        }
        return count;
}

int printqueueto(queue target, FILE * restrict stream, const char *tostring(_queue_node_type *))
{
        struct _queue_node *walk = *target;
        while(walk != NULL)
        {
                const char *string = tostring(walk->value);
                fprintf(stream, "%s --> ", string);
                walk = walk->next;
        }
        fprintf(stream, "NULL.");
        return 1;
}

int __qdestroy__(queue target)
{
	while(*target != NULL)
	{
		if(!dequeue(target)) return 0;
	}
	free(*target);
	return 1;
}
#endif
