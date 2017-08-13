#!/usr/bin/python
#https://projecteuler.net/problem=1

def multiples_of_3_and_5():
    s = 0
    m = 1000

    for x in range(1, m):
        if ((x % 3 == 0) or (x % 5 == 0)):
            s = s + x

    print("The sum of the multiples of 3 and 5 from 1 to %d is: %d" % (m, s))

multiples_of_3_and_5()