#include "macros.h"
#include <string.h>

/*
SET_FUNC_HEAD_DECLARE
*/

void set_func(void* ary, int start, int count, double value_double, unsigned int size)
{
    int i = start;
    int num = (int)value_double;
    int is_inteager = num == value_double;


    if (size == sizeof(char)) {

        for (i = start; i < start + count; i++) {

            ((char*)ary)[i] = (char)value_double;

        }


    }
    else if (size == sizeof(short)) {

        for (i = start; i < start + count; i++) {

            ((short*)ary)[i] = (short)value_double;

        }

    }
    else if (size == sizeof(int) || size == sizeof(float)) {
        
        for (i = start; i < start + count; i++) {

            if (is_inteager) {
                ((int*)ary)[i] = value_double;
            } else {
                ((float*)ary)[i] = value_double;
            }
        }


    }
    else if (size == sizeof(double)) {

        for (i = start; i < start + count; i++) {

            ((double*)ary)[i] = value_double;

        }

    }



}




