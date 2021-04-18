#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define STRING_SIZE 150

int get_number_of_words(char input_string[])
{
	int counter = 0, i = 0, in_word = 0, pointer = 1; //pointer = 1 because '\0'=0, and we want to enter to the first while
	while (pointer != '\0') //do until the end of the string
	{
		pointer = input_string[i];
		if ((47 < pointer && pointer < 58) || (64 < pointer && pointer < 91) || (96 < pointer && pointer < 123)) //if input_string[i] is number or letter 
		{
			if (in_word == 0) //so it is start of a word
			{
				in_word = 1;
				counter++;
			}
		}
		else
			in_word = 0; //end of word
		i++;
	}
	return counter;
}

int main()
{
	char input_str[STRING_SIZE + 1];
	char input_char;
	int i = 0;
	printf("Enter the string:\n");
	// Read the string from the user
	for (i = 0, input_char = getchar(); i < STRING_SIZE && input_char != '\n'; i++, input_char = getchar())
		input_str[i] = input_char;
	input_str[i] = '\0'; //end of string
	printf("Number of words in given string are: %d\n", get_number_of_words(input_str));

	return 0;
}