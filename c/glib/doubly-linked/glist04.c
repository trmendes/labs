#include <glib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	GList *list = g_list_append(NULL, "Austin ");
	list = g_list_append(NULL, "Bowie ");
	list = g_list_append(NULL, "Bowie ");
	list = g_list_append(NULL, "Cheyenne ");
	printf("Here is the list: ");

	g_list_foreach(list, (GFunc)printf, NULL);
	printf("\nItem 'Bowie' is located at index %d\n", g_list_index(list, "Bowie "));
	printf("\nItem 'Dallas' is located at index %d\n", g_list_index(list, "Dallas"));

	GList *last = g_list_last(list);

	printf("Item 'Cheyenne' is located at index %d\n", g_list_position(list, last));
	g_list_free(list);

	return 0;
	
}
