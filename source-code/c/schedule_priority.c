#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

void schedule() {
    while (taskList) {
        struct node *highestPriorityNode = taskList;
        struct node *temp = taskList->next;
        while (temp) {
            if (temp->task->priority > highestPriorityNode->task->priority) {
                highestPriorityNode = temp;
            }
            temp = temp->next;
        }
        run(highestPriorityNode->task, highestPriorityNode->task->burst);
        delete(&taskList, highestPriorityNode->task);
    }
}
