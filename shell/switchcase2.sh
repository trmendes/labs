#!/bin/sh

echo ">"
read text

case $text in
[a-z]* | [A-Z]*)
	echo "start with a char"
	;;
[0-9]*)
	echo "start with a number"
	;;
[a-z] | [A-Z])
	echo "chars only"
	;;
[0-9])
	echo "numbers only"
	;;
?)
	echo "special"
	;;
*)
	echo "rest"
	;;
esac
