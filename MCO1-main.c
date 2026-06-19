#include <stdio.h>
#include <string.h>

void push(char* Infix, char* input){
	int size = strlen(Infix);
	strcat(Infix, input);
	size++;
	printf("%s", Infix);
}


int main(){
	char Infix[256]; //string array with 256 chars
	

	printf("Input: ");
	
	//stores the inputted infix in the array 
	//fgets(Infix, sizeof(Infix), stdin);
	scanf("%[^\n]", Infix);
	char input[] = "-"; //test
	push(Infix, input);
	
}
