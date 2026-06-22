#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> //used for malloc
#include <math.h> //used for pow()
#include "lib.h"

int evaluatePost(Queue* postQueue, bool *valid){
    Node *stack = NULL;
    char temp[4];
    char result[4];
	char firstop[4], secondop[4]; //stores the operands
	int first, second;
    int answer;


    while(postQueue->head != NULL && *valid == 1){
        Node *current = postQueue->head; //current node is the head of postQueue

        if(isOperand(current->data[0])){ //if the value is an operand, push to the stack
            push(&stack, current->data);
        }
        else{ //if an operator is found, pop the first and second operands from the stack and store them in an array
            if(strcmp("!", current->data) == 0) {
                pop(&stack, firstop);
                first = atoi(firstop);

                answer = !first;
            } else if(strcmp("==", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first == second);
            } else if(strcmp("!=", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first != second);
            } else if(strcmp(">=", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first >= second);
            } else if(strcmp("<=", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first <= second);
            } else if(strcmp(">", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first > second);
            } else if(strcmp("<", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first < second);
            } else if(strcmp("&&", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first && second);
            } else if(strcmp("||", current->data) == 0) {
                pop(&stack, secondop);
                pop(&stack, firstop);
                first = atoi(firstop);
                second = atoi(secondop);

                answer = (first || second);
            } else {
                pop(&stack, secondop);
                pop(&stack, firstop);

                first = atoi(firstop);
                second = atoi(secondop);

                switch(current->data[0]){
                    case '+':
                        answer = first + second;
                        break;
                    case '-':
                        answer = first - second;
                        break;
                    case '*':
                        answer = first * second;
                        break;
					case '%':
						answer = first % second;
						break;
					case '^':
						answer = pow(first, second);
						break;
					case '/':
						if(second != 0){
							answer = first / second;
						} else {
							answer = 0;
							*valid = false;
						}
                }
            }

            sprintf(temp, "%d", answer); //converts answer to string then stores in a temporary array to be used again later
            push(&stack, temp); //push the answer back to the stack
        }
        dequeue(postQueue, result);
    }
    pop(&stack, result);
    return atoi(result);
}
