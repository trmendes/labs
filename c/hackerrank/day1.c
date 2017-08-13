#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i = 4;
    double d = 4.0;
    char s[] = "HackerRank ";
  
    // Declare second integer, double, and String variables.
    int si = 0;
    double sd = 0;
    char ss[100];
    
    // Read and save an integer, double, and String to your variables.
    scanf("%d\n",&si);
    scanf("%lf\n", &sd);
    scanf("%[^\n]",ss);
    // Print the sum of both integer variables on a new line.
    printf("%d\n", i+si);
    // Print the sum of the double variables on a new line.
    printf("%0.1lf\n", d+sd);
    // Concatenate and print the String variables on a new line
    printf("%s%s\n", s, ss);
    // The 's' variable above should be printed first.

   return 0;
}