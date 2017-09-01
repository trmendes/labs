#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct person {
	char *name;
	int shoe_size;
} Person;

int main(int argc, char **argv) {
	GSList *list = NULL;

	Person * zeh = (Person *) malloc(sizeof(Person));
	zeh->name = "Jose Silva";
	zeh->shoe_size = 41;

	list = g_slist_append(list, zeh);

	Person * maria = (Person *) malloc(sizeof(Person));
	maria->name = "Maria Silva";
	maria->shoe_size = 36;

	list = g_slist_append(list, maria);

	printf("%s's shoes size is: %d\n", ((Person *)g_slist_last(list)->data)->name, ((Person *)g_slist_last(list)->data)->shoe_size);
	printf("%s's shoes size is: %d\n", ((Person *)list->data)->name, ((Person *)list->data)->shoe_size);

	g_slist_free(list);

	return 0;
}
