#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parentheses.h"

int char_in_str(const char ch, const char* str)
{
	while (*str != '\0') {
		if (ch == *str++) {
			return 1;
		}
	}

	return 0;
}

int math_abs(const int num1, const int num2)
{
	return num1 >= num2 ? num1 - num2 : num2 - num1;
}



size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
	size_t result = 0;
	int i;
	size_t str_size;
	unsigned int str_index = 0;

	char* par_stack;
	char* par_index_stack;
	size_t stack_index = 0;

	char open_parent[] = { '{','(','[','<' }, close_parent[] = { '}',')',']','>' };

	ringbuffer->start_index = 0;

	str_size = strlen(str);
	par_stack = malloc(sizeof(char) * str_size);
	par_index_stack = malloc(sizeof(char) * str_size);
	
	while (str[str_index] != '\0') {

		if (char_in_str(str[str_index], open_parent)) {

			par_stack[stack_index] = str[str_index];
			par_index_stack[stack_index] = str_index;
			
			stack_index++;

		}
		else if (char_in_str(str[str_index], close_parent)) {

			for (i = stack_index - 1; i >= 0; i--) {

				if (math_abs(str[str_index], par_stack[i]) < 3) {
					
					ringbuffer->parentheses[result % ringbuffer->max_size].opening_index = par_index_stack[i];
					ringbuffer->parentheses[result % ringbuffer->max_size].closing_index = str_index;

					result++;

					while (i < stack_index - 1) {
						par_stack[i] = par_stack[i + 1];
						par_index_stack[i] = par_index_stack[i + 1];
						i++;
					}
					stack_index--;

					break;
				}
				


			}

		}

		str_index++;
	}


	free(par_stack);
	par_stack = NULL;

	free(par_index_stack);
	par_index_stack = NULL;


	if (result > ringbuffer->max_size) {
		ringbuffer->start_index = result % ringbuffer->max_size;
	}
	
	return result;
}
