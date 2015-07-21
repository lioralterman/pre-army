#include <stdio.h>
#include <stdlib.h>

/* Structs declarations */
struct item_el;
typedef struct item_el item;
struct list_el;
typedef struct list_el list;

/* Functions declarations */
list * createList();
void deleteList(list * oldList);
void addItem(list * l, int num);
void removeItem(list * l, item * i);
int getListSize(list * l);
item * getFirstItem(list * l);
item * getLastItem(list * l);
item * getNextItem(item * i);
item * getPrevItem(item * i);
int getItemVal(item * i);
double getListAvg(list * l);

/* Main - tests */
int main(int argc, char * argv[]) {
	printf("Hello Army!\n\n");

	/* Create list */
	list * myList = createList();

	/* Add items to list */
	for (int i = 1; i <= 10; i++) {
		addItem(myList, i);
	}

	/* print avg */
	printf("list avg: %lf\n", getListAvg(myList));

	/* get first item */
	item * firstItem = getFirstItem(myList);
	printf("first item: %d\n", getItemVal(firstItem));

	/* get second item */
	item * secondItem = getNextItem(firstItem);
	printf("second item: %d\n", getItemVal(secondItem));

	/* remove second item */
	removeItem(myList, secondItem);

	/* print num items */
	printf("list size: %d\n", getListSize(myList));

	/* get almost last item */
	item * almostLastItem = getPrevItem(getLastItem(myList));
	printf("almost last item: %d\n", getItemVal(almostLastItem));

	/* delete list */
	deleteList(myList);

	/* stop the program from exiting */
	char c = getchar();
}

struct item_el {
	int val;
	struct item_el * next;
	struct item_el * prev;
};

struct list_el {
	item * first;
	item * last;
	int numItems;
	int sum;
};

list * createList() {
	list * newList = (list *)malloc(sizeof(list));
	newList->numItems = 0;
	newList->sum = 0;
	newList->first = NULL;
	newList->last = NULL;
	return newList;
}

void deleteList(list * l) {

	/* Free items memory */
	item * element;
	item * nextElement = l->first;
	while (nextElement) {
		element = nextElement;
		nextElement = element->next;
		free(element);
	}

	/* Free list memory */
	free(l);
}

void addItem(list * l, int num) {

	/* Create item */
	item * newItem = (item *)malloc(sizeof(item));
	newItem->val = num;
	newItem->next = NULL;
	newItem->prev = NULL;

	/* Change items pointers */
	if (l->numItems > 0) {
		item * lastItem = l->last;
		lastItem->next = newItem;
		newItem->prev = lastItem;
	}

	/* Change list pointers */
	l->last = newItem;
	if (l->numItems == 0) {
		l->first = newItem;
	}

	/* Update list counters */
	l->sum += num;
	l->numItems++;
}

void removeItem(list * l, item * i) {

	/* Update pointers backwards */
	if (i->prev)
		i->prev->next = i->next;
	else
		l->first = i->next;

	/* Update pointers forwards */
	if (i->next)
		i->next->prev = i->prev;
	else
		l->last = i->prev;

	/* Update list counters */
	l->sum -= i->val;
	l->numItems--;

	/* Free memory */
	free(i);
}

int getListSize(list * l) {
	return l->numItems;
}

item * getFirstItem(list * l) {
	return l->first;
}

item * getLastItem(list * l) {
	return l->last;
}

item * getNextItem(item * i) {
	return i->next;
}

item * getPrevItem(item * i) {
	return i->prev;
}

int getItemVal(item * i) {
	return i->val;
}

double getListAvg(list * l) {
	return (double)l->sum / l->numItems;
}