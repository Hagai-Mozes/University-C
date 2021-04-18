#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Test cases: 5!! = 15; 10!! = 3840;

// HERE: DEFINE THE RECURSIVE FACTORIAL FUNCTION
unsigned long long one_fact_rec(int n) {
	if (n < 0) //for n<0 return 0
		return 0;
	if (n == 0) //stop condition
		return 1;
	return n * one_fact_rec(n - 1);
}

// HERE: DEFINE THE RECURSIVE DOUBLE-FACTORIAL FUNCTION
unsigned long long double_fact_rec(int n) {
	if (n <= 1) //stop condition
		return 1;
	//n!! = n!/(n-1)!!
	return one_fact_rec(n) / double_fact_rec(n - 1);
}


int main() {
	int n;
	unsigned long long res; //res doesn't have to be of type int.
	printf("Please enter a number:\n");
	scanf("%d", &n);

	// HERE: CALL THE DOUBLE-FACTORIAL FUNCTION WITH THE INPUT ARGUMENT, AND STORE THE RESULT IN THE VARIABLE "res"
	res = double_fact_rec(n);
	printf("%d!! = %lli", n, res); // NOTE: IF YOU CHANGE THE TYPE OF RES - CHANGE THE SPECIAL CHARACTHER SPECIFIER (%) ACCORDINGLY

	return 0;
}