// This script is used to make 1-dim ratio plots for single deltaR bin (project on deltaR axis).
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
#include "FindOptimalRange.C"

#include <iostream>

void myRatioPlotPt_v3(TString menu, TString iso,
                      int pt_bin_lower, int pt_bin_upper,
                      int deltaR_bin_lower, int deltaR_bin_upper)
{
    // Set titles and axes scales for top pad (pad1)
    TString pad1_X_title = "E_{T} [MeV]";
    TString pad1_Y_title = "Efficiency";
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad2)
    TString pad2_X_title = "E_{T} [MeV]";
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

//--------------------

	TString fileName = "../output/ScaleFactors.root";

	TH2F *effdata      = get13TeV2DHistogram(fileName, menu, iso, "EffData_CentralValue_minDeltaR");
	TH2F *effdata_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffData_TotalError_minDeltaR");

	TH2F *effmc      = get13TeV2DHistogram(fileName, menu, iso, "EffMC_CentralValue_minDeltaR");
	TH2F *effmc_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffMC_TotalError_minDeltaR");

	TH2F *sf      = get13TeV2DHistogram(fileName, menu, iso, "SF_CentralValue_minDeltaR");
	TH2F *sf_tot  = get13TeV2DHistogram(fileName, menu, iso, "SF_TotalError_minDeltaR");

    // Remider:
    // x: pt
    // y: deltaR

    TH1F* pt[3]; // keeps total uncertainties
    TH1F* pt_tmp[3]; // keeps statistical uncertainties
    TH1F* tot_err[3];

	// Fill the uncertainties to the histograms
    // Data
	pt[0]       = (TH1F *)effdata->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
	pt_tmp[0]   = (TH1F *)effdata->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
	tot_err[0]  = (TH1F *)effdata_tot->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
	fixHistogramError(pt[0],     tot_err[0]);	

   	// MC
   	pt[1]       = (TH1F *)effmc->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
   	pt_tmp[1]   = (TH1F *)effmc->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
   	tot_err[1]  = (TH1F *)effmc_tot->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
   	fixHistogramError(pt[1],     tot_err[1]);

	// SF
	pt[2]       = (TH1F *)sf->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
	pt_tmp[2]   = (TH1F *)sf->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
	tot_err[2]  = (TH1F *)sf_tot->ProjectionX("", deltaR_bin_lower, deltaR_bin_upper - 1)->Clone();
	fixHistogramError(pt[2],     tot_err[2]);	

//--------------------

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

    float high = 0, low = 0;
    FindOptimalRange(high, low, pt[0], pt[1]);
    pad1_Y_max = high;
    if (low < 0.) {
        pad1_Y_min = 0.;
    }
    else {
        pad1_Y_min = low;
    }

    // Set titles, maximum and minimum of axes
	pt[0]->GetXaxis()->SetTitle(pad1_X_title);
   	pt[0]->GetYaxis()->SetTitle(pad1_Y_title);
	pt[0]->SetMaximum(pad1_Y_max);
   	pt[0]->SetMinimum(pad1_Y_min);

    // Data
	pt[0]->SetLineColor(kBlue);
	pt[0]->SetLineWidth(1);
	pt[0]->SetMarkerColor(kBlue);
	pt[0]->SetMarkerSize(1);
	pt[0]->SetMarkerStyle(20);
	pt[0]->GetXaxis()->SetRangeUser(7000, 125000);
   	pt[0]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.

	// MC
   	pt[1]->SetLineColor(kRed);
   	pt[1]->SetLineWidth(1);
   	pt[1]->SetMarkerColor(kRed);
   	pt[1]->SetMarkerSize(1);
   	pt[1]->SetMarkerStyle(kOpenCircle);
    pt[1]->GetXaxis()->SetRangeUser(7000, 125000);
   	pt[1]->Draw("E0,SAME");

    TLine *line = new TLine(7000, 1., 125000, 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");

	//myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
	ATLASLabel(0.2, 0.85,"Internal");
	myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

	char name[100];
	sprintf(&name[0], "%.2f < #Delta R < %.2f",
			effdata->GetYaxis()->GetBinLowEdge(deltaR_bin_lower),
			effdata->GetYaxis()->GetBinUpEdge(deltaR_bin_upper - 1));
	myText(0.2,0.70, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg->AddEntry(pt[0], "Data", "lp");
	leg->AddEntry(pt[1], "Z #rightarrow ee MC", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad

    FindOptimalRange(high, low, pt[2], pt_tmp[2]);
    pad2_Y_max = high;
    if (low < 0.) {
        pad2_Y_min = 0.;
    }
    else {
        pad2_Y_min = low;
    }

	//TH1F *frame_left = pad2->DrawFrame(7000, pad2_Y_min, 125000, pad2_Y_max);
	TH1F *frame_left = pad2->DrawFrame(7000, 0.8, 125000, 1.2);
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
	pt[2]->SetLineColor(kOrange-3);
	pt[2]->SetLineWidth(1);
	pt[2]->SetMarkerColor(kBlack);
	pt[2]->SetMarkerSize(1);
	pt[2]->SetMarkerStyle(20);
	pt[2]->SetFillStyle(1001); // with color band
	pt[2]->SetFillColor(kOrange-3);
   	pt[2]->Draw("E2,SAME"); // E2: Draw error bars with rectangles.

	// SF with statistical uncertianty as color band
	pt_tmp[2]->SetLineColor(kBlack);
	pt_tmp[2]->SetLineWidth(1);
	pt_tmp[2]->SetMarkerColor(kBlack);
	pt_tmp[2]->SetMarkerSize(1);
	pt_tmp[2]->SetMarkerStyle(20);
   	pt_tmp[2]->Draw("E0,SAME");

	// Add legend
	TLegend *leg_bottom = new TLegend(0.4, 0.8, 0.7, 0.95);
	leg_bottom-> SetNColumns(2);
	leg_bottom->AddEntry(pt[2], "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(pt_tmp[2], "Stat only", "l");
	leg_bottom->SetBorderSize(0);
	leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
	leg_bottom->Draw();

	TString deltaRLowEdge = TString::Format("%.f", effdata->GetYaxis()->GetBinLowEdge(deltaR_bin_lower)*100.);
	TString deltaRUpEdge  = TString::Format("%.f", effdata->GetYaxis()->GetBinUpEdge(deltaR_bin_upper -1)*100.);

	c1->SaveAs("plots/ratio_deltaR" + deltaRLowEdge + "-" + deltaRUpEdge + "_" + folder + ".pdf", "pdf");
}
