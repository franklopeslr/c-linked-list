# C Linked List

## Initialization
```C
linked_list_t int_list = linked_list(INTEGER);
linked_list_t double_list = linked_list(DECIMAL);
linked_list_t string_list = linked_list(STRING);
linked_list_t char_list = linked_list(CHARACTER);
```
## Inserting
```C
list_add2top(list, &data);
list_add2base(list, &data);

// exemple
int ival = 1;
double dval = 1.0;
char cval = 'a';
char * sval = "hello";

list_add2top(string_list, sval);
list_add2top(char_list, &cval);
list_add2top(int_list, &ival);
list_add2top(double_list, &dval);
```

## Deleting
```C
list_delete_by_index(list, index);
list_delete_by_value(list, &value);

// exemple
list_delete_by_index(string_list, 1);
list_delete_by_index(char_list, 2);
list_delete_by_index(int_list, 3);
list_delete_by_index(double_list, 4);

list_delete_by_value(string_list, "hello");
list_delete_by_value(char_list, 'g');
list_delete_by_value(int_list, 34);
list_delete_by_value(double_list, 2.71);
```

## Searching
```C
list_get_value_by_index(list, index);
list_get_value_by_value(list, &value);
list_get_node_by_index(list, index);
list_get_node_by_value(list, &value);

// exemple
int ival = int_cast(list_get_value_by_index(int_list, 1));
int dval = int_double(list_get_value_by_index(double_list, 2));
int cval = int_char(list_get_value_by_index(char_list, 3));
int sval = int_string(list_get_value_by_index(string_list, 4));

```

## Iterate
```C
void callback(callback_param_t data);

list_iterate(list, callback);
```

## Manipulating
```C
uint8_t filter(callback_param_t data);
void * mapper(callback_param_t data);

new_list = list_filter(list, filter_function);
new_list = list_filter_nfree(list, filter_function);
new_list = list_map(list, filter_function);
new_list = list_map_nfree(list, mapper_function);
```

## Free Memory
```C
free_list(list);
```

# Functions
```C
node_t node(value_type_t type, void * value, node_t previous, node_t posterior);

void list_iterate(linked_list_t list, void (*callback)(callback_param_t data));

linked_list_t list_filter(linked_list_t list, uint8_t (*test)(callback_param_t data));

linked_list_t list_filter_nfree(linked_list_t list, uint8_t (*test)(callback_param_t data));

linked_list_t list_map(linked_list_t list, void * (*mapper)(callback_param_t data));

linked_list_t list_map_nfree(linked_list_t list, void * (*mapper)(callback_param_t data));

callback_param_t list_get_value_by_index(linked_list_t list, uint32_t index);

callback_param_t list_get_value_by_value(linked_list_t list, void * value);

node_t list_get_node_by_index(linked_list_t list, uint32_t index);

node_t list_get_node_by_value(linked_list_t list, void * value);

void set_node_value(node_t node, value_type_t type, void * data);

linked_list_t linked_list(value_type_t type);

void free_list(linked_list_t list);

void list_add2top(linked_list_t list, void * value);

void list_add2base(linked_list_t list, void * value);

void list_delete_by_index(linked_list_t list, uint32_t index);

void list_delete_by_value(linked_list_t list, void * value);

void list_show_attributes(linked_list_t list);
```