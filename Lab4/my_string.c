#include "my_string.h"

unsigned int my_strlen(const char* str)
{
	unsigned int result = 0;
	while (str[result++] != '\0');

	return result - 1;
}

void reverse(char* str)
{
	char temp;
	size_t i;
	size_t length = my_strlen(str);


	for (i = 0; i < length / 2; i++) {
		temp = str[length - i - 1];
		str[length - i - 1] = str[i];
		str[i] = temp;
	}
}


int index_of(const char* str, const char* word)
{
	unsigned int i, j;

	unsigned int length_str;
	unsigned int length_word;

	length_str = my_strlen(str);
	length_word = my_strlen(word);
	
	if (length_str == 0 || length_str < length_word)
		return -1;
	
	for (i = 0; i <= length_str - length_word; i++) {

		for (j = 0; j < length_word; j++) {
			if (str[i + j] != word[j])
				break;
			else if (j == length_word - 1)
				return i;
		}
	}

	return -1;
	
}

void reverse_by_words(char* str)
{
	unsigned int i, index;
	unsigned int length;
	length = my_strlen(str);
	
	index = 0;
	for (i = 0; i < length; i++) {

		if (str[i] == ' ') {
			str[i] = '\0';
			reverse(&str[index]);

			index = i + 1;
			str[i] = ' ';
		}
	}
	reverse(&str[index]);
}

char* tokenize(char* str_or_null, const char* delims)
{
	char* result;
	static char* temp;
	
	unsigned int i, j;
	unsigned int length_str, length_del;
	unsigned int length_temp;


	if (str_or_null != 0) {
		result = str_or_null;
	}
	else {
		result = temp;
	}

	length_str = my_strlen(result);
	length_del = my_strlen(delims);

	if (length_str == 0)
		return 0;

	for (i = 0; i < length_str; i++) {
		for (j = 0; j < length_del; j++) {

			if (result[i] == delims[j]) {

				result[i] = 0;
				
				temp = &result[i + 1];
				length_temp = my_strlen(temp);

				for (i = 0; i < length_temp; i++) {
					for (j = 0; j < length_del; j++) {
						
						if (temp[i] == delims[j])
							break;
						else if (j == length_del - 1) {
							temp = &temp[i];
							i = length_str;

							return result;
						}

					}
				}

				return result;

			}

		}
	}

	temp = &result[i];
	return result;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
	char* result;
	static char* temp;

	unsigned int i, j;
	unsigned int length_str, length_del;
	unsigned int length_temp;


	if (str_or_null != 0) {
		result = str_or_null;
	}
	else {
		result = temp;
	}

	length_str = my_strlen(result);
	length_del = my_strlen(delims);

	if (length_str == 0)
		return 0;

	for (i = 0; i < length_str; i++) {
		for (j = 0; j < length_del; j++) {

			if (result[i] == delims[j]) {

				result[i] = 0;

				temp = &result[i + 1];
				length_temp = my_strlen(temp);

				for (i = 0; i < length_temp; i++) {
					for (j = 0; j < length_del; j++) {

						if (temp[i] == delims[j])
							break;
						else if (j == length_del - 1) {
							temp = &temp[i];
							i = length_str;

							reverse(result);
							return result;
						}

					}
				}

				reverse(result);
				return result;

			}

		}
	}
	reverse(result);
	temp = &result[i];
	return result;

	
}

