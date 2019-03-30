// This script is used to make 1-dim ratio plots for single eta bin (project on eta axis).
// Usage: root -l myRatioPlotPt.C"(\"TightLLHMC15_v9\",\"isolTight\")"
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#include <TLine.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"

#include <iostream>

void myRatioPlotPt(TString menu = "TightLLHMC15_v9",
                   TString iso  = "isolTight",
                   int eta = 1)
{
    TString pad1_X_title = "p_{T} [MeV]";
    TString pad1_Y_title = "Efficiency";
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;

    TString pad2_X_title = "p_{T} [MeV]";
    TString pad2_Y_title = "Data / MC";
    double pad2_Y_max = 1.05;
    double pad2_Y_min = 0.95;

    if (iso.Contains("Fixed")) {
        pad1_Y_max = 1.10;
        pad1_Y_min = 0.91;
        pad2_Y_max = 1.05;
        pad2_Y_min = 0.95;
    }

    SetAtlasStyle();

    TString folder;
    if (iso != "")
        folder = menu + "_" + iso;
    else
        folder = menu;

    TString fileName = "~/ScaleFactors.root";

    TH2F *effdata      = get13TeV2DHistogram(fileName, menu, iso, "EffData_CentralValue");
    TH2F *effdata_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffData_TotalError");
    TH2F *effdata_stat = get13TeV2DHistogram(fileName, menu, iso, "EffData_StatError");

    TH2F *effmc      = get13TeV2DHistogram(fileName, menu, iso, "EffMC_CentralValue");
    TH2F *effmc_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffMC_TotalError");
    TH2F *effmc_stat = get13TeV2DHistogram(fileName, menu, iso, "EffMC_StatError");

    TH2F *sf      = get13TeV2DHistogram(fileName, menu, iso, "SF_CentralValue");
    TH2F *sf_tot  = get13TeV2DHistogram(fileName, menu, iso, "SF_TotalError");
    TH2F *sf_stat = get13TeV2DHistogram(fileName, menu, iso, "SF_StatError");

    // Remider:
    // x: pt
    // y: eta

    TH1F* pt[3][30]; // keeps total uncertainties
    TH1F* pt_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot_err[3][30];
    TH1F* sys_err[3][30];
    TH1F* stat_err[3][30];

    // Fill the uncertainties to the histograms
    for (int eta = 0; eta < effdata->GetYaxis()->GetNbins() + 1; eta++) {
        if (eta == 0) continue; // underflow bin
        // Data
        pt[0][eta]       = (TH1F *)effdata->ProjectionX("", eta, eta)->Clone();
        pt_tmp[0][eta]   = (TH1F *)effdata->ProjectionX("", eta, eta)->Clone();
        tot_err[0][eta]  = (TH1F *)effdata_tot->ProjectionX("", eta, eta)->Clone();
        stat_err[0][eta] = (TH1F *)effdata_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt[0][eta],     tot_err[0][eta]);
        fixHistogramError(pt_tmp[0][eta], stat_err[0][eta]);

        // MC
        pt[1][eta]       = (TH1F *)effmc->ProjectionX("", eta, eta)->Clone();
        pt_tmp[1][eta]   = (TH1F *)effmc->ProjectionX("", eta, eta)->Clone();
        tot_err[1][eta]  = (TH1F *)effmc_tot->ProjectionX("", eta, eta)->Clone();
        stat_err[1][eta] = (TH1F *)effmc_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt[1][eta],     tot_err[1][eta]);
        fixHistogramError(pt_tmp[1][eta], stat_err[1][eta]);

        // SF
        pt[2][eta]       = (TH1F *)sf->ProjectionX("", eta, eta)->Clone();
        pt_tmp[2][eta]   = (TH1F *)sf->ProjectionX("", eta, eta)->Clone();
        tot_err[2][eta]  = (TH1F *)sf_tot->ProjectionX("", eta, eta)->Clone();
        stat_err[2][eta] = (TH1F *)sf_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt[2][eta],     tot_err[2][eta]);
        fixHistogramError(pt_tmp[2][eta], stat_err[2][eta]);
    }

    ////int eta = 11; // eta = 0-0.1
    //int eta = 12; // eta = 0.1-0.6
    ////int eta = 13; // eta = 0.6-0.8
    //int eta = 15; // eta = 1.15-1.37
    //int eta = 18; // eta = 1.81-2.01
    //int eta = 19; // eta = 2.01-2.37

    // Big Canvas
    TCanvas* c1 = new TCanvas(folder, folder, 600, 600);

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    pad1->SetRightMargin(0.08);
    //pad1->SetGridy(); // grid lines
    //pad1->SetLogx();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetRightMargin(0.08);
    pad2->SetGridy(); // grid lines
    //pad2->SetLogx();
    pad2->Draw();

    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here

    // Set titles, maximum and minimum of axes
    pt[0][eta]->GetXaxis()->SetTitle(pad1_X_title);
    pt[0][eta]->GetYaxis()->SetTitle(pad1_Y_title);
    pt[0][eta]->SetMaximum(pad1_Y_max);
    pt[0][eta]->SetMinimum(pad1_Y_min);

    // Data with total uncertianty as color band
    pt[0][eta]->SetLineColor(kBlue);
    pt[0][eta]->SetLineWidth(1);
    pt[0][eta]->SetMarkerColor(kBlue);
    pt[0][eta]->SetMarkerSize(1);
    pt[0][eta]->SetMarkerStyle(20);
    pt[0][eta]->GetXaxis()->SetRangeUser(7000, 150000);
    pt[0][eta]->Draw("e0");

    // MC
    pt[1][eta]->SetLineColor(kRed);
    pt[1][eta]->SetLineWidth(1);
    pt[1][eta]->SetMarkerColor(kRed);
    pt[1][eta]->SetMarkerSize(1);
    pt[1][eta]->SetMarkerStyle(kOpenCircle);
    pt[1][eta]->GetXaxis()->SetRangeUser(7000, 150000);
    pt[1][eta]->Draw("e0,same");

    TLine *line = new TLine(7000, 1., 150000, 1.);
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->Draw("same");

    myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));

    char name[100];
    sprintf(&name[0], "%.2f < #eta < %.2f",
            effdata->GetYaxis()->GetBinLowEdge(eta),
            effdata->GetYaxis()->GetBinUpEdge(eta));
    myText(0.2,0.77, kBlack, name);

    // Add legend
    TLegend *leg = new TLegend(0.2, 0.6, 0.7, 0.75);
    leg->AddEntry(pt[1][eta], "Z #rightarrow ee MC", "lp");
    leg->AddEntry(pt[0][eta], "Data", "lp");
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    pad2->cd(); // pad2 becomes the current pad
	
    TH1F *frame_left = pad2->DrawFrame(7000, pad2_Y_min, 150000, pad2_Y_max);
    frame_left->GetXaxis()->SetNdivisions(510);
    frame_left->GetYaxis()->SetNdivisions(405);
    frame_left->SetLineWidth(1);
    frame_left->SetXTitle(pad2_X_title);
    frame_left->GetXaxis()->SetTitleSize(20);
    frame_left->GetXaxis()->SetTitleFont(47);
    frame_left->GetXaxis()->SetTitleOffset(3.0);
    frame_left->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame_left->GetXaxis()->SetLabelSize(16);
    frame_left->SetYTitle(pad2_Y_title);
    frame_left->GetYaxis()->SetTitleSize(17);
    frame_left->GetYaxis()->SetTitleFont(43);
    frame_left->GetYaxis()->SetTitleOffset(2.0);
    frame_left->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame_left->GetYaxis()->SetLabelSize(16);
    frame_left->Draw();

    // SF with total uncertianty as color band
    pt[2][eta]->SetLineColor(kOrange-3);
    pt[2][eta]->SetLineWidth(1);
    pt[2][eta]->SetMarkerColor(kBlack);
    pt[2][eta]->SetMarkerSize(1);
    pt[2][eta]->SetMarkerStyle(20);
    pt[2][eta]->SetFillStyle(1001); // with color band
    pt[2][eta]->SetFillColor(kOrange-3);
    pt[2][eta]->Draw("e2,same");

    // SF with statistical uncertianty as color band
    pt_tmp[2][eta]->SetLineColor(kBlack);
    pt_tmp[2][eta]->SetLineWidth(1);
    pt_tmp[2][eta]->SetMarkerColor(kBlack);
    pt_tmp[2][eta]->SetMarkerSize(1);
    pt_tmp[2][eta]->SetMarkerStyle(20);
    pt_tmp[2][eta]->Draw("e0,same");

    // Add legend
    TLegend *leg_bottom = new TLegend(0.4, 0.8, 0.7, 0.95);
    leg_bottom-> SetNColumns(2);
    leg_bottom->AddEntry(pt[2][eta], "Stat #oplus Syst", "pf");
    leg_bottom->AddEntry(pt_tmp[2][eta], "Stat only", "l");
    leg_bottom->SetBorderSize(0);
    leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
    leg_bottom->Draw();

    TString etaLowEdge = TString::Format("%.f", effdata->GetYaxis()->GetBinLowEdge(eta)*100.);
    TString etaUpEdge  = TString::Format("%.f", effdata->GetYaxis()->GetBinUpEdge(eta)*100.);

    //c1->SaveAs("plots/ratio_eta" + etaLowEdge + "-" + etaUpEdge + "_" + folder + ".pdf", "pdf");
    c1->SaveAs("plots/MC15b_ratio_eta" + etaLowEdge + "-" + etaUpEdge + "_" + folder + ".pdf", "pdf");
}
