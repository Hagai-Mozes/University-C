#define _CRT_SECURE_NO_WARNINGS
# define NAME_LENGTH 200
# define LINE_LENGTH 400
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct hw_component
{
	char name[NAME_LENGTH];
	int copies;
	struct hw_component *next;
}HW_component;

FILE *F_actions = NULL, *F_updated_components = NULL, *F_components_list = NULL;

int get_the_num(char str_copies[LINE_LENGTH]);
HW_component* delete_component(HW_component *component_head, HW_component* component_to_delete);
void split_line(char line[LINE_LENGTH], char action[LINE_LENGTH], char parameter1[LINE_LENGTH], char parameter2[LINE_LENGTH]);
HW_component* create_component(HW_component *component_head, char component_name[], int component_copies);
void read_component_line(char line[], char component_name[], int *component_copies);
HW_component* add_component(HW_component *component_to_add, HW_component *component_head);
HW_component* initialize(FILE *components_list);
HW_component* find_component(HW_component *component_head, char component_name[]);
HW_component* rename_component(HW_component *component_head, char old_name[], char new_name[]);
void reduce_copies(HW_component *component_head, char component_name[], char copies_str[]);
HW_component* add_copies(HW_component *component_head, char component_name[], char copies_str[]);
void finalize(HW_component *component_head, FILE *updated_file);
void file_error(char file_name[NAME_LENGTH]);
void close_files();

/*input arguments:
str_copies: input, pointer to string which include component's number of copies
return: the number in int
functionality: the function should go over the chars in the string
and multiply it in the right power of 10*/
int get_the_num(char str_copies[LINE_LENGTH]) {
	int i = 0, end_str, num = 0;
	while (str_copies[i + 1] != '\0') i++;
	end_str = i;
	i = 0;
	while (end_str - i + 1 != 0)
	{
		num += ((str_copies[end_str - i] - 48)*pow(10, i));
		i++;
	}
	return num;
}

/*input arguments:
component_head: input, pointer to the first element of the components list.
component_to_delete: input, pointer to the component we want to delete
return: pointer to the first element of the components list
functionality: the function should the element in the component list which we want to delete,
if it's on the head_list the function should make the component-next the new head_list
if it's on the middle of the list the function should conect between 2 elements near the element which need to be delete
if it's the last component at the list and at the end progress of the 2 other cases the fanction should free the component
dynamic memory allocation*/
HW_component* delete_component(HW_component *component_head, HW_component* component_to_delete)
{
	HW_component *current_component;
	if (component_to_delete == component_head)
	{
		component_head = component_head->next;
		free(component_to_delete);
		return component_head;
	}
	current_component = component_head;
	while (current_component->next != component_to_delete)
		current_component = current_component->next;
	current_component->next = component_to_delete->next;
	free(component_to_delete);
	return component_head;
}

/*input arguments:
line: input, pointer to the desirble line in file
action: output, pointer to asked action
parameter1: output, the 2nd part at the middle lines in action file
parameter2: output, the 3rd part at the middle lines in action file
return: NULL
functionality:the function split each line to 3 strings*/
void split_line(char line[LINE_LENGTH], char action[LINE_LENGTH], char parameter1[LINE_LENGTH], char parameter2[LINE_LENGTH]) {
	int i = 0, j = 0;
	while (line[i + 1] != '$')
		action[i] = line[i++];
	action[i] = '\0';
	i += 5;
	for (i; line[i + 1] != '$'; i++, j++)
		parameter1[j] = line[i];
	parameter1[j] = '\0';
	i += 5;
	j = 0;
	for (i; line[i] != '\n'; i++, j++)
		parameter2[j] = line[i];
	parameter2[j] = '\0';
}

/*input arguments:
component_name: input, pointer to component_name
component_copies: input, number of coppies
return: pointer to the new component
functionality: the function build a HW_component element by it's name and num of coppies
*/
HW_component* create_component(HW_component *component_head, char component_name[], int component_copies)
{
	HW_component *new_component = NULL;
	if ((new_component = (HW_component*)malloc(sizeof(HW_component))) == NULL)
	{
		while (component_head != NULL)
			component_head = delete_component(component_head, component_head);
		close_files();
		printf("Error: memory allocation failed\n");
		exit(1);
	}
	strcpy(new_component->name, component_name);
	new_component->copies = component_copies;
	new_component->next = NULL;
	return new_component;
}

