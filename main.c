#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> //used for malloc
#include "lib.h"

int main(){
	int i, size, running = 1;
	char tempStr[2]; //temp string used for push function
	char Infix[MAX]; //stores the infix expression
	char Postfix[MAX];
	Node* head = NULL; //initializes head as NULL, since the list is initially empty
	Queue postQueue;
	int result;
	bool valid;

	while(running == 1){
		valid = true;
		initQueue(&postQueue); //initiliazes queue for tokens

		//lets user input and stores the input in the Infix array
		printf("Welcome U S E R! \n");
		printf("Type QUIT to END\n");
		printf("Input an infix expression: ");
		scanf("%s", Infix);

		if(strcmp("QUIT", Infix) != 0){
			running = 1;
			size = strlen(Infix); //gets the size of the array

			for(i = 0; i < size; i++){
				tempStr[0] = Infix[i];
				tempStr[1] = '\0'; //prevents overload
				push(&head, tempStr); //stores the values of the infix expression in the linked list
			}

			//print the linked list
			printf("Linked List: ");
		    Node* temp = head;
		    while (temp != NULL) {
		        printf("%s ", temp->data);
		        temp = temp->next;
		    }
		    printf("\n");

			Postfix[0] = '\0'; //initializes and resets the Postfix expression
			infixToPost(head, &postQueue, Postfix);

			//print the postfix
			printf("Postfix: %s", Postfix);
			printf("\n\n");

			result = evaluatePost(&postQueue, &valid);

			if(valid == 1){
			printf("Evaluation: %d\n", result);
			}
			else if(valid != 1)
			printf("Division by zero error!\n");

		    temp = head;
		    while (temp != NULL) {
		        Node* next_node = temp->next;
		        free(temp); //hides the value
		        temp = next_node;
	    		}

			head = NULL; //resets the position of the head

			} else running = -1;
		//initializer here
	}

	return 0;
}
