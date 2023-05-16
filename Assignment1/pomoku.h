#ifndef POMOKU_H
#define POMOKU_H

#include "color.h"

void show(void);

#define MAX_SIZE 20
#define MIN_SIZE 10

#define COST_INSERT 3
#define COST_REMOVE 3
#define COST_SWAP 2
#define COST_COPY 4

void init_game(void);

unsigned int get_row_count(void);

unsigned int get_column_count(void);

int increase_row_count(void);

int increase_colume_count(void);

int decrease_row_count(void);

int decrease_colume_cout(void);



int get_score(const color_t color);

int spend_score(const color_t color, const int amount);

int get_color(const unsigned int row, const unsigned int col);

int is_placeable(const unsigned int row, const unsigned int col);

int place_stone(const color_t color, const unsigned int row, const unsigned int col);

int check_new_score(const color_t color, const unsigned int row, const unsigned int col);


/* special moves */
int insert_row(const color_t color, const unsigned int row);

int insert_column(const color_t color, const unsigned int col);

int remove_row(const color_t color, const unsigned int row);

int remove_column(const color_t color, const unsigned int col);

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1);

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1);

int copy_row(const color_t color, const unsigned int src, const unsigned int dst);

int copy_column(const color_t color, const unsigned int src, const unsigned int dst);

#endif /* POMOKU_H */
