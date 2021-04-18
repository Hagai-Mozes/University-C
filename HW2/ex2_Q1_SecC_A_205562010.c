#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// Test cases: 5!! = 15; 10!! = 3840;

// HERE: DEFINE THE (TAIL) RECURSIVE DOUBLE-FACTORIAL FUNCTION
unsigned long long double_fact_trec(n, product) {
	if (n < 0) //for n<0 return 0
		return 0;
	if (n == 0) //0!! = 1
		return 1;
	if (n <= 2)
		return product; //product = n!! = n!/(n-1)!!
	return double_fact_trec(n - 2, product*(n - 2));
}

int main() {
	int n;
	unsigned long long res; //res doesn't have to be of type int.
	printf("Please enter a number:\n");
	scanf("%d", &n);

	// HERE: CALL THE DOUBLE-FACTORIAL FUNCTION WITH THE INPUT ARGUMENT, AND STORE THE RESULT IN THE VARIABLE "res"
	res = double_fact_trec(n, n);
	printf("%d!! = %lli", n, res); // NOTE: IF YOU CHANGE THE TYPE OF RES - CHANGE THE SPECIAL CHARACTHER SPECIFIER (%) ACCORDINGLY

	return 0;
}