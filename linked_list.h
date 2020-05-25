#if !defined LINKED_LIST_H
#define  LINKED_LIST_H
#include <inttypes.h>

#define NLINKED_LIST_DEBUG

typedef struct linked_list * linked_list_t;
typedef struct node * node_t;
typedef enum value_type value_type_t;
typedef union value value_t;
typedef const void * const callback_param_t;

#define cast_int(ptr) *((int *) (ptr))
#define cast_double(ptr) *((double *) (ptr))
#define cast_string(ptr) (char *)(ptr)
#define cast_char(ptr) *((char *) ptr)

enum value_type
{
	INTEGER = 1,
	DECIMAL,
	CHARACTER,
	STRING
};

union value
{
	int integer;
	double decimal;
	char character;
	char * string;
};

struct node
{
	struct node * previous;
	struct node * posterior;
	value_t value;
};

struct linked_list
{
	uint32_t length;
	node_t base;
	node_t top;
	value_type_t type;
};

__attribute__((visibility("protected")))
__attribute__((malloc))
node_t node(value_type_t type, void * value, node_t previous, node_t posterior);

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
void list_iterate(linked_list_t list, void (*callback)(callback_param_t data));

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
linked_list_t list_filter(linked_list_t list, uint8_t (*test_function)(callback_param_t data));

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
linked_list_t list_filter_nfree(linked_list_t * list, uint8_t (*test_function)(callback_param_t data));

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
linked_list_t list_map(linked_list_t list, void * (*mapper)(callback_param_t data));

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
linked_list_t list_map_nfree(linked_list_t * list, void * (*mapper)(callback_param_t data));

__attribute__((visibility("protected")))
__attribute__((const))
__attribute__((nonnull(1)))
callback_param_t list_get_value_by_index(linked_list_t list, uint32_t index);

__attribute__((visibility("protected")))
__attribute__((const))
callback_param_t list_get_value_by_value(linked_list_t list, void * value);

__attribute__((visibility("protected")))
__attribute__((const))
__attribute__((nonnull(1)))
node_t list_get_node_by_index(linked_list_t list, uint32_t index);

__attribute__((visibility("protected")))
__attribute__((const))
node_t list_get_node_by_value(linked_list_t list, void * value);

__attribute__((visibility("protected")))
__attribute__((nonnull(1,3)))
void set_node_value(node_t node, value_type_t type, void * data);

__attribute__((visibility("protected")))
__attribute__((malloc))
linked_list_t linked_list(value_type_t type);

__attribute__((visibility("protected")))
__attribute__((nonnull(1)))
void free_list(linked_list_t * list);

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
void list_add2top(linked_list_t list, void * value);

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
void list_add2base(linked_list_t list, void * value);

__attribute__((visibility("protected")))
__attribute__((nonnull(1)))
void list_delete_by_index(linked_list_t list, uint32_t index);

__attribute__((visibility("protected")))
__attribute__((nonnull(1,2)))
void list_delete_by_value(linked_list_t list, void * value);

void list_show_attributes(linked_list_t list);

#endif