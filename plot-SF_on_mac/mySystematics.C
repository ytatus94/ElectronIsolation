//
//
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"

#include <iostream>
using namespace std;

void compareSFVariations(TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h4 = NULL);

void mySystematics(TString menu = "TightLLH_d0z0_v8",
                   TString iso  = "isolTight",
                   int pt_bin = 3)
{
	TString fileName1 = "~/test/ElectronEfficiencyCorrection-00-01-42/data/isolations/efficiencySF.Isolation." + menu + "_" + iso + ".2015.13TeV.rel20p0.25ns.v04.root";
	TFile *file1 = TFile::Open(fileName1);
	TH2F *h_FullSim_sf = (TH2F*)file1->Get("0_9999999/FullSim_sf");
	TH1F *h_FullSim_sf_project_on_eta = (TH1F*)h_FullSim_sf->ProjectionY("", pt_bin, pt_bin)->Clone();

	//--------------------------------------------------//
	
	TString fileName2 = "~/MC15bd0z0_variations_reference.root";
	TFile *file2 = TFile::Open(fileName2);

	// variation central value
	TH2F *h_sf_var_B1D1M1 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_mll80100");
	TH2F *h_sf_var_B1D1M2 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_mll75105");
	TH2F *h_sf_var_B1D1M3 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_mll70110");

	TH2F *h_sf_var_B1D2M1 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_var_B1D2M2 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_var_B1D2M3 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll70110");

	TH2F *h_sf_var_B1D3M1 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_var_B1D3M2 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_var_B1D3M3 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll70110");

	TH2F *h_sf_var_B2D1M1 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_mll80100");
	TH2F *h_sf_var_B2D1M2 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_mll75105");
	TH2F *h_sf_var_B2D1M3 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_mll70110");

	TH2F *h_sf_var_B2D2M1 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_var_B2D2M2 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_var_B2D2M3 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll70110");

	TH2F *h_sf_var_B2D3M1 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_var_B2D3M2 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_var_B2D3M3 = (TH2F*)file2->Get("SF_CentralValue_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll70110");

	//double pt_low = h_sf_var_B1D1M1->GetXaxis()->GetBinLowEdge(pt_bin+1) / 1000.;
	//double pt_up  = h_sf_var_B1D1M1->GetXaxis()->GetBinUpEdge(pt_bin+1) / 1000.;
	//cout << "pt_low=" << pt_low << ", pt_up=" << pt_up << endl;

	// variations:
	// B1=TemplRun2Variation1AndPassTrackQuality, B2=TemplRun2Variation2AndPassTrackQuality
	// D1=TagTightLLHMC15_v8, D2=TagTightLLHMC15_v8_Iso, D3=TagMediumLLHMC15_v8_Iso
	// M1=mll80100, M2=mll75105, M3=mll70110

	TH1F *h_sf_var_B1D1M1_project_on_eta = (TH1F*)h_sf_var_B1D1M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B1D1M2_project_on_eta = (TH1F*)h_sf_var_B1D1M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B1D1M3_project_on_eta = (TH1F*)h_sf_var_B1D1M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_var_B1D2M1_project_on_eta = (TH1F*)h_sf_var_B1D2M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B1D2M2_project_on_eta = (TH1F*)h_sf_var_B1D2M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B1D2M3_project_on_eta = (TH1F*)h_sf_var_B1D2M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_var_B1D3M1_project_on_eta = (TH1F*)h_sf_var_B1D3M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B1D3M2_project_on_eta = (TH1F*)h_sf_var_B1D3M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B1D3M3_project_on_eta = (TH1F*)h_sf_var_B1D3M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_var_B2D1M1_project_on_eta = (TH1F*)h_sf_var_B2D1M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B2D1M2_project_on_eta = (TH1F*)h_sf_var_B2D1M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B2D1M3_project_on_eta = (TH1F*)h_sf_var_B2D1M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_var_B2D2M1_project_on_eta = (TH1F*)h_sf_var_B2D2M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B2D2M2_project_on_eta = (TH1F*)h_sf_var_B2D2M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B2D2M3_project_on_eta = (TH1F*)h_sf_var_B2D2M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_var_B2D3M1_project_on_eta = (TH1F*)h_sf_var_B2D3M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B2D3M2_project_on_eta = (TH1F*)h_sf_var_B2D3M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_var_B2D3M3_project_on_eta = (TH1F*)h_sf_var_B2D3M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	// variation stat error
	TH2F *h_sf_stat_B1D1M1 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_mll80100");
	TH2F *h_sf_stat_B1D1M2 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_mll75105");
	TH2F *h_sf_stat_B1D1M3 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_mll70110");

	TH2F *h_sf_stat_B1D2M1 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_stat_B1D2M2 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_stat_B1D2M3 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll70110");

	TH2F *h_sf_stat_B1D3M1 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_stat_B1D3M2 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_stat_B1D3M3 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll70110");

	TH2F *h_sf_stat_B2D1M1 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_mll80100");
	TH2F *h_sf_stat_B2D1M2 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_mll75105");
	TH2F *h_sf_stat_B2D1M3 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_mll70110");

	TH2F *h_sf_stat_B2D2M1 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_stat_B2D2M2 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_stat_B2D2M3 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLHMC15_v8_Iso_mll70110");

	TH2F *h_sf_stat_B2D3M1 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll80100");
	TH2F *h_sf_stat_B2D3M2 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll75105");
	TH2F *h_sf_stat_B2D3M3 = (TH2F*)file2->Get("SF_StatError_" + menu + "_" + iso + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLHMC15_v8_Iso_mll70110");

	TH1F *h_sf_stat_B1D1M1_project_on_eta = (TH1F*)h_sf_stat_B1D1M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B1D1M2_project_on_eta = (TH1F*)h_sf_stat_B1D1M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B1D1M3_project_on_eta = (TH1F*)h_sf_stat_B1D1M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_stat_B1D2M1_project_on_eta = (TH1F*)h_sf_stat_B1D2M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B1D2M2_project_on_eta = (TH1F*)h_sf_stat_B1D2M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B1D2M3_project_on_eta = (TH1F*)h_sf_stat_B1D2M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_stat_B1D3M1_project_on_eta = (TH1F*)h_sf_stat_B1D3M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B1D3M2_project_on_eta = (TH1F*)h_sf_stat_B1D3M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B1D3M3_project_on_eta = (TH1F*)h_sf_stat_B1D3M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_stat_B2D1M1_project_on_eta = (TH1F*)h_sf_stat_B2D1M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B2D1M2_project_on_eta = (TH1F*)h_sf_stat_B2D1M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B2D1M3_project_on_eta = (TH1F*)h_sf_stat_B2D1M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_stat_B2D2M1_project_on_eta = (TH1F*)h_sf_stat_B2D2M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B2D2M2_project_on_eta = (TH1F*)h_sf_stat_B2D2M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B2D2M3_project_on_eta = (TH1F*)h_sf_stat_B2D2M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	TH1F *h_sf_stat_B2D3M1_project_on_eta = (TH1F*)h_sf_stat_B2D3M1->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B2D3M2_project_on_eta = (TH1F*)h_sf_stat_B2D3M2->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_stat_B2D3M3_project_on_eta = (TH1F*)h_sf_stat_B2D3M3->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();

	// fix the error
	fixHistogramError(h_sf_var_B1D1M1_project_on_eta, h_sf_stat_B1D1M1_project_on_eta);
	fixHistogramError(h_sf_var_B1D1M2_project_on_eta, h_sf_stat_B1D1M2_project_on_eta);
	fixHistogramError(h_sf_var_B1D1M3_project_on_eta, h_sf_stat_B1D1M3_project_on_eta);

	fixHistogramError(h_sf_var_B1D2M1_project_on_eta, h_sf_stat_B1D2M1_project_on_eta);
	fixHistogramError(h_sf_var_B1D2M2_project_on_eta, h_sf_stat_B1D2M2_project_on_eta);
	fixHistogramError(h_sf_var_B1D2M3_project_on_eta, h_sf_stat_B1D2M3_project_on_eta);

	fixHistogramError(h_sf_var_B1D3M1_project_on_eta, h_sf_stat_B1D3M1_project_on_eta);
	fixHistogramError(h_sf_var_B1D3M2_project_on_eta, h_sf_stat_B1D3M2_project_on_eta);
	fixHistogramError(h_sf_var_B1D3M3_project_on_eta, h_sf_stat_B1D3M3_project_on_eta);

	fixHistogramError(h_sf_var_B2D1M1_project_on_eta, h_sf_stat_B2D1M1_project_on_eta);
	fixHistogramError(h_sf_var_B2D1M2_project_on_eta, h_sf_stat_B2D1M2_project_on_eta);
	fixHistogramError(h_sf_var_B2D1M3_project_on_eta, h_sf_stat_B2D1M3_project_on_eta);

	fixHistogramError(h_sf_var_B2D2M1_project_on_eta, h_sf_stat_B2D2M1_project_on_eta);
	fixHistogramError(h_sf_var_B2D2M2_project_on_eta, h_sf_stat_B2D2M2_project_on_eta);
	fixHistogramError(h_sf_var_B2D2M3_project_on_eta, h_sf_stat_B2D2M3_project_on_eta);

	fixHistogramError(h_sf_var_B2D3M1_project_on_eta, h_sf_stat_B2D3M1_project_on_eta);
	fixHistogramError(h_sf_var_B2D3M2_project_on_eta, h_sf_stat_B2D3M2_project_on_eta);
	fixHistogramError(h_sf_var_B2D3M3_project_on_eta, h_sf_stat_B2D3M3_project_on_eta);

	// make plot
	// variate mll
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D1M1_project_on_eta, h_sf_var_B1D1M2_project_on_eta, h_sf_var_B1D1M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D2M1_project_on_eta, h_sf_var_B1D2M2_project_on_eta, h_sf_var_B1D2M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D3M1_project_on_eta, h_sf_var_B1D3M2_project_on_eta, h_sf_var_B1D3M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B2D1M1_project_on_eta, h_sf_var_B2D1M2_project_on_eta, h_sf_var_B2D1M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B2D2M1_project_on_eta, h_sf_var_B2D2M2_project_on_eta, h_sf_var_B2D2M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B2D3M1_project_on_eta, h_sf_var_B2D3M2_project_on_eta, h_sf_var_B2D3M3_project_on_eta);

	// variate denominator
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D1M1_project_on_eta, h_sf_var_B1D2M1_project_on_eta, h_sf_var_B1D3M1_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D1M2_project_on_eta, h_sf_var_B1D2M2_project_on_eta, h_sf_var_B1D3M2_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D1M3_project_on_eta, h_sf_var_B1D2M3_project_on_eta, h_sf_var_B1D3M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B2D1M1_project_on_eta, h_sf_var_B2D2M1_project_on_eta, h_sf_var_B2D3M1_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B2D1M2_project_on_eta, h_sf_var_B2D2M2_project_on_eta, h_sf_var_B2D3M2_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B2D1M3_project_on_eta, h_sf_var_B2D2M3_project_on_eta, h_sf_var_B2D3M3_project_on_eta);

	// variate background template
	compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D1M1_project_on_eta, h_sf_var_B2D1M1_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D1M2_project_on_eta, h_sf_var_B2D1M2_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D1M3_project_on_eta, h_sf_var_B2D1M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D2M1_project_on_eta, h_sf_var_B2D2M1_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D2M2_project_on_eta, h_sf_var_B2D2M2_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D2M3_project_on_eta, h_sf_var_B2D2M3_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D3M1_project_on_eta, h_sf_var_B2D3M1_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D3M2_project_on_eta, h_sf_var_B2D3M2_project_on_eta);
	//compareSFVariations(h_FullSim_sf_project_on_eta, h_sf_var_B1D3M3_project_on_eta, h_sf_var_B2D3M3_project_on_eta);
}

