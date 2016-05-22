#!/usr/bin/python

import os

Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"] 

Eta = ["10-60", "115-137", "181-201", "201-237"]
new_Eta = ["10_60", "115_137", "181_201", "201_237"]

for arg1 in Menu:
  for arg2 in Iso:
    for arg3 in Eta:
      index = Eta.index(arg3)
      arg4 = new_Eta[index]
      os.system("mv ratio_eta" + arg3 + "_" + arg1 + "_" + arg2 + ".C ratio_eta" + arg4 + "_" + arg1 + "_" + arg2 + ".C")