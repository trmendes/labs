#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void print_sizes();
void print_pointer_info();
void insert_a_value(int32_t * pointer, int32_t value);
void print_array_info(int32_t a[], int32_t *pointer);

int32_t main(int32_t argc, char **argv) {
    int32_t *pointer = NULL;
    int32_t value = 4;

    int32_t array[4] = {1, 2, 3, 4};
    int32_t * array_f_element_pointer = NULL;
    array_f_element_pointer = array;

    pointer = (int32_t *) malloc(sizeof(int32_t));
    print_sizes();
    print_pointer_info();
    printf("\n");
    printf("*    Value   of the place pointer points before insert_a_value           : %d\n", *pointer);
    printf("**   Value   addr outside of the function insert_a_value                 : %p\n", &value);
    printf("***  Pointer addr outside of the function insert_a_value                 : %p\n", pointer);
    printf("**** Pointer holder addr outside of the function insert_a_value          : %p\n", &pointer);
    insert_a_value(pointer, value);
    printf("*    Value   of the place pointer points after  insert_a_value           : %d\n", *pointer);
    printf("\n");
    printf("*     Array addr outside the function                                    : %p\n", array);
    printf("**    Pointer addr to the array outside de function                      : %p\n", array_f_element_pointer);
    printf("***   Pointer holder addr to the array outside the function              : %p\n", &array_f_element_pointer);
    print_array_info(array, array_f_element_pointer);
    return EXIT_SUCCESS;
}

void print_array_info(int32_t a[], int32_t *pointer) {
    printf("*     Array addr inside  the function                                    : %p\n", a);
    printf("**    Pointer addr to the array inside de function                       : %p\n", pointer);
    printf("***   Pointer holder addr to the array inside the function               : %p\n", &pointer);
}

void insert_a_value(int32_t * pointer, int32_t value) {
    if (pointer == NULL)
	return;
    printf("**   Value   addr inside of the function insert_a_value                  : %p\n", &value);
    printf("***  Pointer addr inside of the function insert_a_value                  : %p\n", pointer);
    printf("**** Pointer holder addr inside of the function insert_a_value           : %p\n", &pointer);
    *pointer = value;
}

void print_pointer_info() {
    int32_t *pointer = NULL;
    printf("Pointer addr before malloc                                               : %p\n", pointer);
    pointer = (int32_t *) malloc(sizeof(int32_t));
    printf("Pointer addr after  malloc                                               : %p\n", pointer);
    free(pointer);
    printf("Pointer addr after  free                                                 : %p\n", pointer);
    pointer = NULL;
    printf("Pointer addr after  free and = NULL                                      : %p\n", pointer);
}

void print_sizes() {
    printf("---- SIZEOF ----\n\n");
    printf("int64_t    \t\t %d bytes\n", sizeof(int64_t));
    printf("int64_t *  \t\t %d bytes\n\n", sizeof(int64_t *));

    printf("int32_t    \t\t %d bytes\n", sizeof(int32_t));
    printf("int32_t *  \t\t %d bytes\n\n", sizeof(int32_t *));

    printf("int16_t    \t\t %d bytes\n", sizeof(int16_t));
    printf("int16_t *  \t\t %d bytes\n\n", sizeof(int16_t *));

    printf("int8_t     \t\t %d bytes\n", sizeof(int8_t));
    printf("int8_t *   \t\t %d bytes\n\n", sizeof(int8_t *));

    printf("int        \t\t %d bytes\n", sizeof(int));
    printf("int *      \t\t %d bytes\n\n", sizeof(int *));

    printf("char       \t\t %d bytes\n", sizeof(char));
    printf("char *     \t\t %d bytes\n\n", sizeof(char *));

    printf("double     \t\t %d bytes\n", sizeof(double));
    printf("double *   \t\t %d bytes\n\n", sizeof(double *));

    printf("float      \t\t %d bytes\n", sizeof(float));
    printf("float *    \t\t %d bytes\n\n", sizeof(float *));

    printf("long       \t\t %d bytes\n", sizeof(long));
    printf("long *     \t\t %d bytes\n\n", sizeof(long *));

    printf("void       \t\t %d bytes\n", sizeof(void));
    printf("void *     \t\t %d bytes\n\n", sizeof(void *));
}
