#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>

TH2F* getIsolationVariable(TString inputfile,
                           TString menu,
                           TString histName)
{
TFile *file = TFile::Open(inputfile);
TString folder = "PlotVars_" + menu;
// Loading the isolation variables from the file
TString h_pt                   = "PlotVars_" + menu + "_h_el_pt";

TString h_ptvarcone20          = "PlotVars_" + menu + "_h_ptvarcone20";
TString h_ptvarcone20_over_pt  = "PlotVars_" + menu + "_h_ptvarcone20_over_pt";
TString h_ptvarcone20_vs_pt    = "PlotVars_" + menu + "_h_ptvarcone20_vs_pt";

TString h_topoetcone20         = "PlotVars_" + menu + "_h_topoetcone20";
TString h_topoetcone20_over_pt = "PlotVars_" + menu + "_h_topoetcone20_over_pt";
TString h_topoetcone20_vs_pt   = "PlotVars_" + menu + "_h_topoetcone20_vs_pt";

TH1F *h_pt                   = "PlotVars_" + menu + "_h_el_pt";

TH1F *h_ptvarcone20          = "PlotVars_" + menu + "_h_ptvarcone20";
TH1F *h_ptvarcone20_over_pt  = "PlotVars_" + menu + "_h_ptvarcone20_over_pt";
TH2F *h_ptvarcone20_vs_pt    = "PlotVars_" + menu + "_h_ptvarcone20_vs_pt";

TH1F *h_topoetcone20         = "PlotVars_" + menu + "_h_topoetcone20";
TH1F *h_topoetcone20_over_pt = "PlotVars_" + menu + "_h_topoetcone20_over_pt";
TH2F *h_topoetcone20_vs_pt   = "PlotVars_" + menu + "_h_topoetcone20_vs_pt";


TH2F *hist = new TH2F;	
if (histName == "") 

}
