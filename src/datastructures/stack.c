#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct PopResult {
    int value;
    char success;
} popResult;

typedef struct Stack {
    node *head;
    int numOfElem;
    bool (*push)(struct Stack *stack, int val);
    popResult (*pop)(struct Stack *stack);
} Stack;
void stackInit(Stack *stack);

bool push(Stack *self, int val) {
    node *nNode = malloc(sizeof(node));
    if (nNode == NULL) return false; // out of mem
    
    nNode->val = val;
    nNode->next = self->head;
    self->head = nNode;
    self->numOfElem++;
    return true;
}

popResult pop(Stack *self) {
    popResult res;
    if (self->head == NULL) {
        res.success = false;
        res.success = 0;
        return res;
    }
    int value = self->head->val;
    node *tHead = self->head; // create a temporary copy of the node
    self->head = self->head->next;
    free(tHead);
    self->numOfElem--;
    res.success = true;
    res.value = value;
    return res;
}

inline void stackInit(Stack *stack) {
    stack->head = NULL;
    stack->numOfElem = 0;
    stack->push = push;
    stack->pop = pop;
}


int main() {
    Stack stack;
    stackInit(&stack);
    stack.push(&stack, 4);
    stack.push(&stack, 2);
    stack.push(&stack, 0);
    stack.push(&stack, 6);
    stack.push(&stack, 9);
    for (int i=0; i<7; i++) {
        popResult res = stack.pop(&stack);
        if (res.success) {
            printf("Sucessfully popped value %d; Num of elem after pop %d\n", res.value, stack.numOfElem);
        } else {
            printf("Stack empty; Num of elem after pop %d\n", stack.numOfElem);
        }
    }
}
