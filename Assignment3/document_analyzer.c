#include <stdio.h>
#include "document_analyzer.h"
#include <stdlib.h>
#include <string.h>

#define delims_word " ,"
#define delims_sentence ".!?"
#define delims_paragraph "\n\r"


char**** g_document;

int char_in_str(const char ch, const char* str)
{
    while (*str != 0) {
        if (ch == *str) {
            return 1;
        }
        str++;
    }

    return 0;
}

int load_document(const char* document)
{
    char**** result;

    char* document_str;
    char ch;
    unsigned int index = 0;


    char* ptr;
    char* token;
    int cnt;
    size_t size;

    unsigned int i, j;

    FILE* fp = fopen(document, "rb");
    if (fp == NULL) {
        return FALSE;
    }
    fseek(fp, 0, SEEK_END);
    document_str = (char*)calloc(sizeof(char), ftell(fp));
    fseek(fp, 0, SEEK_SET);
    while ((ch = fgetc(fp)) != EOF) {
        document_str[index++] = ch;
    }

    ptr = document_str;
    cnt = 0;
    while (*ptr != '\0') {

        if (char_in_str(*ptr, delims_paragraph)) {

            while (char_in_str(*ptr, delims_paragraph)) {
                if (*ptr == '\0') {
                    break;
                }
                ptr++;
            }
            cnt++;

        }
        else {

            ptr++;

        }

    }
    cnt++;
    result = (char****)calloc(sizeof(char***), cnt);

    ptr = document_str;
    size = _msize(result) / sizeof(char***);
    for (i = 0; i < size; i++) {
        
        cnt = 0;
        while (*ptr != '\0') {

            if (char_in_str(*ptr, delims_paragraph)) {

                while (char_in_str(*ptr, delims_paragraph) && *ptr != '\0') {
                    ptr++;
                }

                break;
            }
            else {

                if (char_in_str(*ptr, delims_sentence)) {

                    while (char_in_str(*ptr, delims_sentence) && *ptr != '\0') {
                        ptr++;
                    }

                    cnt++;
                }
                else {
                    ptr++;
                }

            }

        }
        result[i] = (char***)calloc(sizeof(char**), cnt);

    }


    



    free(document_str);
    document_str = NULL;


    return TRUE;
}




