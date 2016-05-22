#!/usr/bin/python

import ROOT

menu_list = ['TightLLH', 'MediumLLH', 'LooseAndBLayerLLH']
iso_list = ['isolTight', 'isolLoose', 'isolLooseTrackOnly', 'isolGradient', 'isolGradientLoose',
            'isolFixedCutTightTrackOnly', 'isolFixedCutTight', 'isolFixedCutLoose',
            'isolPhFixedCutTightCaloOnly', 'isolPhFixedCutTight', 'isolPhFixedCutLoose']

## Get the name of working points
working_points_list = []
for menu in menu_list:
  for iso in iso_list:
    if "isolPhFixed" not in iso:
      working_points_list.append(menu + "_d0z0_v8_" + iso)
    else:
      working_points_list.append(menu + "MC15_v8_" + iso)
print working_points_list

# Get the name of 2D histograms
plot_type_list = ['EffData', 'EffMC', 'SF']
plot_value_list = ['CentralValue', 'StatError', 'SystError', 'TotalError']
plot_name_list = []
for plot_type in plot_type_list:
  for plot_value in plot_value_list:
    plot_name_list.append(plot_type + "_" + plot_value + "_minDeltaR")
print plot_name_list

#Open a root file
file = ROOT.TFile("ScaleFactors.root")
ROOT.gStyle.SetOptStat(0)

# Get the histograms and make plots
for working_point in working_points_list:
  for plot_name in plot_name_list:
    histogram_name = working_point + "/" + plot_name + "_" + working_point
    #print file.Get(histogram_name)
    histogram = file.Get(histogram_name)
    if histogram:
      canvas = ROOT.TCanvas()
      histogram.GetXaxis().SetTitle("E_{T} [GeV]")
      histogram.GetYaxis().SetTitle("#Delta R")
      histogram.Draw("colz")
      canvas.Print(plot_name + "_" + working_point + ".pdf", "pdf")

