#include <stdio.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

void schedule() {
    struct node *temp;
    int quantum = QUANTUM;
    int maxPriority;

    while (taskList != NULL) {
        temp = taskList;
        maxPriority = temp->task->priority;

        // Find tasks with the highest priority
        while (temp != NULL) {
            if (temp->task->priority > maxPriority) {
                maxPriority = temp->task->priority;
            }
            temp = temp->next;
        }

        temp = taskList;
        while (temp != NULL) {
            if (temp->task->priority == maxPriority) {
                if (temp->task->burst <= quantum) {
                    run(temp->task, temp->task->burst);
                    delete(&taskList, temp->task);
                } else {
                    run(temp->task, quantum);
                    temp->task->burst -= quantum;
                }
            }
            temp = temp->next;
        }
    }
}