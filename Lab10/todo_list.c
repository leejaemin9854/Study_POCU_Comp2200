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

    const char str[] = "Head";

    todo_t* head = calloc(1, sizeof(todo_t));
    head->name = calloc(strlen(str) + 1, sizeof(char));
    strcpy(head->name, str);
    head->seq = INT_MIN;
    head->ftodo = NULL;

    result.todos = head;

    result.max = max_size;
    result.dummy = 0;

    todo_t* todo = result.todos;
    for (int i = 0; i < max_size; i++) {

        todo_t* new_todo = calloc(1, sizeof(todo_t));
        new_todo->seq = INT_MIN;

        todo->ftodo = new_todo;
        todo = todo->ftodo;

    }

    return result;
}


void finalize_todo_list(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return;
    }

    while (todo_list->todos != NULL) {

        if (todo_list->todos->name != NULL) {
            free(todo_list->todos->name);
        }

        todo_t* delete_todo = todo_list->todos;
        todo_list->todos = todo_list->todos->ftodo;
        
        free(delete_todo);

    }


    todo_list->max = 0;
    todo_list->dummy = 0;
}



bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list->dummy >= todo_list->max) {
        return false;
    }

    todo_t* new_todo = todo_list->todos;
    while (new_todo->name != NULL) {
        new_todo = new_todo->ftodo;
    }
	
    new_todo->name = calloc(strlen(task) + 1, sizeof(char));
    strcpy(new_todo->name, task);
    new_todo->seq = priority;
    

    todo_list->dummy++;

    return true;
}


bool complete_todo(todo_list_t* todo_list)
{
    if (todo_list->dummy == 0) {
        return false;
    }

    todo_t* delete_todo = todo_list->todos;
    todo_t* todo = delete_todo;

    while (todo != NULL && todo->name != NULL) {

        if (todo->seq > delete_todo->seq) {
            delete_todo = todo;
        }

        todo = todo->ftodo;
    }
    
    free(delete_todo->name);


    while (delete_todo->ftodo != NULL) {
        delete_todo->name = delete_todo->ftodo->name;
        
        delete_todo->seq = delete_todo->name == NULL ? INT_MIN : delete_todo->ftodo->seq;

        delete_todo = delete_todo->ftodo;
    }
    delete_todo->name = NULL;
    delete_todo->seq = INT_MIN;

    todo_list->dummy--;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->dummy == 0) {
        return NULL;
    }

    todo_t* todo = todo_list->todos;
    todo_t* result_todo = todo;
    while (todo != NULL) {
        
        if (todo->seq > result_todo->seq) {
            result_todo = todo;
        }

        todo = todo->ftodo;
    }

    return result_todo->name;

}

size_t get_count(const todo_list_t* todo_list)
{
    return todo_list->dummy;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->dummy == 0;
}
