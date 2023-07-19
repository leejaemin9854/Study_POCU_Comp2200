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

	todo_t* head = calloc(1, sizeof(todo_t));
	head->seq = INT_MIN;
	head->todo_name = calloc(5, sizeof(char));
	strncpy(head->todo_name, "Head", 4);
	head->todo_name[4] = '\0';
	head->ftodo = NULL;

	result.todos = head;
	result.max = max_size;
	result.dummy = 0;

	return result;
}


void finalize_todo_list(todo_list_t* todo_list)
{
	if (todo_list == NULL) {
		return;
	}
	
	
	todo_t* dtodo = NULL;
	while (todo_list->todos != NULL) {
		dtodo = todo_list->todos;
		todo_list->todos = todo_list->todos->ftodo;
		free(dtodo->todo_name);
		free(dtodo);
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


	todo_t* ptodo = todo_list->todos;
	while (ptodo->ftodo != NULL) {
		ptodo = ptodo->ftodo;
	}
	ptodo->ftodo = todo;

	todo_list->dummy++;

	return true;
}


bool complete_todo(todo_list_t* todo_list)
{
	if (todo_list->dummy == 0) {
		return false;
	}
	
	
	todo_t* todo = todo_list->todos;
	todo_t* pmax_todo = todo;

	while (todo->ftodo != NULL) {

		if (todo->ftodo->seq > pmax_todo->ftodo->seq) {
			pmax_todo = todo;
		}
		todo = todo->ftodo;
	}

	todo = pmax_todo->ftodo;
	pmax_todo->ftodo = todo->ftodo;

	free(todo->todo_name);
	free(todo);
	
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
	todo = todo->ftodo;

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
