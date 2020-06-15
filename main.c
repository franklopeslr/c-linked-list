#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "linked_list.h"
#include "stack.h"

uint8_t filter(callback_param_t data)
{
	return cast_int(data) % 2 == 0;
}

void * mapper(callback_param_t data)
{
	int value = cast_int(data) * 2;
	int * ret = malloc(sizeof(int));
	*ret = value * 2;
	return ret;
}

int main(const int argc, const char * argv[])
{
	linked_list_t A = linked_list(INT), B = linked_list(INT), C = 0;
	uint32_t i;

	for(i = 0; i < 10; i++)
	{
		stack_push(A, &i);
	}
	for(i = 5; i < 15; i++)
	{
		stack_push(B, &i);
	}
	
	C = list_complement_nfree(&A, &B);
	stack_pop(C);
	
	list_show_attributes(A);
	list_show_attributes(B);
	list_show_attributes(C);

	free_list(&A);
	free_list(&B);
	stack_delete(&C);
	return 0;
}