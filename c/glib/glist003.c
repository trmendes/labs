#include <glib.h>
#include <stdio.h>


int main(int argc, char** argv){
	GSList *list = NULL;

	printf("List size: %d\n", g_slist_length(list));
	printf("add item 1\n");
	list = g_slist_append(list, "item 1");
	printf("add item 2\n");
	list = g_slist_append(list, "item 2");
	printf("add item 1\n");
	list = g_slist_append(list, "item 1");
	printf("add item 3\n");
	list = g_slist_append(list, "item 3");
	printf("add item 2\n");
	list = g_slist_append(list, "item 2");
	printf("add item 1\n");
	list = g_slist_append(list, "item 1");
	printf("List size now: %d\n", g_slist_length(list));
	printf("Remove item 1\n");
	list = g_slist_remove(list, "item 1");
	printf("List size now: %d\n", g_slist_length(list));
	printf("list state: [");
	for (unsigned int i = 0 ; i < g_slist_length(list); i++) {
		printf("%s ", g_slist_nth(list,i)->data);
	}
	printf("]\n");
	g_slist_free(list);
	return 0;
}
