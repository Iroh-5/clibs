#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

#ifndef QUEUE_TYPE
	#define QUEUE_TYPE int
#endif

#ifndef QUEUE_TYPED
	#define QUEUE_TYPED(name) name
#endif

typedef struct QUEUE_TYPED(qnode) QUEUE_TYPED(qnode);
typedef struct QUEUE_TYPED(queue) QUEUE_TYPED(queue);

struct QUEUE_TYPED(qnode)
{
	QUEUE_TYPE value;
	QUEUE_TYPED(qnode)* next;
};

struct QUEUE_TYPED(queue)
{
	QUEUE_TYPED(qnode)* head;
	QUEUE_TYPED(qnode)* tail;
	size_t size;
};

QUEUE_TYPED(queue)* QUEUE_TYPED(queue_init)(QUEUE_TYPED(queue)* q)
{
	if (q)
	{
		q->head = q->tail = NULL;
		q->size = 0;
	}
	
	return q;
};

bool QUEUE_TYPED(queue_push)(QUEUE_TYPED(queue)* q, QUEUE_TYPE value)
{
	if (!q)
		return false;
	
	QUEUE_TYPED(qnode)* node = malloc(sizeof(QUEUE_TYPED(qnode)));
	if (!node)
		return false;
	node->value = value;
	node->next = NULL;
	
	if (q->tail)
		q->tail->next = node;
	q->tail = node;

	if (!q->head)
		q->head = node;
	q->size++;
	
	return true;
}

QUEUE_TYPE QUEUE_TYPED(queue_front)(QUEUE_TYPED(queue)* q, bool* success)
{
	if (!q || !q->head)
	{
		if (success)
			*success = false;
		return 0;
	}
	
	if (success)
		*success = true;
	return q->head->value;
}

void QUEUE_TYPED(queue_pop)(QUEUE_TYPED(queue)* q)
{
	if (q && q->head)
	{
		QUEUE_TYPED(qnode)* rem = q->head;
		q->head = q->head->next;
		free(rem);
		q->size--;
	}
}

bool QUEUE_TYPED(queue_empty)(QUEUE_TYPED(queue)* q)
{
	return q->size == 0;
}

void QUEUE_TYPED(queue_destroy)(QUEUE_TYPED(queue)* q)
{
	while (!QUEUE_TYPED(queue_empty(q)))
		QUEUE_TYPED(queue_pop(q));
	free(q);
}

#define queue QUEUE_TYPED(queue)
#define queue_init QUEUE_TYPED(queue_init)
#define queue_push QUEUE_TYPED(queue_push)
#define queue_front QUEUE_TYPED(queue_front)
#define queue_pop QUEUE_TYPED(queue_pop)
#define queue_empty QUEUE_TYPED(queue_empty)
#define queue_destroy QUEUE_TYPED(queue_destroy)

#endif