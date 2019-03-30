#!/bin/bash
current_path=$(pwd)
path=${current_path%20160206_v8} # remove 20160206_v8 in the current_path
echo $path
mc15bd0z0_path=${path}mc15bd0z0/
mc15b_path=${path}mc15b/
AF2d0z0_path=${path}AF2d0z0/
AF2_path=${path}AF2/
echo $mc15bd0z0_path
echo $mc15b_path
echo $AF2d0z0_path
echo $AF2_path

echo cp ${mc15bd0z0_path}output/ScaleFactors.root MC15bd0z0_ScaleFactors.root
echo
#output
#ScaleFactors.root  variations_reference.root
