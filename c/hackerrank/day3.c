#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n;
    scanf("%d",&n);
    if (n%2!=0) {
        printf("Weird\n");
    } else {
        if (n >= 2 && n <= 5) {
            printf("Not Weird\n");
        }
        if (n >= 6 && n <=20) {
            printf("Weird\n");
        }
        if (n > 20) {
            printf("Not Weird\n");
        }
    }
    return 0;
}
