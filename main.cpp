#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct Task {
    string task;
    struct Task* nextTaskNo;
} Task;

typedef struct{
    Task* top;
}TaskStack;

void InitilizeTaskStack(TaskStack *stack){
    stack->top = NULL;
}

void AddTask(TaskStack* TaskList, string addedTask){
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask ->task = addedTask;
    newTask ->nextTaskNo = TaskList -> top;
    TaskList ->top = newTask;
}


string RetrieveTask(TaskStack *TaskList){
    if (TaskList ->top == NULL)
    {
        cout<<"Task list is empty"<<endl;
        exit(EXIT_FAILURE);
    }
    string task = TaskList->top->task;
    Task* rec_task = TaskList -> top;
    TaskList->top = TaskList->top->nextTaskNo;
    free(rec_task);
    return task;
}

int main(){

}