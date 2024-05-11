#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<math.h>

char *TaskType[] = {"Normal", "Critical", "Significant"};
const int NumTaskTypes = sizeof(TaskType) / sizeof(TaskType[0]);
pthread_t thread_eProductionLine;
pthread_t thread_productionLine;
pthread_t thread_deliveryLine;

typedef struct StackNode {
    void *data;  
    struct StackNode *next;  
} StackNode;

typedef struct Stack {
    StackNode *top;  
} Stack;

typedef struct TreeNode {
    char *name;  
    Stack *stack;  
    struct TreeNode **children;  
    int num_children;  
} TreeNode;

Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, void *data) {
    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

void* pop(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    StackNode *temp = stack->top;
    void *data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

void printStack(Stack *stack) {
    StackNode *current = stack->top;
    while (current != NULL) {
        printf("%s\n", (char*)current->data);
        current = current->next;
    }
}

TreeNode* createTreeNode(char *name) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->name = strdup(name);  
    node->stack = createStack();
    node->children = NULL;
    node->num_children = 0;
    return node;
}

void addChild(TreeNode *parent, TreeNode *child) {
    parent->num_children++;
    parent->children = (TreeNode**)realloc(parent->children, parent->num_children * sizeof(TreeNode*));
    if (parent->children == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    parent->children[parent->num_children - 1] = child;
}

TreeNode* createStructure() {
    TreeNode *root = createTreeNode("Root");
    TreeNode *important = createTreeNode("Important");
    TreeNode *normal = createTreeNode("Normal");
    addChild(root, important);
    addChild(root, normal);

    TreeNode *significant = createTreeNode("Significant");
    TreeNode *critical = createTreeNode("Critical");
    addChild(normal, significant);
    addChild(normal, critical);

    return root;
}


int main() {
    // Create the sample structure
    TreeNode *root = createStructure();
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter \n 1 - Add Task \n 2 - Rectrive Task \n 3 - Rectrive all Task \n 4 - Exit\n");
    int choice;
    scanf("%d", &choice);
    while(choice != 4){
        if(choice == 1){
            printf("Enter Task Type\n 1 - Normal\n 2 - Critical\n 3 - Significant\n");
            int taskType;
            scanf("%d", &taskType);
            printf("Enter Task Name\n");
            char taskName[100];
            scanf("%s", taskName);
            char *data = (char*)malloc(sizeof(char) * 100);
            strcpy(data, taskName);
            push(root->stack, data);
        }else if(choice == 2){
            printf("Enter Task Type\n 1 - Normal\n 2 - Critical\n 3 - Significant\n");
            int taskType;
            scanf("%d", &taskType);
            printf("Enter Task Name\n");
            char taskName[100];
            scanf("%s", taskName);
            StackNode *current = root->stack->top;
            while (current != NULL) {
                if(strcmp((char*)current->data, taskName) == 0){
                    printf("Task Found\n");
                    break;
                }
                current = current->next;
            }
            if(current == NULL){
                printf("Task Not Found\n");
            }
        }else if(choice == 3){
            printStack(root->stack);
        }
        printf("Enter \n 1 - Add Task \n 2 - Rectrive Task \n 3 - Rectrive all Task \n 4 - Exit\n");
        scanf("%d", &choice);
    }
    
    // Clean up: Free memory
    free(root->name);
    free(root->stack);
    for (int i = 0; i < root->num_children; i++) {
        free(root->children[i]->name);
        free(root->children[i]->stack);
        free(root->children[i]->children);
        free(root->children[i]);
    }
    free(root->children);
    free(root);

    return 0;
}
