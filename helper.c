#include <stdbool.h>
#include <string.h>
#include "lib.h"

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

//checks if current index is a valid operand/not an operator
bool isOperand(char ch){
	if ((ch >= '0' && ch <= '9')) {
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
