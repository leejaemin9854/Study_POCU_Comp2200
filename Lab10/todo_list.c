#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include "todo_list.h"

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t result;

    todo_t* head = malloc(sizeof(todo_t));
    char* str = "head";

    head->name = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(head->name, str);
    
    head->seq = INT_MIN;
    head->ftodo = NULL;

    result.todos = head;

    for (int i = 0; i < max_size; i++) {
        todo_t* todo = malloc(sizeof(todo_t));
        todo->ftodo = NULL;
        todo->name = NULL;

        head->ftodo = todo;
        head = head->ftodo;
    }

    result.max = max_size;
    result.dummy = 0;

    return result;
}


void finalize_todo_list(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return;
    }

    int i = 0;
    while (todo_list->todos != NULL) {
        if (i < todo_list->dummy) {
            free(todo_list->todos->name);

        }
        
        i++;
        free(todo_list->todos);
        todo_list->todos = todo_list->todos->ftodo;
    }

    todo_list->max = 0;
    todo_list->dummy = 0;
}



bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list->dummy >= todo_list->max) {
        return false;
    }

    todo_t* last_todo = todo_list->todos;
    for (int i = 0; i < todo_list->dummy; i++) {
        last_todo = last_todo->ftodo;

    }

    last_todo->ftodo->name = malloc((strlen(task) + 1) * sizeof(char));
    strncpy(last_todo->ftodo->name, task, strlen(task));
    last_todo->ftodo->name[strlen(task)] = '\0';

    last_todo->ftodo->seq = priority;

    todo_list->dummy++;

    return true;
}


bool complete_todo(todo_list_t* todo_list)
{
    if (todo_list->dummy == 0) {
        return false;
    }
	


    todo_t* post_dtodo = todo_list->todos;
    todo_t* todo = post_dtodo;

    todo_t* last = NULL;

    for (int i = 0; i < todo_list->dummy; i++) {

        if (todo->ftodo->seq > post_dtodo->ftodo->seq) {
            post_dtodo = todo;
        }

        todo = todo->ftodo;

        if (i == todo_list->dummy - 1) {

            last = todo;
        }
    }

    todo = post_dtodo;
    post_dtodo = post_dtodo->ftodo;

    todo->ftodo = todo->ftodo->ftodo;
    free(post_dtodo->name);

    post_dtodo->ftodo = last->ftodo;
    last->ftodo = post_dtodo;
    

    todo_list->dummy--;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->dummy == 0) {
        return NULL;
    }

    
    todo_t* todo = todo_list->todos->ftodo;
    todo_t* max_seq = todo;
    for (int i = 0; i < todo_list->dummy; i++) {
        
        if (todo->seq > max_seq->seq) {
            max_seq = todo;
        }

        todo = todo->ftodo;
    }


    return max_seq->name;
}

size_t get_count(const todo_list_t* todo_list)
{
    return todo_list->dummy;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->dummy == 0;
}
