#!/usr/bin/python
# This python script plots the m_{ll} distribution for all the menu, iso, and tag combinations. 
# Only plots pT = 35 GeV to pT = 40 GeV.
# Use true for data and false for MC.
# Example of root command: root -b -q myMllPlot_pT35to40.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlus\",false)"

import os

Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]
Tag = ["TightLLHMC15_v8", "TightLLHMC15_v8_Iso", "MediumLLHMC15_v8_Iso"]
isData = ["true", "false"]

for arg1 in Menu:
  #for arg2 in Iso:
    for arg3 in Tag:
      for arg4 in isData:
        if arg4 == "true":
          os.system('root -b -q myMllPlot_pT35to40.C"(\\"' + arg1 + '\\", \\"Tag' +  arg3 + '\\", true)"') # data
        elif arg4 == "false":
          os.system('root -b -q myMllPlot_pT35to40.C"(\\"' + arg1 + '\\", \\"Tag' +  arg3 + '\\", false)"') # MC
        else:
          print "Something wrong..."
