#!/usr/bin/python

import os

Menu =["TightLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose"] 
       

for arg1 in Menu:
  for arg2 in Iso:
    for arg3 in range(0, 101):
      os.system('root -b -q myRatioPlotPt.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\",' + str(arg3) + ')"')
