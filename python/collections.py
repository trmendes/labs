#!/bin/python

def string_interpolation():
    print("{} {} {}".format("We","Can","Do it"))
    print("{w} {c} {d}".format(d="Do it", w="We", c="Can"))
    result = 700/111
    print("The result of {}/{} is {:f}".format(700, 111, result))
    print("The result of {}/{} is {:1.2f} (less pressision)".format(700,
                                                                    111,
                                                                    result))
    # More info on string interpolation go to
    # https://pyformat.info/

def list():
    mylist = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    print(mylist)
    print(mylist[1:])
    print(mylist[3:5])
    print(mylist[-1])

def dictionary():
    # A key take you to any type of element
    mydict = {'key1': 1, 'key2': [1, 2], 'key3': True, 'key4': 'tadaa'}

def tuples():
    # Similar to lists but immutable
    mytuple = (1, 2, 3, 4, 1, 1, 1, 2, 2, 2)
    print(mytuple)

def sets():
    # Unique elements
    mylist = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    myset = set(mylist)
    print(myset)


string_interpolation()
list()
dictionary()
tuples()
sets()
