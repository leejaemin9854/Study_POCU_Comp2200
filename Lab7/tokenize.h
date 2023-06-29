#ifndef TOKENIZE_H
#define TOKENIZE_H

int inchar(const char ch, const char* str);

char** tokenize_malloc(const char* str, const char* delim);

#endif /* TOKENIZE_H */
