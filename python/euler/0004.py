#!/usr/bin/python

#https://projecteuler.net/problem=4

def is_palindrome(n):
    return str(n) == str(n)[::-1]

def largest_palindrome_product(digits):
    top = 9
    bot = 1
    r = 0

    bx = 0
    by = 0
    br = 0

    for k in range(digits-1):
        top = top * 10
        top = top + 9
        bot = bot * 10

    for x in range(top,bot,-1):
        for y in range(top,bot,-1):
            r = x * y
            isit = is_palindrome(r)
            if (isit == True):
                if (r > br):
                    br = r
                    bx = x
                    by = y

    print("The largest palindrome for %d digits is %d [%d * %d]" % (digits, br, bx, by))

largest_palindrome_product(3)