#!/bin/sh

echo "username: "
read logname
line=`grep $logname /etc/passwd`
IFS=:
set $line
echo "Username: $1"
echo "UserID  : $3"
echo "GroupID : $4"
echo "Home    : $6"
echo "Default : $7"


