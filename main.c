#include"stack.h"

int main(){
	char prefixBuffer[STR_SIZE*2];
	int prefixIndex = 0;
	double result = 0.0;

	STACK charStack;
	STACK intStack;

	initStack(&charStack, "char");
	initStack(&intStack, "double");

	makePrefix(prefixBuffer, &charStack, &prefixIndex);
	result = calcPrefix(prefixBuffer, &intStack, &prefixIndex);

	printf(" %.2lf \n", result);

	return 0;
}


