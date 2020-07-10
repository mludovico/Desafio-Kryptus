#pragma once
typedef struct dataStruct {
	int value;
} DataSctruct;

typedef struct nodeStruct
{
	DataSctruct data;
	struct nodeStruct* next;
} NodeStruct;

typedef struct linkedList {
	int size;
	NodeStruct* head;
	NodeStruct* tail;
} LinkedList;

LinkedList* createList();
void put(LinkedList* list, DataSctruct data);
void printList(LinkedList* list);
NodeStruct* get(LinkedList* list, int index);
void removeItem(LinkedList* list, int index);
void clear(LinkedList* list);
void first(LinkedList* list);
void last(LinkedList* list);