#include <glib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	GSList *list = NULL;
	printf("The list is now %d itens long\n", g_slist_length(list));
	list = g_slist_append(list, "first");
	list = g_slist_append(list, "second");
	list = g_slist_append(list, "third");
	printf("The last item is %s\n", g_slist_last(list)->data);
	printf("The item at index is %s\n", g_slist_nth(list,0)->data);
	printf("The next item after the first item is %s\n", g_slist_next(list)->data);
	printf("The list is now %d itens long\n", g_slist_length(list));
	g_slist_free(list);
	return 0;

}
