#include "pomoku.h"
#include "color.h"

#include <limits.h>

int g_board[MAX_SIZE][MAX_SIZE];

unsigned int g_row;
unsigned int g_colume;

int g_score_BLACK;
int g_score_WHITE;


void init_game(void)
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			g_board[i][j] = INT_MIN;
		}
	}

	g_row = 15u;
	g_colume = 15u;
	for (i = 0; i < g_row; i++) {
		for (j = 0; j < g_colume; j++) {
			g_board[i][j] = COLOR_NONE;
		}
	}


	g_score_BLACK = 0;
	g_score_WHITE = 0;

}

unsigned int get_row_count(void)
{
	return g_row;
}

unsigned int get_column_count(void)
{
	return g_colume;
}


int increase_row_count(void)
{
	if (g_row == MAX_SIZE)
		return 0;
	
	g_row++;
	return 1;
}

int increase_colume_count(void)
{
	if (g_colume == MAX_SIZE)
		return 0;

	g_colume++;
	return 1;
}

int decrease_row_count(void)
{
	if (g_row == MIN_SIZE)
		return 0;

	g_row--;
	return 1;
}

int decrease_colume_cout(void)
{
	if (g_colume == MIN_SIZE)
		return 0;

	g_colume--;
	return 1;
}

int get_score(const color_t color)
{
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return -1;

	return color == COLOR_BLACK ? g_score_BLACK : g_score_WHITE;
}

int spend_score(const color_t color, const int amount)
{
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;

	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < amount)
			return 0;

		g_score_BLACK -= amount;
	}
	else
	{
		if (g_score_WHITE < amount)
			return 0;

		g_score_WHITE -= amount;
	}

	return 1;
}

int get_color(const unsigned int row, const unsigned int col)
{
	return g_board[row][col] < 0 ? -1 : g_board[row][col];
}

int is_placeable(const unsigned int row, const unsigned int col)
{
	return g_board[row][col] == COLOR_NONE ? 1 : 0;
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
	if (is_placeable(row, col) == 0 || (color != COLOR_BLACK && color != COLOR_WHITE))
	{
		return 0;
	}

	g_board[row][col] = color;

	if (color == COLOR_BLACK)
		g_score_BLACK += check_new_score(color, row, col);
	else
		g_score_WHITE += check_new_score(color, row, col);

	return 1;
}

int check_new_score(const color_t color, const unsigned int row, const unsigned int col)
{
	int result = 0;
	int add_score;

	unsigned int row_pos, col_pos;

	/* row line check */
	row_pos = row;
	while (1) {
		if (row_pos == 0)
			break;

		if (g_board[row_pos - 1][col] != color)
			break;

		row_pos--;
	}
	add_score = 0;
	while (row_pos < g_row) {
		if (g_board[row_pos][col] != color)
			break;

		row_pos++;
		add_score++;
	}
	add_score = add_score >= 5 ? add_score - 4 : 0;
	result += add_score;


	/* colume line check */
	col_pos = col;
	while (1) {
		if (col_pos == 0)
			break;

		if (g_board[row][col_pos - 1] != color)
			break;

		col_pos--;
	}
	add_score = 0;
	while (col_pos < g_colume) {
		if (g_board[row][col_pos] != color)
			break;

		col_pos++;
		add_score++;
	}
	add_score = add_score >= 5 ? add_score - 4 : 0;
	result += add_score;


	/* diagonal line check ( row++, col++) */
	row_pos = row;
	col_pos = col;
	while (1) {
		if (row_pos == 0 || col_pos == 0)
			break;

		if (g_board[row_pos - 1][col_pos - 1] != color)
			break;

		row_pos--;
		col_pos--;
	}
	add_score = 0;
	while (row_pos < g_row && col_pos < g_colume) {
		if (g_board[row_pos][col_pos] != color)
			break;

		row_pos++;
		col_pos++;
		add_score++;
	}
	add_score = add_score >= 5 ? add_score - 4 : 0;
	result += add_score;


	/* diagonal line check ( row++, col--) */
	row_pos = row;
	col_pos = col;
	while (1) {
		if (row_pos == 0 || col_pos == g_colume - 1)
			break;

		if (g_board[row_pos - 1][col_pos + 1] != color)
			break;

		row_pos--;
		col_pos++;
	}
	add_score = 0;
	while (row_pos < g_row && col_pos>0) {
		if (g_board[row_pos][col_pos] != color)
			break;

		row_pos++;
		col_pos--;
		add_score++;
	}
	add_score = add_score >= 5 ? add_score - 4 : 0;
	result += add_score;

	return result;

}


int insert_row(const color_t color, const unsigned int row)
{
	unsigned int i;
	size_t j;

	if (g_row == MAX_SIZE || row > g_row)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_INSERT)
			return 0;

		g_score_BLACK -= COST_INSERT;
	}
	else
	{
		if (g_score_WHITE < COST_INSERT)
			return 0;

		g_score_WHITE -= COST_INSERT;
	}

	g_row++;
	

	for (i = 2; i <= g_row - row; i++) {
		for (j = 0; j < g_colume; j++) {
			g_board[g_row - i + 1][j] = g_board[g_row - i][j];
		}
	}

	for (j = 0; j < g_colume; j++) {
		g_board[row][j] = COLOR_NONE;
	}


	return 1;
}

