//#include "helper.c"
//#include "queue.c"
//#include "stack.c"
#include <stdbool.h>

#define MAX 256

typedef struct Node {
    char data[4]; //stores multi-digit values
    struct Node *next;
} Node;

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
int evaluatePost(Queue* postQueue, bool *valid);

// HELPER FUNCTIONS
bool isOperand(char ch);
void appendToken(char* postfix, char* token);
void initQueue(Queue *q);
bool isQueueEmpty(Queue *q);
bool stackEmpty(Node *head);
