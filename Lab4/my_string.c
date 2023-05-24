#include "my_string.h"

static char* token_temp;

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

    if (str == 0 || word == 0)
        return -1;

    length_str = my_strlen(str);
    length_word = my_strlen(word);

    if (length_word == 0)
        return 0;
	
    if (length_str < length_word)
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
    unsigned int i;
    unsigned int j;
    unsigned int length_str, length_del;

    if (str_or_null != 0) {
        result = str_or_null;
    }
    else {
        result = token_temp;
    }

    length_str = my_strlen(result);
    length_del = my_strlen(delims);

    if (length_str == 0)
        return 0;

    for (i = 0; i < length_str; i++) {
        for (j = 0; j < length_del; j++) {

            if (result[i] == delims[j]) {

                result[i] = '\0';
                token_temp = &result[i + 1];

                while (*token_temp != '\0') {

                    for (j = 0; j < length_del; j++) {
                        if (*token_temp == delims[j])
                            break;
                    }
                    if (j == length_del) {

                        return result;

                    }
                    else {
                        token_temp++;
                    }

                }

            }

        }
    }


    token_temp = &result[i];
    return result;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* result;
    unsigned int i;
    unsigned int j;
    unsigned int length_str, length_del;

    if (str_or_null != 0) {
        result = str_or_null;
    }
    else {
        result = token_temp;
    }

    length_str = my_strlen(result);
    length_del = my_strlen(delims);

    if (length_str == 0)
        return 0;

    for (i = 0; i < length_str; i++) {
        for (j = 0; j < length_del; j++) {

            if (result[i] == delims[j]) {

                result[i] = '\0';
                token_temp = &result[i + 1];

                while (*token_temp != '\0') {

                    for (j = 0; j < length_del; j++) {
                        if (*token_temp == delims[j])
                            break;
                    }
                    if (j == length_del) {

                        reverse(result);
                        return result;

                    }
                    else {
                        token_temp++;
                    }

                }

            }

        }
    }


    token_temp = &result[i];
    reverse(result);
    return result;
}

