// Simple and minimalistic static stack implementation.
// It is fixed-sized and its size is determined by variable MAX_STACK_SIZE
//
// Stack interface:
// void    stack_init(stack*) - initializes stack struct to be zero
// bool    stack_is_full(stack*) - returns true if stack is full 
// bool    stack_is_empty(stack* s) - returns true if stack is empty
// size_t  stack_size(stack* s) - returns the size of the stack, i.e. the number of elements that were added
// void    stack_print(stack* s) - prints stack elements from top to bottom
// void    stack_push(stack* s, int32_t val) - pushed integer value onto the stack
// int32_t stack_top(stack* s) - return the top element without removing it
// void    stack_pop(stack* s) - removes the top element

#ifndef STACK
#define STACK

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#define MAX_STACK_SIZE 1024

typedef struct
{
    int32_t _data[MAX_STACK_SIZE];
    size_t _top;
} stack;

void    stack_init(stack* s);
bool    stack_is_full(stack* s);
bool    stack_is_empty( stack* s);
size_t  stack_size(stack* s);
void    stack_print(stack* s);
void    stack_push(stack* s, int32_t val);
int32_t stack_top(stack* s);
void    stack_pop(stack* s);

#ifdef STACK_IMPL

void stack_init(stack* s)
{
    memset(s->_data, 0, MAX_STACK_SIZE * sizeof(int32_t));
    s->_top = 0;
}

bool stack_is_full(stack* s)
{
    return s->_top == MAX_STACK_SIZE;
}

bool stack_is_empty(stack* s)
{
    return s->_top == 0;
}

size_t stack_size(stack* s)
{
    return s->_top;
}

void stack_print(stack* s)
{
    for (int ind = s->_top - 1; ind >= 0; --ind)
    {
	printf("%d ", s->_data[ind]);
    }
    putchar('\n');
}

void stack_push(stack* s, int32_t val)
{
    if (!stack_is_full(s))
	s->_data[s->_top++] = val;
}

int32_t stack_top(stack* s)
{
    if (stack_is_empty(s))
	return INT32_MIN;
    else
	return s->_data[s->_top - 1];
}

void stack_pop(stack* s)
{
    s->_top--;
}

#endif

#endif
