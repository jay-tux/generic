#ifndef _JAY_GSTACKC
#define _JAY_GSTACKC
#include "stack.h"

struct _stack_node *__sinit__()
{
	struct _stack_node *root = (struct _stack_node *)malloc(sizeof(struct _stack_node));
	if (root == NULL)
	{
		JAY_ERRNO = 20;
		return NULL;
	}

	root->next = NULL;
	root->value = NULL;
	return root;
}

int push(stack target, _stack_node_type *value)
{
	if(target == NULL)
	{
		JAY_ERRNO = 21;
		return 0;
	}

	if(target->value == NULL)
	{
		(*target)->value = value;
		(*target)->next = NULL;
		return 1;
	}

	struct _stack_node *newn = (struct _stack_node *)malloc(sizeof(struct _stack_node));
	newn->value = value;
	newn->next = *target;
	*target = newn;
	return 1;
}

int multpush(stack target, _stack_node_type *values[], int amount)
{
	int res = 0;
	for(int i = 0; i < amount; i++)
	{
		res += push(target, values[i]);
	}
	return (amount - res) + 1;
}

int pop(stack target, _stack_node_type *out)
{
	if(target == NULL || target->value == NULL)
	{
		JAY_ERRNO = 22;
		return 0;
	}

	out = (*target)->value;
	struct _stack_node *tmp = *target;
	*target = tmp->next;
	free(tmp);
	return 1;
}

int peek(stack target, _stack_node_type *out)
{
	if(target == NULL || target->value == NULL)
        {
                JAY_ERRNO = 23;
                return 0;
        }

        out = (*target)->value;
        return 1;
}

int multpop(stack target, _stack_node_type *out[], int amount)
{
	int res = 0;
	_stack_node_type *tmp;
	for(int i = 0; i < amount; i++)
	{
		res += pop(target, tmp);
		out[i] = tmp;
	}
	return (amount - res) + 1;
}

int stack_size(stack target)
{
	if(target == NULL || (*target)->value == NULL)
        {
                 return 0;
        }

        int count = 0;
        struct _stack_node *walk = *target;
        while(walk != NULL)
        {
                count++;
                walk = walk->next;
        }
        return count;
}

int printstackto(stack target, FILE * restrict stream, const char *tostring(_stack_node_type *))
{
        struct _stack_node *walk = *target;
        while(walk != NULL)
        {
                const char *string = tostring(walk->value);
                fprintf(stream, "%s --> ", string);
                walk = walk->next;
        }
        fprintf(stream, "NULL.");
        return 1;
}

int __sdestroy__(stack target)
{
	void *empty;
	while(*target != NULL)
	{
		if(!pop(target, empty)) return 0;
	}
	free(*target);
	return 1;
}
#endif
