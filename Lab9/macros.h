#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) >= (y) ? (x) : (y))

#define MIN(x, y) ((x) <= (y) ? (x) : (y))

#define ABS(x) ((x) >= 0 ? (x) : (x) * -1)

#define RANGE(curr, min, max) for((curr) = (min); (curr) <= (max); (curr)++)

#define RANGE_DESC(curr, max, min) for((curr) = (max); (curr) >= (min); (curr)--)

#define SET(ary, start, count, value) set_func((void*)(ary), (int)(start), (int)(count), (char)(value), (short)(value), (int)value, (float)value, (double)(value), sizeof(value))

void set_func(void* ary, int start, int count, char value_char, short value_short, int value_int, float value_float, double value_double, unsigned int size);

/*
{																		\
	switch (sizeof(value))												\
	{																	\
		case sizeof(char) :												\
			set_func_char((char*)(ary), (start), (count), (value));		\
			break;														\
		case sizeof(short) :											\
			set_func_short((short*)(ary), (start), (count), (value));	\
			break;														\
		case sizeof(int) :												\
			set_func_int((int*)(ary), (start), (count), (value));		\
			break;														\
		case sizeof(float) :											\
			set_func_float((float*)(ary), (start), (count), (value));	\
			break;														\
		case sizeof(double) :											\
			set_func_double((double*)(ary), (start), (count), (value));	\
			break;														\
	}																	\
}																		\
*/

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
