#!/usr/bin/python

import ROOT

# Find the root files in the folder
from os import listdir
from os.path import isfile, join
onlyfiles = [f for f in listdir(".") if isfile(join(".", f))]
onlyfiles.sort()
onlyRootFiles = [ f for f in onlyfiles if "hist-data15_13TeV" in f]
#print onlyRootFiles
#print len(onlyRootFiles)

# Open the root file and check the number of entries processed
ROOT.gROOT.ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C")
ROOT.xAOD.Init()
for fileName in onlyRootFiles:
  #print fileName, 
  f = ROOT.TFile.Open(fileName)
  print f.h_nEvents.Integral()
  f.Close()
