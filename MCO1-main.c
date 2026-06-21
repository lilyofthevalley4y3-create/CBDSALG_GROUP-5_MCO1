#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> //used for malloc

#define MAX 256

typedef struct Node {
    char data[4]; //stores multi-digit values
    struct Node *next;
} Node;

//for operarand stack in evaluate post
typedef struct NumNode{
	int data; //stores numbers only
	struct NumNode *next;
} NumNode;

typedef struct {
	Node *head;
	Node *tail;
} Queue;

// FUNCTION PROTOTYPES
void enqueue(Queue *q, char token[]);
void dequeue(Queue *q, char result[]);
void push(Node** head, char value[]);
void pop(Node** head, char result[]);
char* top(Node **head);
int precedence(char ch[]);
void infixToPost(Node* head, Queue* postQueue, char* postfix);
int evaluatePost(Queue* postQueue);

// HELPER FUNCTIONS
bool isOperand(char ch);
void appendToken(char* postfix, char* token);
void inQueue(Queue *q);
bool isQueueEmpty(Queue *q);
bool stackEmpty(Node *head);

//checks if current index is a valid operand/not an operator
bool isOperand(char ch){
	if ((ch >= '0' && ch <= '9')) {
		return true;
	}
	return false;
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

//helper function for appending postfix
void appendToken(char* postfix, char* token){
	if(strlen(postfix) > 0){
		strcat(postfix, " ");
	}
	strcat(postfix, token);
}

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

//halos same lang ng nsa github :P
int precedence(char ch[]){
	if(strcmp(ch, "!") == 0){
		return 8;
	}
	if(strcmp(ch, "^") == 0){
		return 7;
	}
	if(strcmp(ch, "*") == 0 || strcmp(ch, "/") == 0 || strcmp(ch, "%") == 0){
		return 6;
	}
	if(strcmp(ch, "+") == 0 || strcmp(ch, "-") == 0){
		return 5;
	}
	if(strcmp(ch, "<") == 0 || strcmp(ch, "<=") == 0 || strcmp(ch, ">") == 0 || strcmp(ch, ">=") == 0){
		return 4;
	}
	if(strcmp(ch, "==") == 0 || strcmp(ch, "!=") == 0){
		return 3;
	}
	if(strcmp(ch, "&&") == 0){
		return 2;
	}
	if(strcmp(ch, "||") == 0){
		return 1;
	}
	return -1;
}

void infixToPost(Node* head, Queue* postQueue, char* postfix){
	Node *stack = NULL;
	int i = 0;
	char token[4]; //current digit for both operand and operator
	char multiToken[MAX] = ""; //current digits for operands only
	char popped[4]; //popped digits
	char curr, next; //for multi-char operands

	while(head != NULL){
		if(head->data[0] == ' ' || head->data[0] == '\t'){ //skip spaces
			head = head->next;
		}
		else{
			token[0] = '\0';

			//looks for multi-digit operands
			if(isOperand(head->data[0])){
				i = 0; //reset idx back to 0 for every number (NOT DIGIT)
				while(head != NULL && isOperand(head->data[0])){
					multiToken[i] = head->data[0];
					head = head->next;
					i++;
				}
				multiToken[i] = '\0'; //closes current multiToken
				enqueue(postQueue, multiToken);
				appendToken(postfix, multiToken);
			} else {
				//looks for multi-character operators
				if(head->next != NULL){
					curr = head->data[0];
					next = head->next->data[0];
					if((curr == '>' && next == '=') || (curr == '<' && next == '=') || (curr == '!' && next == '=')
					|| (curr == '=' && next == '=') || (curr == '&' && next == '&') || (curr == '|' && next == '|')){
						token[0] = curr;
						token[1] = next;
						token[2] = '\0';
						head = head->next->next;
					}
				}
				//if single-character operator
				if(token[0] == '\0'){
					token[0] = head->data[0];
					token[1] = '\0';
					head = head->next;
				}

				//parenthesis-check
				if(strcmp(token, "(") == 0){
					push(&stack, token);
				} else if(strcmp(token, ")") == 0){
					while(!stackEmpty(stack) && strcmp(top(&stack), "(") != 0){
						pop(&stack, popped);
						enqueue(postQueue, popped);
						appendToken(postfix, popped);
					}
					pop(&stack,popped); // REMOVES "("
				} else {
					//regular operations and operands
					while(!stackEmpty(stack) && strcmp(top(&stack), "(") != 0 &&
					((strcmp(token, "^") != 0 && precedence(token) <= precedence(top(&stack))) ||
					(strcmp(token, "^") == 0 && precedence(token) < precedence(top(&stack))))){
						pop(&stack, popped);
	                    enqueue(postQueue, popped);
	                    appendToken(postfix, popped);
                    }
                    push(&stack, token);
					}
				}
			}
		}

	//final popping
	while(!stackEmpty(stack)){
		pop(&stack, popped);
		enqueue(postQueue, popped);
		appendToken(postfix, popped);
	}
}

int evaluatePost(Queue* postQueue){
    Node *stack = NULL;
    char temp[4];
    char result[4];
	char firstop[4], secondop[4]; //stores the operands
	int first, second;
    int answer;

    while(postQueue->head != NULL){
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
                    case '/':
                        answer = first / second;
                        break;
                }
            }
            sprintf(temp, "%d", answer); //converts answer to string then stores in a temporary array to be used again later
            push(&stack, temp); //push the answer back to the stack
        }
        postQueue->head = postQueue->head->next;
    }
    pop(&stack, result);
    return atoi(result);
}

int main(){
	int i, size, running = 1;
	char tempStr[2]; //temp string used for push function
	char Infix[MAX]; //stores the infix expression
	char Postfix[MAX];
	Node* head = NULL; //initializes head as NULL, since the list is initially empty
	Queue postQueue;
	int result;
	while(running == 1){
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

			result = evaluatePost(&postQueue);
			printf("Evaluation: %d\n", result);
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
