// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "schedulers.h"
// #include "list.h"
// #include "cpu.h"
// #include "task.h"

// // Comparison function for sorting tasks by priority
// int comparator(const void *a, const void *b) {
//     Task *taskA = *(Task **)a;
//     Task *taskB = *(Task **)b;

//     if (taskA->priority > taskB->priority) return -1;
//     if (taskA->priority < taskB->priority) return 1;

//     return 0;
// }

// // invoke the scheduler
// void schedule() {
//     struct node *temp;
//     int numTasks = 0;

//     // first count the number of tasks
//     temp = taskList;
//     while (temp != NULL) {
//         numTasks++;
//         temp = temp->next;
//     }

//     Task *tasks[numTasks];
//     int i = 0;

//     temp = taskList;
//     while (temp != NULL) {
//         tasks[i++] = temp->task;
//         temp = temp->next;
//     }

//     // main loop of the priority round-robin scheduler
//     while (numTasks > 0) {
//         // sort the tasks by priority
//         qsort(tasks, numTasks, sizeof(Task *), comparator);

//         for (i = 0; i < numTasks; i++) {
//             if (tasks[i]->burst <= QUANTUM) {
//                 run(tasks[i], tasks[i]->burst);
//                 delete(&taskList, tasks[i]);
//                 tasks[i] = NULL; // mark the task for removal
//             } else {
//                 run(tasks[i], QUANTUM);
//                 tasks[i]->burst -= QUANTUM;
//             }
//         }

//         // Rebuild the tasks array, removing NULL entries
//         int newCount = 0;
//         for (i = 0; i < numTasks; i++) {
//             if (tasks[i] != NULL) {
//                 tasks[newCount++] = tasks[i];
//             }
//         }

//         numTasks = newCount;
//     }
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

// struct node *taskList = NULL;

// void add(char *name, int priority, int burst) {
//     Task *newTask = malloc(sizeof(Task));
//     newTask->name = strdup(name);
//     newTask->priority = priority;
//     newTask->burst = burst;
//     insert(&taskList, newTask);
// }

// invoke the scheduler
void schedule()
{
    struct node *temp;
    struct node *rankedTaskList = NULL;

    // Find the task with the highest priority
    temp = taskList;

    while (taskList)
    {
        struct node *highestPriorityNode = taskList;
        struct node *temp = taskList->next;
        while (temp)
        {
            if (temp->task->priority > highestPriorityNode->task->priority)
            {
                highestPriorityNode = temp;
            }
            temp = temp->next;
        }
        insert(&rankedTaskList, highestPriorityNode->task);
        delete (&taskList, highestPriorityNode->task);
    }

    while (rankedTaskList)
    {
        temp = rankedTaskList;
        while (temp)
        {
            if (temp->task->priority != temp->next->task->priority)
            {
                run(temp->task, temp->task->burst);
            }
            else
            {
                struct node *rrTaskList = NULL;
                
                do
                {
                    insert (&rrTaskList, temp->task);
                    temp = temp->next;
                } while (temp->task->priority == temp->next->task->priority);

                while (rrTaskList) {
                    struct node *rrtemp = rrTaskList;
                    while (rrtemp)
                    {
                        if (rrtemp->task->burst <= QUANTUM)
                        {
                            run(rrtemp->task, rrtemp->task->burst);
                            delete (&taskList, rrtemp->task);
                        }
                        else
                        {
                            run(rrtemp->task, QUANTUM);
                            rrtemp->task->burst -= QUANTUM;
                        }
                        rrtemp = rrtemp->next;
                    }
                }
            }
            temp = temp->next;
        }
    }
}
