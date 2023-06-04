#include <string.h>
#include <stdio.h>
#include <time.h>
#include "receipter.h"

char g_buffer[BUFFER_SIZE];

char g_time_line[64];
char g_message[128];


unsigned int g_daily_orders = 0;
char g_items_name[10][128];
double g_items_price[10];
unsigned int g_item_index = 0;


double g_tip = 0;



int add_item(const char* name, double price)
{
    unsigned int i;
    size_t length = strlen(name);

    if (g_item_index > 9) {
        return 0;
    }

    if (length > 25) {
        length = 25;
    }

    for (i = 0; i < length; i++) {
        g_items_name[g_item_index][i] = name[i];
    }
    g_items_name[g_item_index][i] = '\0';
    g_items_price[g_item_index] = price;

    g_item_index++;
    
    return 1;
}

void set_tip(double tip)
{
    g_tip = tip;
}

void set_message(const char* message)
{
    unsigned int i;
    size_t length = strlen(message);
    if (length > 75) {
        length = 75;
    }

    if (length > 50) {

        for (i = 0; i < 50; i++) {
            g_message[i] = message[i];
        }

        g_message[i++] = '\n';

        for (; i <= length; i++) {
            g_message[i] = message[i - 1];
        }

    } else {

        for (i = 0; i < length; i++) {
            g_message[i] = message[i];
        }

    }

    g_message[i] = '\0';
}

int set_time(time_t timestamp)
{
    struct tm* t = gmtime(&timestamp);

    if (t == NULL) {
        return 0;
    }

    sprintf(g_time_line, "%d-%02d-%02d %02d:%02d:%02d", 1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    return 1;
}

int print_receipt(const char* filename, time_t timestamp)
{
    unsigned int i;
    double subtotal = 0;
    double tax = 0;
    double total = 0;

    FILE* fp;
    char receipt[BUFFER_SIZE];


    if (g_item_index == 0) {

        g_item_index = 0;
        set_tip(0);
        g_message[0] = '\0';

        return 0;
    }


    sprintf(receipt, "Charles' Seafood\n--------------------------------------------------\n");
    
    set_time(timestamp);
    sprintf(g_buffer, "%s%26s%05u\n--------------------------------------------------\n", g_time_line, " ", g_daily_orders++);
    strcat(receipt, g_buffer);

    for (i = 0; i < g_item_index; i++) {

        sprintf(g_buffer, "%33s%17.2f\n", g_items_name[i], g_items_price[i]);
        strcat(receipt, g_buffer);

        subtotal += g_items_price[i];

    }
    
    strcat(receipt, "\n");

    sprintf(g_buffer, "%33s%17.2f\n", "Subtotal", subtotal);
    strcat(receipt, g_buffer);

    if (g_tip > 0) {
        sprintf(g_buffer, "%33s%17.2f\n", "Tip", g_tip);
        strcat(receipt, g_buffer);
    }

    tax = subtotal * 0.05;
    sprintf(g_buffer, "%33s%17.2f\n", "Tax", tax);
    strcat(receipt, g_buffer);


    total = subtotal + g_tip + tax;
    sprintf(g_buffer, "%33s%17.2f\n", "Total", total);
    strcat(receipt, g_buffer);

    strcat(receipt, "\n");

    if (strlen(g_message) > 0) {
        sprintf(g_buffer, "%s\n", g_message);
        strcat(receipt, g_buffer);
    }

    strcat(receipt, "==================================================\n");

    sprintf(g_buffer, "%50s", "Tax#-51234");
    strcat(receipt, g_buffer);


    g_item_index = 0;
    set_tip(0);
    g_message[0] = '\0';


    fp = fopen(filename, "wb");
    fputs(receipt, fp);
    fclose(fp);


    return 1;
}
