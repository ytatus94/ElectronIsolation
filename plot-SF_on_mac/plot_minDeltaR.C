#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TLegend.h>
#include <TLine.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"
#include "FindOptimalRange.C"

#include <iostream>
using namespace std;

void plot_minDeltaR(TString menu, TString iso)
{
    bool debug = true;
    //bool debug = false;

    TFile *data_file = TFile::Open("../merged-hist-data.root");
    TFile *mc_file   = TFile::Open("../merged-hist-mc.root");

    TString background_template[2] ={"TemplRun2Variation1AndPassTrackQuality", "TemplRun2Variation2AndPassTrackQuality"};
    TString tag[3] = {"TagTightLLHMC15_v8", "TagTightLLHMC15_v8_Iso", "TagMediumLLHMC15_v8_Iso"};

    TString data_folder, data_den_deltaR, data_num_deltaR, data_den_minDeltaR, data_num_minDeltaR,
            mc_folder,   mc_den_deltaR,   mc_num_deltaR,   mc_den_minDeltaR,   mc_num_minDeltaR;
    // use TemplRun2Variation1AndPassTrackQuality and TagTightLLHMC15_v8 by default
    if (iso.Contains("isolPhFixedCut")) { 
        data_folder        = menu + "MC15_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        data_den_deltaR    = data_folder + "/" + data_folder + "_Data_Den_deltaR_3d";
        data_num_deltaR    = data_folder + "/" + data_folder + "_Data_Num_deltaR_3d";
        data_den_minDeltaR = data_folder + "/" + data_folder + "_Data_Den_minDeltaR_3d";
        data_num_minDeltaR = data_folder + "/" + data_folder + "_Data_Num_minDeltaR_3d";

        mc_folder        = menu + "MC15_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        mc_den_deltaR    = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Den_deltaR_3d";
        mc_num_deltaR    = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Num_deltaR_3d";
        mc_den_minDeltaR = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Den_minDeltaR_3d";
        mc_num_minDeltaR = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Num_minDeltaR_3d";
    }
    else {
        data_folder        = menu + "_d0z0_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        data_den_deltaR    = data_folder + "/" + data_folder + "_Data_Den_deltaR_3d";
        data_num_deltaR    = data_folder + "/" + data_folder + "_Data_Num_deltaR_3d";
        data_den_minDeltaR = data_folder + "/" + data_folder + "_Data_Den_minDeltaR_3d";
        data_num_minDeltaR = data_folder + "/" + data_folder + "_Data_Num_minDeltaR_3d";

        mc_folder        = menu + "_d0z0_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        mc_den_deltaR    = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Den_deltaR_3d";
        mc_num_deltaR    = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Num_deltaR_3d";
        mc_den_minDeltaR = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Den_minDeltaR_3d";
        mc_num_minDeltaR = mc_folder + "/" + data_folder + "_MCZee_NoFilter_Num_minDeltaR_3d";
    }

    TH3F *h_data_den_deltaR    = (TH3F*)data_file->Get(data_den_deltaR);
    TH3F *h_data_num_deltaR    = (TH3F*)data_file->Get(data_num_deltaR);
    TH3F *h_data_den_minDeltaR = (TH3F*)data_file->Get(data_den_minDeltaR);
    TH3F *h_data_num_minDeltaR = (TH3F*)data_file->Get(data_num_minDeltaR);

    TH3F *h_mc_den_deltaR    = (TH3F*)mc_file->Get(mc_den_deltaR);
    TH3F *h_mc_num_deltaR    = (TH3F*)mc_file->Get(mc_num_deltaR);
    TH3F *h_mc_den_minDeltaR = (TH3F*)mc_file->Get(mc_den_minDeltaR);
    TH3F *h_mc_num_minDeltaR = (TH3F*)mc_file->Get(mc_num_minDeltaR);

    gStyle->SetOptStat(0);

    //
    // minDeltaR(pT, eta) plot
    // 
    TCanvas *c1 = new TCanvas("minDeltaR_2D_yx");
    h_data_den_minDeltaR->GetXaxis()->SetRangeUser(7000, 125000);
    h_data_den_minDeltaR->GetXaxis()->SetTitle("E_{T} [MeV]");
    h_data_den_minDeltaR->GetYaxis()->SetTitle("#eta");
    h_data_den_minDeltaR->Project3D("yx")->Draw("colz");
    c1->Print(const_cast<char *>((TString(h_data_den_minDeltaR->GetName()) + ".pdf").Data()));

    //
    // projection to minDeltaR axis (z axis);
    //
    TH1F *h_data_den_deltaR_1D    = (TH1F*)h_data_den_deltaR->ProjectionZ()->Clone();
    TH1F *h_data_num_deltaR_1D    = (TH1F*)h_data_num_deltaR->ProjectionZ()->Clone();
    TH1F *h_data_den_minDeltaR_1D = (TH1F*)h_data_den_minDeltaR->ProjectionZ()->Clone();
    TH1F *h_data_num_minDeltaR_1D = (TH1F*)h_data_num_minDeltaR->ProjectionZ()->Clone();

    TH1F *h_mc_den_deltaR_1D    = (TH1F*)h_mc_den_deltaR->ProjectionZ()->Clone();
    TH1F *h_mc_num_deltaR_1D    = (TH1F*)h_mc_num_deltaR->ProjectionZ()->Clone();
    TH1F *h_mc_den_minDeltaR_1D = (TH1F*)h_mc_den_minDeltaR->ProjectionZ()->Clone();
    TH1F *h_mc_num_minDeltaR_1D = (TH1F*)h_mc_num_minDeltaR->ProjectionZ()->Clone();

    TCanvas *c2 = new TCanvas("minDeltaR_1D_z");
    h_data_den_minDeltaR_1D->SetXTitle("#Delta R");
    h_data_den_minDeltaR_1D->SetYTitle("Event");
    h_data_den_minDeltaR_1D->SetLineColor(kBlue);
    h_data_den_minDeltaR_1D->Draw("hist");

    double scale_value = h_data_den_minDeltaR_1D->Integral() / h_mc_den_minDeltaR_1D->Integral();
    h_mc_den_minDeltaR_1D->Scale(scale_value);
    h_mc_den_minDeltaR_1D->SetLineColor(kRed);
    h_mc_den_minDeltaR_1D->Draw("hist,same");

    TLegend *leg1 = new TLegend(0.5, 0.70, 0.8, 0.82);
    leg1->AddEntry(h_data_den_minDeltaR_1D, "Data", "lp");
    leg1->AddEntry(h_mc_den_minDeltaR_1D, "Z #rightarrow ee MC", "lp");
	leg1->SetBorderSize(0);
	leg1->SetTextFont(42);
    leg1->SetTextSize(0.05);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->Draw();
    myText(0.5, 0.62, kBlack, "MC is normalized to data");
    c2->Print(const_cast<char *>((TString(h_data_den_minDeltaR_1D->GetName()) + ".pdf").Data()));

    //
    // projection to minDeltaR axis (z axis) with different pt ranges;
    //
    int pt_bin[6] = {2, 5, 9, 12, 13, 14}; // pt=7, 20, 40, 60, 80, 125 GeV
    TH1F *h_data_den_minDeltaR_1D_pt_bin[5] = {0}, *h_mc_den_minDeltaR_1D_pt_bin[5] = {0};
    double pt_bin_lower[5] = {0}, pt_bin_upper[5] = {0};
    for (int i = 0; i < 5; i++) { // 5 intervals.
        h_data_den_minDeltaR_1D_pt_bin[i] = (TH1F*)h_data_den_minDeltaR->ProjectionZ("", pt_bin[i], pt_bin[i+1]-1)->Clone();
        h_mc_den_minDeltaR_1D_pt_bin[i]   = (TH1F*)h_mc_den_minDeltaR->ProjectionZ("", pt_bin[i], pt_bin[i+1]-1)->Clone();
        double scale_value = h_data_den_minDeltaR_1D_pt_bin[i]->Integral() / h_mc_den_minDeltaR_1D_pt_bin[i]->Integral();
        h_mc_den_minDeltaR_1D_pt_bin[i]->Scale(scale_value);
        pt_bin_lower[i] = h_data_den_minDeltaR->GetXaxis()->GetBinLowEdge(pt_bin[i]) / 1000.;
        pt_bin_upper[i] = h_data_den_minDeltaR->GetXaxis()->GetBinUpEdge(pt_bin[i+1]-1) / 1000.;
    } 

    if (debug) {
        for (int i = 0; i < 5; i++) {
            cout << pt_bin_lower[i] << " GeV < pT < " << pt_bin_upper[i] << " GeV" << endl;
        }
    }

    TCanvas *c3 = new TCanvas("minDeltaR_1D_vs_pT");
    h_data_den_minDeltaR_1D_pt_bin[1]->SetXTitle("#Delta R");
    h_data_den_minDeltaR_1D_pt_bin[1]->SetYTitle("Events");
    h_data_den_minDeltaR_1D_pt_bin[1]->SetLineColor(1);
    h_data_den_minDeltaR_1D_pt_bin[1]->Draw("hist");
    h_data_den_minDeltaR_1D_pt_bin[0]->SetLineColor(2);
    h_data_den_minDeltaR_1D_pt_bin[0]->Draw("hist,same");
    h_data_den_minDeltaR_1D_pt_bin[2]->SetLineColor(3);
    h_data_den_minDeltaR_1D_pt_bin[2]->Draw("hist,same");
    h_data_den_minDeltaR_1D_pt_bin[3]->SetLineColor(4);
    h_data_den_minDeltaR_1D_pt_bin[3]->Draw("hist,same");
    h_data_den_minDeltaR_1D_pt_bin[4]->SetLineColor(5);
    h_data_den_minDeltaR_1D_pt_bin[4]->Draw("hist,same");
 
    h_mc_den_minDeltaR_1D_pt_bin[0]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_pt_bin[0]->SetLineColor(2);
    h_mc_den_minDeltaR_1D_pt_bin[0]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_pt_bin[1]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_pt_bin[1]->SetLineColor(1);
    h_mc_den_minDeltaR_1D_pt_bin[1]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_pt_bin[2]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_pt_bin[2]->SetLineColor(3);
    h_mc_den_minDeltaR_1D_pt_bin[2]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_pt_bin[3]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_pt_bin[3]->SetLineColor(4);
    h_mc_den_minDeltaR_1D_pt_bin[3]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_pt_bin[4]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_pt_bin[4]->SetLineColor(5);
    h_mc_den_minDeltaR_1D_pt_bin[4]->Draw("hist,same");
    
    TLegend *leg2 = new TLegend(0.5, 0.20, 0.8, 0.82);
    leg2->AddEntry(h_data_den_minDeltaR_1D_pt_bin[1], "Data, 7 GeV < p_{T} < 20 GeV", "lp");
    leg2->AddEntry(h_data_den_minDeltaR_1D_pt_bin[1], "Data, 20 GeV < p_{T} < 40 GeV", "lp");
    leg2->AddEntry(h_data_den_minDeltaR_1D_pt_bin[2], "Data, 40 GeV < p_{T} < 60 GeV", "lp");
    leg2->AddEntry(h_data_den_minDeltaR_1D_pt_bin[3], "Data, 60 GeV < p_{T} < 80 GeV", "lp");
    leg2->AddEntry(h_data_den_minDeltaR_1D_pt_bin[4], "Data, 80 GeV < p_{T} < 125 GeV", "lp");
    leg2->AddEntry(h_mc_den_minDeltaR_1D_pt_bin[0], "MC, 7 GeV < p_{T} < 20 GeV", "lp");
    leg2->AddEntry(h_mc_den_minDeltaR_1D_pt_bin[1], "MC, 20 GeV < p_{T} < 40 GeV", "lp");
    leg2->AddEntry(h_mc_den_minDeltaR_1D_pt_bin[2], "MC, 40 GeV < p_{T} < 60 GeV", "lp");
    leg2->AddEntry(h_mc_den_minDeltaR_1D_pt_bin[3], "MC, 60 GeV < p_{T} < 80 GeV", "lp");
    leg2->AddEntry(h_mc_den_minDeltaR_1D_pt_bin[4], "MC, 80 GeV < p_{T} < 125 GeV", "lp");
	leg2->SetBorderSize(0);
	leg2->SetTextFont(42);
    leg2->SetTextSize(0.03);
    leg2->SetFillColor(0);
    leg2->SetFillStyle(0);
    leg2->Draw();

    TString c3_output_name;
    if (iso.Contains("isolPhFixedCut"))
        c3_output_name = menu + "MC15_v8_" + iso + "_minDeltaR_pt_bins.pdf";
    else
        c3_output_name = menu + "_d0z0_v8_" + iso + "_minDeltaR_pt_bins.pdf";
    
    c3->Print(const_cast<char *>(c3_output_name.Data()));

    //
    // projection to minDeltaR axis (z axis) with different eta ranges;
    // eta = -2.47, -2.37, -2.01, -1.81, -1.52, -1.37, -1.15, -0.8, -0.6, -0.1, 0, 0.1, 0.6, 0.8, 1.15, 1.37, 1.52, 1.81, 2.01, 2.37, 2.47
    //
    TH1F *h_data_den_minDeltaR_1D_eta_bin[21] = {0}, *h_mc_den_minDeltaR_1D_eta_bin[21] = {0};
    double eta_bin_lower[21] = {0}, eta_bin_upper[21] = {0};
    for (int i = 1; i < 21; i++) {
        int xmax = h_data_den_minDeltaR->GetXaxis()->GetNbins();
        h_data_den_minDeltaR_1D_eta_bin[i] = (TH1F*)h_data_den_minDeltaR->ProjectionZ("", 0, xmax, i, i)->Clone();
        h_mc_den_minDeltaR_1D_eta_bin[i]   = (TH1F*)h_mc_den_minDeltaR->ProjectionZ("", 0, xmax, i, i)->Clone();
        double scale_value = h_data_den_minDeltaR_1D_eta_bin[i]->Integral() / h_mc_den_minDeltaR_1D_eta_bin[i]->Integral();
        h_mc_den_minDeltaR_1D_eta_bin[i]->Scale(scale_value);
        eta_bin_lower[i] = h_data_den_minDeltaR->GetYaxis()->GetBinLowEdge(i);
        eta_bin_upper[i] = h_data_den_minDeltaR->GetYaxis()->GetBinUpEdge(i);
    } 

    if (debug) {
        for (int i = 11; i < 21; i++) {
            cout << eta_bin_lower[i] << " < eta < " << eta_bin_upper[i] << endl;
        }
    }

    TCanvas *c4 = new TCanvas("minDeltaR_1D_vs_eta");
    h_data_den_minDeltaR_1D_eta_bin[12]->SetXTitle("#Delta R");
    h_data_den_minDeltaR_1D_eta_bin[12]->SetYTitle("Events");
    h_data_den_minDeltaR_1D_eta_bin[12]->SetLineColor(1);
    h_data_den_minDeltaR_1D_eta_bin[12]->Draw("hist");
    h_data_den_minDeltaR_1D_eta_bin[11]->SetLineColor(2);
    h_data_den_minDeltaR_1D_eta_bin[11]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[12]->SetLineColor(3);
    h_data_den_minDeltaR_1D_eta_bin[12]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[13]->SetLineColor(4);
    h_data_den_minDeltaR_1D_eta_bin[13]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[14]->SetLineColor(5);
    h_data_den_minDeltaR_1D_eta_bin[14]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[15]->SetLineColor(6);
    h_data_den_minDeltaR_1D_eta_bin[15]->Draw("hist,same");
/*
    h_data_den_minDeltaR_1D_eta_bin[16]->SetLineColor(7);
    h_data_den_minDeltaR_1D_eta_bin[16]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[17]->SetLineColor(8);
    h_data_den_minDeltaR_1D_eta_bin[17]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[18]->SetLineColor(9);
    h_data_den_minDeltaR_1D_eta_bin[18]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[19]->SetLineColor(11);
    h_data_den_minDeltaR_1D_eta_bin[19]->Draw("hist,same");
    h_data_den_minDeltaR_1D_eta_bin[20]->SetLineColor(12);
    h_data_den_minDeltaR_1D_eta_bin[20]->Draw("hist,same");
*/
    h_mc_den_minDeltaR_1D_eta_bin[12]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[12]->SetLineColor(1);
    h_mc_den_minDeltaR_1D_eta_bin[12]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[11]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[11]->SetLineColor(2);
    h_mc_den_minDeltaR_1D_eta_bin[11]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[12]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[12]->SetLineColor(3);
    h_mc_den_minDeltaR_1D_eta_bin[12]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[13]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[13]->SetLineColor(4);
    h_mc_den_minDeltaR_1D_eta_bin[13]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[14]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[14]->SetLineColor(5);
    h_mc_den_minDeltaR_1D_eta_bin[14]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[15]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[15]->SetLineColor(6);
    h_mc_den_minDeltaR_1D_eta_bin[15]->Draw("hist,same");
/*
    h_mc_den_minDeltaR_1D_eta_bin[16]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[16]->SetLineColor(7);
    h_mc_den_minDeltaR_1D_eta_bin[16]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[17]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[17]->SetLineColor(8);
    h_mc_den_minDeltaR_1D_eta_bin[17]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[18]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[18]->SetLineColor(9);
    h_mc_den_minDeltaR_1D_eta_bin[18]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[19]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[19]->SetLineColor(11);
    h_mc_den_minDeltaR_1D_eta_bin[19]->Draw("hist,same");
    h_mc_den_minDeltaR_1D_eta_bin[20]->SetLineStyle(2);
    h_mc_den_minDeltaR_1D_eta_bin[20]->SetLineColor(12);
    h_mc_den_minDeltaR_1D_eta_bin[20]->Draw("hist,same");
*/
    TLegend *leg3 = new TLegend(0.5, 0.20, 0.8, 0.82);
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[11], "Data, 0 < #eta < 0.1", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[12], "Data, 0.1 < #eta < 0.6", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[13], "Data, 0.6 < #eta < 0.8", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[14], "Data, 0.8 < #eta < 1.15", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[15], "Data, 1.15 < #eta < 1.37", "lp");

    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[11], "MC, 0 < #eta < 0.1", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[12], "MC, 0.1 < #eta < 0.6", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[13], "MC, 0.6 < #eta < 0.8", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[14], "MC, 0.8 < #eta < 1.15", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[15], "MC, 1.15 < #eta < 1.37", "lp");
