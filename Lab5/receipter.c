#include <string.h>
#include <stdio.h>
#include <time.h>
#include "receipter.h"

char g_buffer[BUFFER_SIZE];
char g_time_line[64];
char g_message[128];


unsigned int daily_orders = 0;
char g_items[10][64];
unsigned int g_item_index = 0;


double g_sub_total = 0;
double g_tip = 0;



int add_item(const char* name, double price)
{
	if (g_item_index == 10) {
		return 0;
	}

	if (strlen(name) > 25u || price > 999.99f || price < 0) {
		return 0;
	}


	sprintf(g_buffer, "%33s%17.2f\n", name, price);
	strcpy(&g_items[g_item_index][0], g_buffer);

	g_item_index++;
	g_sub_total += price;

	return 1;
}

void set_tip(double tip)
{
	if (tip < 0 || tip > 999.99f)
		return;

	g_tip = tip;
}

void set_message(const char* message)
{
	unsigned int i;
	size_t lenth = strlen(message);

	if (lenth > 75) {
		return;
	}

	if (lenth > 50) {

		for (i = 0; i < 50; i++) {
			g_buffer[i] = message[i];
		}
		g_buffer[i++] = '\n';
		for (; i <= lenth; i++) {
			g_buffer[i] = message[i - 1];
		}

	}
	else {
		for (i = 0; i < lenth; i++) {
			g_buffer[i] = message[i];
		}
	}
	g_buffer[i++] = '\n';
	g_buffer[i] = '\0';

	
	sprintf(g_message, g_buffer);
	return;
}

int set_time(time_t timestamp)
{
	struct tm tm = *localtime(&timestamp);

	if (timestamp < 0)
		return 0;

	sprintf(g_time_line, "%d-%02d-%02d.%02d:%02d:%02d", 1900 + tm.tm_year, 1 + tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return 1;

}

int print_receipt(const char* filename, time_t timestamp)
{
	int i = 0;
	double tax = 0, total = 0;

	char receipt[BUFFER_SIZE];

	FILE* fp;
	
	if (g_item_index == 0) {
		return 0;
	}

	sprintf(receipt, "Charles'.Seafood\n");
	strcat(receipt, "--------------------------------------------------\n");

	set_time(time(NULL));
	sprintf(&receipt[strlen(receipt)], "%s%26s%05d\n", g_time_line, " ", ++daily_orders);
	strcat(receipt, "--------------------------------------------------\n");

	for (i = 0; i < g_item_index; i++) {
		strcat(receipt, g_items[i]);
	}
	strcat(receipt, "\n");

	tax = g_sub_total * 0.05f + 0.005f;
	total = g_sub_total + g_tip + tax;

	sprintf(g_buffer, "%33s%17.2f\n%33s%17.2f\n%33s%17.2f\n%33s%17.2f\n\n", "Subtotal", g_sub_total, "Tip", g_tip, "Tax", tax, "Total", total);
	strcat(receipt, g_buffer);

	if (strlen(g_message) > 0)
		strcat(receipt, g_message);

	strcat(receipt, "==================================================\n");

	sprintf(&receipt[strlen(receipt)], "%50s", "Tax#-51234");


	g_item_index = 0;
	g_message[0] = '\0';
	g_sub_total = 0;
	g_tip = 0;

	fp = fopen(filename, "w");
	fputs(receipt, fp);
	fclose(fp);

	return 1;

}
