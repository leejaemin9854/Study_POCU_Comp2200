#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

#define MIN(x, y) ((x) <= (y) ? (x) : (y))

#define ABS(x) ((x) >= 0 ? (x) : (x) * -1)

#define RANGE(curr, min, max) for((curr) = (min); (curr) <= (max); (curr)++)

#define RANGE_DESC(curr, max, min) for((curr) = (max); (curr) >= (min); (curr)--)

int set_func(int* ary, int start, int count, int value);

#define SET(ary, start, count, value) (set_func((int*)(ary), (int)(start), (int)(count), (int)(value)));

int set_func(int* ary, int start, int count, int value)
{
	int i = start;
	for (; i < start + count; i++) {
		ary[i] = value;
	}

	return 1;
}



#endif /* MACROS_H */
