#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool stackEmpty(int top) {
    bool result;
    if(top >= 0)
        result = false;
    else
        result = true;

    return result;
}

bool stackFull(int top) {
    bool result;
    if(top == MAX - 1)
        result = true;
    else
        result = false;

    return result;
}

char top(char* Infix, int size) {
	return Infix(size - 1);
}

// char operatorTop(char* Infix) {
//     return ;
// }

// int operandTop() {
//     return ;
// }

void push(char* Infix, char* input){
	int size = strlen(Infix);
	strcat(Infix, input);
	size++;
	printf("%s", Infix);
}


int main(){
	char Infix[256]; //string array with 256 chars
	int top = -1; // stack empty


	printf("Input: ");

	//stores the inputted infix in the array
	//fgets(Infix, sizeof(Infix), stdin);
	scanf("%[^\n]", Infix);
	char input[] = "-"; //test
	push(Infix, input);

}
