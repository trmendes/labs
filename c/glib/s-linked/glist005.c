#include <glib.h>
#include <stdio.h>

	void print_list();

int main(int argc, char** argv) {
	GSList *list1 = NULL;
	GSList *list2 = NULL;
	GSList *concact_list = NULL;
	GSList *reversed_list = NULL;

	list1 = g_slist_append(list1, "| #1 |");
	list1 = g_slist_append(list1, "| #2 |");
	
	printf("List 1 size %d\n", g_slist_length(list1));

	list2 = g_slist_append(list2, "| #3 |");
	list2 = g_slist_append(list2, "| #4 |");

	printf("List 2 size %d\n", g_slist_length(list2));

	concact_list = g_slist_concat(list1, list2);
	
	printf("List C size %d\n", g_slist_length(concact_list));

	print_list(concact_list);

	printf("Reversing the list\n");

	reversed_list = g_slist_reverse(concact_list);

	print_list(reversed_list);

	g_slist_free(list1);
	g_slist_free(list2);
	g_slist_free(reversed_list);

	return 0;
}

void print_list(GSList *_list) {
	GSList *iterator = NULL;

	for (iterator = _list; iterator; iterator = iterator->next) {
		printf(" %s ", iterator->data);
	}
	printf("\n");
}
