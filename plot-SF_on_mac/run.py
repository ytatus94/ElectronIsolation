#!/usr/bin/python

import os

menu =[["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"],
       ["TightLLHMC15_v8",  "MediumLLHMC15_v8",  "LooseLLHMC15_v8",  "LooseAndBLayerLLHMC15_v8"]]
iso = [["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose"], 
       ["isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose"], 
       ["isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]]

def run_show_bins(file_name):
  for arg1 in menu[1]:
    print arg1
    for arg2 in iso[1]:
      print arg2
    for arg2 in iso[2]:
      print arg2
  for arg1 in menu[2]:
    for arg2 in iso[3]:
      print arg3
      #os.system('root -b -q showNBins.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"' +  arg3 + '\\")"')
####################

def run_my1DPlot():
  for arg1 in menu:
    for arg2 in iso:
      for arg3 in ["Eff", "SF"]:
        os.system('root -b -q my1DPlot.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"' + arg3 + '\\")"')
####################

def run_mySFPlot():
  for arg1 in menu:
    for arg2 in iso:
      os.system('root -b -q mySFPlot.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\")"')
####################

def run_mySF():
  for arg1 in menu:
    for arg2 in iso:
      for arg3 in range(2, 20):
        #print 'root -b -q myEff.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + str(arg3) + ')"'
        os.system('root -b -q mySF.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + str(arg3) + ')"')
####################

def run_myEff():
  for arg1 in menu:
    for arg2 in iso:
      for arg3 in range(2, 20):
        #print 'root -b -q myEff.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + str(arg3) + ')"'
        os.system('root -b -q myEff.C"(\\"' + arg1 + '\\",\\"' + arg2 + '\\",' + str(arg3) + ')"')
####################

def run_myMllPlot():
Tag = ["TightLLHMC15_v8", "TightLLHMC15_v8_Iso", "MediumLLHMC15_v8_Iso"]
isData = ["true", "false"]

for arg1 in Menu:
  for arg2 in Iso:
    for arg3 in Tag:
      for arg4 in isData:
        if arg4 == "true":
          #os.system('root -b -q myMllPlot.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"Tag' +  arg3 + '\\", true)"') # data
          os.system('root -b -q myMllPlot_Normalized.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"Tag' +  arg3 + '\\", true)"') # data
        elif arg4 == "false":
          #os.system('root -b -q myMllPlot.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"Tag' +  arg3 + '\\", false)"') # MC
          os.system('root -b -q myMllPlot_Normalized.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\", \\"Tag' +  arg3 + '\\", false)"') # MC
        else:
          print "Something wrong..."
####################
        
if __name__ == '__main__':
  pass
  #run_show_bins('abc')



#!/usr/bin/python
# This python script plots the weighted Eff vs eta and the weighted Eff vs pT

import os

Menu =["TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"]
Iso = ["isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
       "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose", 
       "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"]

for arg1 in Menu:
  for arg2 in Iso:
    os.system('root -b -q myWeightedEff.C"(\\"' + arg1 + '\\", \\"' + arg2 + '\\")"')
