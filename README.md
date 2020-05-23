# C Linked List

## Initialization
```
linked_list_t int_list = linked_list(INTEGER);
linked_list_t double_list = linked_list(DECIMAL);
linked_list_t string_list = linked_list(STRING);
linked_list_t char_list = linked_list(CHARACTER);
```
## Inserting
```
list_add2top(list, &data);
list_add2base(list, &data);
```

## Deleting
```
list_delete_by_index(list, index);
list_delete_by_value(list, &value);
```

## Searching
```
list_get_value_by_index(list, index);
list_get_value_by_value(list, &value);
list_get_node_by_index(list, index);
list_get_node_by_value(list, &value);
```

## Iterate
```
list_iterate(list, callback);
```

## Manipulating
```
uint8_t filter(callback_param_t data);
void * mapper(callback_param_t data);

new_list = list_filter(list, filter_function);
new_list = list_filter_nfree(list, filter_function);
new_list = list_map(list, filter_function);
new_list = list_map_nfree(list, mapper_function);
```

## Free Memory
```
free_list(list);
```