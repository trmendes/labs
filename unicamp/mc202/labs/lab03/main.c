#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hd.h"

#define BUFSIZE 200

long get_size(long init, char *type);


int main(int argc, char **argv) {
    hd * h = NULL;
    int cmdcnt = 1;
    long partsize = 0;
    long filesize = 0;

    char type[BUFSIZE];
    char cmd1[BUFSIZE];
    char cmd2[BUFSIZE];
    char cmd3[BUFSIZE];

    while (cmdcnt > 0) {
	scanf("%d", &cmdcnt);
	scanf("%ld%s", &partsize, type);


	hd_destroy(&h);
	h = hd_create_part(get_size(partsize, type));

	for (int i = 0; i < cmdcnt; i++) {
	    scanf("%s", cmd1);
	    if (strcmp(cmd1 ,"insere") == 0) {
		scanf("%s %ld%s", cmd2, &filesize, cmd3);
		hd_insert_file(h, cmd2, get_size(filesize, cmd3));
	    } else if (strcmp(cmd1 , "remove") == 0) {
		scanf("%s", cmd2);
		hd_remove_file(h, cmd2);
	    } else if (strcmp(cmd1 , "otimiza") == 0) {
		hd_optimize(h);
	    }
	}
    hd_print_out(h);
    }


    return EXIT_SUCCESS;
}

long get_size(long init, char *type) {
    long ret = 0;
    if (strcmp(type, "Kb") == 0)
	ret = init * 1204;
    else if (strcmp(type, "Mb") == 0)
	ret = init * 1024 * 1024;
    else if (strcmp(type, "Gb") == 0)
	ret = init * 1024 * 1024 * 1024;

    return ret;
}
