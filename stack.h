#if !defined STACK_H
#define STACK_H
#include "linked_list.h"

#define stack_init(type) linked_list(type)
#define stack_push(stack, value) list_add2top(stack, value)
#define stack_pop(stack) list_delete_top(stack)
#define stack_delete(stack) free_list(stack)

#endif