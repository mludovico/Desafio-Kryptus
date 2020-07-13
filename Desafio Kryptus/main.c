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
#include <stdbool.h>
#if _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif // _WIN32

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
	node->next = NULL;
	if (list->size == 0) {
		list->head = node;
		list->tail = node;
	}
	else
	{
		NodeStruct* lastNode = last(list, false);
		lastNode->next = node;
		list->tail = node;
	}
	list->size++;
	printList(list);
}

NodeStruct* get(LinkedList* list, int index, bool print) {
	if (list->size == 0)
	{
		printf("Empty list\n");
		return NULL;
	}
	NodeStruct* pointer = list->head;
	int i = 1;
	while(i < index)
	{
		if (pointer->next == NULL) {
			printf("Item not found\n");
			return NULL;
		}
		pointer = pointer->next;
		i++;
	}
	if(print)
		printf("%d\n", pointer->data.value);
	return pointer;
}

void removeItem(LinkedList* list, int index) {
	if (list->size == 0)
	{
		printf("Empty list\n");
		return;
	}
	if (index < 1)
	{
		printf("Invalid index [%d]\n", index);
		return;
	}
	NodeStruct* current = get(list, index, false);
	if (current == NULL)
		return;
	NodeStruct* previous = get(list, index - 1, false);
	if (previous == NULL)
	{
		return;
	}
	if (current == list->head)
		list->head = current->next;
	else if (current == list->tail)
		list->tail = previous;
	previous->next = current->next;
	free(current);
	list->size--;
	printList(list);
}

void clear(LinkedList* list) {
	if (list->size != 0) {
		NodeStruct* pointer = list->head;
		while (pointer->next != NULL) {
			NodeStruct* next = pointer->next;
			free(pointer);
			pointer = next;
		}
		list->head = NULL;
		list->size = 0;
	}
	printList(list);
}

int indexOf(LinkedList* list, NodeStruct* node) {
	if (list->size == 0) {
		printf("Empty list\n");
		return NULL;
	}
	for (int i = 1; i <= list->size; i++) {
		if (get(list, i, false) == node)
			return i;
	}
	printf("Item not found");
	return 0;
}

void swapNodes(LinkedList* list, NodeStruct* nodeA, NodeStruct* nodeB) {
	if (list->size == 0) return;
	if (nodeA == nodeB) {
		printf("You must choose different items\n");
		return;
	}
	NodeStruct* node;
	int indexA = indexOf(list, nodeA);
	int indexB = indexOf(list, nodeB);
	node = nodeA->next;
	if (nodeB->next == nodeA)
	{
		nodeA->next = get(list, indexB, false);
	}
	else
	{
		nodeA->next = nodeB->next;
	}
	if (node == nodeB)
	{
		nodeB->next = get(list, indexA, false);
	}
	else
	{
		nodeB->next = node;
	}
	if (indexA == 1)
		list->head = nodeB;
	else
	{
		NodeStruct* preA = get(list, indexA - 1, false);
		preA->next = nodeB;
	}
	if (indexB == 1)
		list->head = nodeA;
	else
	{
		NodeStruct* preB = get(list, indexB - 1, false);
		preB->next = nodeA;
	}
	if (indexA == list->size)
		list->tail = nodeB;
	if (indexB == list->tail)
		list->tail = nodeA;
}

void sort(LinkedList* list) {
	if (list->size < 2) {
		printf("sort not permitted due to list size [%d]\n", list->size);
		return;
	}
	NodeStruct* node = list->head;
	int smallest = node->data.value;
	for (int max_hops = 1; max_hops < list->size; max_hops++)
	{
		for (int i = 1; i < list->size; i++) {
			NodeStruct* nodeA = get(list, i, false);
			NodeStruct* nodeB = get(list, i + 1, false);
			if (nodeA->data.value > nodeB->data.value)
				swapNodes(list, nodeA, nodeB);
		}
	}
	list->head = get(list, 1, false);
	list->tail = get(list, list->size, false);
}

NodeStruct* first(LinkedList* list, bool print) {
	NodeStruct* node = list->head;
	if (node != NULL && print)
		printf("%d\n", node->data.value);
	else
		printf("Empty list\n");
	return node;
}

NodeStruct* last(LinkedList* list, bool print) {
	NodeStruct* node = list->tail;
	if (node != NULL && print) {
		printf("%d\n", node->data.value);
	}
	else
		printf("Empty list\n");
	return node;
}

void printList(LinkedList* list) {

	if (list->size == 0) {
		printf("Empty list\n");
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
	printf("first:	get the first item from the list and print it's value\n");
	printf("last:	get the last item from the list and print it's value\n");
	printf("sort:	sort list by it's items values\n");
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
			NodeStruct* firstNode = first(list, true);
		}
		else if (strcmp(input, "last\n", 5) == 0) {
			last(list, true);
		}
		else if (strcmp(input, "list\n", 5) == 0) {
			printList(list);
		}
		else if (strcmp(input, "clear\n", 6) == 0) {
			clear(list);
		}
		else if (strcmp(input, "sort\n", 5) == 0) {
			sort(list);
		}
		else if (strcmp(input, "help\n", 5) == 0) {
			printHelp();
		}
		else if (strcmp(command, "put", 3) == 0 && parameterValue != 0) {
			data.value = parameterValue;
			put(list, data);
		}
		else if (strcmp(command, "get", 3) == 0 && parameterValue != 0) {
			get(list, parameterValue, true);
		}
		else if (strcmp(command, "remove", 6) == 0 && parameterValue != 0) {
			removeItem(list, parameterValue);
		}
		else {
			printf("Invalid command\n\n");
			printHelp();
		}
	}
#ifdef _WIN32
	Sleep(1500);
#else
	sleep(1);
#endif // _WIN32

	return EXIT_SUCCESS;
}
