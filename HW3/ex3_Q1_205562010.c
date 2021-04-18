#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 5


void read_mat(int mat[][SIZE])
{
	int i = 0, j = 0;
	char c = 0;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			if (c != '\n') //get input until '\n'
				c = getchar();
			if (c != '0' && c != '\n') //write values in the matrix due to the input. if c='\n' insert 0
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	while (c != '\n') //ignore the input over 25th
		c = getchar();
}

void mult_mat(int mat1[][SIZE], int mat2[][SIZE], int result_mat[][SIZE])
{
	int i = 0, j = 0, k = 0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			for (k = 0; k < SIZE; k++)
				if (mat1[i][k] * mat2[k][j] == 1) //change the value only to 1 (OR effect)
					result_mat[i][j] = 1;
	}
}

void print_mat(int mat[][SIZE])
{
	//Please use the "%3d" format to print for uniformity.
	int i = 0, j = 0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			printf("%3d", mat[i][j]);
		printf("\n");
	}
}

int main()
{
	int mat_one[SIZE][SIZE] = { 0 }, mat_two[SIZE][SIZE] = { 0 }, mat_res[SIZE][SIZE] = { 0 };
	printf("Please Enter Values For Matrix 1\n");
	// Your function call here..
	read_mat(mat_one);

	printf("Please Enter Values For Matrix 2\n");
	// Your function call here..
	read_mat(mat_two);
	// Do the multiplication magic..
	mult_mat(mat_one, mat_two, mat_res);

	printf("The First Matrix Is :- \n");
	// Your function call here..
	print_mat(mat_one);

	printf("The Second Matrix Is :- \n");
	// Your function call here..
	print_mat(mat_two);

	printf("The Resultant Matrix Is :- \n");
	// Your function call here..
	print_mat(mat_res);

	return 0;
}