#ifndef DEF_PILE
#define DEF_PILE

typedef int value;

typedef struct Element Element;
struct Element{
    value num;
    Element *next;
};

typedef struct stack stack;
struct stack{
    Element *first;
};

/* @requires nothing
   @assigns nothing
   @ensures returns 1 if the stack is empty */
int isEmpty(stack);

/* @requires nothing
   @assings nothing
   @ensures returns an empty stack */
stack emptyStack();

/* @requires nothing
   @assigns stack
   @ensures adds the value to the top of the stack */
void push(stack*, value);

/* @requires valid and not empty stack
   @assigns removes the element at the top of the stack
   @ensures deletes the element to the top of the stack */
void pop(stack*);

/* @requires nothing
   @assigns nothing
   @ensures print the elements of the stack */
void printStack(stack);

#endif