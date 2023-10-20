#include <stdio.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

void schedule() {
    int quantum = QUANTUM;
    while (taskList != NULL) {
        struct node *temp = taskList;
        while (temp != NULL) {
            if (temp->task->burst <= quantum) {
                run(temp->task, temp->task->burst);
                delete(&taskList, temp->task);
            } else {
                run(temp->task, quantum);
                temp->task->burst -= quantum;
            }
            temp = temp->next;
        }
    }
}