/*
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[16], "Data, 1.37 < #eta < 1.52", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[17], "Data, 1.52 < #eta < 1.81", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[18], "Data, 1.81 < #eta < 2.01", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[19], "Data, 2.01 < #eta < 2.37", "lp");
    leg3->AddEntry(h_data_den_minDeltaR_1D_eta_bin[20], "Data, 2.37 < #eta < 2.47", "lp");

    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[16], "MC, 1.37 < #eta < 1.52", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[17], "MC, 1.52 < #eta < 1.81", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[18], "MC, 1.81 < #eta < 2.01", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[19], "MC, 2.01 < #eta < 2.37", "lp");
    leg3->AddEntry(h_mc_den_minDeltaR_1D_eta_bin[20], "MC, 2.37 < #eta < 2.47", "lp");
*/
	leg3->SetBorderSize(0);
	leg3->SetTextFont(42);
    leg3->SetTextSize(0.03);
    leg3->SetFillColor(0);
    leg3->SetFillStyle(0);
    leg3->Draw();

    TString c4_output_name;
    if (iso.Contains("isolPhFixedCut"))
        c4_output_name = menu + "MC15_v8_" + iso + "_minDeltaR_eta_bins.pdf";
    else
        c4_output_name = menu + "_d0z0_v8_" + iso + "_minDeltaR_eta_bins.pdf";
    
    c4->Print(const_cast<char *>(c4_output_name.Data()));


