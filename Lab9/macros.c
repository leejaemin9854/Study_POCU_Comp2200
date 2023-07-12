#include "macros.h"
#include <string.h>

/*
SET_FUNC_HEAD_DECLARE
*/
void set_funcss(int* ary, int start, int count, int value)
{
    int i = start;

    for (; i < start + count; i++) {
        ary[i] = value;
    }

}

void set_func(void* ary, int start, int count, char value_char, short value_short, int value_int, float value_float, double value_double, unsigned int size)
{
    int i = start;



    if (size == sizeof(char)) {

        for (i = start; i < start + count; i++) {

            ((char*)ary)[i] = value_char;

        }


    }
    else if (size == sizeof(short)) {

        for (i = start; i < start + count; i++) {

            ((short*)ary)[i] = value_short;

        }

    }
    else if (size == sizeof(int) || size == sizeof(float)) {

        for (i = start; i < start + count; i++) {
            
            ((int*)ary)[i] = value_int;

        }


    }
    else if (size == sizeof(double)) {

        for (i = start; i < start + count; i++) {

            ((double*)ary)[i] = value_double;

        }

    }



}




