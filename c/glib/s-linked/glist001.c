#include <glib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
	GList * list = NULL;
	list = g_list_append(list, "Hellow world!");
	printf("the first item is '%s'\n", g_list_first(list)->data);
	return 0;
}
