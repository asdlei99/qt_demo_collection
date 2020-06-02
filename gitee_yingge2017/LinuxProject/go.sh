#!/bin/bash
echo "go.sh"
if [ [ $? =~ "-clean" ] ]
then 
	`make clean`
fi

make && ./test

