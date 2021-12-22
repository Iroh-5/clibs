#include "tgdll.h"

// Internal functions
static lnode* _node_create(void* data)
{
    lnode* node = malloc(sizeof(lnode));
    ASSERT(node != NULL, "Couldn't allocate memory");
    
    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

static void _destroy_list_handler(dll* list)
{
    free(list);
}

static void _destroy_node(lnode* node)
{
    free(node);
}

void _insert_sorted(dll* list, lnode* node)
{
    if (dll_is_empty(list))
    {
	list->head = list->tail = node;
	list->size++;
	return;
    }

    lnode* curr = list->head;
    while (curr != NULL && list->cmp(curr->data, node->data) < 0)
	curr = curr->next;

    if (curr == NULL)
    {
	list->tail->next = node;
	node->prev       = list->tail;
	list->tail       = node;
    }
    else if (curr == list->head)
    {
	list->head->prev = node;
	node->next       = list->head;
	list->head       = node;
    }
    else
    {
	curr->prev->next = node;
	node->prev       = curr->prev;
	node->next       = curr;
	curr->prev       = node;
    }

    list->size++;
}

// Create and destroy list
dll* dll_create(void (*destroy)(void* mem), int (*cmp)(void* lhs, void* rhs), bool destroy_data)
{
    dll* list = malloc(sizeof(dll));
    ASSERT(list != NULL, "Couldn't allocate memory\n");

    list->destroy      = destroy;
    list->cmp          = cmp;
    list->head         = NULL;
    list->tail         = NULL;
    list->size         = 0;
    list->destroy_data = destroy_data;

    return list;
}

void dll_destroy(dll* list)
{
    lnode* curr = list->head;
    while (curr != NULL)
    {
	lnode* next = curr->next;

	if (list->destroy_data)
	    list->destroy(curr->data);
	_destroy_node(curr);

	curr = next;
    }

    _destroy_list_handler(list);
}

// Modifiers
void dll_push_back(dll* list, void* data)
{
    lnode* new_node = _node_create(data); 

    // NOTE: list is empty; check whether head is empty is redundant
    if (list->tail == NULL)
    {
	list->head = list->tail = new_node;
    }
    else
    {
	new_node->prev   = list->tail;
	list->tail->next = new_node;
	list->tail       = new_node;
    }

    list->size++;
}

void dll_push_front(dll* list, void* data)
{
    lnode* new_node = _node_create(data);

    // NOTE: list is empty; check whether tail is empty is redundant
    if (list->head == NULL)
    {
	list->head = list->tail = new_node;
    }
    else
    {
	new_node->next   = list->head;
	list->head->prev = new_node;
	list->head       = new_node;
    }

    list->size++;
}

void dll_insert(dll* list, void* data, size_t pos)
{
    ASSERT(pos <= list->size, "Parameter pos is out of range");

    if (pos == 0)
    {
	dll_push_front(list, data);
    }
    else if (pos == list->size)
    {
	dll_push_back(list, data);
    }
    else
    {
	lnode* new_node = _node_create(data);
	lnode* curr = list->head;
	for (size_t ind = 0; ind < pos; ++ind)
	    curr = curr->next;

	lnode* prev = curr->prev;

	new_node->prev = prev;
	new_node->next = curr;
	prev->next     = new_node;	
	curr->prev     = new_node;

	list->size++;
    }
}

void dll_pop_back(dll* list)
{
    ASSERT(list->tail != NULL, "List is empty\n");

    if (list->destroy_data)
	list->destroy(list->tail->data);

    if (list->size > 1)
    {
	list->tail = list->tail->prev;
	_destroy_node(list->tail->next);
	list->tail->next = NULL;
    }
    else
    {
	_destroy_node(list->tail);
	list->tail = list->head = NULL;
    }

    list->size--;
}

void dll_pop_front(dll* list)
{
    ASSERT(list->head != NULL, "List is empty\n");

    if (list->destroy_data)
	list->destroy(list->head->data);

    if (list->size > 1)
    {
	list->head = list->head->next;	
	_destroy_node(list->head->prev);
	list->head->prev = NULL;
    }
    else
    {
	_destroy_node(list->head);
	list->tail = list->head = NULL;
    }

    list->size--;
}

dll* dll_sort(dll* list)
{
    dll* new_list = dll_create(list->destroy, list->cmp, list->destroy_data);
    // NOTE: The problem is that sort function creates a copy of a list
    //       but not a copy of its elements. So when it deletes old list,
    //       data vanishes.
    lnode* curr = list->tail;
    while (curr != NULL)
    {
	lnode* new_node = _node_create(curr->data);
	_insert_sorted(new_list, new_node);
	curr = curr->prev;
    }

    dll_destroy(list);

    return new_list;
}

// Element access
void* dll_get_back(dll* list)
{
    return (list->tail != NULL) ? list->tail->data : NULL; 
}

void*  dll_get_front(dll* list)
{
    return (list->head != NULL) ? list->head->data : NULL;
}

void*  dll_get_at(dll* list, size_t pos)
{
    ASSERT(pos <= list->size, "Parameter pos is out of range");

    if (pos == 0)
	return dll_get_front(list);

    if (pos == list->size)
	return dll_get_back(list);

    lnode* curr = list->head;
    for (size_t ind = 0; ind < pos; ++ind)
	curr = curr->next;

    return curr->data;
}

// Size
size_t dll_size(dll* list)
{
    return list->size;
}

bool dll_is_empty(dll* list)
{
    return list->size == 0;
}

// Traverse list
void dll_to_dot(dll* list)
{
    printf("digraph list\n{\n");
    printf("head -> %d\n", VTOT(int, list->head->data));
    printf("tail -> %d\n", VTOT(int, list->tail->data));

    lnode* node = list->head; 
    while (node != NULL)
    {
	if (node->prev)
	    printf("%d -> %d\n", VTOT(int, node->data), VTOT(int, node->prev->data));
	if (node->next)
	    printf("%d -> %d\n", VTOT(int, node->data), VTOT(int, node->next->data));

	node = node->next;
    }

    printf("}\n");
}

void dll_trav(dll* list, void (*op)(void* data))
{
    lnode* node = list->head; 
    while (node != NULL)
    {
	op(node->data);
	node = node->next;
    }
}

void dll_rtrav(dll* list, void (*op)(void* data))
{
    lnode* node = list->tail; 
    while (node != NULL)
    {
	op(node->data);
	node = node->prev;
    }
}
