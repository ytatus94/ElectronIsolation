#!/bin/bash
# Using rucio download to download files from grid.

if [ -e files.txt ]; then
	rm -rf files.txt
fi

ls ../../input > files.txt

#file_array=$(awk 'BEGIN {FS="."; OFS="."}; {print "user.yushen.Jan29a.egam1T",$2,$3,$6 "_hist"}' files.txt)
file_array=$(awk 'BEGIN {FS="."; OFS="."}; {print "user.yushen.Jan29a.egam1d0z0T",$2,$3,$6 "_hist"}' files.txt)

for file in $file_array
do
	rucio download $file
done

rm -rf files.txt
