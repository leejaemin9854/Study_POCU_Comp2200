#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "document_analyzer.h"

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
	return 0;
}

void set_document_memory(void)
{
	return;
}

void set_document_word(void)
{
	return 0;
}

int load_document(const char* document)
{
	return 0;
}

void dispose(void)
{
	return;
}

unsigned int get_total_word_count(void)
{
	return NULL;
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

