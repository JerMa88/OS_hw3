#include <stdio.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

void schedule() {

    struct node *temp = taskList;
    while (temp) {
        run(temp->task, temp->task->burst);
        temp = temp->next;
    }
    // delete(&taskList, taskList->task);
}