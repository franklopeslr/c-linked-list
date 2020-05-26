#include <stdlib.h>
#define __STDC_WANT_LIB_EXT2__ 1
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "linked_list.h"

#define freemem(ptr) free((ptr)); \
					 ptr = NULL

node_t node(value_type_t type, void * value, node_t previous, node_t posterior)
{
	node_t node = (node_t) malloc(sizeof(struct node));

	if(node == NULL)
	{
		return NULL;
	}

	node->previous = previous;
	node->posterior = posterior;
	set_node_value(node, type, value);
	return node;
}

void * node_get_value(node_t node, value_type_t type)
{
	switch(type)
	{
		case STRING: return node->value.string;
		break;
		case INTEGER: return &(node)->value.integer;
		break;
		case DECIMAL: return &(node)->value.decimal;
		break;
		case CHARACTER: return &(node)->value.character;
		break;
	}
}

uint8_t node_cmp_value(node_t node_a, node_t node_b, value_type_t type)
{
	uint8_t retval = 0;

	switch(type)
	{
		case STRING:
		if(strcmp(node_a->value.string, node_b->value.string) == 0)
		{
			retval = 1;
		}
		break;

		case INTEGER:
		if(node_a->value.integer == node_b->value.integer)
		{
			retval = 1;
		}
		break;

		case DECIMAL:
		if(node_a->value.decimal == node_b->value.decimal)
		{
			retval = 1;
		}
		break;

		case CHARACTER:
		if(node_a->value.character == node_b->value.character)
		{
			retval = 1;
		}
		break;
	}
	return retval;
}

void list_iterate(linked_list_t list, void (*callback)(callback_param_t data))
{
	if(list == NULL || list->base == NULL || list->length == 0 || callback == NULL)
	{
		return;
	}

	node_t current = 0;

	for(current = list->base; current != NULL; current = current->posterior)
	{
		switch(list->type)
		{
			case STRING: callback(current->value.string);
			break;
			case INTEGER: callback(&(current)->value.integer);
			break;
			case DECIMAL: callback(&(current)->value.decimal);
			break;
			case CHARACTER: callback(&(current)->value.character);
			break;
		}
	}
}

linked_list_t list_filter(linked_list_t list, uint8_t (*test_function)(callback_param_t data))
{
	if(list == NULL || list->base == NULL || list->length == 0 || test_function == NULL)
	{
		return NULL;
	}

	node_t current = 0;
	linked_list_t filtered_list = linked_list(list->type);

	for(current = list->base; current != NULL; current = current->posterior)
	{
		switch(list->type)
		{
			case STRING:
			if(test_function(&(current)->value.string))
			{
				list_add2top(filtered_list, current->value.string);
			}
			break;

			case INTEGER:
			if(test_function(&(current)->value.integer))
			{
				list_add2top(filtered_list, &(current)->value.integer);
			}
			break;

			case DECIMAL:
			if(test_function(&(current)->value.decimal))
			{
				list_add2top(filtered_list, &(current)->value.decimal);
			}
			break;

			case CHARACTER:
			if(test_function(&(current)->value.character))
			{
				list_add2top(filtered_list, &(current)->value.character);
			}
			break;
		}
	}
	return filtered_list;
}

linked_list_t list_filter_nfree(linked_list_t * list, uint8_t (*test_function)(callback_param_t data))
{
	if(list == NULL || test_function == NULL)
	{
		return NULL;
	}
	
	linked_list_t filtered_list = list_filter(*list, test_function);
	free_list(list);
	return filtered_list;
}

linked_list_t list_map(linked_list_t list, void * (*mapper)(callback_param_t data))
{
	if(list == NULL || list->base == NULL || list->length == 0 || mapper == NULL)
	{
		return NULL;
	}

	node_t current = 0;
	linked_list_t filtered_list = linked_list(list->type);
	void * returned = 0;

	#define LOCAL_MEMCPY(type, typename)				\
	returned = mapper(&(current)->value.typename);		\
	if(returned != NULL)								\
	{													\
		int buf = cast_##type(returned);				\
		freemem(returned);								\
		list_add2top(filtered_list, &buf);				\
	}

	for(current = list->base; current != NULL; current = current->posterior)
	{
		switch(list->type)
		{
			case STRING:
			returned = mapper(current->value.string);

			if(returned != NULL)
			{
				char * buf = strdup((char *) returned);

				if(buf != NULL)
				{
					freemem(returned);
					list_add2top(filtered_list, buf);
				}
			}
			break;

			case INTEGER:
			LOCAL_MEMCPY(int, integer);
			break;

			case DECIMAL:
			LOCAL_MEMCPY(double, decimal);
			break;

			case CHARACTER:
			LOCAL_MEMCPY(char, character);
			break;
		}
	}
	#undef LOCAL_MEMCPY
	return filtered_list;
}

