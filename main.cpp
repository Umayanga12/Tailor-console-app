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

typedef struct ClassificationTree {
    TaskStack TaskList;
    struct TreeBranch* Important;
    union CriticalTree
    {
        TaskStack TaskList;
        struct TreeBranch* Tree;
    };
    
    struct TreeBranch* Normal;
} ClassificationTree;

typedef struct treenode
{   struct treenode* leftbranch;
    struct treenode* rightbranch; 
}treenode;

ClassificationTree* createtree(string data){
    ClassificationTree* newTree = (ClassificationTree*)malloc(sizeof(treenode));
    newTree -> Normal = NULL;
    
}

int main(){

}