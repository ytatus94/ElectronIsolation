#!/usr/bin/python

import ROOT

def get_histogram(fileName, menu, iso, histName):
  ''' return the 2-dim EffData, EffMC, or SF histogram. '''

  #~ file = ROOT.TFile(fileName)
  folder = menu
  if "isolPhFixed" not in iso:
    folder += "_d0z0_v8_" + iso
  else:
    folder += "MC15_v8_" + iso
  hist = infile.Get(folder + "/" + histName + "_minDeltaR_" + folder)
  if hist:
    #print "Get", folder + "/" + histName + "_minDeltaR_" + folder
    print hist
    return hist
  else:
    print "Histogram", folder + "/" + histName + "_minDeltaR_" + folder, "not found"

def get_histogram_list():
  ''' return a list of histogram names '''
  menu_list = ['TightLLH', 'MediumLLH', 'LooseAndBLayerLLH']
  iso_list = ['isolTight', 'isolLoose', 'isolLooseTrackOnly', 'isolGradient', 'isolGradientLoose',
              'isolFixedCutTightTrackOnly', 'isolFixedCutTight', 'isolFixedCutLoose',
              'isolPhFixedCutTightCaloOnly', 'isolPhFixedCutTight', 'isolPhFixedCutLoose']

  # Get the name of working points
  working_points_list = []
  for menu in menu_list:
    for iso in iso_list:
      if "isolPhFixed" not in iso:
        working_points_list.append(menu + "_d0z0_v8_" + iso)
      else:
        working_points_list.append(menu + "MC15_v8_" + iso)
  #print working_points_list

  # Get the name of 2D histograms
  plot_type_list = ['EffData', 'EffMC', 'SF']
  plot_value_list = ['CentralValue', 'StatError', 'SystError', 'TotalError']
  plot_name_list = []
  for plot_type in plot_type_list:
    for plot_value in plot_value_list:
      plot_name_list.append(plot_type + "_" + plot_value + "_minDeltaR")
  #print plot_name_list

  # Get the histograms name
  histogram_list = []
  for working_point in working_points_list:
    for plot_name in plot_name_list:
      histogram_list.append(working_point + "/" + plot_name + "_" + working_point)

  return histogram_list

if __name__ == '__main__':
  #pass
  infile = ROOT.TFile("ScaleFactors.root")
  print get_histogram("ScaleFactors.root", "LooseAndBLayerLLH", "isolFixedCutTight", "SF_CentralValue")
  #get_histogram("ScaleFactors.root", "TightLLH", "isolFixedCutTight", "SF_CentralValue")
  #print get_histogram_list()

