#!/bin/sh

echo "number?"
read number
if [ $number -gt 10 -a $number -lt 30 ]; then
	echo "brw 10 and 30"
else
	echo "out of my range [10-30]"
fi
