#!/bin/bash
rm -f *pro.user*

datetime=`date +%FT%T`

git add -A
git commit -m "${datetime}"
git push
