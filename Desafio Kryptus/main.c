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
#include "main.h"


LinkedList* createList() {
	LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void put(LinkedList* list, DataSctruct data) {
	NodeStruct* node = (NodeStruct*) malloc(sizeof(NodeStruct));
	node->data = data;
	node->next = list->head;
	list->head = node;
	list->size++;
	printList(list);
}

NodeStruct* get(LinkedList* list, int index) {
	if (list->size == 0)
	{
		printf("Lista vazia\n");
		return NULL;
	}
	NodeStruct* pointer = list->head;
	int i = 1;
	while(i < index)
	{
		if (pointer->next == NULL) {
			printf("Valor não encontrado\n");
			return NULL;
		}
		pointer = pointer->next;
		i++;
	}
	printf("%d\n", pointer->data.value);
	return pointer;
}

void removeItem(LinkedList* list, int index) {
	NodeStruct* current = get(list, index);
	if (current == NULL)
		return;
	NodeStruct* previous = get(list, index - 1);
	if (current == NULL) return;
	printf("Remover %d\n", current->data.value);
	previous->next = current->next;
	free(current);
	list->size--;
	printList(list);
}

void clear(LinkedList* list) {
	NodeStruct* pointer = list->head;
	while (pointer != NULL) {
		NodeStruct* next = pointer->next;
		free(pointer);
		pointer = next;
		list->size--;
	}
	printList(list);
}

void first(LinkedList* list) {
	NodeStruct* node = list->head;
	if (node != NULL)
		printf("First value is %d\n", node->data.value);
	else
		printf("Lista vazia\n");
}

void last(LinkedList* list) {
	NodeStruct* node = list->head;
	if (node != NULL) {
		while (node->next != NULL) {
			node = node->next;
		}
		printf("Last value is %d\n", node->data.value);
	}
	else
		printf("Lista vazia\n");
}

void printList(LinkedList* list) {

	if (list->size == 0) {
		printf("Lista vazia\n");
		return;
	}

	NodeStruct* pointer = list->head;
	while (pointer != NULL)
	{
		printf("%d ", pointer->data.value);
		pointer = pointer->next;
	}
	printf("\n");
}

char* getCommand(char* entry) {
#pragma warning(suppress : 4996)
	char* token = strtok(entry, " ");
	//printf("%s", token);
	return token;
}

char* getParameter(char* entry) {
#pragma warning(suppress : 4996)
	char* token = strtok(NULL, "\n");
	//printf("%s", token);
	return token;
}

void print_entry(char *entry) {
	printf("You entered: %s\n", entry);
}

void printHelp() {
	printf("Usage:	command integer_value\nCommands:\n\n");
	printf("put:	insert new value to the list\n");
	printf("get:	get value from the specified index of list\n");
	printf("list:	print all items from the list\n");
	printf("remove:	remove item at specified index from the list and print it's value\n");
	printf("clear:	clear list\n");
	printf("first:	get the first value from the list and print it's value\n");
	printf("last:	get the last value from the list and print it's value\n");
	printf("exit:	exit to system\n");
	printf("help:	print this info\n\n");
}

int main(int argc, char *argv[]) {
	char input[201];

	LinkedList *list = createList();
	DataSctruct data;

	while (1) {
		printf("prompt> ");
		if (fgets(input, 200, stdin) == NULL) {
			printf("An error ocurred.\n");
			break;
		}

		char* command = getCommand(input);
		char* parameter = getParameter(input);
		int parameterValue;
		if (parameter != NULL)
			parameterValue = atoi(parameter);
		else
			parameterValue = 0;
		

		if (strncmp(input, "\n", 1) == 0) {
			continue;
		}
		else if (strncmp(input, "exit\n", 5) == 0) {
			printf("Leaving. Good bye.\n");
			break;
		}
		else if (strcmp(input, "first\n", 6) == 0) {
			first(list);
		}
		else if (strcmp(input, "last\n", 5) == 0) {
			last(list);
		}
		else if (strcmp(input, "list\n", 5) == 0) {
			printList(list);
		}
		else if (strcmp(input, "clear\n", 6) == 0) {
			clear(list);
		}
		else if (strcmp(input, "help\n", 5) == 0) {
			printHelp();
		}
		else if (strcmp(command, "put", 3) == 0 && parameterValue != 0) {
			data.value = parameterValue;
			put(list, data);
		}
		else if (strcmp(command, "get", 3) == 0 && parameterValue != 0) {
			get(list, parameterValue);
		}
		else if (strcmp(command, "remove", 6) == 0 && parameterValue != 0) {
			removeItem(list, parameterValue);
		}
		else {
			printf("Invalid command\n\n");
			printHelp();
		}
	}

	return EXIT_SUCCESS;
}
