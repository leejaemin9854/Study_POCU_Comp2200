#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"


char* delims_word = " ,";
char* delims_sentence = ".!?";
char* delims_paragraph = "\n\r";

char* g_document_str;

char**** g_document;


int isAlpha(const char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int isNum(const char ch)
{
	return ch >= '0' && ch <= '9';
}

int char_in_str(const char ch, const char* str)
{
	while (*str != '\0') {
		if (ch == *str) {
			return 1;
		}
		*str++;
	}
	return 0;
}

int set_document_string(const char* file_name)
{
	FILE* fp;
	char ch;
	unsigned int index;

	if ((fp = fopen(file_name, "rb")) == NULL) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	g_document_str = malloc((ftell(fp) + 1) * sizeof(char));

	fseek(fp, 0, SEEK_SET);
	index = 0;
	while ((ch = fgetc(fp)) != EOF) {
		g_document_str[index++] = ch;
	}
	g_document_str[index] = '\0';


	return 1;
}

void set_document_memory(void)
{
	char* ptr;

	unsigned int cnt;
	unsigned int i, j;


	/*paragraph size set*/
	ptr = g_document_str;
	cnt = 0;
	while (*ptr != '\0') {

		if (char_in_str(*ptr, delims_paragraph)) {

			cnt++;
			while (char_in_str(*ptr, delims_paragraph) && *ptr != '\0') {
				ptr++;
			}

		}
		else {
			ptr++;
		}

	}
	cnt++;
	g_document = malloc(cnt * sizeof(char***));


	/*sentence size set*/
	ptr = g_document_str;
	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

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
					cnt++;
				}
				ptr++;
			}

		}
		g_document[i] = malloc(cnt * sizeof(char**));

	}

	/*word size set*/
	ptr = g_document_str;
	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		for (j = 0; j < _msize(g_document[i]) / sizeof(char**); j++) {

			cnt = 0;
			while (*ptr != '\0') {

				if (char_in_str(*ptr, delims_sentence)) {

					while (!(isAlpha(*ptr) || isNum(*ptr)) && *ptr != '\0') {
						ptr++;
					}

					break;
				}
				else {

					if (char_in_str(*ptr, delims_word)) {
						
						cnt++;

						while (char_in_str(*ptr, delims_word)) {
							ptr++;
						}
					}
					else {
						ptr++;
					}

				}


			}
			g_document[i][j] = malloc((cnt + 1) * sizeof(char*));

		}


	}

	return;
}

void set_document_word(void)
{
	return;
}

int load_document(const char* document)
{
	if (set_document_string(document) == 0) {
		return 0;
	}
	
	set_document_memory();

	return 0;
}

void dispose(void)
{
	return;
}

unsigned int get_total_word_count(void)
{
	return 0;
}

unsigned int get_total_sentence_count(void)
{
	return 0;
}

unsigned int get_total_paragraph_count(void)
{
	return 0;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
	return NULL;
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
	return 0;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
	return 0;
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
	return NULL;
}

unsigned int get_sentence_word_count(const char** sentence)
{
	return 0;
}

int print_as_tree(const char* filename)
{
	return 0;
}

