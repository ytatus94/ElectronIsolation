#!/usr/bin/python

import os

# v8
#Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
#Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
#       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"] 
#Menu =["TightLLHMC15_v8", "MediumLLHMC15_v8", "LooseAndBLayerLLHMC15_v8"]
#Iso = ["isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]

# v10
#Menu =["TightLLH_d0z0_v10"]
#Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
#       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"] 
Menu =["TightLLHMC15_v10"]
Iso = ["isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]

for arg1 in Menu:
  for arg2 in Iso:
    os.system('root -b -q myRecommendation.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\")"')
