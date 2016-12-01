// This is used to make 2D efficiency plots and scale factor plots
// including the central value and error plots.
// Usage: root -l yt2DPlots.C"(\"TightLLH\",\"isolTight\")"
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "ytUtilities.C"

#include <iostream>
using namespace std;

void yt2DPlots(TString menu = "TightLLH", TString iso  = "isolTight")
{
    //gStyle->SetOptStat(0);
    //SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    TString folder_name;
    if (iso.Contains("isolPhFixedCut"))
        folder_name = menu + "_Smooth_v11_" + iso;
    else
        folder_name = menu + "_d0z0_Smooth_v11_" + iso;
    if (debug) cout << folder_name << endl;

    TFile *file = TFile::Open("../output/ScaleFactors.root");

    TString folder = folder_name;

    TH2F *eff_data_central_value = (TH2F *)file->Get(folder_name + "/EffData_CentralValue_" + folder_name);
    TH2F *eff_data_stat_error    = (TH2F *)file->Get(folder_name + "/EffData_StatError_" + folder_name);
    TH2F *eff_data_syst_error    = (TH2F *)file->Get(folder_name + "/EffData_SystError_" + folder_name);
    TH2F *eff_data_total_error   = (TH2F *)file->Get(folder_name + "/EffData_TotalError_" + folder_name);

    TH2F *eff_mc_central_value = (TH2F *)file->Get(folder_name + "/EffMC_CentralValue_" + folder_name);
    TH2F *eff_mc_stat_error    = (TH2F *)file->Get(folder_name + "/EffMC_StatError_" + folder_name);
    TH2F *eff_mc_syst_error    = (TH2F *)file->Get(folder_name + "/EffMC_SystError_" + folder_name);
    TH2F *eff_mc_total_error   = (TH2F *)file->Get(folder_name + "/EffMC_TotalError_" + folder_name);

    TH2F *sf_central_value = (TH2F *)file->Get(folder_name + "/SF_CentralValue_" + folder_name);
    TH2F *sf_stat_error    = (TH2F *)file->Get(folder_name + "/SF_StatError_" + folder_name);
    TH2F *sf_syst_error    = (TH2F *)file->Get(folder_name + "/SF_SystError_" + folder_name);
    TH2F *sf_total_error   = (TH2F *)file->Get(folder_name + "/SF_TotalError_" + folder_name);

    if (debug) {
        cout << eff_data_central_value << endl;
        cout << eff_data_stat_error << endl;
        cout << eff_data_syst_error << endl;
        cout << eff_data_total_error << endl;

        cout << eff_mc_central_value << endl;
        cout << eff_mc_stat_error << endl;
        cout << eff_mc_syst_error << endl;
        cout << eff_mc_total_error << endl;

        cout << sf_central_value << endl;
        cout << sf_stat_error << endl;
        cout << sf_syst_error << endl;
        cout << sf_total_error << endl;
    }

    TString xtitle = "E_{T} [MeV]";
    TString ytitle = "#eta";
    make_2D_plots(xtitle, ytitle, eff_data_central_value);
    make_2D_plots(xtitle, ytitle, eff_data_stat_error);
    make_2D_plots(xtitle, ytitle, eff_data_syst_error);
    make_2D_plots(xtitle, ytitle, eff_data_total_error);

    make_2D_plots(xtitle, ytitle, eff_mc_central_value);
    make_2D_plots(xtitle, ytitle, eff_mc_stat_error);
    make_2D_plots(xtitle, ytitle, eff_mc_syst_error);
    make_2D_plots(xtitle, ytitle, eff_mc_total_error);

    make_2D_plots(xtitle, ytitle, sf_central_value);
    make_2D_plots(xtitle, ytitle, sf_stat_error);
    make_2D_plots(xtitle, ytitle, sf_syst_error);
    make_2D_plots(xtitle, ytitle, sf_total_error);
}
