#ifndef QUEUE_H
#define QUEUE_H

#include "struct.h"

void enqueue(Queue *q, char token[]);
void dequeue(Queue *q, char result[]);
void initQueue(Queue *q);
bool isQueueEmpty(Queue *q);

#endif
