#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"


char* g_document_str;

char**** g_document;

void Test_Show_Memory(void)
{
	int i = 0, j = 0;

	if (g_document == NULL) {
		return;
	}

	printf("paragraph: %u\n", _msize(g_document) / sizeof(char***));
	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		printf("[%d]paragraph - setence [%u]\n", i, _msize(g_document[i]) / sizeof(char**));
		for (j = 0; j < _msize(g_document[i]) / sizeof(char**); j++) {
			printf("[%d]sentece - word [%u]\n", j, _msize(g_document[i][j]) / sizeof(char*));
		}
		puts("");
	}

	return;
}

void Test_Show_Word(void)
{
	int i = 0, j = 0, k = 0;

	if (g_document == NULL) {
		return;
	}


	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		printf("[%u]paragraph-----------[%u]\n", i, _msize(g_document[i]) / sizeof(char**));

		for (j = 0; j < _msize(g_document[i]) / sizeof(char**); j++) {

			printf("[%u]sentence----[%u]\n", j, _msize(g_document[i][j]) / sizeof(char*));

			for (k = 0; k < _msize(g_document[i][j]) / sizeof(char*); k++) {

				printf("%s\n", g_document[i][j][k]);

			}
			puts("");
		}
		puts("\n");
	}


}

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
	FILE* fp = fopen(file_name, "rb");
	char ch;
	unsigned int index = 0;

	if (fp == NULL) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	g_document_str = calloc(sizeof(char), (ftell(fp) + 1));

	fseek(fp, 0, SEEK_SET);
	while ((ch = fgetc(fp)) != EOF) {
		g_document_str[index++] = ch;
	}

	fclose(fp);

	return 1;
}

void set_document_memory(void)
{
	const char* ptr;

	unsigned int cnt;
	unsigned int i, j;


	ptr = g_document_str;
	cnt = 0;
	while (*ptr != '\0') {
		if (char_in_str(*ptr, delims_paragraph)) {
			cnt++;
			while (char_in_str(*ptr, delims_paragraph)) {
				ptr++;
			}
		}
		else {
			ptr++;
		}

	}

	if (cnt != 0) {
		cnt += 1;
	}

	g_document = malloc(sizeof(char***) * cnt);

	ptr = g_document_str;
	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		cnt = 0;
		while (*ptr != '\0') {

			if (char_in_str(*ptr, delims_paragraph)) {

				while (char_in_str(*ptr, delims_paragraph)) {
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
		g_document[i] = malloc(sizeof(char**) * cnt);

	}


	ptr = g_document_str;
	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		for (j = 0; j < _msize(g_document[i]) / sizeof(char**); j++) {

			cnt = 0;
			while (*ptr != '\0') {
				if (char_in_str(*ptr, delims_sentence)) {

					ptr += 2;

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
			g_document[i][j] = malloc(sizeof(char*) * (cnt + 1));

		}

	}

	return;
}

void set_document_word(void)
{
	char* base;
	char* ptr;

	char* word;
	char** word_bundle;
	unsigned int index;

	unsigned int i, j, k;

	word_bundle = malloc(get_total_word_count() * sizeof(char*));
	index = 0;

	base = g_document_str;
	ptr = base;

	while (*ptr != '\0') {

		if (char_in_str(*ptr, delims_paragraph)) {

			while (char_in_str(*ptr, delims_paragraph)) {
				ptr++;
			}

			base = ptr;
		}
		else if (char_in_str(*ptr, delims_sentence)) {

			word = malloc((ptr - base + 1) * sizeof(char));
			memcpy(word, base, ptr - base);
			word[ptr - base] = '\0';
			word_bundle[index++] = word;


			while (*ptr != '\0' && !isAlpha(*ptr) && !isNum(*ptr)) {
				ptr++;
			}

			base = ptr;
		}
		else if (char_in_str(*ptr, delims_word)) {

			word = malloc((ptr - base + 1) * sizeof(char));
			memcpy(word, base, ptr - base);
			word[ptr - base] = '\0';
			word_bundle[index++] = word;


			while (char_in_str(*ptr, delims_word)) {
				ptr++;
			}

			base = ptr;
		}
		else {

			ptr++;

		}


	}


	index = 0;
	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		for (j = 0; j < _msize(g_document[i]) / sizeof(char**); j++) {

			for (k = 0; k < _msize(g_document[i][j]) / sizeof(char*); k++) {

				g_document[i][j][k] = word_bundle[index++];

			}

		}

	}

	free(word_bundle);

	return;
}

int load_document(const char* document)
{
	const char** par;

	if (!set_document_string(document)) {
		return 0;
	}

	set_document_memory();

	set_document_word();

	return 1;
}

void dispose(void)
{
	return;
}


unsigned int get_total_word_count(void)
{
	unsigned int result = 0;
	unsigned int i, j;

	if (g_document == NULL) {
		return 0;
	}

	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		for (j = 0; j < _msize(g_document[i]) / sizeof(char**); j++) {

			result += _msize(g_document[i][j]) / sizeof(char*);
		}
	}

	return result;
}

unsigned int get_total_sentence_count(void)
{
	unsigned int result = 0;
	unsigned int i;

	if (g_document == NULL) {
		return 0;
	}

	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		result += _msize(g_document[i]) / sizeof(char**);
	}

	return result;
}

unsigned int get_total_paragraph_count(void)
{
	if (g_document == NULL) {
		return 0;
	}

	return _msize(g_document) / sizeof(char***);
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
	return paragraph_index >= _msize(g_document) / sizeof(char***) ? NULL : (const char***)g_document[paragraph_index];
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
	unsigned int result = 0;
	unsigned int i;

	if (paragraph == NULL) {
		return 0;
	}

	for (i = 0; i < _msize(paragraph) / sizeof(char**); i++) {

		result += _msize(paragraph[i]) / sizeof(char*);
	}

	return result;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
	if (paragraph == NULL) {
		return 0;
	}

	return _msize(paragraph) / sizeof(char**);
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
	const char** result;
	const char*** paragraph;

	if (paragraph_index >= _msize(g_document) / sizeof(char***)) {
		return NULL;
	}

	paragraph = get_paragraph_or_null(paragraph_index);

	if (sentence_index >= _msize(g_document[paragraph_index]) / sizeof(char**)) {
		return NULL;
	}

	result = (const char**)g_document[paragraph_index][sentence_index];

	return result;
}

unsigned int get_sentence_word_count(const char** sentence)
{
	if (sentence == NULL) {
		return 0;
	}

	return _msize(sentence) / sizeof(char*);
}

int print_as_tree(const char* filename)
{
	unsigned int i, j, k;

	FILE* fp;
	if (get_total_word_count() == 0) {
		return 0;
	}

	fp = fopen(filename, "w");


	for (i = 0; i < _msize(g_document) / sizeof(char***); i++) {

		fprintf(fp, "Paragraph %d:\n", i);

		for (j = 0; j < _msize(g_document[i]) / sizeof(char**); j++) {

			fprintf(fp, "    Sentence %d:\n", j);

			for (k = 0; k < _msize(g_document[i][j]) / sizeof(char*); k++) {

				fprintf(fp, "        %s\n", g_document[i][j][k]);

			}

		}

		fprintf(fp, "\n");

	}


	fclose(fp);


	return 1;
}
