#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "linked_list.h"

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
		list_add2top(A, &i);
	}
	for(i = 5; i < 15; i++)
	{
		list_add2top(B, &i);
	}
	C = list_intersection_nfree(&A, &B);

	list_show_attributes(A);
	list_show_attributes(B);
	list_show_attributes(C);

	free_list(&A);
	free_list(&B);
	free_list(&C);
	return 0;
}