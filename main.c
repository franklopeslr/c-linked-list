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
	linked_list_t filtered = NULL, test = linked_list(INTEGER);
	uint32_t i;

	for(i = 0; i < 10; i++)
	{
		list_add2top(test, &i);
	}

	filtered = list_filter_nfree(&test, filter);
	filtered = list_map_nfree(&filtered, mapper);

	/**/
	list_show_attributes(filtered);
	/**/
	printf("filtered length: %i\n", filtered->length);
	/*printf("test length: %i\n", test->length);*/

	free_list(&test);
	free_list(&filtered);
	printf("%p %p\n", filtered, test);
	return 0;
}