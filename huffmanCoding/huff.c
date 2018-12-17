#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minheap.h"
// #include "btree.h"

// typedef struct node {
// 		int key;
// 		int element;
// } node_t;


int main(int argc, char *argv[]) {

	char myString[] = "HUBERTEMMAOTIEMMA";
	char array[255];

	printf("\n");
	printf("%s\n", myString);
	printf("\n");

	int x;
	memset(&array, 0, 255);
	int uniqueCharacters = 0;

	// first store frequency of each character using its ascii value as an array index
	for (x = 0; x < strlen(myString); x++) {
		array[myString[x]]++;
		if (array[myString[x]] == 1) {
			uniqueCharacters++;
		}
	}

	heap_node_t *nodeArray = malloc(sizeof(heap_node_t) * uniqueCharacters);
	heap_node_t *nodePtr = nodeArray;

	// run through the entire ASCII-Value/Frequency array and put their element (character) 
	// and keys (frequency) together
	for (x = 0; x < 255; x++) {
		if (array[x] > 0) {
			printf("%c : %d\n", x, array[x]);
			// create a node with letter as key and frequency as element
			nodePtr->element = x;
			nodePtr->key = array[x];
			nodePtr++;
		}
	}

	nodePtr = nodeArray;
	heap_node_t *heap;
	// btree_node_t *newBTNode;
	int currentLength = 0;
	for (x = 0; x < uniqueCharacters; x++) {
		printf("node key: %d | element: %c", nodePtr->key, nodePtr->element);
		printf("\n");

		// nodePtr's element is character frequency, key in priority queue
		heap = heapInsert(heap, &currentLength, nodePtr->key, nodePtr->element);

		// move to next node in array
		nodePtr++;
	}

	// check heap contents
	int i;
	for (i = 0; i < currentLength; i++) {
		printf("Heap array node %i has key: %i ... element: %i  \n\n", i, heap[i].key, heap[i].element);
	}



	int frequency1, frequency2;
	heap_node_t *t1, *t2, *tmp;
	while (currentLength > 1) {
		t1 = malloc(sizeof(heap_node_t));
		t2 = malloc(sizeof(heap_node_t));
		frequency1 = minKey(heap);
		t1 = heapRemoveMin(heap, &currentLength);
		frequency2 = minKey(heap);
		t2 = heapRemoveMin(heap, &currentLength);
		printf("t1: %c %i || ", t1->element, t1->key);
		printf("t2: %c %i\n", t2->element, t2->key);
		printf("frequency1: %i | frequency2: %i\n", frequency1, frequency2);
		printf("Inserting tree into heap with frequency: %i, children w elements: %c and %c\n", (frequency1 + frequency2), t1->element, t2->element );
		heap = heapInsertWithChildren(heap, &currentLength, (frequency1 + frequency2), 0, t1, t2);
		// printf("currentLength: %i\n", currentLength);
	}

	// return 0;
	printf("Now should have coding tree as first and only element in priority queue (heap):\n\n");

	for (i = 0; i < currentLength; i++) {
		// newBTNode = (btree_node_t *) heap[i].something;
		printf("Heap array node %i has key: %d ... element: %c ... \n\n", i, heap[i].key, heap[i].element);
	}	



	printNode(heap, 0);

}