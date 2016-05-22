// We want to see the distributions of isolation variables so we cannot apply isolation requirement on the probe electrons.
// i.e. Only see the histograms under PlotVars_<menu>
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

void myIsoVar6(TString menu = "TightLLH_d0z0_v8")
{
    SetAtlasStyle();
    
    TString folder = "PlotVars_" + menu;
    
    TString path = "~/Desktop/topoetcone40/";
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc   = TFile::Open(path + "merged-hist-mc.root");
    
    // Loading the isolation variables from the data and MC root files.
    TString h_pt = "PlotVars_" + menu + "_h_el_pt";

    TString h_etcone20 = "PlotVars_" + menu + "_h_el_etcone20";
    TString h_etcone30 = "PlotVars_" + menu + "_h_el_etcone30";
    TString h_etcone40 = "PlotVars_" + menu + "_h_el_etcone40";
    
    TString h_topoetcone20 = "PlotVars_" + menu + "_h_el_topoetcone20";
    TString h_topoetcone30 = "PlotVars_" + menu + "_h_el_topoetcone30";
    TString h_topoetcone40 = "PlotVars_" + menu + "_h_el_topoetcone40";
    
    TString h_ptvarcone20 = "PlotVars_" + menu + "_h_el_ptvarcone20";
    TString h_ptvarcone30 = "PlotVars_" + menu + "_h_el_ptvarcone30";
    TString h_ptvarcone40 = "PlotVars_" + menu + "_h_el_ptvarcone40";
    
    TString h_ptvarcone20_over_pt  = "PlotVars_" + menu + "_h_el_ptvarcone20_over_pt";
    TString h_topoetcone20_over_pt = "PlotVars_" + menu + "_h_el_topoetcone20_over_pt";
    // 2D
    TString h_ptvarcone20_vs_pt  = "PlotVars_" + menu + "_h_el_ptvarcone20_vs_pt";
    TString h_topoetcone20_vs_pt = "PlotVars_" + menu + "_h_el_topoetcone20_vs_pt";
    // 3D
    TString h_3D_el_topoetcone40 = "PlotVars_" + menu + "_h_3D_el_topoetcone40";
    TString h_3D_el_topoetcone40_over_pt = "PlotVars_" + menu + "_h_3D_el_topoetcone40_over_pt";
    
    // Data
    TH1F *data_pt           = (TH1F *)fdata->Get(folder + "/" + h_pt);
    TH1F *data_etcone20     = (TH1F *)fdata->Get(folder + "/" + h_etcone20);
    TH1F *data_etcone30     = (TH1F *)fdata->Get(folder + "/" + h_etcone30);
    TH1F *data_etcone40     = (TH1F *)fdata->Get(folder + "/" + h_etcone40);
    TH1F *data_topoetcone20 = (TH1F *)fdata->Get(folder + "/" + h_topoetcone20);
    TH1F *data_topoetcone30 = (TH1F *)fdata->Get(folder + "/" + h_topoetcone30);
    TH1F *data_topoetcone40 = (TH1F *)fdata->Get(folder + "/" + h_topoetcone40);
    TH1F *data_ptvarcone20  = (TH1F *)fdata->Get(folder + "/" + h_ptvarcone20);
    TH1F *data_ptvarcone30  = (TH1F *)fdata->Get(folder + "/" + h_ptvarcone30);
    TH1F *data_ptvarcone40  = (TH1F *)fdata->Get(folder + "/" + h_ptvarcone40);
    TH1F *data_ptvarcone20_over_pt  = (TH1F *)fdata->Get(folder + "/" + h_ptvarcone20_over_pt);
    TH1F *data_topoetcone20_over_pt = (TH1F *)fdata->Get(folder + "/" + h_topoetcone20_over_pt);
    // 2D
    TH2F *data_ptvarcone20_vs_pt    = (TH2F *)fdata->Get(folder + "/" + h_ptvarcone20_vs_pt);
    TH2F *data_topoetcone20_vs_pt   = (TH2F *)fdata->Get(folder + "/" + h_topoetcone20_vs_pt);
    // 3D
    TH3F *data_3D_el_topoetcone40   = (TH3F *)fdata->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *data_3D_el_topoetcone40_over_pt = (TH3F *)fdata->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);

    data_pt->Sumw2();
    data_etcone20->Sumw2();
    data_etcone30->Sumw2();
    data_etcone40->Sumw2();
    data_topoetcone20->Sumw2();
    data_topoetcone30->Sumw2();
    data_topoetcone40->Sumw2();
    data_ptvarcone20->Sumw2();
    data_ptvarcone30->Sumw2();
    data_ptvarcone40->Sumw2();
    data_ptvarcone20_over_pt->Sumw2();
    data_topoetcone20_over_pt->Sumw2();
    data_ptvarcone20_vs_pt->Sumw2();
    data_topoetcone20_vs_pt->Sumw2();
    data_3D_el_topoetcone40->Sumw2();
    data_3D_el_topoetcone40_over_pt->Sumw2();

    // MC
    TH1F *mc_pt           = (TH1F *)fmc->Get(folder + "/" + h_pt);
    TH1F *mc_etcone20     = (TH1F *)fmc->Get(folder + "/" + h_etcone20);
    TH1F *mc_etcone30     = (TH1F *)fmc->Get(folder + "/" + h_etcone30);
    TH1F *mc_etcone40     = (TH1F *)fmc->Get(folder + "/" + h_etcone40);
    TH1F *mc_topoetcone20 = (TH1F *)fmc->Get(folder + "/" + h_topoetcone20);
    TH1F *mc_topoetcone30 = (TH1F *)fmc->Get(folder + "/" + h_topoetcone30);
    TH1F *mc_topoetcone40 = (TH1F *)fmc->Get(folder + "/" + h_topoetcone40);
    TH1F *mc_ptvarcone20  = (TH1F *)fmc->Get(folder + "/" + h_ptvarcone20);
    TH1F *mc_ptvarcone30  = (TH1F *)fmc->Get(folder + "/" + h_ptvarcone30);
    TH1F *mc_ptvarcone40  = (TH1F *)fmc->Get(folder + "/" + h_ptvarcone40);
    TH1F *mc_ptvarcone20_over_pt  = (TH1F *)fmc->Get(folder + "/" + h_ptvarcone20_over_pt);
    TH1F *mc_topoetcone20_over_pt = (TH1F *)fmc->Get(folder + "/" + h_topoetcone20_over_pt);
    // 2D
    TH2F *mc_ptvarcone20_vs_pt    = (TH2F *)fmc->Get(folder + "/" + h_ptvarcone20_vs_pt);
    TH2F *mc_topoetcone20_vs_pt   = (TH2F *)fmc->Get(folder + "/" + h_topoetcone20_vs_pt);
    // 3D
    TH3F *mc_3D_el_topoetcone40   = (TH3F *)fmc->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *mc_3D_el_topoetcone40_over_pt = (TH3F *)fmc->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);
    
    mc_pt->Sumw2();
    mc_etcone20->Sumw2();
    mc_etcone30->Sumw2();
    mc_etcone40->Sumw2();
    mc_topoetcone20->Sumw2();
    mc_topoetcone30->Sumw2();
    mc_topoetcone40->Sumw2();
    mc_ptvarcone20->Sumw2();
    mc_ptvarcone30->Sumw2();
    mc_ptvarcone40->Sumw2();
    mc_ptvarcone20_over_pt->Sumw2();
    mc_topoetcone20_over_pt->Sumw2();
    mc_ptvarcone20_vs_pt->Sumw2();
    mc_topoetcone20_vs_pt->Sumw2();
    mc_3D_el_topoetcone40->Sumw2();
    mc_3D_el_topoetcone40_over_pt->Sumw2();
}