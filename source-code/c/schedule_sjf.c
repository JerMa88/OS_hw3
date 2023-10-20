#include <stdio.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

void schedule() {
    struct node temp;
    Taskshortest = NULL;
    int shortestTime;

    while (taskList != NULL) {
        temp = taskList;
        shortest = temp->task;
        shortestTime = shortest->burst;

        while (temp != NULL) {
            if (temp->task->burst < shortestTime) {
                shortestTime = temp->task->burst;
                shortest = temp->task;
            }
            temp = temp->next;
        }

        run(shortest, shortestTime);
        delete(&taskList, shortest);
    }
}