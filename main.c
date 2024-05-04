#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures
// Stack node
typedef struct StackNode {
    void *data;  
    struct StackNode *next;  
} StackNode;

// Stack structure
typedef struct Stack {
    StackNode *top;  
} Stack;

// Tree node
typedef struct TreeNode {
    char *name;  // Name of the node
    Stack *stack;  // Pointer to the stack associated with the node
    struct TreeNode **children;  // Array of pointers to child nodes
    int num_children;  // Number of children
} TreeNode;

// Function to initialize a stack
Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

// Function to push an item onto the stack
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

// Function to pop an item from the stack
void* pop(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;  // Stack is empty
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

// Function to create a tree node
TreeNode* createTreeNode(char *name) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->name = strdup(name);  // Duplicate the name string
    node->stack = createStack();
    node->children = NULL;
    node->num_children = 0;
    return node;
}

// Function to add a child node to a parent node
void addChild(TreeNode *parent, TreeNode *child) {
    parent->num_children++;
    parent->children = (TreeNode**)realloc(parent->children, parent->num_children * sizeof(TreeNode*));
    if (parent->children == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    parent->children[parent->num_children - 1] = child;
}

// Function to create the sample structure
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
    // Example usage: Pushing and popping items onto/from the stack of a node
    // char *data1 = "Key1: Value1";
    // push(root->stack, data1);
    // char *data2 = "Key2: Value2";
    // push(root->stack, data2);

    // void *popped_data = pop(root->stack);
    // if (popped_data != NULL) {
    //     printf("Popped data: %s\n", (char*)popped_data);
    //     free(popped_data);
    // }

    printf("Enter the number \n 1 - to push data \n 2 - to pop data \n 3 - to exit \n");

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
