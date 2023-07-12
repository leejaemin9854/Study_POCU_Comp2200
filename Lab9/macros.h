#ifndef MACROS_H
#define MACROS_H


typedef union {
	int value_int;
	float value_float;
}int_float_t;

typedef struct {

	char value[4];

}test_t;


#define MAX(x, y) ((x) >= (y) ? (x) : (y))

#define MIN(x, y) ((x) <= (y) ? (x) : (y))

#define ABS(x) ((x) >= 0 ? (x) : (x) * -1)

#define RANGE(curr, min, max) for((curr) = (min); (curr) <= (max); (curr)++)

#define RANGE_DESC(curr, max, min) for((curr) = (max); (curr) >= (min); (curr)--)

#define SET(ary, start, count, value) set_func((void*)(ary), (int)(start), (int)(count), (double)(value), sizeof(value))

void set_func(void* ary, int start, int count, double value_double, unsigned int size);

#define SET_FUNC_HEAD_DECLARE	\
	SET_FUNC(char)				\
	SET_FUNC(short)				\
	SET_FUNC(int)				\
	SET_FUNC(float)				\
	SET_FUNC(double)			\


#define SET_FUNC(type)														\
void set_func_##type(type* ary, int start, int count, type value);			\

SET_FUNC_HEAD_DECLARE

#undef SET_FUNC


#define SET_FUNC(type)														\
void set_func_##type(type* ary, int start, int count, type value)			\
{																			\
	int i;																	\
	for (i = start; i < start + count; i++) {								\
		ary[i] = value;														\
	}																		\
}																			\


#endif /* MACROS_H */
