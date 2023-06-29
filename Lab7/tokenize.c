#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

int inchar(const char ch, const char* str)
{
	while (*str != 0) {
		if (ch == *str) {
			return 1;
		}
		str++;
	}
	
	return 0;
}

char** tokenize_malloc(const char* str, const char* delim)
{
	char** result = NULL;
	size_t token_len = 0;

	char* token;
	size_t index;
	
	const char* ptr = str;
	
	while (*ptr != 0) {
		if (!inchar(*ptr, delim)) {
			ptr++;
		}
		else {
			while (inchar(*ptr, delim)) {
				if (*ptr == 0)
					break;
				ptr++;
			}
			token_len++;
		}
	}
	token_len++;// '\0'
	
	result = (char**)malloc(token_len * sizeof(char*) + 1);
	
	ptr = str;
	index = 0;
	while (*ptr != 0) {
		if (!inchar(*ptr, delim)) {
			ptr++;
		}
		else {
			if (ptr != str) {
				token = (char*)calloc(ptr - str + 1, 1);
				strncat(token, str, ptr - str);

				result[index++] = token;

				ptr++;
			}
			else {
				while (inchar(*ptr, delim)) {
					if (*ptr == 0)
						break;
					ptr++;
				}
			}

			str = ptr;
		}
	}
	if (ptr != str) {
		token = (char*)calloc(ptr - str + 1, 1);
		strncat(token, str, ptr - str);

		result[index++] = token;
	}

	return result;
}

