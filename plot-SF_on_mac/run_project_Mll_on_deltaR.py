#!/usr/bin/python

# Usage: root -l project_Mll_on_deltaR.C"(\"TightLLH\",\"isolLoose\", false, 8, 9, 3, 5)"

import os
menu = ["TightLLH", "MediumLLH", "LooseAndBLayerLLH"]
iso = [["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose"],
       ["isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"],
       ["isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]]

isMC = "false"
dR = [3, 5, 7, 9, 11, 21, 101] # corresponds to deltaR=[0.2, 0.4, 0.6, 0.8, 1, 2, 10]

arg1 = menu[0]
for arg2 in iso[0]:
  #print arg2
  arg3 = isMC
  for arg4 in range(2, 20): # pt bins from bin=2 to bin=19
    arg5 = arg4 + 1
    for arg6 in dR:
      if arg6 != dR[-1]:
        index = dR.index(arg6)
        arg7 = dR[index + 1]
      else:
        continue
      #print arg6, arg7
      #print 'root -b -q project_Mll_on_deltaR.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + arg3 + ',' + str(arg4) + ',' + str(arg5) + ',' + str(arg6) + ',' + str(arg7) + ')"'
      os.system('root -b -q project_Mll_on_deltaR.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + arg3 + ',' + str(arg4) + ',' + str(arg5) + ',' + str(arg6) +     ',' + str(arg7) + ')"')
