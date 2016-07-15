#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
/*
#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"
*/
#include <iostream>
using namespace std;

// Correct the error of histogram
void fixHistogramError(TH1F *h1, TH1F *herr)
{
    for (Int_t ik = 1; ik <= h1->GetXaxis()->GetNbins(); ik++) {
        float err = herr->GetBinContent(ik);
        h1->SetBinError(ik, err);
    }
}

// Average of the histogram
void average(TH2F *h2)
{
    for (int i = 0; i <= h2->GetXaxis()->GetNbins(); i++) {
        for (int j = 0; j <= h2->GetYaxis()->GetNbins(); j++) {
            float value = h2->GetBinContent(i, j);
            h2->SetBinContent(i, j, value / 6.0);
        }
    }
}

void variation(TString menu = "LooseAndBLayer", TString isol = "isolLoose")
{
    gStyle->SetOptStat(0);
    
    bool debug = true;
    
    TFile *AF2mc = TFile::Open("variations_reference.root");
    TFile *FSmc  = TFile::Open("ScaleFactors.root");
    
    // central value
    //TString vary_mll = menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_";
    TH2F *hAF2_mll80100 = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_" + "mll80100");
    TH2F *hAF2_mll75105 = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_" + "mll75105");
    TH2F *hAF2_mll70110 = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_" + "mll70110");
    
    //TString vary_Tag = menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_";
    TH2F *hAF2_TagTightLLH_v11      = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_mll80100");
    TH2F *hAF2_TagTightLLH_v11_Iso  = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_Iso_mll80100");
    TH2F *hAF2_TagMediumLLH_v11_Iso = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLH_v11_Iso_mll80100");
    
    //TString vary_template = menu + "LLH_d0z0_Smooth_v11_" + isol;
    TH2F *hAF2_Variation1 = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_mll80100");
    TH2F *hAF2_Variation2 = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLH_v11_mll80100");
    
    TString folder = menu + "LLH_d0z0_Smooth_v11_" + isol;
    TH2F *hFSmc_EffMC = (TH2F *)FSmc->Get(folder + "/EffMC_CentralValue_" + folder);
    TH2F *hFSmc_EffMC_StatError = (TH2F *)FSmc->Get(folder + "/EffMC_StatError_" + folder);

    if (debug) {
        cout << hAF2_mll80100 << endl;
        cout << hAF2_mll75105 << endl;
        cout << hAF2_mll70110 << endl;
        cout << hAF2_TagTightLLH_v11 << endl;
        cout << hAF2_TagTightLLH_v11_Iso << endl;
        cout << hAF2_TagMediumLLH_v11_Iso << endl;
        cout << hAF2_Variation1 << endl;
        cout << hAF2_Variation2 << endl;
        cout << hFSmc_EffMC << endl;
    }
    
    // stat error
    // mll80100
    TH2F *hAF2_mll80100_StatError_Tag1_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_mll80100");
    TH2F *hAF2_mll80100_StatError_Tag2_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_Iso_mll80100");
    TH2F *hAF2_mll80100_StatError_Tag3_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLH_v11_Iso_mll80100");
    TH2F *hAF2_mll80100_StatError_Tag1_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLH_v11_mll80100");
    TH2F *hAF2_mll80100_StatError_Tag2_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLH_v11_Iso_mll80100");
    TH2F *hAF2_mll80100_StatError_Tag3_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLH_v11_Iso_mll80100");
    hAF2_mll80100_StatError_Tag1_Templ1->Sumw2();
    hAF2_mll80100_StatError_Tag2_Templ1->Sumw2();
    hAF2_mll80100_StatError_Tag3_Templ1->Sumw2();
    hAF2_mll80100_StatError_Tag1_Templ2->Sumw2();
    hAF2_mll80100_StatError_Tag2_Templ2->Sumw2();
    hAF2_mll80100_StatError_Tag3_Templ2->Sumw2();
    // mll75105
    TH2F *hAF2_mll75105_StatError_Tag1_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_mll75105");
    TH2F *hAF2_mll75105_StatError_Tag2_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_Iso_mll75105");
    TH2F *hAF2_mll75105_StatError_Tag3_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLH_v11_Iso_mll75105");
    TH2F *hAF2_mll75105_StatError_Tag1_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLH_v11_mll75105");
    TH2F *hAF2_mll75105_StatError_Tag2_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLH_v11_Iso_mll75105");
    TH2F *hAF2_mll75105_StatError_Tag3_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLH_v11_Iso_mll75105");
    hAF2_mll75105_StatError_Tag1_Templ1->Sumw2();
    hAF2_mll75105_StatError_Tag2_Templ1->Sumw2();
    hAF2_mll75105_StatError_Tag3_Templ1->Sumw2();
    hAF2_mll75105_StatError_Tag1_Templ2->Sumw2();
    hAF2_mll75105_StatError_Tag2_Templ2->Sumw2();
    hAF2_mll75105_StatError_Tag3_Templ2->Sumw2();
    // mll70110
    TH2F *hAF2_mll70110_StatError_Tag1_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_mll70110");
    TH2F *hAF2_mll70110_StatError_Tag2_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_Iso_mll70110");
    TH2F *hAF2_mll70110_StatError_Tag3_Templ1 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagMediumLLH_v11_Iso_mll70110");
    TH2F *hAF2_mll70110_StatError_Tag1_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLH_v11_mll70110");
    TH2F *hAF2_mll70110_StatError_Tag2_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagTightLLH_v11_Iso_mll70110");
    TH2F *hAF2_mll70110_StatError_Tag3_Templ2 = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation2AndPassTrackQuality_TagMediumLLH_v11_Iso_mll70110");
    hAF2_mll70110_StatError_Tag1_Templ1->Sumw2();
    hAF2_mll70110_StatError_Tag2_Templ1->Sumw2();
    hAF2_mll70110_StatError_Tag3_Templ1->Sumw2();
    hAF2_mll70110_StatError_Tag1_Templ2->Sumw2();
    hAF2_mll70110_StatError_Tag2_Templ2->Sumw2();
    hAF2_mll70110_StatError_Tag3_Templ2->Sumw2();

    TH2F *hAF2_mll80100_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ1->Clone();
    TH2F *hAF2_mll75105_StatError = (TH2F *)hAF2_mll75105_StatError_Tag1_Templ1->Clone();
    TH2F *hAF2_mll70110_StatError = (TH2F *)hAF2_mll70110_StatError_Tag1_Templ1->Clone();
    TH2F *hAF2_TagTightLLH_v11_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ1->Clone();
    TH2F *hAF2_TagTightLLH_v11_Iso_StatError = (TH2F *)hAF2_mll80100_StatError_Tag2_Templ1->Clone();
    TH2F *hAF2_TagMediumLLH_v11_Iso_StatError = (TH2F *)hAF2_mll80100_StatError_Tag3_Templ1->Clone();
    TH2F *hAF2_Variation1_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ1->Clone();
    TH2F *hAF2_Variation2_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ2->Clone();
/*
    TH2F *hAF2_mll80100_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ1->Clone();
    hAF2_mll80100_StatError->Add(hAF2_mll80100_StatError_Tag2_Templ1);
    hAF2_mll80100_StatError->Add(hAF2_mll80100_StatError_Tag3_Templ1);
    hAF2_mll80100_StatError->Add(hAF2_mll80100_StatError_Tag1_Templ2);
    hAF2_mll80100_StatError->Add(hAF2_mll80100_StatError_Tag2_Templ2);
    hAF2_mll80100_StatError->Add(hAF2_mll80100_StatError_Tag3_Templ2);
    average(hAF2_mll80100_StatError);

    TH2F *hAF2_mll75105_StatError = (TH2F *)hAF2_mll75105_StatError_Tag1_Templ1->Clone();
    hAF2_mll75105_StatError->Add(hAF2_mll75105_StatError_Tag2_Templ1);
    hAF2_mll75105_StatError->Add(hAF2_mll75105_StatError_Tag3_Templ1);
    hAF2_mll75105_StatError->Add(hAF2_mll75105_StatError_Tag1_Templ2);
    hAF2_mll75105_StatError->Add(hAF2_mll75105_StatError_Tag2_Templ2);
    hAF2_mll75105_StatError->Add(hAF2_mll75105_StatError_Tag3_Templ2);
    average(hAF2_mll75105_StatError);
    
    TH2F *hAF2_mll70110_StatError = (TH2F *)hAF2_mll70110_StatError_Tag1_Templ1->Clone();
    hAF2_mll70110_StatError->Add(hAF2_mll70110_StatError_Tag2_Templ1);
    hAF2_mll70110_StatError->Add(hAF2_mll70110_StatError_Tag3_Templ1);
    hAF2_mll70110_StatError->Add(hAF2_mll70110_StatError_Tag1_Templ2);
    hAF2_mll70110_StatError->Add(hAF2_mll70110_StatError_Tag2_Templ2);
    hAF2_mll70110_StatError->Add(hAF2_mll70110_StatError_Tag3_Templ2);
    average(hAF2_mll70110_StatError);

    // fix Tag
    TH2F *hAF2_TagTightLLH_v11_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ1->Clone();
    hAF2_TagTightLLH_v11_StatError->Add(hAF2_mll75105_StatError_Tag1_Templ1);
    hAF2_TagTightLLH_v11_StatError->Add(hAF2_mll70110_StatError_Tag1_Templ1);
    hAF2_TagTightLLH_v11_StatError->Add(hAF2_mll80100_StatError_Tag1_Templ2);
    hAF2_TagTightLLH_v11_StatError->Add(hAF2_mll75105_StatError_Tag1_Templ2);
    hAF2_TagTightLLH_v11_StatError->Add(hAF2_mll70110_StatError_Tag1_Templ2);
    average(hAF2_TagTightLLH_v11_StatError);
    
    TH2F *hAF2_TagTightLLH_v11_Iso_StatError = (TH2F *)hAF2_mll80100_StatError_Tag2_Templ1->Clone();
    hAF2_TagTightLLH_v11_Iso_StatError->Add(hAF2_mll75105_StatError_Tag2_Templ1);
    hAF2_TagTightLLH_v11_Iso_StatError->Add(hAF2_mll70110_StatError_Tag2_Templ1);
    hAF2_TagTightLLH_v11_Iso_StatError->Add(hAF2_mll80100_StatError_Tag2_Templ2);
    hAF2_TagTightLLH_v11_Iso_StatError->Add(hAF2_mll75105_StatError_Tag2_Templ2);
    hAF2_TagTightLLH_v11_Iso_StatError->Add(hAF2_mll70110_StatError_Tag2_Templ2);
    average(hAF2_TagTightLLH_v11_Iso_StatError);
    
    TH2F *hAF2_TagMediumLLH_v11_Iso_StatError = (TH2F *)hAF2_mll80100_StatError_Tag3_Templ1->Clone();
    hAF2_TagMediumLLH_v11_Iso_StatError->Add(hAF2_mll75105_StatError_Tag3_Templ1);
    hAF2_TagMediumLLH_v11_Iso_StatError->Add(hAF2_mll70110_StatError_Tag3_Templ1);
    hAF2_TagMediumLLH_v11_Iso_StatError->Add(hAF2_mll80100_StatError_Tag3_Templ2);
    hAF2_TagMediumLLH_v11_Iso_StatError->Add(hAF2_mll75105_StatError_Tag3_Templ2);
    hAF2_TagMediumLLH_v11_Iso_StatError->Add(hAF2_mll70110_StatError_Tag3_Templ2);
    average(hAF2_TagMediumLLH_v11_Iso_StatError);
    
    // fix template
    TH2F *hAF2_Variation1_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ1->Clone();
    hAF2_Variation1_StatError->Add(hAF2_mll80100_StatError_Tag2_Templ1);
    hAF2_Variation1_StatError->Add(hAF2_mll80100_StatError_Tag3_Templ1);
    hAF2_Variation1_StatError->Add(hAF2_mll75105_StatError_Tag1_Templ1);
    hAF2_Variation1_StatError->Add(hAF2_mll75105_StatError_Tag2_Templ1);
    hAF2_Variation1_StatError->Add(hAF2_mll75105_StatError_Tag3_Templ1);
    hAF2_Variation1_StatError->Add(hAF2_mll70110_StatError_Tag1_Templ1);
    hAF2_Variation1_StatError->Add(hAF2_mll70110_StatError_Tag2_Templ1);
    hAF2_Variation1_StatError->Add(hAF2_mll70110_StatError_Tag3_Templ1);
    average(hAF2_Variation1_StatError);
    
    TH2F *hAF2_Variation2_StatError = (TH2F *)hAF2_mll80100_StatError_Tag1_Templ2->Clone();
    hAF2_Variation2_StatError->Add(hAF2_mll80100_StatError_Tag2_Templ2);
    hAF2_Variation2_StatError->Add(hAF2_mll80100_StatError_Tag3_Templ2);
    hAF2_Variation2_StatError->Add(hAF2_mll75105_StatError_Tag1_Templ2);
    hAF2_Variation2_StatError->Add(hAF2_mll75105_StatError_Tag2_Templ2);
    hAF2_Variation2_StatError->Add(hAF2_mll75105_StatError_Tag3_Templ2);
    hAF2_Variation2_StatError->Add(hAF2_mll70110_StatError_Tag1_Templ2);
    hAF2_Variation2_StatError->Add(hAF2_mll70110_StatError_Tag2_Templ2);
    hAF2_Variation2_StatError->Add(hAF2_mll70110_StatError_Tag3_Templ2);
    average(hAF2_Variation2_StatError);
    
    if (debug) {
        cout << hAF2_mll80100_StatError_Tag1_Templ1 << endl;
        cout << hAF2_mll80100_StatError_Tag2_Templ2 << endl;
        cout << hAF2_mll80100_StatError_Tag3_Templ1 << endl;
        cout << hAF2_mll80100_StatError_Tag1_Templ2 << endl;
        cout << hAF2_mll80100_StatError_Tag2_Templ1 << endl;
        cout << hAF2_mll80100_StatError_Tag3_Templ2 << endl;
        
        cout << hAF2_mll75105_StatError_Tag1_Templ1 << endl;
        cout << hAF2_mll75105_StatError_Tag2_Templ2 << endl;
        cout << hAF2_mll75105_StatError_Tag3_Templ1 << endl;
        cout << hAF2_mll75105_StatError_Tag1_Templ2 << endl;
        cout << hAF2_mll75105_StatError_Tag2_Templ1 << endl;
        cout << hAF2_mll75105_StatError_Tag3_Templ2 << endl;
        
        cout << hAF2_mll70110_StatError_Tag1_Templ1 << endl;
        cout << hAF2_mll70110_StatError_Tag2_Templ2 << endl;
        cout << hAF2_mll70110_StatError_Tag3_Templ1 << endl;
        cout << hAF2_mll70110_StatError_Tag1_Templ2 << endl;
        cout << hAF2_mll70110_StatError_Tag2_Templ1 << endl;
        cout << hAF2_mll70110_StatError_Tag3_Templ2 << endl;
    }
*/
    //
    // vary Mll
    //

    // low pT: 7 GeV < pT < 10 GeV
    TH1F *hAF2_mll80100_low_pT = (TH1F *)hAF2_mll80100->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_mll75105_low_pT = (TH1F *)hAF2_mll75105->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_mll70110_low_pT = (TH1F *)hAF2_mll70110->ProjectionY("", 2, 2)->Clone();
    
    TH1F *hAF2_mll80100_low_pT_StatError = (TH1F *)hAF2_mll80100_StatError->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_mll75105_low_pT_StatError = (TH1F *)hAF2_mll75105_StatError->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_mll70110_low_pT_StatError = (TH1F *)hAF2_mll70110_StatError->ProjectionY("", 2, 2)->Clone();
    fixHistogramError(hAF2_mll80100_low_pT, hAF2_mll80100_low_pT_StatError);
    fixHistogramError(hAF2_mll75105_low_pT, hAF2_mll75105_low_pT_StatError);
    fixHistogramError(hAF2_mll70110_low_pT, hAF2_mll70110_low_pT_StatError);
    
    TH1F *hFSmc_EffMC_bin2      = (TH1F *)hFSmc_EffMC->ProjectionY("", 2, 2)->Clone();
    TH1F *hFSmc_EffMC_bin2_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 2, 2)->Clone();
    fixHistogramError(hFSmc_EffMC_bin2, hFSmc_EffMC_bin2_stat);

    int low_pT_low_edge = hAF2_mll80100->GetXaxis()->GetBinLowEdge(2) / 1000;
    int low_pT_up_edge  = hAF2_mll80100->GetXaxis()->GetBinUpEdge(2) / 1000;
    TString low_pT_range = TString::Format("%d", static_cast<int>(low_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(low_pT_up_edge)) + " GeV";
    
    // medium pT: 35 GeV < pT < 40 GeV
    TH1F *hAF2_mll80100_medium_pT = (TH1F *)hAF2_mll80100->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_mll75105_medium_pT = (TH1F *)hAF2_mll75105->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_mll70110_medium_pT = (TH1F *)hAF2_mll70110->ProjectionY("", 8, 8)->Clone();
    
    TH1F *hAF2_mll80100_medium_pT_StatError = (TH1F *)hAF2_mll80100_StatError->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_mll75105_medium_pT_StatError = (TH1F *)hAF2_mll75105_StatError->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_mll70110_medium_pT_StatError = (TH1F *)hAF2_mll70110_StatError->ProjectionY("", 8, 8)->Clone();
    fixHistogramError(hAF2_mll80100_medium_pT, hAF2_mll80100_medium_pT_StatError);
    fixHistogramError(hAF2_mll75105_medium_pT, hAF2_mll75105_medium_pT_StatError);
    fixHistogramError(hAF2_mll70110_medium_pT, hAF2_mll70110_medium_pT_StatError);
    
    TH1F *hFSmc_EffMC_bin8      = (TH1F *)hFSmc_EffMC->ProjectionY("", 8, 8)->Clone();
    TH1F *hFSmc_EffMC_bin8_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 8, 8)->Clone();
    fixHistogramError(hFSmc_EffMC_bin8, hFSmc_EffMC_bin8_stat);
    
    int medium_pT_low_edge = hAF2_mll80100->GetXaxis()->GetBinLowEdge(8) / 1000;
    int medium_pT_up_edge  = hAF2_mll80100->GetXaxis()->GetBinUpEdge(8) / 1000;
    TString medium_pT_range = TString::Format("%d", static_cast<int>(medium_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(medium_pT_up_edge)) + " GeV";
    
    // high pT: 60 GeV < pT < 80 GeV
    TH1F *hAF2_mll80100_high_pT = (TH1F *)hAF2_mll80100->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_mll75105_high_pT = (TH1F *)hAF2_mll75105->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_mll70110_high_pT = (TH1F *)hAF2_mll70110->ProjectionY("", 13, 13)->Clone();
    
    TH1F *hAF2_mll80100_high_pT_StatError = (TH1F *)hAF2_mll80100_StatError->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_mll75105_high_pT_StatError = (TH1F *)hAF2_mll75105_StatError->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_mll70110_high_pT_StatError = (TH1F *)hAF2_mll70110_StatError->ProjectionY("", 13, 13)->Clone();
    fixHistogramError(hAF2_mll80100_high_pT, hAF2_mll80100_high_pT_StatError);
    fixHistogramError(hAF2_mll75105_high_pT, hAF2_mll75105_high_pT_StatError);
    fixHistogramError(hAF2_mll70110_high_pT, hAF2_mll70110_high_pT_StatError);
    
    TH1F *hFSmc_EffMC_bin13      = (TH1F *)hFSmc_EffMC->ProjectionY("", 13, 13)->Clone();
    TH1F *hFSmc_EffMC_bin13_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 13, 13)->Clone();
    fixHistogramError(hFSmc_EffMC_bin13, hFSmc_EffMC_bin13_stat);
    
    int high_pT_low_edge = hAF2_mll80100->GetXaxis()->GetBinLowEdge(13) / 1000;
    int high_pT_up_edge  = hAF2_mll80100->GetXaxis()->GetBinUpEdge(13) / 1000;
    TString high_pT_range = TString::Format("%d", static_cast<int>(high_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(high_pT_up_edge)) + " GeV";
 
    TCanvas *c1 = new TCanvas("c1", "M_{ll} variations", 1200, 400);
    c1->Divide(3, 1);
    c1->cd(1);
    //Upper plot will be in pad1up
    TPad *pad1up = new TPad("pad1up", "pad1up", 0, 0.35, 1, 1.0);
    pad1up->SetBottomMargin(0); // Upper and lower plot are joined
    pad1up->Draw();
    // lower plot will be in pad1down
    TPad *pad1down = new TPad("pad1down", "pad1down", 0, 0.05, 1, 0.35);
    pad1down->SetTopMargin(0);
    pad1down->SetBottomMargin(0.3);
    pad1down->SetGridy(); // grid lines
    pad1down->Draw();
    //
    // pad1up: top pad
    //
    pad1up->cd(); // pad1up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin2->SetTitle(low_pT_range);
    hFSmc_EffMC_bin2->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin2->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin2->SetMaximum(1.05);
    hFSmc_EffMC_bin2->SetMinimum(0.95);
    hFSmc_EffMC_bin2->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin2->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin2->SetMarkerSize(0.7);
    hFSmc_EffMC_bin2->SetLineColor(kBlack);
    hFSmc_EffMC_bin2->Draw("E1");

    hAF2_mll80100_low_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_mll80100_low_pT->SetMarkerColor(kRed);
    hAF2_mll80100_low_pT->SetMarkerSize(0.7);
    hAF2_mll80100_low_pT->SetLineColor(kRed);
    hAF2_mll80100_low_pT->Draw("E1,same");
 
    hAF2_mll75105_low_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_mll75105_low_pT->SetMarkerColor(kBlue);
    hAF2_mll75105_low_pT->SetMarkerSize(0.7);
    hAF2_mll75105_low_pT->SetLineColor(kBlue);
    hAF2_mll75105_low_pT->Draw("E1,same");
    
    hAF2_mll70110_low_pT->SetMarkerStyle(kFullSquare);
    hAF2_mll70110_low_pT->SetMarkerColor(kMagenta);
    hAF2_mll70110_low_pT->SetMarkerSize(0.7);
    hAF2_mll70110_low_pT->SetLineColor(kMagenta);
    hAF2_mll70110_low_pT->Draw("E1,same");
 
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend1 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend1->SetBorderSize(0);
    legend1->SetFillColor(0);
    legend1->SetFillStyle(0);
    legend1->AddEntry(hFSmc_EffMC_bin2, "FullSim MC");
    legend1->AddEntry(hAF2_mll80100_low_pT, "AF2 80 GeV < M_{ll} < 100 GeV");
    legend1->AddEntry(hAF2_mll75105_low_pT, "AF2 75 GeV < M_{ll} < 105 GeV");
    legend1->AddEntry(hAF2_mll70110_low_pT, "AF2 70 GeV < M_{ll} < 110 GeV");
    legend1->Draw();
    
    //
    // pad1down: bottom pad
    //
    pad1down->cd(); // pad1down becomes the current pad
    
    TH1F *frame1 = pad1down->DrawFrame(hAF2_mll80100->GetYaxis()->GetXmin(), 0.95, hAF2_mll80100->GetYaxis()->GetXmax(), 1.049);
    frame1->GetXaxis()->SetNdivisions(510);
    frame1->GetYaxis()->SetNdivisions(405);
    frame1->SetLineWidth(1);
    frame1->SetXTitle("#eta");
    frame1->GetXaxis()->SetTitleSize(12);
    frame1->GetXaxis()->SetTitleFont(47);
    frame1->GetXaxis()->SetTitleOffset(3.5);
    frame1->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1->GetXaxis()->SetLabelSize(12);
    frame1->SetYTitle("AF2/FullSim");
    frame1->GetYaxis()->SetTitleSize(10);
    frame1->GetYaxis()->SetTitleFont(43);
    frame1->GetYaxis()->SetTitleOffset(1.5);
    frame1->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1->GetYaxis()->SetLabelSize(10);
    frame1->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin2->Sumw2();
    hAF2_mll80100_low_pT->Sumw2();
    hAF2_mll75105_low_pT->Sumw2();
    hAF2_mll70110_low_pT->Sumw2();
    TH1F *ratio1_low_pT = (TH1F *)hAF2_mll80100_low_pT->Clone();
    TH1F *ratio2_low_pT = (TH1F *)hAF2_mll75105_low_pT->Clone();
    TH1F *ratio3_low_pT = (TH1F *)hAF2_mll70110_low_pT->Clone();
    ratio1_low_pT->Divide(hFSmc_EffMC_bin2);
    ratio2_low_pT->Divide(hFSmc_EffMC_bin2);
    ratio3_low_pT->Divide(hFSmc_EffMC_bin2);
    
    ratio1_low_pT->SetLineColor(kRed);
    ratio1_low_pT->SetLineWidth(1);
    ratio1_low_pT->SetMarkerColor(kRed);
    ratio1_low_pT->SetMarkerSize(0.7);
    ratio1_low_pT->SetMarkerStyle(20);
    ratio1_low_pT->Draw("E1,same");
    
    ratio2_low_pT->SetLineColor(kBlue);
    ratio2_low_pT->SetLineWidth(1);
    ratio2_low_pT->SetMarkerColor(kBlue);
    ratio2_low_pT->SetMarkerSize(0.7);
    ratio2_low_pT->SetMarkerStyle(20);
    ratio2_low_pT->Draw("E1,same");
    
    ratio3_low_pT->SetLineColor(kMagenta);
    ratio3_low_pT->SetLineWidth(1);
    ratio3_low_pT->SetMarkerColor(kMagenta);
    ratio3_low_pT->SetMarkerSize(0.7);
    ratio3_low_pT->SetMarkerStyle(20);
    ratio3_low_pT->Draw("E1,same");

    c1->cd(2);
    //Upper plot will be in pad2up
    TPad *pad2up = new TPad("pad2up", "pad2up", 0, 0.35, 1, 1.0);
    pad2up->SetBottomMargin(0); // Upper and lower plot are joined
    pad2up->Draw();
    // lower plot will be in pad2down
    TPad *pad2down = new TPad("pad2down", "pad2down", 0, 0.05, 1, 0.35);
    pad2down->SetTopMargin(0);
    pad2down->SetBottomMargin(0.3);
    pad2down->SetGridy(); // grid lines
    pad2down->Draw();
    //
    // pad2up: top pad
    //
    pad2up->cd(); // pad2up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin8->SetTitle(medium_pT_range);
    hFSmc_EffMC_bin8->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin8->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin8->SetMaximum(1.05);
    hFSmc_EffMC_bin8->SetMinimum(0.95);
    hFSmc_EffMC_bin8->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin8->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin8->SetMarkerSize(0.7);
    hFSmc_EffMC_bin8->SetLineColor(kBlack);
    hFSmc_EffMC_bin8->Draw("E1");
    
    hAF2_mll80100_medium_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_mll80100_medium_pT->SetMarkerColor(kRed);
    hAF2_mll80100_medium_pT->SetMarkerSize(0.7);
    hAF2_mll80100_medium_pT->SetLineColor(kRed);
    hAF2_mll80100_medium_pT->Draw("E1,same");
    
    hAF2_mll75105_medium_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_mll75105_medium_pT->SetMarkerColor(kBlue);
    hAF2_mll75105_medium_pT->SetMarkerSize(0.7);
    hAF2_mll75105_medium_pT->SetLineColor(kBlue);
    hAF2_mll75105_medium_pT->Draw("E1,same");
    
    hAF2_mll70110_medium_pT->SetMarkerStyle(kFullSquare);
    hAF2_mll70110_medium_pT->SetMarkerColor(kMagenta);
    hAF2_mll70110_medium_pT->SetMarkerSize(0.7);
    hAF2_mll70110_medium_pT->SetLineColor(kMagenta);
    hAF2_mll70110_medium_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend2 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend2->SetBorderSize(0);
    legend2->SetFillColor(0);
    legend2->SetFillStyle(0);
    legend2->AddEntry(hFSmc_EffMC_bin8, "FullSim MC");
    legend2->AddEntry(hAF2_mll80100_medium_pT, "AF2 80 GeV < M_{ll} < 100 GeV");
    legend2->AddEntry(hAF2_mll75105_medium_pT, "AF2 75 GeV < M_{ll} < 105 GeV");
    legend2->AddEntry(hAF2_mll70110_medium_pT, "AF2 70 GeV < M_{ll} < 110 GeV");
    legend2->Draw();
    
    //
    // pad2down: bottom pad
    //
    pad2down->cd(); // pad2down becomes the current pad
    
    TH1F *frame2 = pad2down->DrawFrame(hAF2_mll80100->GetYaxis()->GetXmin(), 0.95, hAF2_mll80100->GetYaxis()->GetXmax(), 1.049);
    frame2->GetXaxis()->SetNdivisions(510);
    frame2->GetYaxis()->SetNdivisions(405);
    frame2->SetLineWidth(1);
    frame2->SetXTitle("#eta");
    frame2->GetXaxis()->SetTitleSize(12);
    frame2->GetXaxis()->SetTitleFont(47);
    frame2->GetXaxis()->SetTitleOffset(3.5);
    frame2->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2->GetXaxis()->SetLabelSize(12);
    frame2->SetYTitle("AF2/FullSim");
    frame2->GetYaxis()->SetTitleSize(10);
    frame2->GetYaxis()->SetTitleFont(43);
    frame2->GetYaxis()->SetTitleOffset(1.5);
    frame2->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2->GetYaxis()->SetLabelSize(10);
    frame2->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin8->Sumw2();
    hAF2_mll80100_medium_pT->Sumw2();
    hAF2_mll75105_medium_pT->Sumw2();
    hAF2_mll70110_medium_pT->Sumw2();
    TH1F *ratio1_medium_pT = (TH1F *)hAF2_mll80100_medium_pT->Clone();
    TH1F *ratio2_medium_pT = (TH1F *)hAF2_mll75105_medium_pT->Clone();
    TH1F *ratio3_medium_pT = (TH1F *)hAF2_mll70110_medium_pT->Clone();
    ratio1_medium_pT->Divide(hFSmc_EffMC_bin8);
    ratio2_medium_pT->Divide(hFSmc_EffMC_bin8);
    ratio3_medium_pT->Divide(hFSmc_EffMC_bin8);
    
    ratio1_medium_pT->SetLineColor(kRed);
    ratio1_medium_pT->SetLineWidth(1);
    ratio1_medium_pT->SetMarkerColor(kRed);
    ratio1_medium_pT->SetMarkerSize(0.7);
    ratio1_medium_pT->SetMarkerStyle(20);
    ratio1_medium_pT->Draw("E1,same");
    
    ratio2_medium_pT->SetLineColor(kBlue);
    ratio2_medium_pT->SetLineWidth(1);
    ratio2_medium_pT->SetMarkerColor(kBlue);
    ratio2_medium_pT->SetMarkerSize(0.7);
    ratio2_medium_pT->SetMarkerStyle(20);
    ratio2_medium_pT->Draw("E1,same");
    
    ratio3_medium_pT->SetLineColor(kMagenta);
    ratio3_medium_pT->SetLineWidth(1);
    ratio3_medium_pT->SetMarkerColor(kMagenta);
    ratio3_medium_pT->SetMarkerSize(0.7);
    ratio3_medium_pT->SetMarkerStyle(20);
    ratio3_medium_pT->Draw("E1,same");
    
    c1->cd(3);
    //Upper plot will be in pad3up
    TPad *pad3up = new TPad("pad3up", "pad3up", 0, 0.35, 1, 1.0);
    pad3up->SetBottomMargin(0); // Upper and lower plot are joined
    pad3up->Draw();
    // lower plot will be in pad3down
    TPad *pad3down = new TPad("pad3down", "pad3down", 0, 0.05, 1, 0.35);
    pad3down->SetTopMargin(0);
    pad3down->SetBottomMargin(0.3);
    pad3down->SetGridy(); // grid lines
    pad3down->Draw();
    //
    // pad3up: top pad
    //
    pad3up->cd(); // pad3up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin13->SetTitle(high_pT_range);
    hFSmc_EffMC_bin13->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin13->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin13->SetMaximum(1.1);
    hFSmc_EffMC_bin13->SetMinimum(0.9);
    hFSmc_EffMC_bin13->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin13->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin13->SetMarkerSize(0.7);
    hFSmc_EffMC_bin13->SetLineColor(kBlack);
    hFSmc_EffMC_bin13->Draw("E1");
    
    hAF2_mll80100_high_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_mll80100_high_pT->SetMarkerColor(kRed);
    hAF2_mll80100_high_pT->SetMarkerSize(0.7);
    hAF2_mll80100_high_pT->SetLineColor(kRed);
    hAF2_mll80100_high_pT->Draw("E1,same");
    
    hAF2_mll75105_high_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_mll75105_high_pT->SetMarkerColor(kBlue);
    hAF2_mll75105_high_pT->SetMarkerSize(0.7);
    hAF2_mll75105_high_pT->SetLineColor(kBlue);
    hAF2_mll75105_high_pT->Draw("E1,same");
    
    hAF2_mll70110_high_pT->SetMarkerStyle(kFullSquare);
    hAF2_mll70110_high_pT->SetMarkerColor(kMagenta);
    hAF2_mll70110_high_pT->SetMarkerSize(0.7);
    hAF2_mll70110_high_pT->SetLineColor(kMagenta);
    hAF2_mll70110_high_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend3 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend3->SetBorderSize(0);
    legend3->SetFillColor(0);
    legend3->SetFillStyle(0);
    legend3->AddEntry(hFSmc_EffMC_bin13, "FullSim MC");
    legend3->AddEntry(hAF2_mll80100_high_pT, "AF2 80 GeV < M_{ll} < 100 GeV");
    legend3->AddEntry(hAF2_mll75105_high_pT, "AF2 75 GeV < M_{ll} < 105 GeV");
    legend3->AddEntry(hAF2_mll70110_high_pT, "AF2 70 GeV < M_{ll} < 110 GeV");
    legend3->Draw();
    
    //
    // pad3down: bottom pad
    //
    pad3down->cd(); // pad3down becomes the current pad
    
    TH1F *frame3 = pad3down->DrawFrame(hAF2_mll80100->GetYaxis()->GetXmin(), 0.95, hAF2_mll80100->GetYaxis()->GetXmax(), 1.049);
    frame3->GetXaxis()->SetNdivisions(510);
    frame3->GetYaxis()->SetNdivisions(405);
    frame3->SetLineWidth(1);
    frame3->SetXTitle("#eta");
    frame3->GetXaxis()->SetTitleSize(12);
    frame3->GetXaxis()->SetTitleFont(47);
    frame3->GetXaxis()->SetTitleOffset(3.5);
    frame3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame3->GetXaxis()->SetLabelSize(12);
    frame3->SetYTitle("AF2/FullSim");
    frame3->GetYaxis()->SetTitleSize(10);
    frame3->GetYaxis()->SetTitleFont(43);
    frame3->GetYaxis()->SetTitleOffset(1.5);
    frame3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame3->GetYaxis()->SetLabelSize(10);
    frame3->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin13->Sumw2();
    hAF2_mll80100_high_pT->Sumw2();
    hAF2_mll75105_high_pT->Sumw2();
    hAF2_mll70110_high_pT->Sumw2();
    TH1F *ratio1_high_pT = (TH1F *)hAF2_mll80100_high_pT->Clone();
    TH1F *ratio2_high_pT = (TH1F *)hAF2_mll75105_high_pT->Clone();
    TH1F *ratio3_high_pT = (TH1F *)hAF2_mll70110_high_pT->Clone();
    ratio1_high_pT->Divide(hFSmc_EffMC_bin13);
    ratio2_high_pT->Divide(hFSmc_EffMC_bin13);
    ratio3_high_pT->Divide(hFSmc_EffMC_bin13);
    
    ratio1_high_pT->SetLineColor(kRed);
    ratio1_high_pT->SetLineWidth(1);
    ratio1_high_pT->SetMarkerColor(kRed);
    ratio1_high_pT->SetMarkerSize(0.7);
    ratio1_high_pT->SetMarkerStyle(20);
    ratio1_high_pT->Draw("E1,same");
    
    ratio2_high_pT->SetLineColor(kBlue);
    ratio2_high_pT->SetLineWidth(1);
    ratio2_high_pT->SetMarkerColor(kBlue);
    ratio2_high_pT->SetMarkerSize(0.7);
    ratio2_high_pT->SetMarkerStyle(20);
    ratio2_high_pT->Draw("E1,same");
    
    ratio3_high_pT->SetLineColor(kMagenta);
    ratio3_high_pT->SetLineWidth(1);
    ratio3_high_pT->SetMarkerColor(kMagenta);
    ratio3_high_pT->SetMarkerSize(0.7);
    ratio3_high_pT->SetMarkerStyle(20);
    ratio3_high_pT->Draw("E1,same");
    
    c1->Print("plots/variation_Mll.pdf");

    //
    // vary Tag
    //
    
    // low pT: 7 GeV < pT < 10 GeV
    TH1F *hAF2_TagTightLLH_v11_low_pT      = (TH1F *)hAF2_TagTightLLH_v11->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_TagTightLLH_v11_Iso_low_pT  = (TH1F *)hAF2_TagTightLLH_v11_Iso->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_TagMediumLLH_v11_Iso_low_pT = (TH1F *)hAF2_TagMediumLLH_v11_Iso->ProjectionY("", 2, 2)->Clone();
    
    TH1F *hAF2_TagTightLLH_v11_low_pT_StatError      = (TH1F *)hAF2_TagTightLLH_v11_StatError->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_TagTightLLH_v11_Iso_low_pT_StatError  = (TH1F *)hAF2_TagTightLLH_v11_Iso_StatError->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_TagMediumLLH_v11_Iso_low_pT_StatError = (TH1F *)hAF2_TagMediumLLH_v11_Iso_StatError->ProjectionY("", 2, 2)->Clone();
    fixHistogramError(hAF2_TagTightLLH_v11_low_pT, hAF2_TagTightLLH_v11_low_pT_StatError);
    fixHistogramError(hAF2_TagTightLLH_v11_Iso_low_pT, hAF2_TagTightLLH_v11_Iso_low_pT_StatError);
    fixHistogramError(hAF2_TagMediumLLH_v11_Iso_low_pT, hAF2_TagMediumLLH_v11_Iso_low_pT_StatError);
/* 
    TH1F *hFSmc_EffMC_bin2      = (TH1F *)hFSmc_EffMC->ProjectionY("", 2, 2)->Clone();
    TH1F *hFSmc_EffMC_bin2_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 2, 2)->Clone();
    fixHistogramError(hFSmc_EffMC_bin2, hFSmc_EffMC_bin2_stat);

    int low_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(2) / 1000;
    int low_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(2) / 1000;
    TString low_pT_range = TString::Format("%d", static_cast<int>(low_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(low_pT_up_edge)) + " GeV";
*/
    low_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(2) / 1000;
    low_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(2) / 1000;
    low_pT_range = TString::Format("%d", static_cast<int>(low_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(low_pT_up_edge)) + " GeV";
    
    // medium pT: 35 GeV < pT < 40 GeV
    TH1F *hAF2_TagTightLLH_v11_medium_pT      = (TH1F *)hAF2_TagTightLLH_v11->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_TagTightLLH_v11_Iso_medium_pT  = (TH1F *)hAF2_TagTightLLH_v11_Iso->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_TagMediumLLH_v11_Iso_medium_pT = (TH1F *)hAF2_TagMediumLLH_v11_Iso->ProjectionY("", 8, 8)->Clone();
    
    TH1F *hAF2_TagTightLLH_v11_medium_pT_StatError      = (TH1F *)hAF2_TagTightLLH_v11_StatError->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_TagTightLLH_v11_Iso_medium_pT_StatError  = (TH1F *)hAF2_TagTightLLH_v11_Iso_StatError->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_TagMediumLLH_v11_Iso_medium_pT_StatError = (TH1F *)hAF2_TagMediumLLH_v11_Iso_StatError->ProjectionY("", 8, 8)->Clone();
    fixHistogramError(hAF2_TagTightLLH_v11_medium_pT, hAF2_TagTightLLH_v11_medium_pT_StatError);
    fixHistogramError(hAF2_TagTightLLH_v11_Iso_medium_pT, hAF2_TagTightLLH_v11_Iso_medium_pT_StatError);
    fixHistogramError(hAF2_TagMediumLLH_v11_Iso_medium_pT, hAF2_TagMediumLLH_v11_Iso_medium_pT_StatError);
/*    
    TH1F *hFSmc_EffMC_bin8      = (TH1F *)hFSmc_EffMC->ProjectionY("", 8, 8)->Clone();
    TH1F *hFSmc_EffMC_bin8_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 8, 8)->Clone();
    fixHistogramError(hFSmc_EffMC_bin8, hFSmc_EffMC_bin8_stat);
    
    int medium_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(8) / 1000;
    int medium_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(8) / 1000;
    TString medium_pT_range = TString::Format("%d", static_cast<int>(medium_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(medium_pT_up_edge)) + " GeV";
*/
    medium_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(8) / 1000;
    medium_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(8) / 1000;
    medium_pT_range = TString::Format("%d", static_cast<int>(medium_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(medium_pT_up_edge)) + " GeV";
    
    // high pT: 60 GeV < pT < 80 GeV
    TH1F *hAF2_TagTightLLH_v11_high_pT      = (TH1F *)hAF2_TagTightLLH_v11->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_TagTightLLH_v11_Iso_high_pT  = (TH1F *)hAF2_TagTightLLH_v11_Iso->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_TagMediumLLH_v11_Iso_high_pT = (TH1F *)hAF2_TagMediumLLH_v11_Iso->ProjectionY("", 13, 13)->Clone();
    
    TH1F *hAF2_TagTightLLH_v11_high_pT_StatError      = (TH1F *)hAF2_TagTightLLH_v11_StatError->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_TagTightLLH_v11_Iso_high_pT_StatError  = (TH1F *)hAF2_TagTightLLH_v11_Iso_StatError->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_TagMediumLLH_v11_Iso_high_pT_StatError = (TH1F *)hAF2_TagMediumLLH_v11_Iso_StatError->ProjectionY("", 13, 13)->Clone();
    fixHistogramError(hAF2_TagTightLLH_v11_high_pT, hAF2_TagTightLLH_v11_high_pT_StatError);
    fixHistogramError(hAF2_TagTightLLH_v11_Iso_high_pT, hAF2_TagTightLLH_v11_Iso_high_pT_StatError);
    fixHistogramError(hAF2_TagMediumLLH_v11_Iso_high_pT, hAF2_TagMediumLLH_v11_Iso_high_pT_StatError);
/* 
    TH1F *hFSmc_EffMC_bin13      = (TH1F *)hFSmc_EffMC->ProjectionY("", 13, 13)->Clone();
    TH1F *hFSmc_EffMC_bin13_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 13, 13)->Clone();
    fixHistogramError(hFSmc_EffMC_bin13, hFSmc_EffMC_bin13_stat);
    
    int high_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(13) / 1000;
    int high_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(13) / 1000;
    TString high_pT_range = TString::Format("%d", static_cast<int>(high_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(high_pT_up_edge)) + " GeV";
*/
    high_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(13) / 1000;
    high_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(13) / 1000;
    high_pT_range = TString::Format("%d", static_cast<int>(high_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(high_pT_up_edge)) + " GeV";
    
    TCanvas *c2 = new TCanvas("c2", "Tag variations", 1200, 400);
    c2->Divide(3, 1);
    c2->cd(1);
    //Upper plot will be in pad4up
    TPad *pad4up = new TPad("pad4up", "pad4up", 0, 0.35, 1, 1.0);
    pad4up->SetBottomMargin(0); // Upper and lower plot are joined
    pad4up->Draw();
    // lower plot will be in pad4down
    TPad *pad4down = new TPad("pad4down", "pad4down", 0, 0.05, 1, 0.35);
    pad4down->SetTopMargin(0);
    pad4down->SetBottomMargin(0.3);
    pad4down->SetGridy(); // grid lines
    pad4down->Draw();
    //
    // pad1up: top pad
    //
    pad4up->cd(); // pad4up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin2->SetTitle(low_pT_range);
    hFSmc_EffMC_bin2->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin2->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin2->SetMaximum(1.05);
    hFSmc_EffMC_bin2->SetMinimum(0.95);
    hFSmc_EffMC_bin2->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin2->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin2->SetMarkerSize(0.7);
    hFSmc_EffMC_bin2->SetLineColor(kBlack);
    hFSmc_EffMC_bin2->Draw("E1");
    
    hAF2_TagTightLLH_v11_low_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_TagTightLLH_v11_low_pT->SetMarkerColor(kRed);
    hAF2_TagTightLLH_v11_low_pT->SetMarkerSize(0.7);
    hAF2_TagTightLLH_v11_low_pT->SetLineColor(kRed);
    hAF2_TagTightLLH_v11_low_pT->Draw("E1,same");
    
    hAF2_TagTightLLH_v11_Iso_low_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_TagTightLLH_v11_Iso_low_pT->SetMarkerColor(kBlue);
    hAF2_TagTightLLH_v11_Iso_low_pT->SetMarkerSize(0.7);
    hAF2_TagTightLLH_v11_Iso_low_pT->SetLineColor(kBlue);
    hAF2_TagTightLLH_v11_Iso_low_pT->Draw("E1,same");
    
    hAF2_TagMediumLLH_v11_Iso_low_pT->SetMarkerStyle(kFullSquare);
    hAF2_TagMediumLLH_v11_Iso_low_pT->SetMarkerColor(kMagenta);
    hAF2_TagMediumLLH_v11_Iso_low_pT->SetMarkerSize(0.7);
    hAF2_TagMediumLLH_v11_Iso_low_pT->SetLineColor(kMagenta);
    hAF2_TagMediumLLH_v11_Iso_low_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend4 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend4->SetBorderSize(0);
    legend4->SetFillColor(0);
    legend4->SetFillStyle(0);
    legend4->AddEntry(hFSmc_EffMC_bin2, "FullSim MC");
    legend4->AddEntry(hAF2_TagTightLLH_v11_low_pT, "AF2 TagTightLLH_v11");
    legend4->AddEntry(hAF2_TagTightLLH_v11_Iso_low_pT, "AF2 TagTightLLH_v11_Iso");
    legend4->AddEntry(hAF2_TagMediumLLH_v11_Iso_low_pT, "AF2 TagMediumLLH_v11_Iso");
    legend4->Draw();
    
    //
    // pad4down: bottom pad
    //
    pad4down->cd(); // pad4down becomes the current pad
    
    TH1F *frame4 = pad4down->DrawFrame(hAF2_TagTightLLH_v11->GetYaxis()->GetXmin(), 0.95, hAF2_TagTightLLH_v11->GetYaxis()->GetXmax(), 1.049);
    frame4->GetXaxis()->SetNdivisions(510);
    frame4->GetYaxis()->SetNdivisions(405);
    frame4->SetLineWidth(1);
    frame4->SetXTitle("#eta");
    frame4->GetXaxis()->SetTitleSize(12);
    frame4->GetXaxis()->SetTitleFont(47);
    frame4->GetXaxis()->SetTitleOffset(3.5);
    frame4->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame4->GetXaxis()->SetLabelSize(12);
    frame4->SetYTitle("AF2/FullSim");
    frame4->GetYaxis()->SetTitleSize(10);
    frame4->GetYaxis()->SetTitleFont(43);
    frame4->GetYaxis()->SetTitleOffset(1.5);
    frame4->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame4->GetYaxis()->SetLabelSize(10);
    frame4->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin2->Sumw2();
    hAF2_TagTightLLH_v11_low_pT->Sumw2();
    hAF2_TagTightLLH_v11_Iso_low_pT->Sumw2();
    hAF2_TagMediumLLH_v11_Iso_low_pT->Sumw2();
    TH1F *ratio4_low_pT = (TH1F *)hAF2_TagTightLLH_v11_low_pT->Clone();
    TH1F *ratio5_low_pT = (TH1F *)hAF2_TagTightLLH_v11_Iso_low_pT->Clone();
    TH1F *ratio6_low_pT = (TH1F *)hAF2_TagMediumLLH_v11_Iso_low_pT->Clone();
    ratio4_low_pT->Divide(hFSmc_EffMC_bin2);
    ratio5_low_pT->Divide(hFSmc_EffMC_bin2);
    ratio6_low_pT->Divide(hFSmc_EffMC_bin2);
    
    ratio4_low_pT->SetLineColor(kRed);
    ratio4_low_pT->SetLineWidth(1);
    ratio4_low_pT->SetMarkerColor(kRed);
    ratio4_low_pT->SetMarkerSize(0.7);
    ratio4_low_pT->SetMarkerStyle(20);
    ratio4_low_pT->Draw("E1,same");
    
    ratio5_low_pT->SetLineColor(kBlue);
    ratio5_low_pT->SetLineWidth(1);
    ratio5_low_pT->SetMarkerColor(kBlue);
    ratio5_low_pT->SetMarkerSize(0.7);
    ratio5_low_pT->SetMarkerStyle(20);
    ratio5_low_pT->Draw("E1,same");
    
    ratio6_low_pT->SetLineColor(kMagenta);
    ratio6_low_pT->SetLineWidth(1);
    ratio6_low_pT->SetMarkerColor(kMagenta);
    ratio6_low_pT->SetMarkerSize(0.7);
    ratio6_low_pT->SetMarkerStyle(20);
    ratio6_low_pT->Draw("E1,same");
    
    c2->cd(2);
    //Upper plot will be in pad5up
    TPad *pad5up = new TPad("pad5up", "pad5up", 0, 0.35, 1, 1.0);
    pad5up->SetBottomMargin(0); // Upper and lower plot are joined
    pad5up->Draw();
    // lower plot will be in pad5down
    TPad *pad5down = new TPad("pad5down", "pad5down", 0, 0.05, 1, 0.35);
    pad5down->SetTopMargin(0);
    pad5down->SetBottomMargin(0.3);
    pad5down->SetGridy(); // grid lines
    pad5down->Draw();
    //
    // pad5up: top pad
    //
    pad5up->cd(); // pad5up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin8->SetTitle(medium_pT_range);
    hFSmc_EffMC_bin8->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin8->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin8->SetMaximum(1.05);
    hFSmc_EffMC_bin8->SetMinimum(0.95);
    hFSmc_EffMC_bin8->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin8->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin8->SetMarkerSize(0.7);
    hFSmc_EffMC_bin8->SetLineColor(kBlack);
    hFSmc_EffMC_bin8->Draw("E1");
    
    hAF2_TagTightLLH_v11_medium_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_TagTightLLH_v11_medium_pT->SetMarkerColor(kRed);
    hAF2_TagTightLLH_v11_medium_pT->SetMarkerSize(0.7);
    hAF2_TagTightLLH_v11_medium_pT->SetLineColor(kRed);
    hAF2_TagTightLLH_v11_medium_pT->Draw("E1,same");
    
    hAF2_TagTightLLH_v11_Iso_medium_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_TagTightLLH_v11_Iso_medium_pT->SetMarkerColor(kBlue);
    hAF2_TagTightLLH_v11_Iso_medium_pT->SetMarkerSize(0.7);
    hAF2_TagTightLLH_v11_Iso_medium_pT->SetLineColor(kBlue);
    hAF2_TagTightLLH_v11_Iso_medium_pT->Draw("E1,same");
    
    hAF2_TagMediumLLH_v11_Iso_medium_pT->SetMarkerStyle(kFullSquare);
    hAF2_TagMediumLLH_v11_Iso_medium_pT->SetMarkerColor(kMagenta);
    hAF2_TagMediumLLH_v11_Iso_medium_pT->SetMarkerSize(0.7);
    hAF2_TagMediumLLH_v11_Iso_medium_pT->SetLineColor(kMagenta);
    hAF2_TagMediumLLH_v11_Iso_medium_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend5 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend5->SetBorderSize(0);
    legend5->SetFillColor(0);
    legend5->SetFillStyle(0);
    legend5->AddEntry(hFSmc_EffMC_bin8, "FullSim MC");
    legend5->AddEntry(hAF2_TagTightLLH_v11_medium_pT, "AF2 TagTightLLH_v11");
    legend5->AddEntry(hAF2_TagTightLLH_v11_Iso_medium_pT, "AF2 TagTightLLH_v11_Iso");
    legend5->AddEntry(hAF2_TagMediumLLH_v11_Iso_medium_pT, "AF2 TagMediumLLH_v11_Iso");
    legend5->Draw();
    
    //
    // pad5down: bottom pad
    //
    pad5down->cd(); // pad5down becomes the current pad
    
    TH1F *frame5 = pad5down->DrawFrame(hAF2_TagTightLLH_v11->GetYaxis()->GetXmin(), 0.95, hAF2_TagTightLLH_v11->GetYaxis()->GetXmax(), 1.049);
    frame5->GetXaxis()->SetNdivisions(510);
    frame5->GetYaxis()->SetNdivisions(405);
    frame5->SetLineWidth(1);
    frame5->SetXTitle("#eta");
    frame5->GetXaxis()->SetTitleSize(12);
    frame5->GetXaxis()->SetTitleFont(47);
    frame5->GetXaxis()->SetTitleOffset(3.5);
    frame5->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame5->GetXaxis()->SetLabelSize(12);
    frame5->SetYTitle("AF2/FullSim");
    frame5->GetYaxis()->SetTitleSize(10);
    frame5->GetYaxis()->SetTitleFont(43);
    frame5->GetYaxis()->SetTitleOffset(1.5);
    frame5->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame5->GetYaxis()->SetLabelSize(10);
    frame5->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin8->Sumw2();
    hAF2_TagTightLLH_v11_medium_pT->Sumw2();
    hAF2_TagTightLLH_v11_Iso_medium_pT->Sumw2();
    hAF2_TagMediumLLH_v11_Iso_medium_pT->Sumw2();
    TH1F *ratio4_medium_pT = (TH1F *)hAF2_TagTightLLH_v11_medium_pT->Clone();
    TH1F *ratio5_medium_pT = (TH1F *)hAF2_TagTightLLH_v11_Iso_medium_pT->Clone();
    TH1F *ratio6_medium_pT = (TH1F *)hAF2_TagMediumLLH_v11_Iso_medium_pT->Clone();
    ratio4_medium_pT->Divide(hFSmc_EffMC_bin8);
    ratio5_medium_pT->Divide(hFSmc_EffMC_bin8);
    ratio6_medium_pT->Divide(hFSmc_EffMC_bin8);
    
    ratio4_medium_pT->SetLineColor(kRed);
    ratio4_medium_pT->SetLineWidth(1);
    ratio4_medium_pT->SetMarkerColor(kRed);
    ratio4_medium_pT->SetMarkerSize(0.7);
    ratio4_medium_pT->SetMarkerStyle(20);
    ratio4_medium_pT->Draw("E1,same");
    
    ratio5_medium_pT->SetLineColor(kBlue);
    ratio5_medium_pT->SetLineWidth(1);
    ratio5_medium_pT->SetMarkerColor(kBlue);
    ratio5_medium_pT->SetMarkerSize(0.7);
    ratio5_medium_pT->SetMarkerStyle(20);
    ratio5_medium_pT->Draw("E1,same");
    
    ratio6_medium_pT->SetLineColor(kMagenta);
    ratio6_medium_pT->SetLineWidth(1);
    ratio6_medium_pT->SetMarkerColor(kMagenta);
    ratio6_medium_pT->SetMarkerSize(0.7);
    ratio6_medium_pT->SetMarkerStyle(20);
    ratio6_medium_pT->Draw("E1,same");
    
    c2->cd(3);
    //Upper plot will be in pad6up
    TPad *pad6up = new TPad("pad6up", "pad6up", 0, 0.35, 1, 1.0);
    pad6up->SetBottomMargin(0); // Upper and lower plot are joined
    pad6up->Draw();
    // lower plot will be in pad6down
    TPad *pad6down = new TPad("pad6down", "pad6down", 0, 0.05, 1, 0.35);
    pad6down->SetTopMargin(0);
    pad6down->SetBottomMargin(0.3);
    pad6down->SetGridy(); // grid lines
    pad6down->Draw();
    //
    // pad6up: top pad
    //
    pad6up->cd(); // pad1up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin13->SetTitle(high_pT_range);
    hFSmc_EffMC_bin13->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin13->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin13->SetMaximum(1.05);
    hFSmc_EffMC_bin13->SetMinimum(0.95);
    hFSmc_EffMC_bin13->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin13->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin13->SetMarkerSize(0.7);
    hFSmc_EffMC_bin13->SetLineColor(kBlack);
    hFSmc_EffMC_bin13->Draw("E1");
    
    hAF2_TagTightLLH_v11_high_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_TagTightLLH_v11_high_pT->SetMarkerColor(kRed);
    hAF2_TagTightLLH_v11_high_pT->SetMarkerSize(0.7);
    hAF2_TagTightLLH_v11_high_pT->SetLineColor(kRed);
    hAF2_TagTightLLH_v11_high_pT->Draw("E1,same");
    
    hAF2_TagTightLLH_v11_Iso_high_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_TagTightLLH_v11_Iso_high_pT->SetMarkerColor(kBlue);
    hAF2_TagTightLLH_v11_Iso_high_pT->SetMarkerSize(0.7);
    hAF2_TagTightLLH_v11_Iso_high_pT->SetLineColor(kBlue);
    hAF2_TagTightLLH_v11_Iso_high_pT->Draw("E1,same");
    
    hAF2_TagMediumLLH_v11_Iso_high_pT->SetMarkerStyle(kFullSquare);
    hAF2_TagMediumLLH_v11_Iso_high_pT->SetMarkerColor(kMagenta);
    hAF2_TagMediumLLH_v11_Iso_high_pT->SetMarkerSize(0.7);
    hAF2_TagMediumLLH_v11_Iso_high_pT->SetLineColor(kMagenta);
    hAF2_TagMediumLLH_v11_Iso_high_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend6 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend6->SetBorderSize(0);
    legend6->SetFillColor(0);
    legend6->SetFillStyle(0);
    legend6->AddEntry(hFSmc_EffMC_bin13, "FullSim MC");
    legend6->AddEntry(hAF2_TagTightLLH_v11_high_pT, "AF2 TagTightLLH_v11");
    legend6->AddEntry(hAF2_TagTightLLH_v11_Iso_high_pT, "AF2 TagTightLLH_v11_Iso");
    legend6->AddEntry(hAF2_TagMediumLLH_v11_Iso_high_pT, "AF2 TagMediumLLH_v11_Iso");
    legend6->Draw();
    
    //
    // pad6down: bottom pad
    //
    pad6down->cd(); // pad6down becomes the current pad
    
    TH1F *frame6 = pad6down->DrawFrame(hAF2_TagTightLLH_v11->GetYaxis()->GetXmin(), 0.95, hAF2_TagTightLLH_v11->GetYaxis()->GetXmax(), 1.049);
    frame6->GetXaxis()->SetNdivisions(510);
    frame6->GetYaxis()->SetNdivisions(405);
    frame6->SetLineWidth(1);
    frame6->SetXTitle("#eta");
    frame6->GetXaxis()->SetTitleSize(12);
    frame6->GetXaxis()->SetTitleFont(47);
    frame6->GetXaxis()->SetTitleOffset(3.5);
    frame6->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame6->GetXaxis()->SetLabelSize(12);
    frame6->SetYTitle("AF2/FullSim");
    frame6->GetYaxis()->SetTitleSize(10);
    frame6->GetYaxis()->SetTitleFont(43);
    frame6->GetYaxis()->SetTitleOffset(1.5);
    frame6->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame6->GetYaxis()->SetLabelSize(10);
    frame6->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin13->Sumw2();
    hAF2_TagTightLLH_v11_high_pT->Sumw2();
    hAF2_TagTightLLH_v11_Iso_high_pT->Sumw2();
    hAF2_TagMediumLLH_v11_Iso_high_pT->Sumw2();
    TH1F *ratio4_high_pT = (TH1F *)hAF2_TagTightLLH_v11_high_pT->Clone();
    TH1F *ratio5_high_pT = (TH1F *)hAF2_TagTightLLH_v11_Iso_high_pT->Clone();
    TH1F *ratio6_high_pT = (TH1F *)hAF2_TagMediumLLH_v11_Iso_high_pT->Clone();
    ratio4_high_pT->Divide(hFSmc_EffMC_bin13);
    ratio5_high_pT->Divide(hFSmc_EffMC_bin13);
    ratio6_high_pT->Divide(hFSmc_EffMC_bin13);
    
    ratio4_high_pT->SetLineColor(kRed);
    ratio4_high_pT->SetLineWidth(1);
    ratio4_high_pT->SetMarkerColor(kRed);
    ratio4_high_pT->SetMarkerSize(0.7);
    ratio4_high_pT->SetMarkerStyle(20);
    ratio4_high_pT->Draw("E1,same");
    
    ratio5_high_pT->SetLineColor(kBlue);
    ratio5_high_pT->SetLineWidth(1);
    ratio5_high_pT->SetMarkerColor(kBlue);
    ratio5_high_pT->SetMarkerSize(0.7);
    ratio5_high_pT->SetMarkerStyle(20);
    ratio5_high_pT->Draw("E1,same");
    
    ratio6_high_pT->SetLineColor(kMagenta);
    ratio6_high_pT->SetLineWidth(1);
    ratio6_high_pT->SetMarkerColor(kMagenta);
    ratio6_high_pT->SetMarkerSize(0.7);
    ratio6_high_pT->SetMarkerStyle(20);
    ratio6_high_pT->Draw("E1,same");
    
    c2->Print("plots/variation_Tag.pdf");
    
    //
    // vary template
    //
    
    // low pT: 7 GeV < pT < 10 GeV
    TH1F *hAF2_Variation1_low_pT = (TH1F *)hAF2_Variation1->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_Variation2_low_pT = (TH1F *)hAF2_Variation2->ProjectionY("", 2, 2)->Clone();
    
    TH1F *hAF2_Variation1_low_pT_StatError = (TH1F *)hAF2_Variation1_StatError->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_Variation2_low_pT_StatError = (TH1F *)hAF2_Variation2_StatError->ProjectionY("", 2, 2)->Clone();
    fixHistogramError(hAF2_Variation1_low_pT, hAF2_Variation1_low_pT_StatError);
    fixHistogramError(hAF2_Variation2_low_pT, hAF2_Variation2_low_pT_StatError);
    /*
     TH1F *hFSmc_EffMC_bin2      = (TH1F *)hFSmc_EffMC->ProjectionY("", 2, 2)->Clone();
     TH1F *hFSmc_EffMC_bin2_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 2, 2)->Clone();
     fixHistogramError(hFSmc_EffMC_bin2, hFSmc_EffMC_bin2_stat);
     
     int low_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(2) / 1000;
     int low_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(2) / 1000;
     TString low_pT_range = TString::Format("%d", static_cast<int>(low_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(low_pT_up_edge)) + " GeV";
     */
    low_pT_low_edge = hAF2_Variation1->GetXaxis()->GetBinLowEdge(2) / 1000;
    low_pT_up_edge  = hAF2_Variation1->GetXaxis()->GetBinUpEdge(2) / 1000;
    low_pT_range = TString::Format("%d", static_cast<int>(low_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(low_pT_up_edge)) + " GeV";
    
    // medium pT: 35 GeV < pT < 40 GeV
    TH1F *hAF2_Variation1_medium_pT = (TH1F *)hAF2_Variation1->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_Variation2_medium_pT = (TH1F *)hAF2_Variation2->ProjectionY("", 8, 8)->Clone();
    
    TH1F *hAF2_Variation1_medium_pT_StatError = (TH1F *)hAF2_Variation1_StatError->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_Variation2_medium_pT_StatError = (TH1F *)hAF2_Variation2_StatError->ProjectionY("", 8, 8)->Clone();
    fixHistogramError(hAF2_Variation1_medium_pT, hAF2_Variation1_medium_pT_StatError);
    fixHistogramError(hAF2_Variation2_medium_pT, hAF2_Variation2_medium_pT_StatError);
    /*
     TH1F *hFSmc_EffMC_bin8      = (TH1F *)hFSmc_EffMC->ProjectionY("", 8, 8)->Clone();
     TH1F *hFSmc_EffMC_bin8_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 8, 8)->Clone();
     fixHistogramError(hFSmc_EffMC_bin8, hFSmc_EffMC_bin8_stat);
     
     int medium_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(8) / 1000;
     int medium_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(8) / 1000;
     TString medium_pT_range = TString::Format("%d", static_cast<int>(medium_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(medium_pT_up_edge)) + " GeV";
     */
    medium_pT_low_edge = hAF2_Variation1->GetXaxis()->GetBinLowEdge(8) / 1000;
    medium_pT_up_edge  = hAF2_Variation1->GetXaxis()->GetBinUpEdge(8) / 1000;
    medium_pT_range = TString::Format("%d", static_cast<int>(medium_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(medium_pT_up_edge)) + " GeV";
    
    // high pT: 60 GeV < pT < 80 GeV
    TH1F *hAF2_Variation1_high_pT = (TH1F *)hAF2_Variation1->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_Variation2_high_pT = (TH1F *)hAF2_Variation2->ProjectionY("", 13, 13)->Clone();
    
    TH1F *hAF2_Variation1_high_pT_StatError = (TH1F *)hAF2_Variation1_StatError->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_Variation2_high_pT_StatError = (TH1F *)hAF2_Variation2_StatError->ProjectionY("", 13, 13)->Clone();
    fixHistogramError(hAF2_Variation1_high_pT, hAF2_Variation1_high_pT_StatError);
    fixHistogramError(hAF2_Variation2_high_pT, hAF2_Variation2_high_pT_StatError);
    /*
     TH1F *hFSmc_EffMC_bin13      = (TH1F *)hFSmc_EffMC->ProjectionY("", 13, 13)->Clone();
     TH1F *hFSmc_EffMC_bin13_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 13, 13)->Clone();
     fixHistogramError(hFSmc_EffMC_bin13, hFSmc_EffMC_bin13_stat);
     
     int high_pT_low_edge = hAF2_TagTightLLH_v11->GetXaxis()->GetBinLowEdge(13) / 1000;
     int high_pT_up_edge  = hAF2_TagTightLLH_v11->GetXaxis()->GetBinUpEdge(13) / 1000;
     TString high_pT_range = TString::Format("%d", static_cast<int>(high_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(high_pT_up_edge)) + " GeV";
     */
    high_pT_low_edge = hAF2_Variation1->GetXaxis()->GetBinLowEdge(13) / 1000;
    high_pT_up_edge  = hAF2_Variation2->GetXaxis()->GetBinUpEdge(13) / 1000;
    high_pT_range = TString::Format("%d", static_cast<int>(high_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(high_pT_up_edge)) + " GeV";
    
    TCanvas *c3 = new TCanvas("c3", "Template variations", 1200, 400);
    c3->Divide(3, 1);
    c3->cd(1);
    //Upper plot will be in pad7up
    TPad *pad7up = new TPad("pad7up", "pad7up", 0, 0.35, 1, 1.0);
    pad7up->SetBottomMargin(0); // Upper and lower plot are joined
    pad7up->Draw();
    // lower plot will be in pad7down
    TPad *pad7down = new TPad("pad7down", "pad7down", 0, 0.05, 1, 0.35);
    pad7down->SetTopMargin(0);
    pad7down->SetBottomMargin(0.3);
    pad7down->SetGridy(); // grid lines
    pad7down->Draw();
    //
    // pad7up: top pad
    //
    pad7up->cd(); // pad7up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin2->SetTitle(low_pT_range);
    hFSmc_EffMC_bin2->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin2->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin2->SetMaximum(1.05);
    hFSmc_EffMC_bin2->SetMinimum(0.95);
    hFSmc_EffMC_bin2->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin2->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin2->SetMarkerSize(0.7);
    hFSmc_EffMC_bin2->SetLineColor(kBlack);
    hFSmc_EffMC_bin2->Draw("E1");
    
    hAF2_Variation1_low_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_Variation1_low_pT->SetMarkerColor(kRed);
    hAF2_Variation1_low_pT->SetMarkerSize(0.7);
    hAF2_Variation1_low_pT->SetLineColor(kRed);
    hAF2_Variation1_low_pT->Draw("E1,same");
    
    hAF2_Variation2_low_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_Variation2_low_pT->SetMarkerColor(kBlue);
    hAF2_Variation2_low_pT->SetMarkerSize(0.7);
    hAF2_Variation2_low_pT->SetLineColor(kBlue);
    hAF2_Variation2_low_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend7 = new TLegend(0.5, 0.6, 0.89, 0.89);
    legend7->SetBorderSize(0);
    legend7->SetFillColor(0);
    legend7->SetFillStyle(0);
    legend7->AddEntry(hFSmc_EffMC_bin2, "FullSim MC");
    legend7->AddEntry(hAF2_Variation1_low_pT, "AF2 TemplRun2Variation1AndPassTrackQuality");
    legend7->AddEntry(hAF2_Variation2_low_pT, "AF2 TemplRun2Variation2AndPassTrackQuality");
    legend7->Draw();
    
    //
    // pad7down: bottom pad
    //
    pad7down->cd(); // pad1down becomes the current pad
    
    TH1F *frame7 = pad7down->DrawFrame(hAF2_Variation1->GetYaxis()->GetXmin(), 0.95, hAF2_Variation1->GetYaxis()->GetXmax(), 1.049);
    frame7->GetXaxis()->SetNdivisions(510);
    frame7->GetYaxis()->SetNdivisions(405);
    frame7->SetLineWidth(1);
    frame7->SetXTitle("#eta");
    frame7->GetXaxis()->SetTitleSize(12);
    frame7->GetXaxis()->SetTitleFont(47);
    frame7->GetXaxis()->SetTitleOffset(3.5);
    frame7->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame7->GetXaxis()->SetLabelSize(12);
    frame7->SetYTitle("AF2/FullSim");
    frame7->GetYaxis()->SetTitleSize(10);
    frame7->GetYaxis()->SetTitleFont(43);
    frame7->GetYaxis()->SetTitleOffset(1.5);
    frame7->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame7->GetYaxis()->SetLabelSize(10);
    frame7->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin2->Sumw2();
    hAF2_Variation1_low_pT->Sumw2();
    hAF2_Variation2_low_pT->Sumw2();
    TH1F *ratio7_low_pT = (TH1F *)hAF2_Variation1_low_pT->Clone();
    TH1F *ratio8_low_pT = (TH1F *)hAF2_Variation2_low_pT->Clone();
    ratio7_low_pT->Divide(hFSmc_EffMC_bin2);
    ratio8_low_pT->Divide(hFSmc_EffMC_bin2);
    
    ratio7_low_pT->SetLineColor(kRed);
    ratio7_low_pT->SetLineWidth(1);
    ratio7_low_pT->SetMarkerColor(kRed);
    ratio7_low_pT->SetMarkerSize(0.7);
    ratio7_low_pT->SetMarkerStyle(20);
    ratio4_low_pT->Draw("E1,same");
    
    ratio8_low_pT->SetLineColor(kBlue);
    ratio8_low_pT->SetLineWidth(1);
    ratio8_low_pT->SetMarkerColor(kBlue);
    ratio8_low_pT->SetMarkerSize(0.7);
    ratio8_low_pT->SetMarkerStyle(20);
    ratio8_low_pT->Draw("E1,same");
    
    c3->cd(2);
    //Upper plot will be in pad8
    TPad *pad8up = new TPad("pad8up", "pad8up", 0, 0.35, 1, 1.0);
    pad8up->SetBottomMargin(0); // Upper and lower plot are joined
    pad8up->Draw();
    // lower plot will be in pad8down
    TPad *pad8down = new TPad("pad8down", "pad8down", 0, 0.05, 1, 0.35);
    pad8down->SetTopMargin(0);
    pad8down->SetBottomMargin(0.3);
    pad8down->SetGridy(); // grid lines
    pad8down->Draw();
    //
    // pad8up: top pad
    //
    pad8up->cd(); // pad8up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin8->SetTitle(medium_pT_range);
    hFSmc_EffMC_bin8->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin8->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin8->SetMaximum(1.05);
    hFSmc_EffMC_bin8->SetMinimum(0.95);
    hFSmc_EffMC_bin8->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin8->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin8->SetMarkerSize(0.7);
    hFSmc_EffMC_bin8->SetLineColor(kBlack);
    hFSmc_EffMC_bin8->Draw("E1");
    
    hAF2_Variation1_medium_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_Variation1_medium_pT->SetMarkerColor(kRed);
    hAF2_Variation1_medium_pT->SetMarkerSize(0.7);
    hAF2_Variation1_medium_pT->SetLineColor(kRed);
    hAF2_Variation1_medium_pT->Draw("E1,same");
    
    hAF2_Variation2_medium_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_Variation2_medium_pT->SetMarkerColor(kBlue);
    hAF2_Variation2_medium_pT->SetMarkerSize(0.7);
    hAF2_Variation2_medium_pT->SetLineColor(kBlue);
    hAF2_Variation2_medium_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend8 = new TLegend(0.5, 0.6, 0.89, 0.89);
    legend8->SetBorderSize(0);
    legend8->SetFillColor(0);
    legend8->SetFillStyle(0);
    legend8->AddEntry(hFSmc_EffMC_bin8, "FullSim MC");
    legend8->AddEntry(hAF2_Variation1_medium_pT, "AF2 TemplRun2Variation1AndPassTrackQuality");
    legend8->AddEntry(hAF2_Variation2_medium_pT, "AF2 TemplRun2Variation2AndPassTrackQuality");
    legend8->Draw();
    
    //
    // pad8down: bottom pad
    //
    pad8down->cd(); // pad8down becomes the current pad
    
    TH1F *frame8 = pad8down->DrawFrame(hAF2_Variation1->GetYaxis()->GetXmin(), 0.95, hAF2_Variation1->GetYaxis()->GetXmax(), 1.049);
    frame8->GetXaxis()->SetNdivisions(510);
    frame8->GetYaxis()->SetNdivisions(405);
    frame8->SetLineWidth(1);
    frame8->SetXTitle("#eta");
    frame8->GetXaxis()->SetTitleSize(12);
    frame8->GetXaxis()->SetTitleFont(47);
    frame8->GetXaxis()->SetTitleOffset(3.5);
    frame8->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame8->GetXaxis()->SetLabelSize(12);
    frame8->SetYTitle("AF2/FullSim");
    frame8->GetYaxis()->SetTitleSize(10);
    frame8->GetYaxis()->SetTitleFont(43);
    frame8->GetYaxis()->SetTitleOffset(1.5);
    frame8->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame8->GetYaxis()->SetLabelSize(10);
    frame8->Draw();
    
    // Calculate the ratio between data and MC
    hFSmc_EffMC_bin8->Sumw2();
    hAF2_Variation1_medium_pT->Sumw2();
    hAF2_Variation2_medium_pT->Sumw2();
    TH1F *ratio7_medium_pT = (TH1F *)hAF2_Variation1_medium_pT->Clone();
    TH1F *ratio8_medium_pT = (TH1F *)hAF2_Variation2_medium_pT->Clone();
    ratio7_medium_pT->Divide(hFSmc_EffMC_bin8);
    ratio8_medium_pT->Divide(hFSmc_EffMC_bin8);
    
    ratio7_medium_pT->SetLineColor(kRed);
    ratio7_medium_pT->SetLineWidth(1);
    ratio7_medium_pT->SetMarkerColor(kRed);
    ratio7_medium_pT->SetMarkerSize(0.7);
    ratio7_medium_pT->SetMarkerStyle(20);
    ratio7_medium_pT->Draw("E1,same");
    
    ratio8_medium_pT->SetLineColor(kBlue);
    ratio8_medium_pT->SetLineWidth(1);
    ratio8_medium_pT->SetMarkerColor(kBlue);
    ratio8_medium_pT->SetMarkerSize(0.7);
    ratio8_medium_pT->SetMarkerStyle(20);
    ratio8_medium_pT->Draw("E1,same");
    
    c3->cd(3);
    //Upper plot will be in pad9up
    TPad *pad9up = new TPad("pad9up", "pad9up", 0, 0.35, 1, 1.0);
    pad9up->SetBottomMargin(0); // Upper and lower plot are joined
    pad9up->Draw();
    // lower plot will be in pad9down
    TPad *pad9down = new TPad("pad9down", "pad9down", 0, 0.05, 1, 0.35);
    pad9down->SetTopMargin(0);
    pad9down->SetBottomMargin(0.3);
    pad9down->SetGridy(); // grid lines
    pad9down->Draw();
    //
    // pad9up: top pad
    //
    pad9up->cd(); // pad9up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin13->SetTitle(high_pT_range);
    hFSmc_EffMC_bin13->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin13->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin13->SetMaximum(1.05);
    hFSmc_EffMC_bin13->SetMinimum(0.95);
    hFSmc_EffMC_bin13->SetMarkerStyle(kFullCircle);
    hFSmc_EffMC_bin13->SetMarkerColor(kBlack);
    hFSmc_EffMC_bin13->SetMarkerSize(0.7);
    hFSmc_EffMC_bin13->SetLineColor(kBlack);
    hFSmc_EffMC_bin13->Draw("E1");
    
    hAF2_Variation1_high_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2_Variation1_high_pT->SetMarkerColor(kRed);
    hAF2_Variation1_high_pT->SetMarkerSize(0.7);
    hAF2_Variation1_high_pT->SetLineColor(kRed);
    hAF2_Variation1_high_pT->Draw("E1,same");
    
    hAF2_Variation2_high_pT->SetMarkerStyle(kFullTriangleDown);
    hAF2_Variation2_high_pT->SetMarkerColor(kBlue);
    hAF2_Variation2_high_pT->SetMarkerSize(0.7);
    hAF2_Variation2_high_pT->SetLineColor(kBlue);
    hAF2_Variation2_high_pT->Draw("E1,same");
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend9 = new TLegend(0.5, 0.6, 0.89, 0.89);
    legend9->SetBorderSize(0);
    legend9->SetFillColor(0);
    legend9->SetFillStyle(0);
    legend9->AddEntry(hFSmc_EffMC_bin13, "FullSim MC");
    legend9->AddEntry(hAF2_Variation1_high_pT, "AF2 TemplRun2Variation1AndPassTrackQuality");
    legend9->AddEntry(hAF2_Variation2_high_pT, "AF2 TemplRun2Variation2AndPassTrackQuality");
    legend9->Draw();
    
    //
    // pad9down: bottom pad
    //
    pad9down->cd(); // pad9down becomes the current pad
    
    TH1F *frame9 = pad9down->DrawFrame(hAF2_Variation1->GetYaxis()->GetXmin(), 0.95, hAF2_Variation2->GetYaxis()->GetXmax(), 1.049);
    frame9->GetXaxis()->SetNdivisions(510);
    frame9->GetYaxis()->SetNdivisions(405);
    frame9->SetLineWidth(1);
    frame9->SetXTitle("#eta");
    frame9->GetXaxis()->SetTitleSize(12);
    frame9->GetXaxis()->SetTitleFont(47);
    frame9->GetXaxis()->SetTitleOffset(3.5);
    frame9->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame9->GetXaxis()->SetLabelSize(12);
    frame9->SetYTitle("AF2/FullSim");
    frame9->GetYaxis()->SetTitleSize(10);
    frame9->GetYaxis()->SetTitleFont(43);
    frame9->GetYaxis()->SetTitleOffset(1.5);
    frame9->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame9->GetYaxis()->SetLabelSize(10);
    frame9->Draw();
    
    // Calculate the ratio between hOld and hNew
    hFSmc_EffMC_bin13->Sumw2();
    hAF2_Variation1_high_pT->Sumw2();
    hAF2_Variation2_high_pT->Sumw2();
    TH1F *ratio7_high_pT = (TH1F *)hAF2_Variation1_high_pT->Clone();
    TH1F *ratio8_high_pT = (TH1F *)hAF2_Variation2_high_pT->Clone();
    ratio7_high_pT->Divide(hFSmc_EffMC_bin13);
    ratio8_high_pT->Divide(hFSmc_EffMC_bin13);
    
    ratio7_high_pT->SetLineColor(kRed);
    ratio7_high_pT->SetLineWidth(1);
    ratio7_high_pT->SetMarkerColor(kRed);
    ratio7_high_pT->SetMarkerSize(0.7);
    ratio7_high_pT->SetMarkerStyle(20);
    ratio7_high_pT->Draw("E1,same");
    
    ratio8_high_pT->SetLineColor(kBlue);
    ratio8_high_pT->SetLineWidth(1);
    ratio8_high_pT->SetMarkerColor(kBlue);
    ratio8_high_pT->SetMarkerSize(0.7);
    ratio8_high_pT->SetMarkerStyle(20);
    ratio8_high_pT->Draw("E1,same");
    
    c3->Print("plots/variation_Templ.pdf");
}
