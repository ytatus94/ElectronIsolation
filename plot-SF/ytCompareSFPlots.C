// This is used to make 1 dim ratio plots comparison
// projection on X axis (pt axis) and Y axis (eta axis).
// Usage: root -l ytCompareRatioPlots.C"(\"TightLLH\",\"isolTight\")"
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

void ytCompareSFPlots(TString menu = "TightLLH", TString iso = "isolTight")
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

    TH2F *sf_central_value = (TH2F *)file->Get(folder_name + "/SF_CentralValue_" + folder_name);
    TH2F *sf_stat_error    = (TH2F *)file->Get(folder_name + "/SF_StatError_" + folder_name);
    TH2F *sf_syst_error    = (TH2F *)file->Get(folder_name + "/SF_SystError_" + folder_name);
    TH2F *sf_total_error   = (TH2F *)file->Get(folder_name + "/SF_TotalError_" + folder_name);

    if (debug) {
        cout << sf_central_value << endl;
        cout << sf_stat_error << endl;
        cout << sf_syst_error << endl;
        cout << sf_total_error << endl;
    }
/*
	TString rootcore_path = TString(std::getenv("ROOTCOREBIN"));
	TString tool_path = rootcore_path + "/include/ElectronEfficiencyCorrection/../data/";
	if (debug) {
		cout << "ROOTCOREBINE=" << rootcore_path << endl;
		cout << tool_path << endl;
	}
    TFile *tool_file = TFile::Open(tool_path + "efficiencySF.Isolation." + menu + "_d0z0_v8_" + iso + ".2015.13TeV.rel20p0.25ns.v04.root");
    //TFile *tool_file = TFile::Open(tool_path + "efficiencySF.Isolation." + folder_name + ".2015.13TeV.rel20p0.25ns.v04.root");
    //TFile *tool_file = TFile::Open("/afs/cern.ch/user/y/yushen/moriond/efficiencySF.Isolation." + folder_name + ".2015.13TeV.rel20p0.25ns.v04.root");

    TH2F *tool_sf      = (TH2F *)tool_file->Get("0_9999999/FullSim_sf");
    TH2F *tool_sf_tot  = (TH2F *)tool_file->Get("0_9999999/FullSim_tot");
    TH2F *tool_sf_stat = (TH2F *)tool_file->Get("0_9999999/FullSim_stat");
*/
	// Kristin Lohwasser move all the root files inside /data/ to CalibArea
	TString file_path = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/ElectronEfficiencyCorrection/2015_2016/rel20.7/ICHEP_June2016_v1/isolation/";
	TFile *tool_file = TFile::Open(file_path + "efficiencySF.Isolation." + menu + "_d0z0_v11_" + iso + ".2015_2016.13TeV.rel20.7.25ns.v01.root");

	// 2015 recommendation uses 266904_284484
	// 2016 pre-recommendation uses 296939_9999999
    TH2F *tool_sf      = (TH2F *)tool_file->Get("296939_9999999/FullSim_sf");
    TH2F *tool_sf_tot  = (TH2F *)tool_file->Get("296939_9999999/FullSim_tot");
    TH2F *tool_sf_stat = (TH2F *)tool_file->Get("296939_9999999/FullSim_stat");

    if (debug) {
        cout << tool_sf << endl;
        cout << tool_sf_tot << endl;
        cout << tool_sf_stat << endl;
    }

    //
    // projection on eta axis
    //
    for (int pt_bin = 2; pt_bin < sf_central_value->GetXaxis()->GetNbins() + 1; pt_bin++) {
        int pt_bin_low = static_cast<int>(sf_central_value->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.);
        int pt_bin_up  = static_cast<int>(sf_central_value->GetXaxis()->GetBinUpEdge(pt_bin) / 1000.);
        char pt_range[100];
        sprintf(&pt_range[0], "%d GeV < p_{T} < %d GeV", pt_bin_low, pt_bin_up);
        // SF
        TH1F *central_value = (TH1F *)sf_central_value->ProjectionY("", pt_bin, pt_bin)->Clone();
        TH1F *total_error   = (TH1F *)sf_total_error->ProjectionY("", pt_bin, pt_bin)->Clone();
        TH1F *central_value_clone = (TH1F*)central_value->Clone();
        TH1F *stat_error    = (TH1F *)sf_stat_error->ProjectionY("", pt_bin, pt_bin)->Clone();
        fixHistogramError(central_value, total_error);
        fixHistogramError(central_value_clone, stat_error);
        // recommendation
        // In recommendation, the first bin is 7 GeV to 10 GeV
        TH1F *recommendation       = (TH1F *)tool_sf->ProjectionY("", pt_bin - 1, pt_bin - 1)->Clone();
        TH1F *recommendation_tot   = (TH1F *)tool_sf_tot->ProjectionY("", pt_bin - 1, pt_bin - 1)->Clone();
        TH1F *recommendation_clone = (TH1F *)recommendation->Clone();
        TH1F *recommendation_stat  = (TH1F *)tool_sf_stat->ProjectionY("", pt_bin - 1, pt_bin - 1)->Clone();
        fixHistogramError(recommendation, recommendation_tot);
        fixHistogramError(recommendation_clone, recommendation_stat);

        if (debug) {
            cout << central_value << endl;
            cout << total_error << endl;
            cout << central_value_clone << endl;
            cout << stat_error << endl;
            cout << sf_central_value->GetXaxis()->GetBinLowEdge(pt_bin) << endl;
            cout << sf_central_value->GetXaxis()->GetBinUpEdge(pt_bin) << endl;

            cout << recommendation << endl;
            cout << recommendation_tot << endl;
            cout << recommendation_clone << endl;
            cout << recommendation_stat << endl;
            cout << tool_sf->GetXaxis()->GetBinLowEdge(pt_bin - 1) << endl;
            cout << tool_sf->GetXaxis()->GetBinUpEdge(pt_bin - 1) << endl;
			cout << "***" << endl;
        }
//        make_compare_plot("#eta", "Scale Factor", folder_name, TString(pt_range), pt_bin_low, pt_bin_up,
//                          "Moriond recommendation", "reprocessed 2015 data", recommendation, central_value);
        make_compare_ratio_plot("#eta", "Scale Factor", folder_name, TString(pt_range), pt_bin_low, pt_bin_up,
                                "pre-recommendation", "2016 DS1.3", recommendation, central_value);
    }

    //
    // projection on pt axis
    //
    for (int eta_bin = 1; eta_bin < sf_central_value->GetYaxis()->GetNbins() + 1; eta_bin++) {
        float eta_bin_low = sf_central_value->GetYaxis()->GetBinLowEdge(eta_bin);
        float eta_bin_up  = sf_central_value->GetYaxis()->GetBinUpEdge(eta_bin);
        char eta_range[100];
        sprintf(&eta_range[0], "%.2f < #eta < %.2f", eta_bin_low, eta_bin_up);
        // SF
        TH1F *central_value = (TH1F *)sf_central_value->ProjectionX("", eta_bin, eta_bin)->Clone();
        TH1F *total_error   = (TH1F *)sf_total_error->ProjectionX("", eta_bin, eta_bin)->Clone();
        TH1F *central_value_clone = (TH1F*)central_value->Clone();
        TH1F *stat_error    = (TH1F *)sf_stat_error->ProjectionX("", eta_bin, eta_bin)->Clone();
        fixHistogramError(central_value, total_error);
        fixHistogramError(central_value_clone, stat_error);
        // recommendation
        TH1F *recommendation       = (TH1F *)tool_sf->ProjectionX("", eta_bin, eta_bin)->Clone();
        TH1F *recommendation_tot   = (TH1F *)tool_sf_tot->ProjectionX("", eta_bin, eta_bin)->Clone();
        TH1F *recommendation_clone = (TH1F *)recommendation->Clone();
        TH1F *recommendation_stat  = (TH1F *)tool_sf_stat->ProjectionX("", eta_bin, eta_bin)->Clone();
        fixHistogramError(recommendation, recommendation_tot);
        fixHistogramError(recommendation_clone, recommendation_stat);

        if (debug) {
            cout << central_value << endl;
            cout << total_error << endl;
            cout << central_value_clone << endl;
            cout << stat_error << endl;
            cout << sf_central_value->GetYaxis()->GetBinLowEdge(eta_bin) << endl;
            cout << sf_central_value->GetYaxis()->GetBinUpEdge(eta_bin) << endl;

            cout << recommendation << endl;
            cout << recommendation_tot << endl;
            cout << recommendation_clone << endl;
            cout << recommendation_stat << endl;
            cout << tool_sf->GetYaxis()->GetBinLowEdge(eta_bin) << endl;
            cout << tool_sf->GetYaxis()->GetBinUpEdge(eta_bin) << endl;
			cout << "***" << endl;
        }
//        make_compare_plot("E_{T} [MeV]", "Scale Factor", folder_name, TString(eta_range), eta_bin_low, eta_bin_up,
//                          "Moriond recommendation", "reprocessed 2015 data", recommendation, central_value);
        make_compare_ratio_plot("E_{T} [MeV]", "Scale Factor", folder_name, TString(eta_range), eta_bin_low, eta_bin_up,
                                "pre-recommendation", "2016 DS1.3", recommendation, central_value);
    }
}
