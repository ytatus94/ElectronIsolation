#!/usr/bin/python
# This python script plots the weighted SF vs eta and the weighted SF vs pT.

import os

Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]

for arg1 in Menu:
  for arg2 in Iso:
    os.system('root -b -q myWeightedSF.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\")"')