/*
    // projection to pT axis (x axis);
    TH1F *h_data_den_deltaR_1D_x, *h_data_num_deltaR_1D_x, *h_data_den_minDeltaR_1D_x, *h_data_num_minDeltaR_1D_x,
         *h_mc_den_deltaR_1D_x,   *h_mc_num_deltaR_1D_x,   *h_mc_den_minDeltaR_1D_x,   *h_mc_num_minDeltaR_1D_x;
    h_data_den_deltaR_1D_x    = (TH1F*)h_data_den_deltaR->ProjectionX()->Clone();
    h_data_num_deltaR_1D_x    = (TH1F*)h_data_num_deltaR->ProjectionX()->Clone();
    h_data_den_minDeltaR_1D_x = (TH1F*)h_data_den_minDeltaR->ProjectionX()->Clone();
    h_data_num_minDeltaR_1D_x = (TH1F*)h_data_num_minDeltaR->ProjectionX()->Clone();
    h_mc_den_deltaR_1D_x    = (TH1F*)h_mc_den_deltaR->ProjectionX()->Clone();
    h_mc_num_deltaR_1D_x    = (TH1F*)h_mc_num_deltaR->ProjectionX()->Clone();
    h_mc_den_minDeltaR_1D_x = (TH1F*)h_mc_den_minDeltaR->ProjectionX()->Clone();
    h_mc_num_minDeltaR_1D_x = (TH1F*)h_mc_num_minDeltaR->ProjectionX()->Clone();

*/
}