/*input arguments:
line: input, pointer to asked line in file
component_name: output , pointer to component name
component_copies: output, pointer to number of copies
return: NULL
functionality: the function will stract the number of copies from the line
and sent it to a faunction which should tranform the num fro str to int*/
void read_component_line(char line[], char component_name[], int *component_copies)
{
	int i = 0, j = 0;
	*component_copies = 0;
	while (line[i + 1] != '$')
	{
		component_name[i] = line[i];
		i++;
	}
	component_name[i] = '\0';
	i += 5;
	while (line[i] != '\n')
		line[j++] = line[i++];
	line[j] = '\0';
	*component_copies = get_the_num(line);
}

/*input arguments:
component_to_add: input, pointer to the component we want to add
component_head: input, pointer to the first element of the components list.
return: pointer to the first element of the components list
functionality: the function has 3 options for adding a component to the list
1. if the list is empty the function should add the component at the head of the list
2. if the element should be before the first element by the abc order - the function should
put it at the head of the list
3. if there are elements at the list the function should go over the elements in the list and add
the component at the right place by the abc order
*/
HW_component* add_component(HW_component *component_to_add, HW_component *component_head)
{
	HW_component *curr_component, *prev_component = NULL;
	if (component_head == NULL)
		return component_to_add;
	if (strcmp(component_to_add->name, component_head->name) < 0)
	{
		component_to_add->next = component_head;
		return component_to_add;
	}
	curr_component = component_head;
	while (curr_component != NULL && strcmp(component_to_add->name, curr_component->name) > 0)
	{
		prev_component = curr_component;
		curr_component = curr_component->next;
	}
	prev_component->next = component_to_add;
	component_to_add->next = curr_component;
	return component_head;
}

/*input arguments:
components_list: input, pointer to components list file
return: pointer to the first element of the components list
functionality: the function should go over the lines, read the component's name and copies
by other functions, send every element to add_fuction
*/
HW_component* initialize(FILE *components_list)
{
	char component_line[LINE_LENGTH + 1], component_name[NAME_LENGTH + 1];
	int zero;
	int *component_copies = &zero;
	HW_component *head_component = NULL, *new_component = NULL;
	while (fgets(component_line, LINE_LENGTH, components_list) != NULL)
	{
		read_component_line(component_line, component_name, component_copies);
		new_component = create_component(head_component, component_name, *component_copies);
		head_component = add_component(new_component, head_component);
	}
	return head_component;
}

/*input arguments:
component_head: input, pointer to the first element of the components list.
component_name: input, the name of the desirable component (as string)
return: pointer to the componenet which we look for at the components list, NULL if there isn't such an element
functionality: the function should go over the elements and check if there is an element whith the same name by other function
*/
HW_component* find_component(HW_component *component_head, char component_name[])
{
	HW_component *component;
	component = component_head;
	while (component != NULL && strcmp(component_name, component->name) != 0)
		component = component->next;
	return component;

}

/*input arguments:
component_head: input, pointer to the first element of the components list.
old_name: input, component's current name
new_name: input, desireble component's name
return: pointer to the first element of the components list
functionality: by find_fanction, the function should check if the component which we want to rename exist in the list
if not - do nothing
else - by using other functipns, the function should create a new component with the new name and delete the
component with the old name
*/
HW_component* rename_component(HW_component *component_head, char old_name[], char new_name[])
{
	HW_component *component_to_rename, *new_component;
	component_to_rename = find_component(component_head, old_name);
	if (component_to_rename == NULL)
		return component_head;
	new_component = create_component(component_head, new_name, component_to_rename->copies);
	component_head = delete_component(component_head, component_to_rename);
	component_head = add_component(new_component, component_head);
	return component_head;
}

