#include <glib.h>
#include <stdio.h>

void print_iterator(gpointer item, gpointer prefix) {
	printf("%s %s\n", prefix, item);
}

void print_iterator_short(gpointer item) {
	printf("%s\n", item);
}

int main(int argc, char **argv) {
	GSList * list = NULL, *iterator = NULL;
	list = g_slist_append(list, "first");
	list = g_slist_append(list, "second");
	list = g_slist_append(list, "third");
	g_slist_foreach(list, print_iterator, "-->");
	g_slist_foreach(list, (GFunc)print_iterator_short, NULL);
	g_slist_free(list);
	return 0;
}
