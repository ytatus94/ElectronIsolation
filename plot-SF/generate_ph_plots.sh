#!/bin/bash
root -q -b ytMllPlot.C"(\"TightLLH\",\"isolPhFixedCutTightCaloOnly\")"
root -q -b ytMllPlot.C"(\"TightLLH\",\"isolPhFixedCutTight\")"
root -q -b ytMllPlot.C"(\"TightLLH\",\"isolPhFixedCutLoose\")"

root -q -b yt2DPlots.C"(\"TightLLH\",\"isolPhFixedCutTightCaloOnly\")"
root -q -b yt2DPlots.C"(\"TightLLH\",\"isolPhFixedCutTight\")"
root -q -b yt2DPlots.C"(\"TightLLH\",\"isolPhFixedCutLoose\")"

root -q -b yt1DEffPlots.C"(\"TightLLH\",\"isolPhFixedCutTightCaloOnly\")"
root -q -b yt1DEffPlots.C"(\"TightLLH\",\"isolPhFixedCutTight\")"
root -q -b yt1DEffPlots.C"(\"TightLLH\",\"isolPhFixedCutLoose\")"

root -q -b yt1DSFPlots.C"(\"TightLLH\",\"isolPhFixedCutTightCaloOnly\")"
root -q -b yt1DSFPlots.C"(\"TightLLH\",\"isolPhFixedCutTight\")"
root -q -b yt1DSFPlots.C"(\"TightLLH\",\"isolPhFixedCutLoose\")"

root -q -b ytRatioPlots.C"(\"TightLLH\",\"isolPhFixedCutTightCaloOnly\")"
root -q -b ytRatioPlots.C"(\"TightLLH\",\"isolPhFixedCutTight\")"
root -q -b ytRatioPlots.C"(\"TightLLH\",\"isolPhFixedCutLoose\")"

root -q -b ytCompareSFPlots.C"(\"TightLLH\",\"isolPhFixedCutTightCaloOnly\")"
root -q -b ytCompareSFPlots.C"(\"TightLLH\",\"isolPhFixedCutTight\")"
root -q -b ytCompareSFPlots.C"(\"TightLLH\",\"isolPhFixedCutLoose\")"
