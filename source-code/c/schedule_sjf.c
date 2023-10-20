#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

void schedule() {
    struct node *temp;
    while (taskList) {
        struct node *minTaskNode = taskList;
        temp = taskList->next;
        while (temp) {
            if (temp->task->burst < minTaskNode->task->burst) {
                minTaskNode = temp;
            }
            temp = temp->next;
        }
        run(minTaskNode->task, minTaskNode->task->burst);
        delete(&taskList, minTaskNode->task);
    }
}