linked_list_t list_map_nfree(linked_list_t * list, void * (*mapper)(callback_param_t data))
{
	if(list == NULL || mapper == NULL)
	{
		return NULL;
	}

	linked_list_t filtered_list = list_map(*list, mapper);
	free_list(list);
	return filtered_list;
}

callback_param_t list_get_value_by_index(linked_list_t list, uint32_t index)
{
	if(list == NULL || index >= list->length)
	{
		return NULL;
	}

	node_t current = list->base;
	uint32_t i;

	for(i = 0; i < index && current != NULL; i++, current = current->posterior);
	switch(list->type)
	{
		case STRING: return current->value.string;
		break;
		case INTEGER: return &(current)->value.integer;
		break;
		case DECIMAL: return &(current)->value.decimal;
		break;
		case CHARACTER: return &(current)->value.character;
		break;
	}
}

callback_param_t list_get_value_by_value(linked_list_t list, void * value)
{
	if(list == NULL || value == NULL)
	{
		return NULL;
	}

	node_t current = list->base;

	for(; current != NULL; current = current->posterior)
	{
		switch(list->type)
		{
			case STRING:
			if(strncmp(current->value.string, value, strlen(current->value.string)) == 0)
			{
				return current->value.string;
			}
			break;

			case INTEGER:
			if(current->value.integer == cast_int(value))
			{
				return &(current)->value.integer;
			}
			break;

			case DECIMAL:
			if(current->value.decimal == cast_double(value))
			{
				return &(current)->value.decimal;
			}
			break;

			case CHARACTER: 
			if(current->value.character == cast_char(value))
			{
				return &(current)->value.character;
			}
			break;
		}
	}

	return NULL;
}

node_t list_get_node_by_index(linked_list_t list, uint32_t index)
{
	if(list == NULL || index >= list->length)
	{
		return NULL;
	}

	node_t current = list->base;
	uint32_t i;

	for(i = 0; i < index && current != NULL; i++, current = current->posterior);
	return current;
}

node_t list_get_node_by_value(linked_list_t list, void * value)
{
	if(list == NULL || value == NULL)
	{
		return NULL;
	}

	node_t current = list->base;

	for(; current != NULL; current = current->posterior)
	{
		switch(list->type)
		{
			case STRING:
			if(strncmp(current->value.string, value, strlen(current->value.string)) == 0)
			{
				return current;
			}
			break;

			case INTEGER:
			if(current->value.integer == cast_int(value))
			{
				return current;
			}
			break;

			case DECIMAL:
			if(current->value.decimal == cast_double(value))
			{
				return current;
			}
			break;

			case CHARACTER: 
			if(current->value.character == cast_char(value))
			{
				return current;
			}
			break;
		}
	}

	return NULL;
}


void set_node_value(node_t node, value_type_t type, void * data)
{
	value_t value;

	switch(type)
	{
		case INTEGER:
			value.integer = *((int *) data);
			break;

		case DECIMAL:
			value.decimal = *((double *) data);
			break;

		case CHARACTER:
			value.character = *((char *) data);
			break;

		case STRING:
			value.string = strdup((char *) data);
			break;

		default: return;
	}

	node->value = value;
}

linked_list_t linked_list(value_type_t type)
{
	linked_list_t list = (linked_list_t) malloc(sizeof(struct linked_list));
	int value = 0;

	if(list == NULL)
	{
		return NULL;
	}

	list->type = type;
	list->base = NULL;
	list->top = NULL;
	list->length = 0;
	return list;
}

void free_list(linked_list_t * $list)
{
	linked_list_t list = *$list;

	if(list == NULL)
	{
		return;
	}

	if(list->base != NULL)
	{
		node_t current = list->base;

		for(;current != NULL;)
		{
			node_t aux = current->posterior;

			if(list->type == STRING && current->value.string != NULL)
			{
				#if defined LINKED_LIST_DEBUG
				printf("deleting string `%-20s` at %-20p\n", current->value.string, current->value.string);
				#endif
				freemem(current->value.string);
			}

			#if defined LINKED_LIST_DEBUG
			printf("deleting at %-20p\n", current);
			#endif

			freemem(current);
			current = aux;
			list->length -= 1;
		}
	}
	freemem(*$list);
}

/* manipulating */

