#!/bin/sh

echo "number?"
read number

case $number in
[a-z])
		echo "low case"
		;;
[A-Z])
		echo "upper case"
		;;
[0-9])
		echo "numbers"
		;;
?)
		echo "anything else"
		;;
*)
		echo "more than one chars"
		;;
esac
