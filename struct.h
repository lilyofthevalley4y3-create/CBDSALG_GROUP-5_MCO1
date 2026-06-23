#ifndef STRUCT_H
#define STRUCT_H

#define MAX 256

typedef struct Node {
    char data[4]; //stores multi-digit values
    struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
} Queue;

#endif
