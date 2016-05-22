#!/usr/bin/python

import os

FileName = ["../output-SF/ScaleFactors.root", "../output-simpleSF/ScaleFactors.root"]
Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]

for arg1 in FileName:
  for arg2 in Menu:
    for arg3 in Iso:
      os.system('root -b -q showNBins.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"' +  arg3 + '\\")"')
