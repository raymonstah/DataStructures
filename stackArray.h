// Raymond Ho
// A generic stack using an array.
// Change DEFAULT_CAPACITY as needed.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define DEFAULT_CAPACITY 40

typedef struct Stack Stack;

struct Stack {
	int size;
	int type;
	int capacity;
	void **data; // An array of generic data.
};

Stack *new_stack(int type) {
	Stack *tmp = malloc(sizeof(Stack));
	assert(tmp != NULL);
	tmp->size = 0;
	tmp->type = type;
	tmp->capacity = DEFAULT_CAPACITY;
	tmp->data = calloc(tmp->capacity, type);
	assert(tmp->data != NULL);
	return tmp;
}

void free_stack(Stack *s) {
	free(s->data);
	free(s);
}

bool full_stack(Stack *s) {
	return s->size == s->capacity;
}

bool empty_stack(Stack *s) {
	return s->size == 0;
}

void push_stack (Stack *s, void *data) {
	assert(!full_stack(s));
	s->data[s->size++] = data;
}

void* pop_stack(Stack *s) {
	assert(!empty_stack(s));
	void *tmp = s->data[s->size -1];
	s->data[s->size -1] = NULL;
	s->size--;
	return tmp;
}

void* peek_stack(Stack *s) {
	return s->data[s->size-1];
}

void printt_stack(Stack *s) {
	while (!empty_stack(s)) {
		printf("%d\n", pop_stack(s));
	}
}

