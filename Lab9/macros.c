#include "macros.h"

void set_func(int* ary, int start, int count, int value)
{
	int i = start;
	for (; i < start + count; i++) {
		ary[i] = value;
	}

}
