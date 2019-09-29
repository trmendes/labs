#!/bin/python

for num in range(0, 11, 2):
    print(num)

# range is a generator
# generators are sort of functions that
# will generate data instead of saving it to memory (?)

# to save it to memory you have to connect it to some variable

mylist = list(range(0, 11, 2))
print(mylist)

idx_cnt = 0
for letter in 'abcd':
    print('at index {} the letter is {}'.format(idx_cnt, letter))
    idx_cnt = idx_cnt + 1

# inumarate
# it will return me tooples :O
for item in enumerate('abcde'):
    print(item)

# because it returns tooples I can use the toople unpacking
for (idx, item) in enumerate('abcde'):
    print("{} - {}".format(idx, item))

mylist1 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
mylist2 = ['a', 'b', 'c', 'd']

# just like a zipper in a jacket it will
# zip to lists or objects together :O
# zip will go trough the ammount of elements of the smallest list
# it will ignore the rest
for item in zip(mylist1, mylist2):
    print(item)

# it also returns a tupple so we can use tupple unpaking
for (idx, item) in zip(mylist1, mylist2):
    print("{} - {}".format(idx, item))

