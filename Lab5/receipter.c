#include <stdio.h>
#include <time.h>
#include "receipter.h"

char receipt[RECEIPT_LENGTH];
char time_string[64] = "";
char thank_message[128] = "";

int daily_orders = 0;

char items[10][64];
unsigned int item_index = 0;
double g_tip = 0;
double sub_total = 0;


int add_item(const char* name, double price)
{
	char buffer[60];


	if (item_index == 10)
		return 0;

	if (strlen(name) > 25 || price > 999.99f || price < 0)
		return 0;


	sprintf(buffer, "%33s%17.2f\n", name, price);
	strcpy(&items[item_index][0], buffer);

	item_index++;
	sub_total += price;

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
	unsigned int i = 0;
	size_t length = strlen(message);

	char buffer[128];

	if (length > 75)
	{
		return;
	}

	if (length > 50)
	{
		for (i = 0; i < 50; i++) {
			buffer[i] = message[i];
		}

		buffer[i++] = '\n';

		for (; i <= length; i++) {
			buffer[i] = message[i - 1];
		}

	}
	else
	{
		for (i = 0; i < length; i++) {
			buffer[i] = message[i];
		}
	}
	buffer[i++] = '\n';
	buffer[i] = '\0';

	strcpy(thank_message, buffer);
	return;
}


int set_time(time_t timestamp)
{
	struct tm tm = *localtime(&timestamp);

	if (timestamp < 0)
		return 0;

	sprintf(time_string, "%d-%02d-%02d.%02d:%02d:%02d", 1900 + tm.tm_year, 1+tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return 1;
	
}

int file_check(const char* filename)
{
	int result = 0;
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		result = 0;
	}
	else {
		result = 1;
	}

	fclose(fp);

	return result;
}


int print_receipt(const char* filename, time_t timestamp)
{
	int i = 0;
	double tax = 0, total = 0;

	FILE* receipt_file;

	if (file_check(filename) == 0)
		return 0;

	if (item_index == 0)
		return 0;

	receipt_file = fopen(filename, "w");

	sprintf(receipt, "Charles'.Seafood\n");
	strcat(receipt, "--------------------------------------------------\n");

	set_time(time(NULL));
	strcat(receipt, time_string);
	sprintf(&receipt[strlen(receipt)], "%26s%05d\n", " ", ++daily_orders);
	strcat(receipt, "--------------------------------------------------\n");

	for (i = 0; i < item_index; i++) {
		strcat(receipt, items[i]);
	}

	strcat(receipt, "\n");

	tax = sub_total * 0.05f + 0.005f;
	total = sub_total + g_tip + tax;

	sprintf(&receipt[strlen(receipt)], "%33s%17.2f\n", "Subtotal", sub_total);
	sprintf(&receipt[strlen(receipt)], "%33s%17.2f\n", "Tip", g_tip);
	sprintf(&receipt[strlen(receipt)], "%33s%17.2f\n", "Tax", tax);
	sprintf(&receipt[strlen(receipt)], "%33s%17.2f\n", "Total", total);

	strcat(receipt, "\n");


	if (strcmp(thank_message, "") != 0) {
		strcat(receipt, thank_message);
	}

	strcat(receipt, "==================================================\n");

	sprintf(&receipt[strlen(receipt)], "%50s", "Tax#-51234");	

	
	fwrite(receipt, 1, strlen(receipt), receipt_file);

	fclose(receipt_file);
	
	item_index = 0;
	sub_total = 0;
	g_tip = 0;
	strcpy(thank_message, "");

	return 1;
}
