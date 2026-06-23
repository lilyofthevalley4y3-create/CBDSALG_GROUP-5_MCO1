#ifndef STACK_H
#define STACK_H

#include "struct.h"

void push(Node** head, char value[]);
void pop(Node** head, char result[]);
char* top(Node **head);
bool stackEmpty(Node *head);

#endif
