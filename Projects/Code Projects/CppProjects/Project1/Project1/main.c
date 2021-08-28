#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100
#define EMPTY -1

struct stack {
	char items[SIZE];
	int top;
};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
int peek(struct stack* stackPtr);
void print_stack(struct stack* stackPtr);

int checkBalance(char exp[]);

int priority(char ch);
int isOperator(char ch);
char *infixToPostfix(char infix[]);
int isParentheses(char ch1);


int main(void) {
	int ch;
	char exp[SIZE];
	char c;
	int valid;

	printf("\nEnter experession: ");
	scanf("%[^\n]s", exp);
	printf("Your input expression: %s\n", exp);

	valid = checkBalance(exp);

	if (valid) {
		char *postfix = infixToPostfix(exp);
		printf("The postfix is: %s\n", postfix);

		free(postfix);
	}

	system("pause");
	return 0;
}

int checkBalance(char exp[]) {
	int valid = 1;
	struct stack mine;

	initialize(&mine);

	printf("Checking balance...\n");
	for (int i = 0; exp[i] != '\0'; i++) { //can use i<sizeof(exp) instead...
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
			push(&mine, exp[i]);
		}
		else if (exp[i] == ')') {
			char temp = pop(&mine);
			if (temp == 'I' || temp != '(') {
				valid = 0;
				printf("INVALID for )!!!\n");
				return valid;
			}
		}
		else if (exp[i] == ']') {
			char temp = pop(&mine);
			if (temp == 'I' || temp != ']') {
				valid = 0;
				printf("INVALID for ]!!!\n");
				return valid;
			}
		}
		else if (exp[i] == '}') {
			char temp = pop(&mine);
			if (temp == 'I' || temp != '}') {
				valid = 0;
				printf("INVALID for }!!!\n");
				return valid;
			}
		}
	}

	if (pop(&mine) != 'I') {
		valid = 0;
		printf("INVALID. you have extra !!!\n");
	}

	if (valid == 1) {
		printf("VALID\n");
	}
	return valid;
}


void print_stack(struct stack* stackPtr) {
	for (int i = 0; i < stackPtr->top; i++) {
		printf("%c-->", stackPtr->items[i]);
	}

	printf("\n");
}

void initialize(struct stack* stackPtr) {
	stackPtr->top = -1;
}

int push(struct stack* stackPtr, char value) {
	if (full(stackPtr))
	{
		return 0;
	}
	else {
		stackPtr->items[stackPtr->top + 1] = value;
		(stackPtr->top)++;
		return 1;
	}
}

int full(struct stack* stackPtr) {
	return (stackPtr->top == SIZE - 1);
}

int priority(char ch) {
	if (ch == '^') {
		return 3;
	}
	else if (ch == '*' || ch == '/' || ch == '%') {
		return 2;
	}
	else if (ch == '+' || ch == '-') {
		return 1;
	}
	else if (ch == '(' || ch == '[' || ch == '{')
	{
		return 0;
	}
}

int empty(struct stack* stackPtr) {
	return (stackPtr->top == -1);
}

char pop(struct stack* stackPtr) {
	char retval;

	if (empty(stackPtr)) {
		return 'I';
	}
	else {
		retval = stackPtr->items[stackPtr->top];
		(stackPtr->top)--;
		return retval;
	}
}

int peek(struct stack* stackPtr) {
	if (empty(stackPtr)) {
		return EMPTY;
	}
	else {
		return stackPtr->items[stackPtr->top];
	}
}

char *infixToPostfix(char infix[]) {
	struct stack operators;
	initialize(&operators);

	int count = 0;

	char *postfix = malloc(sizeof(char) * (strlen(infix) * 2) + 1);
	//multiply by 2 to account for whitespaces, and add 1 for null char at end...

	for (int i = 0; i < strlen(infix); i++) {
		if (isdigit(infix[i])) {
			while (isdigit(infix[i])) {
				postfix[count] = infix[i];
				i++;
				count++;
			}
			i--;

			postfix[count] = ' ';
			count++;
		}
		else if (isOperator(infix[i])) {
			if (empty(&operators)) {
				push(&operators, infix[i]);
			}
			else if (priority(infix[i] > priority(peek(&operators)))) {
				push(&operators, infix[i]);
			}
			else {
				while (!empty(&operators) && (priority(infix[i]) <= priority(peek(&operators))) && !isParentheses(peek(&operators))) {
					postfix[count] = pop(&operators);
					count++;
					postfix[count] = ' ';
					count++;
				}
				push(&operators, infix[i]);
			}
		}
		else if (infix[i] == '(' || infix[i] == ')') {
			if (infix[i] == '(') {
				push(&operators, infix[i]);
			}
			else {
				while (peek(&operators) != '(') {
					postfix[count] = pop(&operators);
					count++;
					postfix[count] = ' ';
					count++;
				}
				pop(&operators);
			}
		}
	}

	int opCount = 0;
	while (operators.items[opCount] != 'Ì') {
		if (isOperator(operators.items[opCount])) {
			postfix[count] = operators.items[opCount];
			opCount++;
			count++;
			postfix[count] = ' ';
			count++;
		}
		else {
			postfix[count] = NULL;
			opCount++;
			count++;
		}
	}
	postfix[count] = NULL; //set final char to null...

	return postfix;
}

int isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%') {
		return 1;
	}
	else {
		return 0;
	}
}

int isParentheses(char ch1) {
	if (ch1 == '(' || ch1 == ')' || ch1 == '[' || ch1 == ']' || ch1 == '{' || ch1 == '}') {
		return 1;
	}
	else {
		return 0;
	}
}