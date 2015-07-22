#include <stdio.h>
#include <stdlib.h>

/* Structs declarations */
struct item_el;
typedef struct item_el item;

struct queue_el;
typedef struct queue_el queue;

/* Functions declarations */
queue * createQueue();
void deleteQueue(queue * q);

void addItem(queue * q, int num);
int removeItem(queue * q);

int getQueueSize(queue * q);
int getFirstVal(queue * q);

/* Main - tests */
int main(int argc, char * argv[]) {
	printf("Hello Army!\n\n");

	/* Create queue */
	queue * myQueue = createQueue();

	/* Add items to queue */
	for (int i = 1; i <= 10; i++) {
		addItem(myQueue, i);
	}

	/* pop first item */
	int firstVal = removeItem(myQueue);
	printf("first item: %d\n", firstVal);

	/* print num items */
	printf("queue size: %d\n", getQueueSize(myQueue));

	/* get first item */
	firstVal = getFirstVal(myQueue);
	printf("first item: %d\n", firstVal);

	/* delete queue */
	deleteQueue(myQueue);

	/* stop the program from exiting */
	char c = getchar();
}

struct item_el {
	item * next;
	int val;
};

struct queue_el {
	item * first;
	item * last;
	int numItems;
};

queue * createQueue() {
	queue * newQueue = (queue *)malloc(sizeof(queue));
	newQueue->numItems = 0;
	newQueue->first = NULL;
	newQueue->last = NULL;
	return newQueue;
}

void deleteQueue(queue * q) {

	/* Free items memory */
	item * element;
	item * nextElement = q->first;
	while (nextElement) {
		element = nextElement;
		nextElement = element->next;
		free(element);
	}

	/* Free queue memory */
	free(q);
}

void addItem(queue * q, int num) {

	/* Create item */
	item * newItem = (item *)malloc(sizeof(item));
	newItem->val = num;
	newItem->next = NULL;

	/* Change item pointers */
	if (q->numItems > 0) {
		item * lastItem = q->last;
		lastItem->next = newItem;
	}
	/* Change queue pointers */
	else {
		q->first = newItem;
	}

	/* Change queue pointers */
	q->last = newItem;

	/* Update queue counters */
	q->numItems++;
}

int removeItem(queue * q) {

	item * firstItem = q->first;

	/* Update queue pointer */
	q->first = firstItem->next;

	/* Update queue counters */
	q->numItems--;

	int num = firstItem->val;

	/* Free memory */
	free(firstItem);

	return num;
}

int getQueueSize(queue * q) {
	return q->numItems;
}

int getFirstVal(queue * q) {
	return q->first->val;
}