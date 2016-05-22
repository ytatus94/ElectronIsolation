#!/usr/bin/python
# This python script plots the m_{ll} distribution for all the menu, iso, and tag combinations. 
# 
# 
# Example of root command: root -b -q myPlot6.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlus\")"

import os

#Menu =["TightLLHMC15_v9", "MediumLLHMC15_v9", "LooseLLHMC15_v9", "LooseAndBLayerLLHMC15_v9"]
Menu =["TightLLH_d0z0_v9", "MediumLLH_d0z0_v9", "LooseLLH_d0z0_v9", "LooseAndBLayerLLH_d0z0_v9"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]
Tag = ["TightLLHMC15_v8", "TightLLHMC15_v8_Iso", "MediumLLHMC15_v8_Iso"]

for arg1 in Menu:
  for arg2 in Iso:
    for arg3 in Tag:
      os.system('root -b -q myPlot6.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"Tag' +  arg3 + '\\")"')
