#ifndef _JAY_ERRNO
#define _JAY_ERRNO
#include "const.h"

const char *get_error(int errno)
{
	switch(errno)
	{
		case 0:  return "No error";

		case 10: return "Generic list error: can't create root node.";
		case 11: return "Generic list error: can't append; list is NULL.";
		case 12: return "Generic list error: can't get index of element in empty list.";
		case 13: return "Generic list error: element not in list.";
		case 14: return "Generic list error: index larger than max index (size - 1).";
		case 15: return "Generic list error: index smaller than 0.";
		case 16: return "Generic list error: can't remove from NULL-list.";
		case 17: return "Generic list error: can't sort empty list.";
		case 18: return "Generic list error: can't sort 1-element list.";
		case 19: return "Generic list error: STALIN SORT FAILED.";

		case 20: return "Generic stack error: can't create root node.";
		case 21: return "Generic stack error: can't push; stack is NULL.";
		case 22: return "Generic stack error: can't pop from NULL-stack.";
		case 23: return "Generic stack error: can't peek empty stack.";
		case 24: return "Generic stack error: can't pop more elements than stack has.";
		case 25: return "Generic stack error: failed to count NULL.";

		default: return "Unknown error.";
	}
}

const char *get_err()
{
	return get_error(JAY_ERRNO);
}

#endif
