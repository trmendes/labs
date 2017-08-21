#include <glib.h>
#include <stdio.h>

int main(int argc, char **atgv) {
	GList *list = g_list_append(NULL, "Austin ");
	list = g_list_append(list, "Bowie ");
	list = g_list_append(list, "Chicago ");
	printf("Here is the list: ");
	g_list_foreach(list, (GFunc)printf, NULL);

	GList *bowie = g_list_nth(list,1);
	list = g_list_remove_link(list, bowie);
	g_list_free_1(bowie);

	printf("\nHere is the list after the remove_link call: ");
	g_list_foreach(list, (GFunc)printf, NULL);
	list = g_list_delete_link(list, g_list_nth(list, 1));
	printf("\nHere is the list after the delete_link call: ");
	g_list_foreach(list, (GFunc)printf, NULL);
	g_list_free(list);
	return 0;
}
