// Simple and minimalistic static float stack implementation.
// It is fixed-sized and its size is determined by variable MAX_STACK_SIZE
//
// Stack interface:
// void    fstack_init(fstack*) - initializes fstack struct to be zero
// bool    fstack_is_full(fstack*) - returns true if fstack is full 
// bool    fstack_is_empty(fstack* s) - returns true if fstack is empty
// size_t  fstack_size(fstack* s) - returns the size of the fstack, i.e. the number of elements that were added
// void    fstack_print(fstack* s) - prints fstack elements from top to bottom
// void    fstack_push(fstack* s, double val) - pushed integer value onto the fstack
// double  fstack_top(fstack* s) - return the top element without removing it
// void    fstack_pop(fstack* s) - removes the top element

#ifndef FSTACK_H
#define FSTACK_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#define MAX_STACK_SIZE 1024

typedef struct
{
    double _data[MAX_STACK_SIZE];
    size_t _top;
} fstack;

void    fstack_init(fstack* s);
bool    fstack_is_full(fstack* s);
bool    fstack_is_empty( fstack* s);
size_t  fstack_size(fstack* s);
void    fstack_print(fstack* s);
void    fstack_push(fstack* s, double val);
double fstack_top(fstack* s);
void    fstack_pop(fstack* s);

#ifdef FSTACK_IMPL

void fstack_init(fstack* s)
{
    memset(s->_data, 0, MAX_STACK_SIZE * sizeof(double));
    s->_top = 0;
}

bool fstack_is_full(fstack* s)
{
    return s->_top == MAX_STACK_SIZE;
}

bool fstack_is_empty(fstack* s)
{
    return s->_top == 0;
}

size_t fstack_size(fstack* s)
{
    return s->_top;
}

void fstack_print(fstack* s)
{
    for (int ind = s->_top - 1; ind >= 0; --ind)
    {
	printf("%lf ", s->_data[ind]);
    }
    putchar('\n');
}

void fstack_push(fstack* s, double val)
{
    if (!fstack_is_full(s))
	s->_data[s->_top++] = val;
}

double fstack_top(fstack* s)
{
    if (fstack_is_empty(s))
	return INT32_MIN;
    else
	return s->_data[s->_top - 1];
}

void fstack_pop(fstack* s)
{
    s->_top--;
}

#endif

#endif
