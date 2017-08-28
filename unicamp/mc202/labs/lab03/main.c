#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hd.h"

int main(int argc, char **argv) {

    FILE * ifp;
    int cmdcnt = 0;
    char part_size[200];
    char cmd1[200];
    char cmd2[200];
    char cmd3[200];

    if (argc < 2) {
	printf("Eh necessario especificar o arquivo para o teste\n");
	return EXIT_FAILURE;
    }

    ifp = fopen(argv[1], "r");

    if (ifp == NULL) {
	fprintf(stderr, "Nao consegui abrir o arquivo!\n");
	exit(1);
    }

    while (!feof(ifp)) {
	fscanf(ifp, "%d", &cmdcnt);
	printf("Numero de comandos: %d\n", cmdcnt);
	fscanf(ifp, "%s", part_size);
	printf("Tamanho da particao: %s\n", part_size);
	for (int i = 0; i < cmdcnt; i++) {
	    fscanf(ifp, "%s %s %s", cmd1, cmd2, cmd3);
	    printf("comando: %s %s %s\n", cmd1, cmd2, cmd3);
	}
    }

    return EXIT_SUCCESS;
}

void exec_cmd(hd *_hd, char *_name, long _size, char *_cmd) {
    if (strcmp(_cmd,"insere") > 0) {
	hd_insert_file(_hd, _name, _size);
    } else if (strcmp(_cmd, "remove") > 0) {
	hd_remove_file(_hd, _name);
    } else if (strcmp(_cmd, "otimiza") > 0) {
	hd_optimize(_hd);
    } else {
	printf("Comando desconhecido\n");
    }
}
