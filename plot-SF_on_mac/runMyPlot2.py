#!/usr/bin/python
# This python script plots the m_{ll} distribution for all the menu, iso, and tag combinations. 
# Only plots pT = 35 GeV to pT = 40 GeV.
# Use true for data and false for MC.
# Example of root command: root -b -q myPlot2.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlus\",false)"

import os

#Menu =["TightLLHMC15_v6", "MediumLLHMC15_v6"] #, "LooseLLHMC15_v6"]
#Menu =["TightLLHMC15_v8", "MediumLLHMC15_v8", "LooseLLHMC15_v8"]
#Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose"]
#Tag = ["TightPlusPlus", "TightPlusPlusAndCaloIso", "MediumPlusPlusAndCaloIso"]

#Menu =["TightLLHMC15_v9", "MediumLLHMC15_v9", "LooseLLHMC15_v9", "LooseAndBLayerLLHMC15_v9"]
Menu =["TightLLH_d0z0_v9", "MediumLLH_d0z0_v9", "LooseLLH_d0z0_v9", "LooseAndBLayerLLH_d0z0_v9"]
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
          #os.system('root -b -q myPlot2.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"Tag' +  arg3 + '\\", true)"') # data
          os.system('root -b -q myPlot2.C"(\\"' + arg1 + '\\", \\"Tag' +  arg3 + '\\", true)"') # data
        elif arg4 == "false":
          #os.system('root -b -q myPlot2.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"Tag' +  arg3 + '\\", false)"') # MC
          os.system('root -b -q myPlot2.C"(\\"' + arg1 + '\\", \\"Tag' +  arg3 + '\\", false)"') # MC
        else:
          print "Something wrong..."
