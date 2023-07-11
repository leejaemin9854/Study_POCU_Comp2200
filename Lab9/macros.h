#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) (x >= y ? x : y)

#define MIN(x, y) (x <= y ? x : y)

#define ABS(x) (x >= 0 ? x : x * -1)

#define RANGE(curr, min, max)		\
	curr=min-1;						\
	while(curr++<=max)				\


#define RANGE_DESC(curr, max, min)		\
	curr=max+1;							\
	while(curr-->=min)					\


#define RANGE_DESCS(curr, max, min) for(curr=max; curr>=min; curr--)



#define SET(ary, start, count, value) set_func((int*)ary, (int)start, (int)count, (int)value);



void set_func(int* ary, int start, int count, int value);


void set_func(int* ary, int start, int count, int value)
{
	int i = start;
	for (; i < start + count; i++) {
		ary[i] = value;
	}

}

#endif /* MACROS_H */
