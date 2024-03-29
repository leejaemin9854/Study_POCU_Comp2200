#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "todo_list.h"

void test(void)
{
    todo_list_t todo_list = init_todo_list(5U);


    assert(is_empty(&todo_list));


    assert(add_todo(&todo_list, 22, "A"));
    assert(add_todo(&todo_list, 22, "B"));
    assert(add_todo(&todo_list, 22, "C"));
    assert(add_todo(&todo_list, 22, "D"));
    assert(add_todo(&todo_list, 22, "E"));


    assert(get_count(&todo_list) == 5U);


    assert(strcmp("A", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));

    assert(strcmp("B", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));


    assert(strcmp("C", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));


    assert(strcmp("D", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));


    assert(strcmp("E", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));


    finalize_todo_list(&todo_list);
}

void test2(void)
{
    todo_list_t todo_list = init_todo_list(9U);

    assert(is_empty(&todo_list));

    assert(add_todo(&todo_list, 10, "A"));
    assert(add_todo(&todo_list, 22, "B"));
    assert(add_todo(&todo_list, 3, "C"));
    assert(add_todo(&todo_list, 34, "D"));
    assert(add_todo(&todo_list, 20, "E"));
    assert(add_todo(&todo_list, 59, "F"));
    assert(add_todo(&todo_list, 60, "G"));
    assert(add_todo(&todo_list, 55, "H"));
    assert(add_todo(&todo_list, 22, "I"));

    assert(get_count(&todo_list) == 9U);
    assert(!is_empty(&todo_list));

    assert(!add_todo(&todo_list, -5, "J"));

    assert(get_count(&todo_list) == 9U);

    assert(strcmp("G", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));

    assert(strcmp("F", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));
    
    assert(strcmp("H", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));

    assert(strcmp("D", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));
    
    assert(strcmp("B", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));

    assert(strcmp("I", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));

    assert(strcmp("E", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));
    
    assert(strcmp("A", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));
    
    assert(strcmp("C", peek_or_null(&todo_list)) == 0);
    assert(complete_todo(&todo_list));

    assert(is_empty(&todo_list));
    assert(!complete_todo(&todo_list));
    
    finalize_todo_list(&todo_list);
}

int main(void)
{
    /*
    todo_list_t todo_list = init_todo_list(10);
    todo_t* todo = NULL;

    add_todo(&todo_list, 36, "Do homework");
    add_todo(&todo_list, 11, "Play games");
    add_todo(&todo_list, 45, "Eat breakfast");
    add_todo(&todo_list, 37, "Change clothes");
    add_todo(&todo_list, 35, "Brush my teeth");
    add_todo(&todo_list, 36, "Brush my teeth2");
    add_todo(&todo_list, 37, "Brush my teeth3");
    add_todo(&todo_list, 38, "Brush my teeth4");
    add_todo(&todo_list, 39, "Brush my teeth5");
    add_todo(&todo_list, 40, "Brush my teeth6");


    todo = todo_list.todos;
    while (todo != NULL) {
        printf(" - %s\n", todo->name);
        todo = todo->ftodo;
    }
    printf("peek: %s\n\n", peek_or_null(&todo_list));

    complete_todo(&todo_list);

    todo = todo_list.todos;
    while (todo != NULL) {
        printf(" - %s\n", todo->name);
        todo = todo->ftodo;
    }
    printf("peek: %s\n\n", peek_or_null(&todo_list));
    
    finalize_todo_list(&todo_list);
    */

    /*
    todo_list_t todo_list = init_todo_list(10);

    
    add_todo(&todo_list, 36, "Do homework"); // [ "Do homework" ]
    add_todo(&todo_list, 11, "Play games"); // [ "Do homework", "Play games" ]
    add_todo(&todo_list, 40, "Eat breakfast"); // [ "Do homework", "Play games", "Eat breakfast" 
    add_todo(&todo_list, 37, "Change clothes"); // [ "Do homework", "Play games", "Eat breakfast", "Change clothes" ]
    add_todo(&todo_list, 35, "Brush my teeth"); // [ "Do homework", "Play games", "Eat breakfast", "Change clothes", "Brush my teeth" ]

    printf("%s\n", peek_or_null(&todo_list));

    complete_todo(&todo_list);
    
    printf("%s\n", peek_or_null(&todo_list));

    printf("%s\n", peek_or_null(&todo_list));

    printf("%s\n", peek_or_null(&todo_list));

    complete_todo(&todo_list);

    printf("%s\n", peek_or_null(&todo_list));

    complete_todo(&todo_list);

    printf("%s\n", peek_or_null(&todo_list));
    complete_todo(&todo_list);

    printf("%s\n", peek_or_null(&todo_list));

    
    todo_t* todo;
    todo = todo_list.todos;
    printf("{  ");
    for (int i = 0; i <= todo_list.dummy; i++) {
        printf("%s, ", todo->name);
        todo = todo->ftodo;

    }
    printf(" }\n\n");
    
    complete_todo(&todo_list);
    


    finalize_todo_list(&todo_list);

    */

    
    test();
    test2();
    

    printf("Done");
    return 0;
}
