#!/usr/bin/python

import os

Menu =["TightLLH_d0z0_v9", "MediumLLH_d0z0_v9", "LooseLLH_d0z0_v9", "LooseAndBLayerLLH_d0z0_v9"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]

for arg1 in Menu:
  for arg2 in Iso:
    for arg3 in range(2, 20):
      #print 'root -b -q myEff.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + str(arg3) + ')"'
      os.system('root -b -q myEff.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + str(arg3) + ')"')
