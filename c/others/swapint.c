#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("\nUsage: binary n1 n2\n");
    }
    else
    {
        int x = atoi(argv[1]);
        int y = atoi(argv[2]);

        printf(("x = %d, y = %d\n"), x, y);
        printf(("Performing x^=y^=x^=y...\n"));
        x^=y;
        printf("1) x^=y : x = %d, y = %d\n", x, y);
        y^=x;
        printf("2) y^=x : x = %d, y = %d\n", x, y);
        x^=y;
        printf("3) x^=y : x = %d, y = %d\n", x, y);
	// x^=y^=x^=y;
        printf(("x = %d, y = %d\n"), x, y);

    }
    return 0;
}
