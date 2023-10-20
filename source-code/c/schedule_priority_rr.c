#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

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
        while (temp && temp->next) // CHECK if temp is not NULL before accessing temp->next
        {
// printf("temp is %s \n", temp->task->name);
            if (temp->task->priority != temp->next->task->priority)
            {
                run(temp->task, temp->task->burst);
                delete (&rankedTaskList, temp->task); // Delete the task from rankedTaskList instead of taskList
                temp = temp->next;
            }
            else
            {
                struct node *rrTaskList = NULL;
                int currentPriority = temp->task->priority;

// int dC = 0;
                do
                {
                    insert(&rrTaskList, temp->task);
                    delete (&rankedTaskList, temp->task); // Delete the task from rankedTaskList instead of taskList
                    temp = temp->next;
// dC++;
                } while (temp && temp->next && temp->task->priority == currentPriority); // CHECK if temp is not NULL
// struct node *debug = rrTaskList;
//     while (debug) {
//         //run(debug->task, debug->task->burst);
//         printf("dC = %d | Debug task = [%s] [%d] [%d] for %d units.\n", dC, debug->task->name, debug->task->priority, debug->task->burst, debug->task->burst);
//         debug = debug->next;
//     }
                while (rrTaskList)
                {
                    struct node *rrtemp = rrTaskList;
                    while (rrtemp)
                    {
                        if (rrtemp->task->burst <= QUANTUM)
                        {
                            run(rrtemp->task, rrtemp->task->burst);
                            delete (&rrTaskList, rrtemp->task); // Delete the task from rrTaskList
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
        }
        if (temp) { // If temp hasn't been processed yet, execute it.
            run(temp->task, temp->task->burst);
            delete (&rankedTaskList, temp->task);
        }
    }
}
