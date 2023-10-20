#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include "task.h"

// Insertion sort helper function to sort by task names
void sortTasksByName(struct node **head) {
    if (*head == NULL) return;

    struct node *sorted = NULL;

    struct node *current = *head;
    while (current != NULL) {
        struct node *next = current->next;

        if (sorted == NULL || strcmp(current->task->name, sorted->task->name) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            struct node *temp = sorted;
            while (temp->next != NULL && strcmp(current->task->name, temp->next->task->name) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;
}

// invoke the scheduler
void schedule() {
    struct node *temp;

    // Sort the tasks by name using insertion sort
    sortTasksByName(&taskList);

    // Execute tasks in the order they appear
    temp = taskList;
    while (temp != NULL) {
        run(temp->task, temp->task->burst);
        temp = temp->next;
    }
}

//Below is the implementation which we assume task came first in the file came first rather than T1 came first

// #include <stdio.h>
// #include "schedulers.h"
// #include "task.h"
// #include "cpu.h"
// #include "list.h"

// void schedule() {

//     struct node *temp = taskList;
//     while (temp) {
//         run(temp->task, temp->task->burst);
//         temp = temp->next;
//     }
//     // delete(&taskList, taskList->task);
// }