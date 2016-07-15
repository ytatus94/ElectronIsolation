#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

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

void mc2mc_plots(TString menu = "LooseAndBLayer", TString isol = "isolLoose")
{
    gStyle->SetOptStat(0);
    
    bool debug = true;
    
    TFile *AF2mc = TFile::Open("variations_reference.root");
    TFile *FSmc  = TFile::Open("ScaleFactors.root");
    
    // central value
    TH2F *hAF2_mll80100 = (TH2F *)AF2mc->Get("EffMC_CentralValue_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_mll80100");
    TH2F *hAF2_mll80100_StatError = (TH2F *)AF2mc->Get("EffMC_StatError_" + menu + "LLH_d0z0_Smooth_v11_" + isol + "_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11_mll80100");

    TString folder = menu + "LLH_d0z0_Smooth_v11_" + isol;
    TH2F *hFSmc_EffMC = (TH2F *)FSmc->Get(folder + "/EffMC_CentralValue_" + folder);
    TH2F *hFSmc_EffMC_StatError = (TH2F *)FSmc->Get(folder + "/EffMC_StatError_" + folder);

    // low pT: 7 GeV < pT < 10 GeV
    TH1F *hAF2_mll80100_low_pT           = (TH1F *)hAF2_mll80100->ProjectionY("", 2, 2)->Clone();
    TH1F *hAF2_mll80100_low_pT_StatError = (TH1F *)hAF2_mll80100_StatError->ProjectionY("", 2, 2)->Clone();
    fixHistogramError(hAF2_mll80100_low_pT, hAF2_mll80100_low_pT_StatError);
    
    TH1F *hFSmc_EffMC_bin2      = (TH1F *)hFSmc_EffMC->ProjectionY("", 2, 2)->Clone();
    TH1F *hFSmc_EffMC_bin2_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 2, 2)->Clone();
    fixHistogramError(hFSmc_EffMC_bin2, hFSmc_EffMC_bin2_stat);
    
    int low_pT_low_edge = hAF2_mll80100->GetXaxis()->GetBinLowEdge(2) / 1000;
    int low_pT_up_edge  = hAF2_mll80100->GetXaxis()->GetBinUpEdge(2) / 1000;
    TString low_pT_range = TString::Format("%d", static_cast<int>(low_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(low_pT_up_edge)) + " GeV";
    
    // medium pT: 35 GeV < pT < 40 GeV
    TH1F *hAF2_mll80100_medium_pT           = (TH1F *)hAF2_mll80100->ProjectionY("", 8, 8)->Clone();
    TH1F *hAF2_mll80100_medium_pT_StatError = (TH1F *)hAF2_mll80100_StatError->ProjectionY("", 8, 8)->Clone();
    fixHistogramError(hAF2_mll80100_medium_pT, hAF2_mll80100_medium_pT_StatError);
    
    TH1F *hFSmc_EffMC_bin8      = (TH1F *)hFSmc_EffMC->ProjectionY("", 8, 8)->Clone();
    TH1F *hFSmc_EffMC_bin8_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 8, 8)->Clone();
    fixHistogramError(hFSmc_EffMC_bin8, hFSmc_EffMC_bin8_stat);
    
    int medium_pT_low_edge = hAF2_mll80100->GetXaxis()->GetBinLowEdge(8) / 1000;
    int medium_pT_up_edge  = hAF2_mll80100->GetXaxis()->GetBinUpEdge(8) / 1000;
    TString medium_pT_range = TString::Format("%d", static_cast<int>(medium_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(medium_pT_up_edge)) + " GeV";
    
    // high pT: 60 GeV < pT < 80 GeV
    TH1F *hAF2_mll80100_high_pT            = (TH1F *)hAF2_mll80100->ProjectionY("", 13, 13)->Clone();
    TH1F *hAF2_mll80100_high_pT_StatError  = (TH1F *)hAF2_mll80100_StatError->ProjectionY("", 13, 13)->Clone();
    fixHistogramError(hAF2_mll80100_high_pT, hAF2_mll80100_high_pT_StatError);
    
    TH1F *hFSmc_EffMC_bin13      = (TH1F *)hFSmc_EffMC->ProjectionY("", 13, 13)->Clone();
    TH1F *hFSmc_EffMC_bin13_stat = (TH1F *)hFSmc_EffMC_StatError->ProjectionY("", 13, 13)->Clone();
    fixHistogramError(hFSmc_EffMC_bin13, hFSmc_EffMC_bin13_stat);
    
    int high_pT_low_edge = hAF2_mll80100->GetXaxis()->GetBinLowEdge(13) / 1000;
    int high_pT_up_edge  = hAF2_mll80100->GetXaxis()->GetBinUpEdge(13) / 1000;
    TString high_pT_range = TString::Format("%d", static_cast<int>(high_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(high_pT_up_edge)) + " GeV";
    
    TCanvas *c1 = new TCanvas("c1", "MC2MC", 1200, 400);
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
    hFSmc_EffMC_bin2->SetMinimum(0.6);
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
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend1 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend1->SetBorderSize(0);
    legend1->SetFillColor(0);
    legend1->SetFillStyle(0);
    legend1->AddEntry(hFSmc_EffMC_bin2, "FullSim MC");
    legend1->AddEntry(hAF2_mll80100_low_pT, "AF2 80 GeV < M_{ll} < 100 GeV");
    legend1->Draw();
    
    //
    // pad1down: bottom pad
    //
    pad1down->cd(); // pad1down becomes the current pad
    
    TH1F *frame1 = pad1down->DrawFrame(hAF2_mll80100->GetYaxis()->GetXmin(), 0.60, hAF2_mll80100->GetYaxis()->GetXmax(), 1.19);
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
    
    // Calculate the ratio between FullSim and AF2
    hFSmc_EffMC_bin2->Sumw2();
    hAF2_mll80100_low_pT->Sumw2();
    TH1F *ratio1_low_pT = (TH1F *)hAF2_mll80100_low_pT->Clone();
    ratio1_low_pT->Divide(hFSmc_EffMC_bin2);
    
    ratio1_low_pT->SetLineColor(kRed);
    ratio1_low_pT->SetLineWidth(1);
    ratio1_low_pT->SetMarkerColor(kRed);
    ratio1_low_pT->SetMarkerSize(0.7);
    ratio1_low_pT->SetMarkerStyle(20);
    ratio1_low_pT->Draw("E1,same");

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
    hFSmc_EffMC_bin8->SetMaximum(1.02);
    hFSmc_EffMC_bin8->SetMinimum(0.98);
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
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend2 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend2->SetBorderSize(0);
    legend2->SetFillColor(0);
    legend2->SetFillStyle(0);
    legend2->AddEntry(hFSmc_EffMC_bin8, "FullSim MC");
    legend2->AddEntry(hAF2_mll80100_medium_pT, "AF2 80 GeV < M_{ll} < 100 GeV");
    legend2->Draw();
    
    //
    // pad2down: bottom pad
    //
    pad2down->cd(); // pad2down becomes the current pad

    TH1F *frame2 = pad2down->DrawFrame(hAF2_mll80100->GetYaxis()->GetXmin(), 0.98, hAF2_mll80100->GetYaxis()->GetXmax(), 1.019);
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
    
    // Calculate the ratio between hOld and hNew
    hFSmc_EffMC_bin8->Sumw2();
    hAF2_mll80100_medium_pT->Sumw2();
    TH1F *ratio1_medium_pT = (TH1F *)hAF2_mll80100_medium_pT->Clone();
    ratio1_medium_pT->Divide(hFSmc_EffMC_bin8);
    
    ratio1_medium_pT->SetLineColor(kRed);
    ratio1_medium_pT->SetLineWidth(1);
    ratio1_medium_pT->SetMarkerColor(kRed);
    ratio1_medium_pT->SetMarkerSize(0.7);
    ratio1_medium_pT->SetMarkerStyle(20);
    ratio1_medium_pT->Draw("E1,same");
    
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
    pad3up->cd(); // pad1up becomes the current pad
    // Draw curve here
    hFSmc_EffMC_bin13->SetTitle(high_pT_range);
    hFSmc_EffMC_bin13->GetXaxis()->SetTitle("#eta");
    hFSmc_EffMC_bin13->GetYaxis()->SetTitle("Efficiency");
    hFSmc_EffMC_bin13->SetMaximum(1.02);
    hFSmc_EffMC_bin13->SetMinimum(0.98);
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
    
    //ATLASLabel(0.1, 0.85,"Internal");
    
    TLegend *legend3 = new TLegend(0.6, 0.6, 0.89, 0.89);
    legend3->SetBorderSize(0);
    legend3->SetFillColor(0);
    legend3->SetFillStyle(0);
    legend3->AddEntry(hFSmc_EffMC_bin13, "FullSim MC");
    legend3->AddEntry(hAF2_mll80100_high_pT, "AF2 80 GeV < M_{ll} < 100 GeV");
    legend3->Draw();
    
    //
    // pad3down: bottom pad
    //
    pad3down->cd(); // pad3down becomes the current pad
    
    TH1F *frame3 = pad3down->DrawFrame(hAF2_mll80100->GetYaxis()->GetXmin(), 0.98, hAF2_mll80100->GetYaxis()->GetXmax(), 1.019);
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
    
    // Calculate the ratio between hOld and hNew
    hFSmc_EffMC_bin13->Sumw2();
    hAF2_mll80100_high_pT->Sumw2();
    TH1F *ratio1_high_pT = (TH1F *)hAF2_mll80100_high_pT->Clone();
    ratio1_high_pT->Divide(hFSmc_EffMC_bin13);
    
    ratio1_high_pT->SetLineColor(kRed);
    ratio1_high_pT->SetLineWidth(1);
    ratio1_high_pT->SetMarkerColor(kRed);
    ratio1_high_pT->SetMarkerSize(0.7);
    ratio1_high_pT->SetMarkerStyle(20);
    ratio1_high_pT->Draw("E1,same");
    
    c1->Print("plots/mc2mc_" + folder + ".pdf");

}