/*
 ============================================================================
 Name        : Prompt.c
 Author      :
 Version     :
 Copyright   :
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Number_Struct
{
	int number;
	struct Number_Struct *next;
}Number;

void add(Number **list, int newNumber) {
	Number *new_number;
	new_number = (Number *)malloc(sizeof(Number));
	if (new_number == NULL) exit(0);
	new_number->number = newNumber;
	new_number->next = NULL;

	if (*list == NULL) {
		*list = new_number;
	}
	else {
		Number *aux;
		aux = *list;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = new_number;
		*list = aux;
	}
}

Number last() {
	return 
}

Number first() {

}

void print_entry(char *entry) {
	printf("You entered: %s\n", entry);
}

void printHelp() {
	printf("Commands:\n");
	printf("put:	insert new value to the list\n");
	printf("get:	get value from the specified index of list\n");
	printf("list:	print all items from the list\n");
	printf("remove:	remove item at specified index from the list and print it's value\n");
	printf("clear:	clear list\n");
	printf("first:	get the first value from the list and print it's value\n");
	printf("last:	get the last value from the list and print it's value\n");
	printf("exit:	exit to system\n");
	printf("help:	print this info\n");
}

char **split_str(char *in_str, const char in_delim) {
	char** result = 0;
	size_t count = 0;
	char* tmp = in_str;
	char* last_space = 0;
	char delim[2];
	delim[0] = in_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp)
	{
		if (in_delim == *tmp)
		{
			count++;
			last_space = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_space < (in_str + strlen(in_str) - 1);

	/* Add space for terminating null string so caller
	   knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx = 0;
		char* token = strtok(in_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

int main(int argc, char *argv[]) {
	char input[201];

	Number *numberPtr;

	while (1) {
		printf("prompt> ");
		if (fgets(input, 200, stdin) == NULL) {
			printf("An error ocurred.\n");
			break;
		}

		if (strncmp(input, "exit\n", 5) == 0) {
			printf("Leaving. Good bye.\n");
			break;
		}

		char *command = split_str(&input, ' ');
		char *parameter = split_str()
		if (strcmp(command, "put") == 0) {
			add
		}

		print_entry(input);
	}

	return EXIT_SUCCESS;
}
