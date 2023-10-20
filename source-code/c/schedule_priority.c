#include <stdio.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

void schedule() {
    struct node temp;
    TaskhighestPriority = NULL;
    int maxPriority;

    while (taskList != NULL) {
        temp = taskList;
        highestPriority = temp->task;
        maxPriority = highestPriority->priority;

        while (temp != NULL) {
            if (temp->task->priority > maxPriority) {
                maxPriority = temp->task->priority;
                highestPriority = temp->task;
            }
            temp = temp->next;
        }

        run(highestPriority, highestPriority->burst);
        delete(&taskList, highestPriority);
    }
}