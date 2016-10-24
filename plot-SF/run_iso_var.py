#!/usr/bin/python
import os, ROOT

ROOT.gROOT.LoadMacro("iso_var.C")

# ptvarcone20
ROOT.gROOT.ProcessLine('ptvarcone20("testGrid_newT/", "TightLLH")')
ROOT.gROOT.ProcessLine('ptvarcone20("testGrid_newM/", "MediumLLH")')
ROOT.gROOT.ProcessLine('ptvarcone20("testGrid_newL/", "LooseAndBLayerLLH")')

## ptvarcone20/pt
ROOT.gROOT.ProcessLine('ptvarcone20_over_pt("testGrid_newT/", "TightLLH")')
ROOT.gROOT.ProcessLine('ptvarcone20_over_pt("testGrid_newM/", "MediumLLH")')
ROOT.gROOT.ProcessLine('ptvarcone20_over_pt("testGrid_newL/", "LooseAndBLayerLLH")')

ROOT.gROOT.ProcessLine('ptvarcone20_over_pt_ratio_plot("testGrid_newT/", "TightLLH")')
ROOT.gROOT.ProcessLine('ptvarcone20_over_pt_ratio_plot("testGrid_newM/", "MediumLLH")')
ROOT.gROOT.ProcessLine('ptvarcone20_over_pt_ratio_plot("testGrid_newL/", "LooseAndBLayerLLH")')

# topoetcone20
ROOT.gROOT.ProcessLine('topoetcone20("testGrid_newT/", "TightLLH")')
ROOT.gROOT.ProcessLine('topoetcone20("testGrid_newM/", "MediumLLH")')
ROOT.gROOT.ProcessLine('topoetcone20("testGrid_newL/", "LooseAndBLayerLLH")')

# topoetcone20/pt
ROOT.gROOT.ProcessLine('topoetcone20_over_pt("testGrid_newT/", "TightLLH")')
ROOT.gROOT.ProcessLine('topoetcone20_over_pt("testGrid_newM/", "MediumLLH")')
ROOT.gROOT.ProcessLine('topoetcone20_over_pt("testGrid_newL/", "LooseAndBLayerLLH")')

ROOT.gROOT.ProcessLine('topoetcone20_over_pt_ratio_plot("testGrid_newT/", "TightLLH")')
ROOT.gROOT.ProcessLine('topoetcone20_over_pt_ratio_plot("testGrid_newM/", "MediumLLH")')
ROOT.gROOT.ProcessLine('topoetcone20_over_pt_ratio_plot("testGrid_newL/", "LooseAndBLayerLLH")')
