#!/usr/bin/python

import ROOT
import myUtilities

histogram_list = myUtilities.get_histogram_list()
#print histogram_list

#Open a root file
file = ROOT.TFile("testGrid_Mp/output/ScaleFactors.root")
ROOT.gStyle.SetOptStat(0)

# Get the histograms and make plots
for histogram_name in histogram_list:
    histogram = file.Get(histogram_name)
    if histogram:
      canvas = ROOT.TCanvas()
      histogram.GetXaxis().SetTitle("E_{T} [GeV]")
      histogram.GetYaxis().SetTitle("#Delta R")
      histogram.Draw("colz")
      canvas.Print("2D_plots/" + histogram_name.split("/")[1] + ".pdf", "pdf")

