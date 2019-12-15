# Generic Collections [C]
This repo will contain semi-generic versions of C's dynamic data structures. Semi-generic in this context means that any one kind of structure will be able to hold any one type of variable.  
All header/source files are double-import protected using ``_JAY_<filename>`` macros.

## Meta files
### ./const.h
 The ``./const.h`` file contains the definition of some "pseudo"-constants. These variables will be/can be set by the rest of the code, but you shouldn't set them yourself. Most are defined as ``static <type> JAY_<name> = <base value>;``. Following is a list of all of these variables, their uses and default values.
 * ``JAY_ERRNO``; is set to the error number by a failing function. Functions returning ``NULL`` or ``0``, will typically set this to an appropriate error.

### ./jerrno.h
 ![Dependency: ./const.h](https://img.shields.io/static/v1?label=Dependency&message=./const.h&color=informational)  
 The ``./jerrno.h`` file contains two functions:
 * ``const char *get_error(int errno)``; which returns the error message for an existing error, or "Unknown Error" for non-defined errors.
 * ``const char *get_err()``; which returns the error message for the last error thrown (using the ``JAY_ERRNO`` value defined in ``./const.h``. This value will also be set by other functions.

## List
### ./list.h
 ![Dependency: stdlib.h](https://img.shields.io/static/v1?label=Dependency&message=stdlib.h&color=informational)  
 ![Dependency: stdio.h](https://img.shields.io/static/v1?label=Dependency&message=stdio.h&color=informational)  
 ![Dependency: ./const.h](https://img.shields.io/static/v1?label=Dependency&message=./const.h&color=informational)  
 The ``./list.h`` file defines all structs and typedefs required for the list structure. All will be described in order of appearance:
 * ``_list_node_type``: this is the variable type contained within the list. Change the ``char`` in this line to any other variable type to store other variables in it. Currently, the list needs three helper functions to enable all implemented functionality; see ``./list.c``.
 * ``struct _list_node``: this contains the list nodes themselves.
 * ``list``: ``list`` is an alias for a pointer to a ``struct _list_node`` pointer (aka ``struct _list_node **``) this kind of pointer is necessary for all functionality.  
 ![Warning: the ``__linit__`` is an exception](https://img.shields.io/static/v1?label=WARNING&message=The%20__linit__%20function%20returns%20a%20_list_node%20*,%20not%20a%20list&color=orange)  
 ``./list.h`` also contains all function headers for the ``./list.c`` file.

### ./list.c
 ![Dependency: ./list.h](https://img.shields.io/static/v1?label=Dependency&message=./list.h&color=informational)  
 The ``./list.c`` file contains the actual implementation of all functionality, using the structs and typedefs of the ``./list.h`` file. It is divided into 7 parts (most functions return 1 when succesfull, otherwise 0. If they fail, they set ``JAY_ERRNO`` accordingly):
 * Initialization (**INIT**); contains one method:
   * ``struct _list_node __linit__()``; this method initializes an empty list. Returns ``NULL`` when failed, and sets ``JAY_ERRNO`` accordingly.  
  ![Warning: the ``__linit__`` does not return a list, but a ``struct _list_node*``](https://img.shields.io/static/v1?label=WARNING&message=The%20__linit__%20function%20returns%20a%20_list_node%20*,%20not%20a%20list&color=orange)  
    
 * Adding one element; contains three methods:
   * ``int append(list target, _list_node_type *value)``; appends a value (of the type defined in ``./list.h``).
   * ``int insert_at(list target, _list_node_type *value, int index)``; puts a value inside a list, at the position defined by ``int index``.
   * ``int insort(list target, _list_node *value, int order(_list_node_type *, _list_node_type *))``; this function inserts an element into a sorted list. 
     * The ``int order(...)`` parameter is a function pointer. This pointer should return -1 (or any negative number) when its first parameter precedes its second one, 0 when they are 'equal', and +1 (or any positive value) when its second parameter precedes its first one.  
       
  * Removing one element; contains two methods:
    * ``int removeAt(list target, int index)``; removes the element at index ``index``. 
    * ``int remove_elem(list target, _list_node_type *value, int same(_list_node_type *, _list_node_type *))``; removes the first occurence of ``value``. 
      * The ``int same(...)`` parameter is a function pointer. It should return 1 when its parameters are 'equal', otherwise 0.  
  
  * Getting data about the list; contains two methods:
    * ``int list_size(list target)``; returns the amount of items in the list, or -1 on failure. When failing, ``JAY_ERRNO`` is set.  
    * ``indexof(list target, _list_node_type *value, int same(_list_node_type *, _list_node_type *))``; returns the index of the first occurence of ``value``. Equality is determined by the ``int same(...)`` parameter, which should return 1 when both are equal.  
      
 * Adding objects in batch (each normal adding method has a batch version); contains four methods (each batch method returns ``(1 - <amount of failed insertions>)``):
   * ``int batch_append(list target, _list_node_type *values[], int amount)``; adds the first ``amount`` elements from ``values`` to the list, using the ``append`` method.
   * ``int batch_insertAt(list target, _list_node_type *values[], int amount, int firstind)``; adds the first ``amount`` elements from ``values`` to the list, starting at index ``firstind``, using the ``insert_at`` method. The order of the elements in ``values`` is preserved.
   * ``int batch_insort(list target, _list_node_type *values[], int amount, int order(...))``; adds the first ``amount`` elements of ``values`` to the list in a sorted manner. The ``insort`` method is used on each element. The ``order(...)`` parameter is described with the ``insort`` method.
   * ``int sort(list target, int order(_list_node_type *, _list_node_type *))``; sorts a list using the given comparing method. The ``int order(...)`` method should return -1 when the first parameter precedes the second one, 0 when both are 'equal', and +1 when the first parameter succeeds the second one. Upon failing, nothing happens and the method returns 0.
   * ``int stalin_sort(list target, int order(_list_node_type *, _list_node_type *))``; Stalin-sorts the list (iterates over the list and eliminates all elements that are not in the right place).  
     
 * Removing objects in batch (each normal removing method has a batch version); contains three methods (each batch method returns ``(1 - <amount of failed removals>)``):
   * ``int batch_removeAt(list target, int indexes[], int amount)``; removes the items at the given indexes from the list. Each index is corrected with the amount of succesfull removals, so the indexes should be the indexes for the items before the removal started.
   * ``int batch_remove_elem(list target, _list_node_type *values[], int amount, int same(...))``; removes the first occurence of each item in ``values``. The ``same`` parameter is used for comparison, see the ``delete_elem`` method.  
   * ``int __ldestroy__(list target)``; removes the whole list from memory.  
   ![May be unstable](https://img.shields.io/badge/May%20be%20unstable-If%20the%20removal%20fails,%20the%20list%20is%20corrupted-ff69b4)  
  
 * Printing the list; contains one method:
   * ``int printlistto(list target, FILE * restrict stream, const char *tostring(_list_node_type *))``; prints the given list to the specified stream (usually ``stdout`` or ``stderr``, but can be a file stream as well)
     * The ``tostring`` parameter determines how a ``_list_node_type *`` is converted to a string (aka ``const char *``). It can be whatever you like, it only should return a NULL-terminated string. The string is not modified or freed.

## Stack
### ./stack.h
 ![Dependency: stdlib.h](https://img.shields.io/static/v1?label=Dependency&message=stdlib.h&color=informational)  
 ![Dependency: stdio.h](https://img.shields.io/static/v1?label=Dependency&message=stdio.h&color=informational)  
 ![Dependency: ./const.h](https://img.shields.io/static/v1?label=Dependency&message=./const.h&color=informational)  
 The ``./stack.h`` file defines all structs and typedefs required for the stack structure (last-in, first-out). All will be described in order of appearance:
 * ``_stack_node_type``: this is the variable type contained within the stack. Change the ``char`` in this line to any other variable type to store other variables in it. Currently, the list needs three helper functions to enable all implemented functionality; see ``./stack.c``.
 * ``struct _stack_node``: this contains the stack nodes themselves. Each element of the stack is represented as a stack node.
 * ``stack``: ``stack`` is an alias for a pointer to a ``struct _stack_node`` pointer (aka ``struct _stack_node **``) this kind of pointer is necessary for all functionality.  
 ![Warning: the ``__sinit__`` is an exception](https://img.shields.io/static/v1?label=WARNING&message=The%20__sinit__%20function%20returns%20a%20_stack_node%20*,%20not%20a%20stack&color=orange)  
 ``./stack.h`` also contains all function headers for the ``./stack.c`` file.

 ### ./stack.c
  ![Dependency: ./stack.h](https://img.shields.io/static/v1?label=Dependency&message=./stack.h&color=informational)  
  The ``./stack.c`` file implements all functionality for the stack, in 9 methods (most of these methods return 1 when succesfull, or otherwise 0. When any of these methods fail, ``JAY_ERRNO`` is set accordingly):  
  * ``struct _stack_node *__sinit__()``; this method creates an empty stack. When failed, returns a ``NULL`` pointer and sets ``JAY_ERRNO`` accordingly.  
  ![Warning: the ``__sinit__`` method does not return a stack, but a ``struct _stack_node*``](https://img.shields.io/static/v1?label=WARNING&message=The%20__sinit__%20function%20returns%20a%20_stack_node%20*,%20not%20a%20stack&color=orange)
  * ``int push(stack target, _stack_node_type *value)`` pushes a new value onto the stack.
  * ``int batch_push(stack target, stack_node_type *values[], int amount)`` pushes the first ``amount`` values from ``values[]`` onto the stack. This reverses the order of the elements (for example, when batch pushing ``{ 1, 2, 3, 4, 5 }``, the stack's top will contain (in popping order) ``5 --> 4 --> 3 --> 2 --> 1``).
  * ``_stack_node_type *pop(stack target)`` pops (removes) the top value of the stack. Returns that value, or ``NULL`` when failed.
  * ``_stack_node_type *peek(stack target)`` peeks (looks at) the top value of the stack and returns either that value (on success) or ``NULL`` (on failure).  
  ![Candidate for renaming](https://img.shields.io/badge/Not%20OK-Candidate%20for%20renaming-red)
  * ``int batch_pop(stack target, _stack_node_type *out[], int amount)`` pops the top ``amount`` values from the stack (fails if there are less than ``amount`` values). Those values are contained within ``out[]``. Returns (1 + amount of successes), or 0 when there are less than ``amount`` values on the stack.
  * ``int stack_size(stack target)`` counts the amount of elements on the stack, and returns that number. Upon failure, returns 0.
  * ``int printstackto(stack target, FILE * restrict stream, const char *tostring(_stack_node_type *))`` prints the whole stack, top-to-bottom, using the ``tostring`` method, to the specified stream.
  * ``int __sdestroy__(stack target)`` removes the whole stack from memory.  
  ![May be unstable](https://img.shields.io/badge/May%20be%20unstable-If%20the%20removal%20fails,%20the%20stack%20is%20corrupted-ff69b4)  
