#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    double meal_cost = 0, total_cost = 0;
    int tip_percent = 0;
    int tax_percent = 0;
    scanf("%le", &meal_cost);
    scanf("%d", &tip_percent);
    scanf("%d", &tax_percent);
    total_cost = meal_cost + meal_cost * ((double)tip_percent/100) + meal_cost * ((double)tax_percent/100);
    printf("The total meal cost is %d dollars.\n",(int)round(total_cost));
    return 0;
}
