#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "btree.h"

/* Implement HEAP with array
functions:
swapNodes
heapRemoveMin
heapInsert
bottomUmHeap() // professor Shewchuck added this at the end of Priority Queues lecture 25 CS61B
 */

typedef struct heap_node {
		int key; // the frequency
		int element;
		// void *something;
		struct heap_node *left;
		struct heap_node *right;
} heap_node_t;

// not tested/working
typedef struct minheap {
	heap_node_t *root;
	int currentLength;
} minheap_t;

void swapNodes(heap_node_t *a, heap_node_t *b) {
	heap_node_t tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
this builds a binary heap with heap-order and complete properties from any list of elements

void buttomUpHeap(array of heap_node_t) {
	1) make a complete tree out of n entries in any order (throw them into an array size n)
	2) walk backward from the last INTERNAL node to root i.e. reverse order in array
	when we visit a node, bubble it down as in heapRemoveMin()

}
*/

// simply return root's key
int minKey(heap_node_t *arrayHead) {
	// printf("minkey returning: %i\n", arrayHead[0].key);
	if (arrayHead[0].key) {
		return arrayHead[0].key;
	}
	else {
		return -1;
	}
}

// used during removeMin
heap_node_t * heapRemoveLast(heap_node_t *arrayHead, int *currentLength) {
	arrayHead = realloc(arrayHead, sizeof(heap_node_t) * ((*currentLength) - 1));
	*currentLength = *currentLength - 1;
	return arrayHead;
}

// this will remove the min and return the binary tree node it contains
heap_node_t * heapRemoveMin(heap_node_t *arrayHead, int *currentLength) {
	// currentLength is number of elements, so arrayHead[*currentLength] will seg fault
	heap_node_t *s;
	heap_node_t *r; // pointers
	heap_node_t *min = malloc(sizeof(heap_node_t));
	int r_index = 0;
	// Edge case, heap is empty

	if (*currentLength == 0) {
		return NULL;
	}

	// min->key = arrayHead[0].key;
	// min = (arrayHead[0]).something;
	// memcpy(min, arrayHead, sizeof(heap_node_t));
	min->key = arrayHead[0].key;
	min->element = arrayHead[0].element;
	min->left = arrayHead[0].left;
	min->right = arrayHead[0].right;

	// min->element = ((btree_node_t *) arrayHead[0].something)->element;
	// if root has no children (its index * 2 is greater than currentLength) - we're done
	if (*currentLength == 1) {
		*currentLength = *currentLength - 1;	
		return min;
	}

	// First, copy the last node to the root
	arrayHead[0] = arrayHead[*currentLength - 1];
	// Remove the last node

	arrayHead = heapRemoveLast(arrayHead, currentLength);
	while (r_index < *currentLength - 1) {
		r = &arrayHead[r_index];

		if ( (2 * r_index + 1) == *currentLength - 1) {
			// then r only has a left child and it's the last node!
			// point s to r's left child
			// printf("Node with index %i has only a left child or is last node.\n", 2*r_index+1);
			s = &arrayHead[(2 * r_index + 1)];
			r_index = 2 * r_index + 1;
		}
		else if ( (2 * r_index + 2) <= *currentLength - 1 ) {


			// printf("r's left: %i\n", arrayHead[2 * r_index + 1].key);
			// printf("r's right: %i\n", arrayHead[2 * r_index + 2].key);

			// then r has two children, need to find the smallest of them
			// and swap if its key is less than r's key
			// if the left child is greater than the right ...
			if (arrayHead[2 * r_index + 1].key > arrayHead[2 * r_index + 2].key) {
				// printf("r's left and right children: %i .. %i\n", arrayHead[2 * r_index + 1].key, arrayHead[2 * r_index + 2].key);

				// make s point to the right child
				s = &arrayHead[2 * r_index + 2];
				r_index = 2 * r_index + 2;
			}
			else {

				// otherwise make s point to the left child
				s = &arrayHead[2 * r_index + 1];
				r_index = 2 * r_index + 1;
			}
		}
		else {
			// we're at a leaf node,  this will let us out of the loop
			r_index = *currentLength;
		}
		// if r's key is greater than s's key, swap r and s
		if (r->key > s->key) {
			swapNodes(r, s);
		}
	}

	return min;
}

// heap_node_t * heapInsert(heap_node_t *arrayHead, int *currentLength, int key, int element) {
heap_node_t * heapInsert(heap_node_t *arrayHead, int *currentLength, int key, int element) {
	// first add a spot for the new element
	// printf("New array length: %i\n", *currentLength);
	arrayHead = realloc(arrayHead, sizeof(heap_node_t) * ((*currentLength) + 1));
	arrayHead[*currentLength].key = key; // last element of array of n elements
	arrayHead[*currentLength].element = element;
	arrayHead[*currentLength].right = NULL;
	arrayHead[*currentLength].left = NULL;
	// arrayHead[*currentLength].something = something;

	// now the new element is inserted at the tail of the array
	// need a loop to heap-bubble it up
	// this wont run for first node to be inserted since i would be 1
	// in pseudo code i/2 should be floor'd but C's integer division doesnt require this
	int i = *currentLength;
	heap_node_t tmp;
	while (i > 0 && arrayHead[i/2].key > arrayHead[i].key ) {
		// as long as the current node's key is less than its parent, swap their places
		swapNodes(&arrayHead[i/2], &arrayHead[i]);
		i = i/2; // mover follows the new node that is bubbling up!
	}
	(*currentLength) = (*currentLength) + 1; // we grew the number of elements by 1

	return arrayHead;
}

heap_node_t * heapInsertWithChildren(heap_node_t *arrayHead, int *currentLength, int key, int element, heap_node_t *left, heap_node_t *right) {
	// first add a spot for the new element
	// printf("New array length: %i\n", *currentLength);
	arrayHead = realloc(arrayHead, sizeof(heap_node_t) * ((*currentLength) + 1));
	arrayHead[*currentLength].key = key; // last element of array of n elements
	arrayHead[*currentLength].element = element;
	arrayHead[*currentLength].left = left;
	arrayHead[*currentLength].right = right;
	// arrayHead[*currentLength].something = something;

	// now the new element is inserted at the tail of the array
	// need a loop to heap-bubble it up
	// this wont run for first node to be inserted since i would be 1
	// in pseudo code i/2 should be floor'd but C's integer division doesnt require this
	int i = *currentLength;
	heap_node_t tmp;
	while (i > 0 && arrayHead[i/2].key > arrayHead[i].key ) {
		// as long as the current node's key is less than its parent, swap their places
		swapNodes(&arrayHead[i/2], &arrayHead[i]);
		i = i/2; // mover follows the new node that is bubbling up!
	}
	(*currentLength) = (*currentLength) + 1; // we grew the number of elements by 1

	return arrayHead;
}



void printNode(heap_node_t *node, int ugh) {
	if (node == NULL) {
		return;
	}
	// printf("ugh: %i \n", ugh);
	int i;

	printNode(node->left, ugh + 1);
	for (i = 0; i < 10*ugh + 1; i++) {
		printf("  ");
	}
	printf("key: %i element: %c\n", node->key, node->element);
	printNode(node->right, ugh + 1);

}