void list_add2top(linked_list_t list, void * value)
{
	if(list == NULL)
	{
		return;
	}

	if(list->length == 0)
	{
		/* head --> new_node */
		node_t new_node = node(list->type, value, NULL, NULL);

		list->base = new_node;
		list->top = list->base;
	}
	else
	{
		/* head --> node --> node --> ... --> top --> new_node */
		node_t old_top = list->top;
		node_t new_node = node(list->type, value, old_top, NULL);
		old_top->posterior = new_node;
		list->top = new_node;
	}
	list->length += 1;
}

void list_add2base(linked_list_t list, void * value)
{
	if(list == NULL)
	{
		return;
	}

	if(list->length == 0)
	{
		/* new_node (base) --> old base (new top) */
		node_t new_node = node(list->type, value, NULL, list->base);
		list->base = new_node;
		list->top = list->base;
	}
	else
	{
		/* new_node (base) --> old base --> node --> ... --> top */
		node_t new_node = node(list->type, value, NULL, list->base);
		list->base->previous = new_node;
		list->base = new_node;
	}
	list->length += 1;
}

void list_delete_by_index(linked_list_t list, uint32_t index)
{
	if(list == NULL || list->length == 0 || index >= list->length)
	{
		return;
	}

	node_t node = list_get_node_by_index(list, index);

	node_t previous = node->previous;
	node_t posterior = node->posterior;
	previous->posterior = posterior;
	posterior->previous = previous;
	freemem(node);
	list->length -= 1;
}

void list_delete_by_value(linked_list_t list, void * value)
{
	if(list == NULL || list->length == 0)
	{
		return;
	}

	node_t node = list_get_node_by_value(list, value);

	if(node == NULL)
	{
		return;
	}

	node_t previous = node->previous;
	node_t posterior = node->posterior;
	previous->posterior = posterior;
	posterior->previous = previous;
	freemem(node);
	list->length -= 1;
}

linked_list_t list_union(linked_list_t A, linked_list_t B)
{
	if(A == NULL || B == NULL || A->length == 0 || B->length == 0 || A->type != B->type)
	{
		return NULL;
	}
	linked_list_t new_list = linked_list(A->type);
	node_t current = 0;

	for(current = A->base; current != NULL; current = current->posterior)
	{
		list_add2top(new_list, node_get_value(current, new_list->type));
	}
	for(current = B->base; current != NULL; current = current->posterior)
	{
		list_add2top(new_list, node_get_value(current, new_list->type));
	}
	return new_list;
}

linked_list_t list_union_nfree(linked_list_t * A, linked_list_t * B)
{
	linked_list_t new_list = list_union(*A, *B);
	free_list(A);
	free_list(B);
	return new_list;
}

linked_list_t list_intersection(linked_list_t A, linked_list_t B)
{
	if(A == NULL || B == NULL || A->length == 0 || B->length == 0 || A->type != B->type)
	{
		return NULL;
	}

	linked_list_t new_list = linked_list(A->type);
	node_t current_A = 0, current_B = 0;

	for(current_A = A->base; current_A != NULL; current_A = current_A->posterior)
	{
		for(current_B = B->base; current_B != NULL; current_B = current_B->posterior)
		{
			if(node_cmp_value(current_A, current_B, new_list->type))
			{
				list_add2top(new_list, node_get_value(current_A, new_list->type));
			}
		}
	}
	return new_list;
}

linked_list_t list_intersection_nfree(linked_list_t * A, linked_list_t * B)
{
	linked_list_t new_list = list_intersection(*A, *B);
	free_list(A);
	free_list(B);
	return new_list;
}

void list_show_attributes(linked_list_t list)
{
	if(list == NULL || list->base == NULL || list->length == 0)
	{
		return;
	}

	node_t current = list->base;
	int cc_fmt = 0;

	#define LOCAL_DRAW_LINES(n)							\
	printf("+");										\
	for(cc_fmt = 0;cc_fmt < (n); cc_fmt++) printf("-");	\
	printf("+");										\
	for(cc_fmt = 0;cc_fmt < (n); cc_fmt++) printf("-");	\
	printf("+\n")										

	LOCAL_DRAW_LINES(40);
	printf("|%-40s|%-40s|\n", "value", "address");
	LOCAL_DRAW_LINES(40);


	for(; current != NULL; current = current->posterior)
	{
		switch(list->type)
		{
			case INTEGER:
				printf("|%-40i", current->value.integer);
				break;

			case DECIMAL:
				printf("|%-20.20lf", current->value.decimal);
				break;

			case CHARACTER:
				printf("|%-40c", current->value.character);
				break;

			case STRING:
				printf("|%-40s", current->value.string);
				break;
			default: return;
		}
		printf("|%-40p|\n", current);
	}

	LOCAL_DRAW_LINES(40);
	#undef LOCAL_DRAW_LINES
}