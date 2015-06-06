#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void initStack(STACK *node, char *type){
	node->top = -1;
	if (strcmp(type, "char") == 0)
		node->buffer = (char *)malloc(sizeof(char)*STACK_SIZE);
	else if (strcmp(type, "int") == 0)
		node->buffer = (int *)malloc(sizeof(int)*STACK_SIZE);
	else if (strcmp(type, "double") == 0)
		node->buffer = (double *)malloc(sizeof(double)*STACK_SIZE);
}

int push(STACK *node, void *key, char *type){
	if (isFull(*node) == DTRUE){
		printf(" 스택이 꽉 찼습니다.\n");
		return DFALSE;
	}
	else{
		if (strcmp(type, "char") == 0){
			node->top++;
			*((char *)node->buffer + node->top) = *(char *)key;
		}
		else if (strcmp(type, "int") == 0){
			node->top++;
			*((int *)node->buffer + node->top) = *(int *)key;
		}
		else if (strcmp(type, "double") == 0){
			node->top++;
			*((double *)node->buffer + node->top) = *(double *)key;
		}
		return DTRUE;
	}
}
void *pop(STACK *node, char *type){
	if (isEmpty(*node) == DTRUE){
		printf(" 스택이 비었습니다.");
		return NULL;
	}
	else{
		if (strcmp(type, "char") == 0){
			node->top--;
			return ((char *)node->buffer + (node->top + 1));
		}
		else if (strcmp(type, "int") == 0){
			node->top--;
			return ((int *)node->buffer + (node->top + 1));
		}
		else if (strcmp(type, "double") == 0){
			node->top--;
			return ((double *)node->buffer + (node->top + 1));
		}
		return NULL;
	}
}
int checkTop(STACK node){
	if (isEmpty(node) == DTRUE)
		return DFALSE;
	else
		return node.top;
}
BOOLEAN isFull(STACK node){
	if (STACK_SIZE - 1 == node.top)
		return etrue;
	else
		return efalse;
}
BOOLEAN isEmpty(STACK node){
	if (node.top == -1)
		return etrue;
	else
		return efalse;
}

int returnRank(char oper){
	switch (oper){
	case ')':
		return 0;
	case '-':
	case '+':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
		return 3;
	default:
		return 100;
	}
}

double todigit(char num){
	switch (num)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		return -979898;
	}
}
void makePrefix(char *preFix, STACK *node, int *index){
	char buff;

	while (buff = getchar()){
		if (buff == ' ')
			continue;
		if (buff == '\n')
			break;
		if (isdigit(buff)){
			preFix[*index] = buff;
			(*index)++;
		}
		else{	//연산자가 나올시.

			if (buff == '+' || buff == '-' || buff == '/' || buff == '*'){
				preFix[*index] = ' ';
				(*index)++;
				if (checkTop(*node) == DFALSE){	//스택이 비었을경우
					push(node, &buff, "char");
				}
				else{	//비어있지 않은경우
					while (returnRank(*((char *)node->buffer + checkTop(*node))) >= returnRank(buff)){	//스택안의 우선순위가 더크거나 같으면 빼고 출력
						if (checkTop(*node) == DFALSE){	//스택이 비었으면 아웃
							break;
						}
						preFix[*index] = *(char *)pop(node, "char");
						(*index)++;
						preFix[*index] = ' ';
						(*index)++;
					}
					push(node, &buff, "char");	//마지막에 삽입
				}
			}
			else{	// ( ) 괄호가 나올시
				while (returnRank(*((char *)node->buffer + checkTop(*node))) >= returnRank(buff)){	//스택안의 우선순위가 더크거나 같으면 빼고 출력
					if (checkTop(*node) == DFALSE){	//스택이 비었으면 아웃
						break;
					}
					preFix[*index] = ' ';
					(*index)++;
					preFix[*index] = *(char *)pop(node, "char");
					(*index)++;
				}
			}
		}
	}
	while (checkTop(*node) != DFALSE){	//스택이 빌떄까지 
		preFix[*index] = ' ';
		(*index)++;
		preFix[*index] = *(char *)pop(node, "char");
		(*index)++;
	}

}

double calcPrefix(char *preFix, STACK *node, int *index){
	int i = 0;
	double stackValue = 0, firstOutBackCalc, secondOutFrontCalc;
	for (i = 0; i < *index; i++){
		if (preFix[i] == ' '){
			push(node, &stackValue, "double");
			stackValue = 0;
		}
		else if (isdigit(preFix[i])){	//숫자이면
			stackValue *= 10;
			stackValue += todigit(preFix[i]);
		}
		else{	//연산자이면
			firstOutBackCalc = *(double *)pop(node, "double");
			secondOutFrontCalc = *(double *)pop(node, "double");
			if (preFix[i] == '+')
				stackValue = secondOutFrontCalc + firstOutBackCalc;
			else if (preFix[i] == '-')
				stackValue = secondOutFrontCalc + firstOutBackCalc;
			else if (preFix[i] == '*')
				stackValue = secondOutFrontCalc * firstOutBackCalc;
			else if (preFix[i] == '/')
				stackValue = secondOutFrontCalc / firstOutBackCalc;
			push(node, &stackValue, "double");
			stackValue = 0;
			i++;
		}
	}
	return *(double *)pop(node, "double");
}
