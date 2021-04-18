#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#define ENTERING_QUESTION "Please choose a question by entering 1-5 (enter 0 to exit):" 
#define DYNAMIC_ALLOCATION_FAILED "dynamic allocation failed"

//Q1//
#define MAX_SIZE_INPUT 31
#define QUESTION1_INPUT_MESSAGE "Please enter binary number input:"
#define QUESTION1_OUTPUT_MESSAGE_DECIMAL "to decimal is:"
#define QUESTION1_OUTPUT_MESSAGE_HEXADECIMAL "to hexadecimal is:"
#define QUESTION1_ERROR_MESSAGE "invalid input, please try again."

//Q2//
#define QUESTION2_INPUT1_MESSAGE "Please enter num1 value:"
#define QUESTION2_INPUT2_MESSAGE "Please enter num2 value:"
#define QUESTION2_OUTPUT_MESSAGE "After swapping:"

//Q3//
#define QUESTION3_INPUT1_MESSAGE "Please enter an integer:"
#define QUESTION3_OUTPUT_MESSAGE "Output:"

//Q4//
#define QUESTION4_INPUT1_MESSAGE "Please enter an integer:"
#define QUESTION4_OUTPUT1_MESSAGE "in binary is a palindrome"
#define QUESTION4_OUTPUT0_MESSAGE "in binary is not a palindrome"

//Q5//
#define QUESTION5_INPUT1_MESSAGE "Please enter an integer:"
#define QUESTION5_OUTPUT1_MESSAGE "Output of Q5:"

void get_bin_str(char *bin_str);
void bin2hexanddec(char *bin_str);
void swap(int* xp, int* yp);
int minPowerOf2(int num);
int isPalindrome(int num);
int swap_even_odd(int num);

void get_bin_str(char *bin_str)
{
	printf("%s ", QUESTION1_INPUT_MESSAGE);
	scanf("%s", bin_str);
	bin2hexanddec(bin_str);
	return;
}

void bin2hexanddec(char *bin_str)
{
	int i = 0, num = 0b0;
	while (bin_str[i] != '\0')
	{
		if (47 < bin_str[i] && bin_str[i] < 50)  //so bin_str[i] is 0 or 1
		{
			num <<= 1;
			num |= bin_str[i] - 48;
			i++;
		}
		else
		{
			printf("%s\n", QUESTION1_ERROR_MESSAGE);
			get_bin_str(bin_str);   //recall to get new num
			return;
		}
	}
	printf("%s %s %d\n", bin_str, QUESTION1_OUTPUT_MESSAGE_DECIMAL, num);
	printf("%s %s 0x%x\n", bin_str, QUESTION1_OUTPUT_MESSAGE_HEXADECIMAL, num);
}

void swap(int* xp, int* yp)
{
	printf("%s ", QUESTION2_INPUT1_MESSAGE);
	scanf("%d", xp);
	printf("%s ", QUESTION2_INPUT2_MESSAGE);
	scanf("%d", yp);
	*xp ^= *yp;  //the distinct values indexes are 1
	*yp ^= *xp;  //change the value in the distinct values indexes
	*xp ^= *yp;  //in the equal values indexes - copy, in the distinct values indexes - copy values after inverter
	printf("%s num1=%d, num2=%d\n", QUESTION2_OUTPUT_MESSAGE, *xp, *yp);
}

int minPowerOf2(int num)
{
	unsigned int mask = 0x80000000, max_pow;
	if (num <= 0) return 1; //the minimum power of 2
	max_pow = mask & num;
	for (; max_pow == 0; mask >>= 1)  //get the maximum power of 2 less than num
		max_pow = mask & num;
	if (max_pow < num) max_pow <<= 1;  //correct to the bigger than num power of 2
	return max_pow;
}

int isPalindrome(int num)
{
	int straight = num, inverse = 0;
	while (straight != 0)
	{
		inverse <<= 1;
		inverse |= straight & 1;  //copy the MLB to inverse
		straight >>= 1;
	}
	return inverse == num;
}

int swap_even_odd(int num)
{
	int new_num = 0, mask = 0xaaaaaaaa;
	new_num |= (mask & num) >> 1;  //copy the odd indexes of num to even indexes of new_num
	mask >>= 1;
	new_num |= (mask & num) << 1;  //copy the even indexes of num to odd indexes of new_num
	return new_num;
}

int main()
{
	char bin_str[MAX_SIZE_INPUT + 1];
	int x, y;
	int *xp = &x, *yp = &y;
	char user_choice = '6';
	while (user_choice != '0')
	{
		printf(ENTERING_QUESTION);
		printf("\n");
		scanf(" %c", &user_choice);
		switch (user_choice)
		{
		case '1':
			get_bin_str(bin_str);
			break;
		case '2':
			swap(xp, yp);
			break;
		case '3':
			printf("%s ", QUESTION3_INPUT1_MESSAGE);
			scanf("%d", &x);
			printf("%s%d\n", QUESTION3_OUTPUT_MESSAGE, minPowerOf2(x));
			break;
		case '4':
			printf("%s ", QUESTION4_INPUT1_MESSAGE);
			scanf("%d", &x);
			printf("%d %s.\n", x, isPalindrome(x) ? QUESTION4_OUTPUT1_MESSAGE : QUESTION4_OUTPUT0_MESSAGE);  //(short term of if)
			break;
		case '5':
			printf("%s ", QUESTION5_INPUT1_MESSAGE);
			scanf("%d", &x);
			printf("%s %d\n", QUESTION5_OUTPUT1_MESSAGE, swap_even_odd(x));
			break;
		}
	}
	return 0;
}