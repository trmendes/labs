#!/bin/sh

count=1

while [ $count -lt 10 ]; do
	echo $count
	count=`expr $count + 1`
done
