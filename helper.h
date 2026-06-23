#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>
#include "struct.h"

// FUNCTION PROTOTYPES
int precedence(char ch[]);
bool isOperand(char ch);
void appendToken(char* postfix, char* token);

#endif
