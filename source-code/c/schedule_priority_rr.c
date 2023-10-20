#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include "task.h"

// Comparison function for sorting tasks by priority
int comparator(const void *a, const void *b) {
    Task *taskA = *(Task **)a;
    Task *taskB = *(Task **)b;

    if (taskA->priority > taskB->priority) return -1;
    if (taskA->priority < taskB->priority) return 1;

    return 0; 
}


// invoke the scheduler
void schedule() {
    struct node *temp;
    int numTasks = 0;

    // first count the number of tasks
    temp = taskList;
    while (temp != NULL) {
        numTasks++;
        temp = temp->next;
    }

    Task *tasks[numTasks];
    int i = 0;

    temp = taskList;
    while (temp != NULL) {
        tasks[i++] = temp->task;
        temp = temp->next;
    }

    // main loop of the priority round-robin scheduler
    while (numTasks > 0) {
        // sort the tasks by priority
        qsort(tasks, numTasks, sizeof(Task *), comparator);

        for (i = 0; i < numTasks; i++) {
            if (tasks[i]->burst <= QUANTUM) {
                run(tasks[i], tasks[i]->burst);
                delete(&taskList, tasks[i]);
                tasks[i] = NULL; // mark the task for removal
            } else {
                run(tasks[i], QUANTUM);
                tasks[i]->burst -= QUANTUM;
            }
        }

        // Rebuild the tasks array, removing NULL entries
        int newCount = 0;
        for (i = 0; i < numTasks; i++) {
            if (tasks[i] != NULL) {
                tasks[newCount++] = tasks[i];
            }
        }

        numTasks = newCount;
    }
}
