#ifndef GDLL_H
#define GDLL_H

// Type Generic Double-Linked List - TGDLL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils.h"

#define VTOT(type, expr) *((type*)expr)

typedef struct dll dll;
typedef struct lnode lnode;

struct dll
{
    void (*destroy)(void* mem);
    int (*cmp)(void* lhs, void* rhs);

    lnode* head;
    lnode* tail;
    size_t size;
    bool   destroy_data;
};

struct lnode
{
    void*  data;
    lnode* next;
    lnode* prev;
};

// Internal functions
static lnode* _node_create(void* data);
static void   _destroy_list_handler(dll* list);
static void   _destroy_node(lnode* node);
static void   _insert_sorted(dll* list, lnode* node);

// Create and destroy list
dll*  dll_create(void (*destroy)(void* mem), int (*cmp)(void* lhs, void* rhs), bool destroy_data);
void   dll_destroy(dll* list);

// Modifiers
void   dll_push_back(dll* list, void* data);
void   dll_push_front(dll* list, void* data);
void   dll_insert(dll* list, void* data, size_t pos);
void   dll_pop_back(dll* list);
void   dll_pop_front(dll* list);
dll*   dll_sort(dll* list);

// Examine list
void*  dll_get_back(dll* list);
void*  dll_get_front(dll* list);
void*  dll_get_at(dll* list, size_t pos);

// Size
size_t dll_size(dll* list);
bool   dll_is_empty(dll* list);

// Traverse list
void   dll_to_dot(dll* list);
void   dll_trav(dll* list, void (*op)(void* data));
void   dll_rtrav(dll* list, void (*op)(void* data));

#endif
