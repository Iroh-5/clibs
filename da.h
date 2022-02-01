#ifndef DA_H
#define DA_H

#include <stdlib.h>

#define DA_GROWTH_FACTOR 2

#define da_capacity(arr)                                                 \
    ((arr) ? ((size_t*)(arr))[-1] : (size_t) 0)                          \

#define da_size(arr)                                                     \
    ((arr) ? ((size_t*)(arr))[-2] : (size_t) 0)                          \

#define da_is_empty(arr)                                                 \
    (da_size(arr) == 0)                                                  \

#define da_set_cap(arr, cap)                                             \
    do                                                                   \
    {                                                                    \
	if (arr)                                                         \
	    ((size_t*)(arr))[-1] = (cap);                                \
    } while (0)                                                          \

#define da_set_size(arr, size)                                           \
    do                                                                   \
    {                                                                    \
	if (arr)                                                         \
	    ((size_t*)(arr))[-2] = (size);                               \
    } while (0)                                                          \

#define da_grow(arr)                                                     \
    do                                                                   \
    {                                                                    \
	if (arr)                                                         \
	{                                                                \
	    size_t cap = da_capacity(arr);                               \
	    cap *= DA_GROWTH_FACTOR;                                     \
	    size_t new_size = 2 * sizeof(size_t) + cap * sizeof(*(arr)); \
	    size_t size = da_size(arr);                                  \
	    size_t* p1 = &(((size_t*)(arr))[-2]);                        \
	    size_t* p2 = realloc(p1, new_size);                          \
	    (arr) = (void*)(p2 + 2);                                     \
	    da_set_size(arr, size);                                      \
	    da_set_cap(arr, cap);                                        \
	}                                                                \
	else                                                             \
	{                                                                \
	    (arr) = malloc(2 * sizeof(size_t) + sizeof(*(arr)));         \
	    (arr) = (void*)((size_t*)(arr) + 2);                         \
	    da_set_cap(arr, 1);                                          \
	}                                                                \
    } while (0)                                                          \

#define da_push_back(arr, val)                                           \
    do                                                                   \
    {                                                                    \
	size_t size = da_size(arr);                                      \
	if (size >= da_capacity(arr))                                    \
	    da_grow((arr));                                              \
	arr[size] = (val);                                               \
	da_set_size(arr, size + 1);                                      \
    } while (0)                                                          \

#define da_destroy(arr)                                                  \
    free((void*)(&((size_t*)(arr))[-2]))                                 \

#endif
