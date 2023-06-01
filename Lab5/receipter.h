#ifndef RECEIPTER_H
#define RECEIPTER_H

#include <time.h>

#define TRUE (1)
#define FALSE (0)

#define BUFFER_SIZE 4096
#define LINE_LENGTH 50

int add_item(const char* name, double price);

void set_tip(double tip);

void set_message(const char* message);

int set_time(time_t timestamp);

int print_receipt(const char* filename, time_t timestamp);

#endif /* RECEIPTER_H */
