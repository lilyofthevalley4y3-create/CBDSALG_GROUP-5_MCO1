#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> //used for malloc
#include "stack.h"

void push(Node** head, char value[]) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->data, value);
    new_node->next = NULL;

    //if the list is empty, the new node becomes the head
    if (*head == NULL) {
        *head = new_node;

    }else{ //otherwise, travel to the last node and link it there
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node; //sets new node as the tail
	}
}

void pop(Node** head, char result[]) {
    if(stackEmpty(*head))
         result[0] = '\0';
    else {
        Node* temp = *head;
        Node* prev = NULL;

        while (temp->next!= NULL) {
            prev = temp;
            temp = temp->next;
        }
        strcpy(result, temp->data);

        if (prev == NULL) {
                *head = NULL;
            } else {
                prev->next = NULL;
            }
        free(temp);
    }
}

bool stackEmpty(Node *head) {
    return head == NULL;
}

char* top(Node **head) {
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}
