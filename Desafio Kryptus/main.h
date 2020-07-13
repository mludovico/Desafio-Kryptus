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
NodeStruct* get(LinkedList* list, int index, bool print);
void removeItem(LinkedList* list, int index);
void clear(LinkedList* list);
int indexOf(LinkedList* list, NodeStruct* node);
void sort(LinkedList* list);
void swapNodes(LinkedList* list, NodeStruct* nodeA, NodeStruct* nodeB);
NodeStruct* first(LinkedList* list, bool print);
NodeStruct* last(LinkedList* list, bool print);