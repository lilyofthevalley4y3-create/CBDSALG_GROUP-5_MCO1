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
