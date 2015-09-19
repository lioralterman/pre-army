#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Dictionary Implemination from Section 6.6 of The C Programming Language
*/

struct nlist { /* table entry: */
	struct nlist *next; /* next entry in chain */
	char *name; /* defined name */
	char *defn; /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; /* found */
	return NULL; /* not found */
}

char *strdup(char *);
/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else /* already there */
		free((void *)np->defn); /*free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

char *strdup(char *s) /* make a duplicate of s */
{
	char *p;
	p = (char *)malloc(strlen(s) + 1); /* +1 for ’\0’ */
	if (p != NULL)
		strcpy(p, s);
	return p;
}




void readVoc(char * fileName){

	/* Open file */
	char * mode = "r";
	FILE * file;
	fopen_s(&file, fileName, mode);

	char word[255];
	char def[255];

	/* Add words to dictionary */
	while (fscanf(file, "%s", word) == 1) {
		fscanf(file, "%s", def);
		install(word, def);
	}

	fclose(file);
}

void readText(char * fileName) {

	/* Open file */
	char * mode = "r";
	FILE * file;
	fopen_s(&file, fileName, mode);

	char word[255];
	nlist * newWord;

	/* Read words */
	while (fscanf(file, "%s", word) == 1) {

		/* Found word in dictionary */
		if ((newWord = lookup(word)) != NULL) {
			printf("%s ", newWord->defn);
		}
		else{
			printf("%s ", word);
		}
	}

	fclose(file);
}

/* Main */
int main(int argc, char * argv[]) {

	printf("Hello Army!\n\n");

	readVoc(argv[2]);
	readText(argv[1]);

	/* stop the program from exiting */
	char c = getchar();
}