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

    result.todos = NULL;
    result.max = max_size;
    result.dummy = 0;

    return result;
}


void finalize_todo_list(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return;
    }
	

    todo_t* dtodo = todo_list->todos;
    while (dtodo != NULL) {
        todo_list->todos = todo_list->todos->ftodo;
        free(dtodo->todo_name);
        free(dtodo);
        dtodo = todo_list->todos;
    }


    todo_list->max = 0;
    todo_list->dummy = 0;
}



bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    if (todo_list->dummy >= todo_list->max) {
        return false;
    }
	
    todo_t* todo = calloc(1, sizeof(todo_t));
    todo->seq = priority;
    todo->todo_name = calloc(strlen(task) + 1, sizeof(char));
    strncpy(todo->todo_name, task, strlen(task));
    todo->todo_name[strlen(task)] = '\0';
    todo->ftodo = NULL;

    if (todo_list->todos == NULL) {

        todo_list->todos = todo;

    } else {

        todo_t* ptodo = todo_list->todos;
        while (ptodo->ftodo != NULL) {
            ptodo = ptodo->ftodo;
        }
        ptodo->ftodo = todo;

    }

    todo_list->dummy++;

    return true;
}


bool complete_todo(todo_list_t* todo_list)
{
    if (todo_list->dummy == 0) {
        return false;
    }
	
    todo_t head;
    head.seq = INT_MIN;
    head.ftodo = todo_list->todos;

    todo_t* todo = &head;
    todo_t* pmax_todo = todo;

    while (todo->ftodo != NULL) {

        if (todo->ftodo->seq > pmax_todo->ftodo->seq) {
            pmax_todo = todo;
        }
        todo = todo->ftodo;

    }
    
    if (pmax_todo->ftodo == todo_list->todos) {
        todo = todo_list->todos->ftodo;
        free(todo_list->todos->todo_name);
        free(todo_list->todos);
        todo_list->todos = todo;
    }
    else {
        todo = pmax_todo->ftodo;
        pmax_todo->ftodo = todo->ftodo;

        free(todo->todo_name);
        free(todo);
    }
    
    todo_list->dummy--;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    if (todo_list->dummy == 0) {
        return NULL;
    }

    todo_t* todo = todo_list->todos;
    todo_t* max = todo;
    
    while (todo != NULL) {
        if (todo->seq > max->seq) {
            max = todo;
        }

        todo = todo->ftodo;
    }

    return max->todo_name;
}

size_t get_count(const todo_list_t* todo_list)
{
    return todo_list->dummy;
}

bool is_empty(const todo_list_t* todo_list)
{
    return todo_list->dummy == 0;
}
