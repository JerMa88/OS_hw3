#include <stdio.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

void schedule() {
    printf("Scheduling FCFS...\n");
    if (taskList != NULL) {
        traverse(taskList);
    }
    printf("FCFS scheduling complete.\n");
    delete(&taskList, taskList->task);


    // struct node *temp;
    // temp = head;

    // while (temp != NULL) {
    //     run(temp->task, temp->task->burst);
    //     temp = temp->next;
    // }
}