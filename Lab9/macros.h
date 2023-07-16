#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

#define MIN(x, y) ((x) <= (y) ? (x) : (y))

#define ABS(x) ((x) >= ((x) * -1) ? (x) : (x) * -1)

#define RANGE(curr, min, max) for((curr) = (min); (curr) <= (max); (curr)++)

#define RANGE_DESC(curr, max, min) for((curr) = (max); (curr) >= (min); (curr)--)

#define SET(ary, start, count, value) set_func((void*)(ary), (int)(start), (int)(count), (double)(value), sizeof(value))

void set_func(void* ary, int start, int count, double value_double, unsigned int size);

#endif /* MACROS_H */