int insert_column(const color_t color, const unsigned int col)
{
	unsigned int i;
	size_t j;

	if (g_colume == MAX_SIZE || col > g_colume)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_INSERT)
			return 0;

		g_score_BLACK -= COST_INSERT;
	}
	else
	{
		if (g_score_WHITE < COST_INSERT)
			return 0;

		g_score_WHITE -= COST_INSERT;
	}

	g_colume++;


	for (i = 2; i <= g_colume - col; i++) {
		for (j = 0; j < g_row; j++) {
			g_board[j][g_row - i + 1] = g_board[j][g_row - i];
		}
	}

	for (j = 0; j < g_row; j++) {
		g_board[j][col] = COLOR_NONE;
	}


	return 1;
}

int remove_row(const color_t color, const unsigned int row)
{
	unsigned int i;
	size_t j;

	if (g_row == MIN_SIZE || row > g_row)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_REMOVE)
			return 0;

		g_score_BLACK -= COST_REMOVE;
	}
	else
	{
		if (g_score_WHITE < COST_REMOVE)
			return 0;

		g_score_WHITE -= COST_REMOVE;
	}
	g_row--;


	for (i = row; i < g_row; i++) {
		for (j = 0; j < g_colume; j++) {
			g_board[i][j] = g_board[i + 1][j];
		}
	}

	for (j = 0; j < g_colume; j++) {
		g_board[g_row][j] = INT_MIN;
	}

	return 1;
}

int remove_column(const color_t color, const unsigned int col)
{
	unsigned int i;
	size_t j;

	if (g_colume == MIN_SIZE || col > g_colume)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_REMOVE)
			return 0;

		g_score_BLACK -= COST_REMOVE;
	}
	else
	{
		if (g_score_WHITE < COST_REMOVE)
			return 0;

		g_score_WHITE -= COST_REMOVE;
	}
	g_colume--;


	for (i = col; i < g_colume; i++) {
		for (j = 0; j < g_row; j++) {
			g_board[j][i] = g_board[j][i + 1];
		}
	}

	for (j = 0; j < g_row; j++) {
		g_board[j][g_colume] = INT_MIN;
	}

	return 1;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
	unsigned int i;
	int temp[MAX_SIZE] = { COLOR_NONE, };

	if (row0 >= g_row || row1 >= g_row)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_SWAP)
			return 0;

		g_score_BLACK -= COST_SWAP;
	}
	else
	{
		if (g_score_WHITE < COST_SWAP)
			return 0;

		g_score_WHITE -= COST_SWAP;
	}


	for (i = 0; i < g_colume; i++) {
		temp[i] = g_board[row0][i];
	}
	for (i = 0; i < g_colume; i++) {

		g_board[row0][i] = g_board[row1][i];
		g_board[row1][i] = temp[i];

	}

	return 1;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
	unsigned int i;
	int temp[MAX_SIZE] = { COLOR_NONE, };
	if (col0 >= g_colume || col1 >= g_colume)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_SWAP)
			return 0;

		g_score_BLACK -= COST_SWAP;
	}
	else
	{
		if (g_score_WHITE < COST_SWAP)
			return 0;

		g_score_WHITE -= COST_SWAP;
	}


	for (i = 0; i < g_row; i++) {
		temp[i] = g_board[i][col0];
	}
	for (i = 0; i < g_row; i++) {

		g_board[i][col0] = g_board[i][col1];
		g_board[i][col1] = temp[i];

	}

	return 1;

}


int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
	unsigned int i;
	
	if (src >= g_row || dst >= g_row)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_COPY)
			return 0;

		g_score_BLACK -= COST_COPY;
	}
	else
	{
		if (g_score_WHITE < COST_COPY)
			return 0;

		g_score_WHITE -= COST_COPY;
	}

	for (i = 0; i < g_colume; i++) {
		g_board[dst][i] = g_board[src][i];
	}

	return 1;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
	unsigned i;

	if (src >= g_colume || dst >= g_colume)
		return 0;
	if (color != COLOR_BLACK && color != COLOR_WHITE)
		return 0;
	if (color == COLOR_BLACK)
	{
		if (g_score_BLACK < COST_COPY)
			return 0;

		g_score_BLACK -= COST_COPY;
	}
	else
	{
		if (g_score_WHITE < COST_COPY)
			return 0;

		g_score_WHITE -= COST_COPY;
	}

	for (i = 0; i < g_colume; i++) {
		g_board[dst][i] = g_board[src][i];
	}

	for (i = 0; i < g_row; i++) {
		g_board[i][dst] = g_board[i][src];
	}

	return 1;
}
