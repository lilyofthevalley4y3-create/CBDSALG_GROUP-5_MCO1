#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> //used for malloc

#define MAX 256

typedef struct Node {
    char data;
    struct Node *next;
} Node;

void push(Node** head, char value);
char pop(Node** head);
bool stackEmpty(Node *head);
char top(Node **head);

void push(Node** head, char value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
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

char pop(Node** head) {
    char result;
    if(stackEmpty(*head))
         result = '\0';
    else {
        Node* temp = *head;
        Node* prev = NULL;

        while (temp->next!= NULL) {
            prev = temp;
            temp = temp->next;
        }
        result = temp->data;

        if (prev == NULL) {
                *head = NULL;
            } else {
                prev->next = NULL;
            }
        free(temp);
    }
    return result;
}

bool stackEmpty(Node *head) {
    return head == NULL;
}

char top(Node **head) {
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}

int precedence(char op[]) {
    int result = -1;
    if(strcmp(op, "||") == 0)
        result = 1;
    if(strcmp(op, "&&") == 0)
        result = 2;
    if(strcmp(op, "==") == 0 || strcmp(op, "!=") == 0)
        result = 3;
    if(strcmp(op, "<") == 0 || strcmp(op, ">") == 0 || strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0)
        result = 4;
    if(strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        result = 5;
    if(strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0)
        result = 6;
    if(strcmp(op, "^") == 0)
        result = 7;
    return result;
}

int main(){
	int i, size;
	char Infix[MAX]; //stores the infix expression
	Node* head = NULL; //initializes head as NULL, since the list is initially empty
	int running = 1;

	while(running == 1) {
    	//lets user input and stores the input in the Infix array
    	// printf("Input an infix expression: ");
    	scanf("%255[^\n]", Infix);
        if(strcmp("QUIT", Infix) != 0) {
            size = strlen(Infix); //gets the size of the array

           	for(i = 0; i < size; i++){
                if(Infix[i] >= '0' && Infix[i] <= '9')
                    // append operand to postfix
                else if(Infix[i] == '(')
                    push(&head, Infix[i]); //stores the values of the infix expression in the linked list
                else if(Infix[i] == ')')
                    pop(&head);
                else {
                    // operator
                }

           	}

           	//print the linked list
           	printf("Linked List: ");
            Node* temp = head;
            while (temp != NULL) {
                printf("%c ", temp->data);
                temp = temp->next;
            }
            printf("\n");

            temp = head;
            while (temp != NULL) {
                Node* next_node = temp->next;
                free(temp); //hides the value
                temp = next_node;
            }
        } else running = -1;
	}

	return 0;
}

// bool stackEmpty(int top) {
//     bool result;
//     if(top >= 0)
//         result = false;
//     else
//         result = true;

//     return result;
// }

// bool stackFull(int top) {
//     bool result;
//     if(top == MAX - 1)
//         result = true;
//     else
//         result = false;

//     return result;
// }

// char operatorTop(char* Infix) {
//     return ;
// }

// int operandTop() {
//     return ;
// }
