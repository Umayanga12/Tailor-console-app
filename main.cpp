#include<iostream>
#include<map>
#include<vector>

#define MAX_SIZE 100

using namespace std;

typedef struct{

}ClassificationTree;

//creating data structure 
typedef struct{
    string task[MAX_SIZE];
    int top;
}TaskStack;

//Initilize the task stack
void InitilizeTaskStack(TaskStack *stack){
    stack->top = -1;
}

//Add task to the stack
bool AddTask(TaskStack* stackTask, string task){
    if (stackTask->top == MAX_SIZE - 1)
    {
        cout<<"Task Stack is Full"<<endl;
        return;
    }
    stackTask->task[++stackTask->top] = task;
    return true;
}

//Rectrieve the task from stack
string RetrieveTask(TaskStack *Task){
    if (Task->top == -1)
    {   
        cout<<"DOn't have any Task"<<endl;
        exit(EXIT_FAILURE);
    }
    return Task->task[Task->top];
}

int main(){

}