/*input arguments:
component_head: input, pointer to the first element of the components list.
component_name: input, the component name of the component to add copies to (as string)
copies_str: input, the number of copies to reduce (as string)
return: pointer to the first element of the components list
fuctionality: find the desirable component and reduce the number of copies due to component_copies*/
void reduce_copies(HW_component *component_head, char component_name[], char copies_str[])
{
	HW_component *component = NULL;
	int copies_num;
	copies_num = get_the_num(copies_str);
	component = find_component(component_head, component_name);
	if (component != NULL)
	{
		component->copies -= copies_num;
		if (component->copies < 0)
			component->copies = 0;
	}
}

/*input arguments:
component_head: input, pointer to the first element of the components list
component_name: input, the component name of the component to add copies to (as string)
component_copies: input, the number of copies to add (as string)
return: pointer to the first element of the components list
fuctionality: find the desirable component and add the number of copies due to component_copies*/
HW_component* add_copies(HW_component *component_head, char component_name[], char copies_str[]) {
	HW_component *component_to_add;
	int num_copies;
	num_copies = get_the_num(copies_str);
	if (find_component(component_head, component_name) == NULL) {
		component_to_add = create_component(component_head, component_name, num_copies);
		component_head = add_component(component_to_add, component_head);
	}
	else {
		component_to_add = find_component(component_head, component_name);
		component_to_add->copies += num_copies;
	}
	return component_head;
}

/*input arguments:
component_head: input, the first element of the components list.
updated file: output, updated components file pointer
fuctionality: print all components to updated_file
and free all the list memory allocations using delete_component*/
void finalize(HW_component *component_head, FILE *updated_file)
{
	while (component_head != NULL)
	{
		fprintf(updated_file, "%s $$$ %d", component_head->name, component_head->copies);
		if (component_head->next != NULL)
			fprintf(updated_file, "\n");
		component_head = delete_component(component_head, component_head);
	}
}

/*input arguments :
file_name: input, the file name of the file generated the error
fuctionality : closing the opened input and output files using close_files, printing error message and exit the program
with exit code 1.*/
void file_error(char file_name[NAME_LENGTH])
{
	close_files();
	printf("Error: opening %s failed\n", file_name);
	exit(1);
}

/*input arguments: None
fuctionality: closing the opened input and output files*/
void close_files()
{
	if (F_actions != NULL)
		fclose(F_actions);
	if (F_components_list != NULL)
		fclose(F_components_list);
	if (F_updated_components != NULL)
		fclose(F_updated_components);
}

/*input arguments:
argc: input, number of argv elements.
argv[1]:input, components list file name
argv[2]:input, actions file name
argv[3]:output, updated components file name
return: 0 - success, 1 - error
fuctionality: opens the input and output files, read actions from the actions file,
and assign each action the appropiate function*/
int main(int argc, char* argv[])
{
	char action[LINE_LENGTH] = { 0 }, parameter1[LINE_LENGTH] = { 0 }, parameter2[LINE_LENGTH] = { 0 };
	HW_component* component_head = NULL;
	char line[LINE_LENGTH + 1];
	if (argc != 4)
	{
		printf("Error: invalid number of arguments (<%d> instead of 3)\n", argc - 1);
		return 1;
	}
	F_actions = fopen(argv[2], "r");
	if (F_actions == NULL)
		file_error(argv[2]);
	F_updated_components = fopen(argv[3], "w");
	if (F_updated_components == NULL)
		file_error(argv[3]);
	F_components_list = fopen(argv[1], "r");
	if (F_components_list == NULL)
		file_error(argv[1]);
	while (fgets(line, LINE_LENGTH, F_actions) != NULL) {
		if (!strcmp(line, "Initialize\n"))
			component_head = initialize(F_components_list);

		else if (!strcmp(line, "Finalize"))
			finalize(component_head, F_updated_components);

		else //split_line defined for middle lines only
		{
			split_line(line, action, parameter1, parameter2);
			if (!strcmp(action, "Rename"))
				component_head = rename_component(component_head, parameter1, parameter2);
			if (!strcmp(action, "Fire") || !strcmp(action, "Fatal_malfunction"))
				reduce_copies(component_head, parameter1, parameter2);
			if (!strcmp(action, "Returned_from_customer") || !strcmp(action, "Production"))
				component_head = add_copies(component_head, parameter1, parameter2);
		}
	}
	close_files();
	return 0;
}
