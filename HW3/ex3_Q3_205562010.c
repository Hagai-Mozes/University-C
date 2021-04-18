#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define STRING_SIZE 100

void read_str(char str1[STRING_SIZE + 1])
{
	int i = 0;
	char input_char = 0;
	for (i = 0, input_char = getchar(); i < STRING_SIZE && input_char != '\n'; i++, input_char = getchar())
		str1[i] = input_char;
	str1[i] = '\0'; //end of string
	while (input_char != '\n') //ignore input over STRING_SIZE
		input_char = getchar();
}

int comp_str(char str1[STRING_SIZE + 1], char str2[STRING_SIZE + 1])
{
	int i = 0, j = 0, k = 0, m = 0;
	while (str1[i] != '\0')
	{
		k = i;
		j = 0;
		while (str2[j] != '\0') //skip over equal string
		{
			if (str1[k] != str2[j])
			{
				k = i; //if two letters are not equal dont skip
				break;
			}
			k++;
			j++;
			if (str2[j] == '\0' && str1[k] == str2[0]) //skip over all times str2 in str1 in sequence
			{
				j = 0;
				i = k;
			}
		}
		i = k;
		str1[m] = str1[i]; //copy letters after skipping similar patterns
		if (str1[i] != '\0')
		{
			i++;
			m++;
		}
	}
	str1[m] = '\0'; //end of string
	if (m == i) //so there wasn't skip
		return 0;
	else
		return 1;
}

int main() {
	char result_string[STRING_SIZE + 1], find_string[STRING_SIZE + 1];


	printf("Please enter the main string..\n");
	// Your function call here..
	read_str(result_string);
	printf("Please enter the pattern string to find..\n");
	// Your function call here..
	read_str(find_string);

	int is_stripped = comp_str(result_string, find_string); // Your function call here..
	// Store the result in the result_string if it exists
	printf("> ");
	printf(is_stripped ? result_string : "Cannot find the pattern in the string!");
	return 0;
}