#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/* @requires nothing
   @assigns nothing
   @ensures returns 1 if the stack is empty     */

int isEmpty(stack s){
    return (NULL == s.first); 
}

/* @requires nothing
   @assings nothing
   @ensures returns an empty stack */
stack emptyStack(){
    stack stack;
    stack.first=NULL;
    return stack;
}

/* @requires nothing
   @assigns stack
   @ensures adds the value to the top of the stack */
void push(stack *s, value a){
    Element *new = malloc(sizeof(*new));
    if (s == NULL || new == NULL){
        exit(EXIT_FAILURE);
    }

    new->num = a;
    new->next = s->first;
    s->first = new;
}

/* @requires valid and not empty stack
   @assigns removes the element at the top of the stack
   @ensures deletes and returns the element to the top of the stack */
void pop(stack *s){
    if (s == NULL){
        exit(EXIT_FAILURE);
    }
    // int numPushed = 0;
    Element *elementPushed = s->first;
    if (s != NULL && s->first != NULL){
        // numPushed = elementPushed->num;
        s->first = elementPushed->next;
        free(elementPushed);
    }
}

/* @requires nothing
   @assigns nothing
   @ensures print the elements of the stack */
void printStack(stack s){
    if (s.first == NULL){
        exit(EXIT_FAILURE);
    }
    Element *current = s.first;
    while (current != NULL){
        printf("%d\n", current->num);
        current = current->next;
    }
    printf("\n");
}