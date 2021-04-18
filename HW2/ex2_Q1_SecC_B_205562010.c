#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Test cases: 5!! = 15; 10!! = 3840;

// HERE: DEFINE THE RECURSIVE FACTORIAL FUNCTION
unsigned long long one_fact_rec(n) {
	if (n == 0) //stop condition
		return 1;
	return n * one_fact_rec(n - 1);
}

// HERE: DEFINE THE (TAIL) RECURSIVE DOUBLE-FACTORIAL FUNCTION

unsigned long long double_fact_trec(n, counter, product) {
	if (n < 0) //for n<0 return 0
		return 0;
	if (counter == n + 1) //stop condition
		return product; //product = n!! = n!/(n-1)!!
	return double_fact_trec(n, counter + 1, one_fact_rec(counter) / product);
}

int main() {
	int n;
	unsigned long long res; //res doesn't have to be of type int.
	printf("Please enter a number:\n");
	scanf("%d", &n);
	//n!! = n!/(n-1)!!
	res = double_fact_trec(n, 0, 1);
	// HERE: CALL THE DOUBLE-FACTORIAL FUNCTION WITH THE INPUT ARGUMENT, AND STORE THE RESULT IN THE VARIABLE "res"

	printf("%d!! = %lli", n, res); // NOTE: IF YOU CHANGE THE TYPE OF RES - CHANGE THE SPECIAL CHARACTHER SPECIFIER (%) ACCORDINGLY

	return 0;
}