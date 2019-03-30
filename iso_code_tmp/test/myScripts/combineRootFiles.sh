#!/bin/bash
# combine the root file in the current directory.

# 1. Find directories name begin with "user.yushen.Jan29a.egam1d0z0T."
#for dir in $(ls -d user.yushen.Jan29a.egam1T.*)
for dir in $(ls -d user.yushen.Jan29a.egam1d0z0T.*)
do
	cd $dir
	name=$(echo $dir | awk 'BEGIN {FS=".";OFS="."}; {print "hist-data15_13TeV",$5,$6,"merge.DAOD_EGAM1",$7,"root"}')
	output_root=$(echo $name | sed 's/_hist//g')
	hadd -f $output_root $(ls user.yushen.*.hist-output.root)
	mv $output_root ../
	cd ../
done
