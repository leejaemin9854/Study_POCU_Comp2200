#ifndef TRANSLATE_H
#define TRANSLATE_H

#define TRUE (1)
#define FALSE (0)

typedef enum error_code {
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER = 1,
    ERROR_CODE_INVALID_FLAG,
    ERROR_CODE_INVALID_FORMAT,
    ERROR_CODE_ARGUMENT_TOO_LONG,
    ERROR_CODE_INVALID_RANGE
} error_code_t;

#define BUFFER_SIZE 512

int change_case(char ch);

int escape_convert(char* buffer, unsigned int buffer_size, const char* input);

int convert_string(char* buffer, unsigned int buffer_size, const char* argv);

int translate(int argc, const char** argv);

#endif /* TRANSLATE_H */
