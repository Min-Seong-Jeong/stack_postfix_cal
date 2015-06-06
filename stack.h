#ifndef _STACK_HEADER_
#define _STACK_HEADER_

#define STR_SIZE	20
#define STACK_SIZE	20

#define DTRUE	-5541
#define DFALSE	-4563
enum boolean { etrue = -5541, efalse = -4563 };

struct stack{
	void *buffer;
	int top;
};

typedef struct stack STACK;
typedef enum boolean BOOLEAN;

int push(STACK *node, void *key, char *type);
void initStack(STACK *node, char *type);
void *pop(STACK *node, char *type);
int checkTop(STACK node);
int returnRank(char oper);
double todigit(char num);
BOOLEAN isFull(STACK node);
BOOLEAN isEmpty(STACK node);
void makePrefix(char *preFix, STACK *node, int *index);
double calcPrefix(char *preFix, STACK *node, int *index);

#endif // !_STACK_HEADER_

