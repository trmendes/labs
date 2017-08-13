#!/bin/sh

echo "Number?"
read number
if [ $number -lt 10 ]; then
	echo "$number < 10"
elif [ $number -gt 20 ]; then
	echo "$number > 20"
else
	echo "in my range [10-20]"
fi
