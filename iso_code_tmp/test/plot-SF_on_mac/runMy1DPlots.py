#!/usr/bin/python
# This python script plots 1-dim efficiency and scale factors for each pT bin.
# Example of root command:
# 1.) to plot efficiency: root -b -q my1DPlot.C"(\"TightLLHMC15_v6\",\"isolTight\", \"Eff\")"
# 2.) to plot scale factors: root -b -q my1DPlot.C"(\"TightLLHMC15_v6\",\"isolTight\", \"SF\")"

import os

Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]
Plot = ["Eff", "SF"]

for arg1 in Menu:
  for arg2 in Iso:
    for arg3 in Plot:
      os.system('root -b -q my1DPlot.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"' + arg3 + '\\")"')
