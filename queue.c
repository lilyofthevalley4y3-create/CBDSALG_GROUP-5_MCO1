#include <stdio.h>
#include <string.h>
#include <stdlib.h> //used for malloc
#include <stdbool.h>
#include "queue.h"

void enqueue(Queue *q, char token[]){
	Node* new_node = (Node*)malloc(sizeof(Node));
	strcpy(new_node->data, token);
	new_node->next = NULL;

	//if queue is empty, head and tail become the only node
	if(q->tail == NULL){
		q->head = new_node;
		q->tail = new_node;
	} else {
		q->tail->next = new_node;
		q->tail = new_node; //moves tail to newest node
	}
}

void dequeue(Queue *q, char result[]){
	if(isQueueEmpty(q)){
		result[0] = '\0';
	} else {
		Node* temp = q->head;
		strcpy(result, temp->data);
		q->head = q->head->next;

		if(q->head == NULL){
			q->tail = NULL;
		}
		free(temp);
	}
}

void initQueue(Queue *q){
	q->head = NULL;
	q->tail = NULL;
}

bool isQueueEmpty(Queue *q){
	if (q->head == NULL){
		return true;
	}
	return false;
}
