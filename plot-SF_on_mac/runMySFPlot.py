#!/usr/bin/python
# This python script plots SF centeral value and uncertainties.
# Example of root command: root -b -q mySFPlot.C"(\"TightLLHMC15_v6\",\"isolTight\")"

import os

Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]

for arg1 in Menu:
  for arg2 in Iso:
    os.system('root -b -q mySFPlot.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\")"')
