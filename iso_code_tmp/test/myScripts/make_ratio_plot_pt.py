#!/usr/bin/python

import ROOT

verbose = True

file = ROOT.TFile("ScaleFactors.root");
menu = "LooseAndBLayerLLH"
iso = "isolFixedCutTight"
working_point = menu + "_d0z0_v8_" + iso
# debug
if verbose is True:
  print working_point + "/" + "EffData_CentralValue_minDeltaR_" + working_point

# Get all histograms
h_EffData_central_value = file.Get(working_point + "/" + "EffData_CentralValue_minDeltaR_" + working_point)
h_EffData_total_error   = file.Get(working_point + "/" + "EffData_TotalError_minDeltaR_" + working_point)
h_EffMC_central_value   = file.Get(working_point + "/" + "EffMC_CentralValue_minDeltaR_" + working_point)
h_EffMC_total_error     = file.Get(working_point + "/" + "EffMC_TotalError_minDeltaR_" + working_point)
h_SF_central_value      = file.Get(working_point + "/" + "SF_CentralValue_minDeltaR_" + working_point)
h_SF_total_error        = file.Get(working_point + "/" + "SF_TotalError_minDeltaR_" + working_point)
# debug
if verbose is True:
  # print the memory address
  print h_EffData_central_value
  print h_EffData_total_error
  print h_EffMC_central_value
  print h_EffMC_total_error
  print h_SF_central_value
  print h_SF_total_error

  print 'In {histogram_name}: NbinsX={NbinsX}, NbinsY={NBinsY}'.format(histogram_name=h_EffData_central_value.GetName(),
                                                                       NbinsX=h_EffData_central_value.GetXaxis().GetNbins(),
                                                                       NBinsY=h_EffData_central_value.GetYaxis().GetNbins())
# X: pT
# Y: deltaR

#
# project on deltR axis
#
for pt in range(1, h_EffData_central_value.GetXaxis().GetNbins() + 1):
  data = h_EffData_central_value.ProjectionY("", pt, pt).Clone();
  data_err = h_EffData_total_error.ProjectionY("", pt, pt).Clone();
  # fix the error of each bin
  for ik in range(1, h_EffData_central_value.GetXaxis().GetNbins()):
    h_EffData_central_value.SetBinError(ik, h_EffData_total_error.GetBinContent(ik))
#
# project on pt axis
#
for deltaR in range(1, h_EffData_central_value.GetYaxis().GetNbins() + 1):
  h_EffData_central_value.ProjectionX("", deltaR, deltaR).Clone();
  h_EffData_total_error.ProjectionX("", deltaR, deltaR).Clone();


#
# Make ratio plot
#
c1 = ROOT.TCanvas(h_EffData_central_value.GetName())
# Upper plot will be in pad1
pad1 = ROOT.TPad("pad1", "pad1", 0, 0.35, 1, 1.0)
pad1.SetBottomMargin(0) # Upper and lower plot are joined
#pad1.SetGridy() # grid lines
pad1.Draw()

# lower plot will be in pad
pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
pad2.SetTopMargin(0)
pad2.SetBottomMargin(0.3)
pad2.SetGridy() # grid lines
pad2.Draw()

pad1.cd() # pad1 becomes the current pad

# Draw curve here

