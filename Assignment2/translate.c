#include <stdio.h>
#include <string.h>
#include "translate.h"


int change_case(char ch)
{
    int def = 'a' - 'A';

    if (ch >= 'A' && ch <= 'Z') {
        return ch + def;
    } else if (ch >= 'a' && ch <= 'z') {
        return ch - def;
    } else {
        return 0;
    }
}

int escape_convert(char* buffer, unsigned int buffer_size, const char* input)
{
    unsigned int index;
    unsigned int input_index;
    size_t length = strlen(input);

    if (length > BUFFER_SIZE) {
        length = BUFFER_SIZE;
    }

    index = 0;
    input_index = 0;
    while (input_index < length) {
        if (index >= buffer_size) {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }


        /* 92: \ */
        if (input[input_index] == 92) {

            if (input[input_index + 1] == 92) {
                buffer[index] = 92;

            } else if (input[input_index + 1] == 97) {
                buffer[index] = 7;

            } else if (input[input_index + 1] == 98) {
                buffer[index] = 8;

            } else if (input[input_index + 1] == 102) {
                buffer[index] = 12;

            } else if (input[input_index + 1] == 110) {
                buffer[index] = 10;

            } else if (input[input_index + 1] == 114) {
                buffer[index] = 13;

            } else if (input[input_index + 1] == 116) {
                buffer[index] = 9;

            } else if (input[input_index + 1] == 118) {
                buffer[index] = 11;

            } else if (input[input_index + 1] == 39) {
                buffer[index] = 39;

            } else if (input[input_index + 1] == 34) {
                buffer[index] = 34;

            } else {
                return ERROR_CODE_INVALID_FORMAT;

            }


            input_index += 2;
        } else {
            buffer[index] = input[input_index];

            input_index++;
        }

        index++;
    }

    return 0;
}


int convert_string(char* buffer, unsigned int buffer_size, const char* argv)
{
    int result = 0;
    unsigned int index = 0;

    char escape_buffer[BUFFER_SIZE * 2] = { 0, };
    unsigned int escape_index = 0;
    unsigned int length;

    char range_ch[2];

    result = escape_convert(escape_buffer, BUFFER_SIZE, argv);
    if (result != 0) {
        goto exit;
    }

    length = strlen(escape_buffer);
    if (length > BUFFER_SIZE) {
        length = BUFFER_SIZE;
    }

    while (escape_index < length) {

        if (index >= buffer_size) {
            result = ERROR_CODE_ARGUMENT_TOO_LONG;
            goto exit;
        }

        if (escape_buffer[escape_index] == '-' && escape_index > 0 && escape_index < length - 1 && escape_buffer[escape_index - 1] != '\0') {

            range_ch[0] = escape_buffer[escape_index - 1];
            range_ch[1] = escape_buffer[escape_index + 1];

            if (range_ch[0] > range_ch[1]) {
                result = ERROR_CODE_INVALID_RANGE;
                goto exit;
            }
            range_ch[0]++;

            while (range_ch[0] <= range_ch[1]) {

                if (index >= buffer_size) {
                    result = ERROR_CODE_ARGUMENT_TOO_LONG;
                    goto exit;
                }

                buffer[index] = range_ch[0];

                range_ch[0]++;
                index++;

            }

            escape_buffer[escape_index + 1] = '\0';
            escape_index += 2;

        } else {

            buffer[index] = escape_buffer[escape_index];

            escape_index++;
            index++;

        }




    }




exit:

    return result;
}


int translate(int argc, const char** argv)
{
    int result = 0;

    char target[BUFFER_SIZE * 2] = { 0, };
    char replace[BUFFER_SIZE * 2] = { 0, };

    char convert_characters[128] = { 0, };
    int input_ch;

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
            result = ERROR_CODE_INVALID_FLAG;
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
    }




    i = 0;
    while (target[i] != 0) {

        input_ch = target[i];
        convert_characters[input_ch] = replace[i];
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





