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

void myRatioPlotPt(TString menu = "TightLLH_d0z0_v8",
				   TString iso  = "isolTight",
				   int deltaR = 21)
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

	TString fileName = "../ScaleFactors_rebin.root";

	TH2F *effdata      = get13TeV2DHistogram(fileName, menu, iso, "EffData_CentralValue_minDeltaR");
	TH2F *effdata_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffData_TotalError_minDeltaR");
	TH2F *effdata_stat = get13TeV2DHistogram(fileName, menu, iso, "EffData_StatError_minDeltaR");

	TH2F *effmc      = get13TeV2DHistogram(fileName, menu, iso, "EffMC_CentralValue_minDeltaR");
	TH2F *effmc_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffMC_TotalError_minDeltaR");
	TH2F *effmc_stat = get13TeV2DHistogram(fileName, menu, iso, "EffMC_StatError_minDeltaR");

	TH2F *sf      = get13TeV2DHistogram(fileName, menu, iso, "SF_CentralValue_minDeltaR");
	TH2F *sf_tot  = get13TeV2DHistogram(fileName, menu, iso, "SF_TotalError_minDeltaR");
	TH2F *sf_stat = get13TeV2DHistogram(fileName, menu, iso, "SF_StatError_minDeltaR");

    // Remider:
    // x: pt
    // y: deltaR

    TH1F* pt[3][100]; // keeps total uncertainties
    TH1F* pt_tmp[3][100]; // keeps statistical uncertainties
    TH1F* tot_err[3][100];
    TH1F* sys_err[3][100];
    TH1F* stat_err[3][100];

	// Fill the uncertainties to the histograms
    for (int deltaR = 0; deltaR < effdata->GetYaxis()->GetNbins() + 1; deltaR++) {
		if (deltaR == 0) continue; // underflow bin
		// Data
		pt[0][deltaR]       = (TH1F *)effdata->ProjectionX("", deltaR, deltaR)->Clone();
		pt_tmp[0][deltaR]   = (TH1F *)effdata->ProjectionX("", deltaR, deltaR)->Clone();
		tot_err[0][deltaR]  = (TH1F *)effdata_tot->ProjectionX("", deltaR, deltaR)->Clone();
		stat_err[0][deltaR] = (TH1F *)effdata_stat->ProjectionX("", deltaR, deltaR)->Clone();
		fixHistogramError(pt[0][deltaR],     tot_err[0][deltaR]);	
		fixHistogramError(pt_tmp[0][deltaR], stat_err[0][deltaR]);	

	   	// MC
	   	pt[1][deltaR]       = (TH1F *)effmc->ProjectionX("", deltaR, deltaR)->Clone();
	   	pt_tmp[1][deltaR]   = (TH1F *)effmc->ProjectionX("", deltaR, deltaR)->Clone();
	   	tot_err[1][deltaR]  = (TH1F *)effmc_tot->ProjectionX("", deltaR, deltaR)->Clone();
	   	stat_err[1][deltaR] = (TH1F *)effmc_stat->ProjectionX("", deltaR, deltaR)->Clone();
	   	fixHistogramError(pt[1][deltaR],     tot_err[1][deltaR]);
	   	fixHistogramError(pt_tmp[1][deltaR], stat_err[1][deltaR]);

		// SF
		pt[2][deltaR]       = (TH1F *)sf->ProjectionX("", deltaR, deltaR)->Clone();
		pt_tmp[2][deltaR]   = (TH1F *)sf->ProjectionX("", deltaR, deltaR)->Clone();
		tot_err[2][deltaR]  = (TH1F *)sf_tot->ProjectionX("", deltaR, deltaR)->Clone();
		stat_err[2][deltaR] = (TH1F *)sf_stat->ProjectionX("", deltaR, deltaR)->Clone();	
		fixHistogramError(pt[2][deltaR],     tot_err[2][deltaR]);	
		fixHistogramError(pt_tmp[2][deltaR], stat_err[2][deltaR]);	
	}
