#!/usr/bin/python

import os

Menu =["TightLLH", "MediumLLH", "LooseAndBLayerLLH"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"]

for arg1 in Menu:
  for arg2 in Iso:
    for arg3 in range(12, 20):
    #for arg3 in [12, 15, 18, 19]:
      os.system('root -b -q myCompTwoFilesEffAndSFPt.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\",' + str(arg3) + ')"')
