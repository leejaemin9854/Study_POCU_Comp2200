#include <stdio.h>
#include "translate.h"

#include <string.h>


int change_case(char ch)
{
	int def = 'a' - 'A';

	if (ch >= 'A' && ch <= 'Z')
		return ch + def;
	else if (ch >= 'a' && ch <= 'z')
		return ch - def;
	else
		return 0;
}

int escape_convert(char* buffer, unsigned int buffer_size, const char* input)
{
	unsigned int index;

	index = 0;
	while (*input != '\0') {
		if (index >= buffer_size) {
			return ERROR_CODE_ARGUMENT_TOO_LONG;
		}

		/* 92: \ */
		if (*input == 92) {

			switch (*(input + 1))
			{
			case 92:/*\*/
				buffer[index] = 92;/*\\*/
				break;
			case 97:/*a*/
				buffer[index] = 7;/*\a*/
				break;
			case 98:/*b*/
				buffer[index] = 8;/*\b*/
				break;
			case 102:/*f*/
				buffer[index] = 12;/*\f*/
				break;
			case 110:/*n*/
				buffer[index] = 10;/*\n*/
				break;
			case 114:/*r*/
				buffer[index] = 13;/*\r*/
				break;
			case 116:/*t*/
				buffer[index] = 9;/*\t*/
				break;
			case 118:/*v*/
				buffer[index] = 11;/*\v*/
				break;
			case 39:/*'*/
				buffer[index] = 39;/*\'*/
				break;
			case 34:/*"*/
				buffer[index] = 34;/*\"*/
				break;
			default:

				return ERROR_CODE_INVALID_FORMAT;
			}

			input += 2;
		}
		else {
			buffer[index] = *input;

			input++;
		}

		index++;
	}


	return 0;
}








int convert_string(char* buffer, unsigned int buffer_size, const char* argv)
{
	int result = 0;
	unsigned int index = 0;
	char escape_buffer[BUFFER_SIZE] = { 0, };
	unsigned int escape_index = 0;

	char range_ch[2];

	if ((result = escape_convert(escape_buffer, sizeof(escape_buffer), argv)) != 0) {
		goto out;
	}
	
	while (escape_buffer[escape_index] != '\0') {

		if (index >= buffer_size) {
			result = ERROR_CODE_ARGUMENT_TOO_LONG;
			goto out;
		}

		if (escape_buffer[escape_index] == '-' && index > 0 && index < buffer_size - 1 && escape_buffer[escape_index - 1] != '\0') {

			range_ch[0] = escape_buffer[escape_index - 1] + 1;
			range_ch[1] = escape_buffer[escape_index + 1];

			if (range_ch[0] > range_ch[1]) {
				result = ERROR_CODE_INVALID_RANGE;
				goto out;
			}

			while (range_ch[0] <= range_ch[1]) {

				if (index >= buffer_size) {
					result = ERROR_CODE_ARGUMENT_TOO_LONG;
					goto out;
				}

				buffer[index] = range_ch[0];

				range_ch[0]++;
				index++;
			}

			escape_buffer[escape_index + 1] = '\0';
			escape_index += 2;
		}
		else {
			buffer[index] = escape_buffer[escape_index];

			escape_index++;
			index++;
		}


	}


out:

	return result;
}


int translate(int argc, const char** argv)
{
	int result = 0;

	char target[BUFFER_SIZE] = { 0, };
	char replace[BUFFER_SIZE] = { 0, };

	char convert_characters[128] = { 0, };
	char input_ch;

	unsigned int i;
	unsigned int j;

	int i_flag = 0;


	if (argc != 3 && argc != 4) {
		result = ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
		goto exit;
	}

	if (argc == 4) {
		i_flag = strncmp(argv[1], "-i", 2) == 0;

		if (!i_flag) {
			result= ERROR_CODE_INVALID_FLAG;
			goto exit;
		}
	}



	result = convert_string(target, BUFFER_SIZE, argv[1 + i_flag]);
	if (result != 0) {
		goto exit;
	}

	result = convert_string(replace, BUFFER_SIZE, argv[2 + i_flag]);
	if (result != 0) {
		goto exit;
	}

	i = strlen(target);
	j = strlen(replace);
	if (i > j) {

		input_ch = replace[j - 1];

		for (; j < i; j++) {
			replace[j] = input_ch;
		}
		replace[j] = 0;

	}


	i = 0;
	while (target[i] != 0) {

		convert_characters[target[i]] = replace[i];
		if (i_flag && (input_ch = change_case(target[i])) != 0) {

			convert_characters[input_ch] = replace[i];

		}
		i++;

	}
	
	while ((input_ch = fgetc(stdin)) != EOF) {

		if (convert_characters[input_ch] != 0) {
			fputc(convert_characters[input_ch], stdout);
			continue;
		}

		fputc(input_ch, stdout);
	}


exit:

	return result;
}


