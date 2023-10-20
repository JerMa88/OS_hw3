#include <stdlib.h>
#include <string.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"

struct node *taskList = NULL; 
int last_tid = 0;

void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    if (newTask == NULL) {
        // Handle memory allocation failure
        return;
    }
    newTask->name = strdup(name);
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = last_tid++;
    insert(&taskList, newTask);
}
