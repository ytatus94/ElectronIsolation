#!/usr/bin/python
 
import ROOT
import os

dirList = []
for d in os.listdir("."):
  if os.path.isdir(d):
    dirList.append(d)
print dirList
print len(dirList)

fileList = []
for d in dirList:
  for f in os.listdir(d):
    fileList.append(d+"/"+f)
print filelist
print len(filelist)
fileList.sort()
 
# Open the root file and check the number of entries processed
ROOT.gROOT.ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C")
ROOT.xAOD.Init()
for fileName in fileList:
    print fileName, 
    f = ROOT.TFile.Open(fileName)
    print f.h_nEvents.Integral()
    f.Close()
