// Simple and minimalistic static integer stack implementation.
// It is fixed-sized and its size is determined by variable MAX_STACK_SIZE
//
// Stack interface:
// void    istack_init(istack*) - initializes istack struct to be zero
// bool    istack_is_full(istack*) - returns true if istack is full 
// bool    istack_is_empty(istack* s) - returns true if istack is empty
// size_t  istack_size(istack* s) - returns the size of the istack, i.e. the number of elements that were added
// void    istack_print(istack* s) - prints istack elements from top to bottom
// void    istack_push(istack* s, int64_t val) - pushed integer value onto the istack
// int64_t istack_top(istack* s) - return the top element without removing it
// void    istack_pop(istack* s) - removes the top element

#ifndef ISTACK_H
#define ISTACK_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#define MAX_STACK_SIZE 1024

typedef struct
{
    int64_t _data[MAX_STACK_SIZE];
    size_t _top;
} istack;

void    istack_init(istack* s);
bool    istack_is_full(istack* s);
bool    istack_is_empty( istack* s);
size_t  istack_size(istack* s);
void    istack_print(istack* s);
void    istack_push(istack* s, int64_t val);
int64_t istack_top(istack* s);
void    istack_pop(istack* s);

#ifdef ISTACK_IMPL

void istack_init(istack* s)
{
    memset(s->_data, 0, MAX_STACK_SIZE * sizeof(int64_t));
    s->_top = 0;
}

bool istack_is_full(istack* s)
{
    return s->_top == MAX_STACK_SIZE;
}

bool istack_is_empty(istack* s)
{
    return s->_top == 0;
}

size_t istack_size(istack* s)
{
    return s->_top;
}

void istack_print(istack* s)
{
    for (int ind = s->_top - 1; ind >= 0; --ind)
    {
	printf("%ld ", s->_data[ind]);
    }
    putchar('\n');
}

void istack_push(istack* s, int64_t val)
{
    if (!istack_is_full(s))
	s->_data[s->_top++] = val;
}

int64_t istack_top(istack* s)
{
    if (istack_is_empty(s))
	return INT32_MIN;
    else
	return s->_data[s->_top - 1];
}

void istack_pop(istack* s)
{
    s->_top--;
}

#endif

#endif
