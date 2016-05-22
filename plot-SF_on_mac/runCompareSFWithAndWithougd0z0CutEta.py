#!/usr/bin/python

import os

Menu =["TightLLH", "MediumLLH", "LooseAndBLayerLLH"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"]

for arg1 in Menu:
  for arg2 in Iso:
    #for arg3 in [2, 3, 4, 13]:
    for arg3 in range(2, 14):
    os.system('root -b -q compareSFWithAndWithougd0z0CutEta.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\",' + str(arg3) + ')"')
