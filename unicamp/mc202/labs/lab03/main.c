#include <stdlib.h>
#include <stdio.h>
#include "hd.h"

int main(int argc, char **argv) {
    hd *h = hd_create_part(4000L);
    hd_insert_file(h, "teste.a", 1);
    hd_insert_file(h, "teste.b", 3000);
    hd_insert_file(h, "teste.c", 200);
    hd_remove_file(h, "teste.b");
    hd_insert_file(h, "teste.d", 100);
    hd_insert_file(h, "teste.e", 100);
    hd_insert_file(h, "teste.f", 10);
    hd_insert_file(h, "teste.g", 100);
    hd_insert_file(h, "teste.h", 1000);

    hd_ls(h);
    hd_print_out(h);
    hd_format(h);

    return EXIT_SUCCESS;
}
