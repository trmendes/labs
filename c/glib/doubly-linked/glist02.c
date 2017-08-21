#include <glib.h>
#include <stdio.h>

int main (int argc, char **argv) {
	GList *list = g_list_append(NULL, "Austin ");
	list = g_list_append(list, "Bowie ");
	list = g_list_append(list, "Charleston ");
	printf("Here is the list: ");
	g_list_foreach(list, (GFunc)printf, NULL);
	
	GList *last = g_list_last(list);
	printf("the first item using g_list_first is %s\n", g_list_first(last)->data);
	printf("the next-to-last item is %s\n", g_list_previous(last)->data);
	printf("the next-to-last item is %s\n", g_list_nth_prev(last,1)->data);
	g_list_free(list);
	return 0;
}