void compareSFVariations(TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h4 = NULL)
{
	TCanvas *c1 = new TCanvas("c1", "Variate M_{ll}", 600, 600);
	gStyle->SetOptStat(0);

	//Upper plot will be in pad1
	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
	pad1->SetBottomMargin(0); // Upper and lower plot are joined
	//pad1->SetGridy(); // grid lines
	pad1->Draw();

	// lower plot will be in pad
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.3);
	pad2->SetGridy(); // grid lines
	pad2->Draw();

	pad1->cd(); // pad1 becomes the current pad
	//pad1->SetFrameLineWidth(2);

	// Draw curve here

	//h1->SetTitle("Scale Factors project on #eta axis");
	h1->SetTitle("");
	h1->SetXTitle("#eta");
	h1->SetYTitle("Scale Factor");
    h1->GetYaxis()->SetTitleSize(14);
    h1->GetYaxis()->SetTitleFont(43);
    h1->GetYaxis()->SetTitleOffset(2.0);
	h1->SetMaximum(1.03);
	h1->SetMinimum(0.981);

	h1->SetLineColor(kBlue);
	h1->SetMarkerSize(1);
	h1->SetMarkerStyle(kFullCircle);
	h1->SetMarkerColor(kBlue);
	h1->Draw("E1");

	h2->SetLineColor(kRed);
	h2->SetMarkerSize(1);
	h2->SetMarkerStyle(kFullTriangleUp);
	h2->SetMarkerColor(kRed);
	h2->Draw("E1,SAME");

	h3->SetLineColor(kGreen+2);
	h3->SetMarkerSize(1);
	h3->SetMarkerStyle(kFullTriangleDown);
	h3->SetMarkerColor(kGreen+2);
	h3->Draw("E1,SAME");

	if (h4 != NULL) {
		h4->SetLineColor(kViolet);
		h4->SetMarkerSize(1);
		h4->SetMarkerStyle(kFullDiamond);
		h4->SetMarkerColor(kViolet);
		h4->Draw("E1,SAME");
	}

	TLine *line = new TLine(h1->GetXaxis()->GetXmin(), 1., h1->GetXaxis()->GetXmax(), 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");

	TLegend *legend = new TLegend(0.2, 0.7, 0.8, 0.9);
	legend->SetNColumns(2);
	legend->AddEntry(h1, "SF (Nominal)", "lp");
	//legend->AddEntry(h2, "SF (80 GeV < m_{ll} < 100 GeV)", "lp");
	//legend->AddEntry(h3, "SF (75 GeV < m_{ll} < 105 GeV)", "lp");
	//legend->AddEntry(h4, "SF (70 GeV < m_{ll} < 110 GeV)", "lp");
	//legend->AddEntry(h2, "SF (TagTightLLHMC15_v8)", "lp");
	//legend->AddEntry(h3, "SF (TagTightLLHMC15_v8_Iso)", "lp");
	//legend->AddEntry(h4, "SF (TagMediumLLHMC15_v8_Iso)", "lp");
	legend->AddEntry(h2, "SF (template 1)", "lp");
	legend->AddEntry(h3, "SF (template 2)", "lp");
	legend->SetBorderSize(0);
	legend->SetTextFont(42);
	//legend->SetTextSize(0.05);
	legend->SetFillColor(0);
	legend->SetFillStyle(0);
	legend->Draw();

	pad2->cd(); // pad2 becomes the current pad

	TString pad2_X_title = "#eta";
	TString pad2_Y_title = "Variation/Nominal";
	float pad2_X_min = h1->GetXaxis()->GetXmin();
	float pad2_X_max = h1->GetXaxis()->GetXmax();
	float pad2_Y_min = 0.98;
	float pad2_Y_max = 1.019;

	TH1F *frame = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
	frame->GetXaxis()->SetNdivisions(510);
	frame->GetYaxis()->SetNdivisions(405);
	frame->SetLineWidth(1);
	frame->SetXTitle(pad2_X_title);
	frame->GetXaxis()->SetTitleSize(20);
	frame->GetXaxis()->SetTitleFont(47);
	frame->GetXaxis()->SetTitleOffset(3.0);
	frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame->GetXaxis()->SetLabelSize(16);
	frame->SetYTitle(pad2_Y_title);
	frame->GetYaxis()->SetTitleSize(14);
	frame->GetYaxis()->SetTitleFont(43);
	frame->GetYaxis()->SetTitleOffset(2.0);
	frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame->GetYaxis()->SetLabelSize(14);
	frame->Draw();

	TH1F *ratio2 = (TH1F*)h2->Clone();
	ratio2->Divide(h1);
	ratio2->SetLineColor(kRed);
	ratio2->SetLineWidth(1);
	ratio2->SetMarkerColor(kRed);
	ratio2->SetMarkerSize(1);
	ratio2->SetMarkerStyle(kFullTriangleUp);
	ratio2->Draw("E1,SAME");

	TH1F *ratio3 = (TH1F*)h3->Clone();
	ratio3->Divide(h1);
	ratio3->SetLineColor(kGreen+2);
	ratio3->SetLineWidth(1);
	ratio3->SetMarkerColor(kGreen+2);
	ratio3->SetMarkerSize(1);
	ratio3->SetMarkerStyle(kFullTriangleDown);
	ratio3->Draw("E1,SAME");

	if (h4 != NULL) {
		TH1F *ratio4 = (TH1F*)h4->Clone();
		ratio4->Divide(h1);
		ratio4->SetLineColor(kViolet);
		ratio4->SetLineWidth(1);
		ratio4->SetMarkerColor(kViolet);
		ratio4->SetMarkerSize(1);
		ratio4->SetMarkerStyle(kFullDiamond);
		ratio4->Draw("E1,SAME");
	}
}
