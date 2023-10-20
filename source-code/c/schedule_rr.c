#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

void schedule() {
    while (taskList) {
        struct node *temp = taskList;
        while (temp) {
            if (temp->task->burst <= QUANTUM) {
                run(temp->task, temp->task->burst);
                delete(&taskList, temp->task);
            } else {
                run(temp->task, QUANTUM);
                temp->task->burst -= QUANTUM;
            }
            temp = temp->next;
        }
    }
}