//pt[2][21]->Draw();
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
    FindOptimalRange(high, low, pt[0][deltaR], pt[1][deltaR]);
    pad1_Y_max = high;
    if (low < 0.) {
        pad1_Y_min = 0.;
    }
    else {
        pad1_Y_min = low;
    }

    // Set titles, maximum and minimum of axes
	pt[0][deltaR]->GetXaxis()->SetTitle(pad1_X_title);
   	pt[0][deltaR]->GetYaxis()->SetTitle(pad1_Y_title);
	//pt[0][deltaR]->SetMaximum(pad1_Y_max);
   	//pt[0][deltaR]->SetMinimum(pad1_Y_min);
	pt[0][deltaR]->SetMaximum(1.1);
   	pt[0][deltaR]->SetMinimum(0.81);

    // Data
	pt[0][deltaR]->SetLineColor(kBlue);
	pt[0][deltaR]->SetLineWidth(1);
	pt[0][deltaR]->SetMarkerColor(kBlue);
	pt[0][deltaR]->SetMarkerSize(1);
	pt[0][deltaR]->SetMarkerStyle(20);
	pt[0][deltaR]->GetXaxis()->SetRangeUser(7000, 125000);
   	pt[0][deltaR]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.

	// MC
   	pt[1][deltaR]->SetLineColor(kRed);
   	pt[1][deltaR]->SetLineWidth(1);
   	pt[1][deltaR]->SetMarkerColor(kRed);
   	pt[1][deltaR]->SetMarkerSize(1);
   	pt[1][deltaR]->SetMarkerStyle(kOpenCircle);
    pt[1][deltaR]->GetXaxis()->SetRangeUser(7000, 125000);
   	pt[1][deltaR]->Draw("E0,SAME");

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
			effdata->GetYaxis()->GetBinLowEdge(deltaR),
			effdata->GetYaxis()->GetBinUpEdge(deltaR));
	myText(0.2,0.70, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg->AddEntry(pt[0][deltaR], "Data", "lp");
	leg->AddEntry(pt[1][deltaR], "Z #rightarrow ee MC", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad

    FindOptimalRange(high, low, pt[2][deltaR], pt_tmp[2][deltaR]);
    pad2_Y_max = high;
    if (low < 0.) {
        pad2_Y_min = 0.;
    }
    else {
        pad2_Y_min = low;
    }

	//TH1F *frame_left = pad2->DrawFrame(7000, pad2_Y_min, 125000, pad2_Y_max);
	TH1F *frame_left = pad2->DrawFrame(7000, 0.89, 125000, 1.11);
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
	pt[2][deltaR]->SetLineColor(kOrange-3);
	pt[2][deltaR]->SetLineWidth(1);
	pt[2][deltaR]->SetMarkerColor(kBlack);
	pt[2][deltaR]->SetMarkerSize(1);
	pt[2][deltaR]->SetMarkerStyle(20);
	pt[2][deltaR]->SetFillStyle(1001); // with color band
	pt[2][deltaR]->SetFillColor(kOrange-3);
   	pt[2][deltaR]->Draw("E2,SAME"); // E2: Draw error bars with rectangles.

	// SF with statistical uncertianty as color band
	pt_tmp[2][deltaR]->SetLineColor(kBlack);
	pt_tmp[2][deltaR]->SetLineWidth(1);
	pt_tmp[2][deltaR]->SetMarkerColor(kBlack);
	pt_tmp[2][deltaR]->SetMarkerSize(1);
	pt_tmp[2][deltaR]->SetMarkerStyle(20);
   	pt_tmp[2][deltaR]->Draw("E0,SAME");

	// Add legend
	TLegend *leg_bottom = new TLegend(0.4, 0.8, 0.7, 0.95);
	leg_bottom-> SetNColumns(2);
	leg_bottom->AddEntry(pt[2][deltaR], "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(pt_tmp[2][deltaR], "Stat only", "l");
	leg_bottom->SetBorderSize(0);
	leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
	leg_bottom->Draw();

	TString deltaRLowEdge = TString::Format("%.f", effdata->GetYaxis()->GetBinLowEdge(deltaR)*100.);
	TString deltaRUpEdge  = TString::Format("%.f", effdata->GetYaxis()->GetBinUpEdge(deltaR)*100.);

	c1->SaveAs("plots/ratio_deltaR" + deltaRLowEdge + "-" + deltaRUpEdge + "_" + folder + ".pdf", "pdf");

}
