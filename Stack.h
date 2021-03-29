#ifndef STACK_H_
#define STACK_H_

#include "Structs.h"
#include <stdbool.h>

typedef struct Stack* Stack;
typedef struct StackNode* StackNode;

extern Stack newStack();
extern bool isEmpty(Stack s);
extern void push(Stack s, String k, char c);
extern StackNode pop(Stack s);
extern StackNode peek(Stack s);

#endif /* STACK_H_ */
