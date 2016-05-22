// This script is used to make 1-dim ratio plots for single eta bin (project on eta axis).
// Compare MC and data efficiency of two files at the top pad and SFs at the bottom pad.
// The plot will include data and MC efficiency (for both files) at the top pad and SF (for both files) at the bottom pad.
// Usage: root -l myRatioPlotPt.C"(\"TightLLHMC15_v9\",\"isolTight\")"
//
//
////int eta = 11; // eta = 0-0.1
//int eta = 12; // eta = 0.1-0.6
////int eta = 13; // eta = 0.6-0.8
//int eta = 15; // eta = 1.15-1.37
//int eta = 18; // eta = 1.81-2.01
//int eta = 19; // eta = 2.01-2.37
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

void myOverlapTwoFilesPt(TString menu = "TightLLH_d0z0_v10",
                         TString iso  = "isolTight",
                         int eta = 1)
{
    // Set titles and axes scales for top pad (pad1)
    TString pad1_X_title = "E_{T} [MeV]";
    TString pad1_Y_title = "Efficiency";
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad2)
    TString pad2_X_title = "E_{T} [MeV]";
    TString pad2_Y_title = "Data/MC";
    double pad2_Y_max = 1.05;
    double pad2_Y_min = 0.95;

    SetAtlasStyle();

    TString folder;
    if (iso != "")
		folder = menu + "_" + iso;
    else
		folder = menu;

	TString fileName1 = "~/Desktop/v10/20160131/MC15bd0z0_ScaleFactors.root";

	TH2F *effdata1      = get13TeV2DHistogram(fileName1, menu, iso, "EffData_CentralValue");
	TH2F *effdata1_tot  = get13TeV2DHistogram(fileName1, menu, iso, "EffData_TotalError");
	TH2F *effdata1_stat = get13TeV2DHistogram(fileName1, menu, iso, "EffData_StatError");

	TH2F *effmc1      = get13TeV2DHistogram(fileName1, menu, iso, "EffMC_CentralValue");
	TH2F *effmc1_tot  = get13TeV2DHistogram(fileName1, menu, iso, "EffMC_TotalError");
	TH2F *effmc1_stat = get13TeV2DHistogram(fileName1, menu, iso, "EffMC_StatError");

	TH2F *sf1      = get13TeV2DHistogram(fileName1, menu, iso, "SF_CentralValue");
	TH2F *sf1_tot  = get13TeV2DHistogram(fileName1, menu, iso, "SF_TotalError");
	TH2F *sf1_stat = get13TeV2DHistogram(fileName1, menu, iso, "SF_StatError");

    // Remider:
    // x: pt
    // y: eta

    TH1F* pt1[3][30]; // keeps total uncertainties
    TH1F* pt1_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot1_err[3][30];
    TH1F* sys1_err[3][30];
    TH1F* stat1_err[3][30];

	// Fill the uncertainties to the histograms
    for (int eta = 0; eta < effdata1->GetYaxis()->GetNbins() + 1; eta++) {
		if (eta == 0) continue; // underflow bin
		// Data
		pt1[0][eta]       = (TH1F *)effdata1->ProjectionX("", eta, eta)->Clone();
		pt1_tmp[0][eta]   = (TH1F *)effdata1->ProjectionX("", eta, eta)->Clone();
		tot1_err[0][eta]  = (TH1F *)effdata1_tot->ProjectionX("", eta, eta)->Clone();
		stat1_err[0][eta] = (TH1F *)effdata1_stat->ProjectionX("", eta, eta)->Clone();
		fixHistogramError(pt1[0][eta],     tot1_err[0][eta]);	
		fixHistogramError(pt1_tmp[0][eta], stat1_err[0][eta]);	

	   	// MC
	   	pt1[1][eta]       = (TH1F *)effmc1->ProjectionX("", eta, eta)->Clone();
	   	pt1_tmp[1][eta]   = (TH1F *)effmc1->ProjectionX("", eta, eta)->Clone();
	   	tot1_err[1][eta]  = (TH1F *)effmc1_tot->ProjectionX("", eta, eta)->Clone();
	   	stat1_err[1][eta] = (TH1F *)effmc1_stat->ProjectionX("", eta, eta)->Clone();
	   	fixHistogramError(pt1[1][eta],     tot1_err[1][eta]);
	   	fixHistogramError(pt1_tmp[1][eta], stat1_err[1][eta]);

		// SF
		pt1[2][eta]       = (TH1F *)sf1->ProjectionX("", eta, eta)->Clone();
		pt1_tmp[2][eta]   = (TH1F *)sf1->ProjectionX("", eta, eta)->Clone();
		tot1_err[2][eta]  = (TH1F *)sf1_tot->ProjectionX("", eta, eta)->Clone();
		stat1_err[2][eta] = (TH1F *)sf1_stat->ProjectionX("", eta, eta)->Clone();	
		fixHistogramError(pt1[2][eta],     tot1_err[2][eta]);	
		fixHistogramError(pt1_tmp[2][eta], stat1_err[2][eta]);	
	}

//--------------------------------------------------

	TString fileName2 = "~/Desktop/v10/20160131/AF2d0z0_ScaleFactors.root";

	TH2F *effdata2      = get13TeV2DHistogram(fileName2, menu, iso, "EffData_CentralValue");
	TH2F *effdata2_tot  = get13TeV2DHistogram(fileName2, menu, iso, "EffData_TotalError");
	TH2F *effdata2_stat = get13TeV2DHistogram(fileName2, menu, iso, "EffData_StatError");

	TH2F *effmc2      = get13TeV2DHistogram(fileName2, menu, iso, "EffMC_CentralValue");
	TH2F *effmc2_tot  = get13TeV2DHistogram(fileName2, menu, iso, "EffMC_TotalError");
	TH2F *effmc2_stat = get13TeV2DHistogram(fileName2, menu, iso, "EffMC_StatError");

	TH2F *sf2      = get13TeV2DHistogram(fileName2, menu, iso, "SF_CentralValue");
	TH2F *sf2_tot  = get13TeV2DHistogram(fileName2, menu, iso, "SF_TotalError");
	TH2F *sf2_stat = get13TeV2DHistogram(fileName2, menu, iso, "SF_StatError");

    // Remider:
    // x: pt
    // y: eta

    TH1F* pt2[3][30]; // keeps total uncertainties
    TH1F* pt2_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot2_err[3][30];
    TH1F* sys2_err[3][30];
    TH1F* stat2_err[3][30];

	// Fill the uncertainties to the histograms
    for (int eta = 0; eta < effdata2->GetYaxis()->GetNbins() + 1; eta++) {
		if (eta == 0) continue; // underflow bin
		// Data
		pt2[0][eta]       = (TH1F *)effdata2->ProjectionX("", eta, eta)->Clone();
		pt2_tmp[0][eta]   = (TH1F *)effdata2->ProjectionX("", eta, eta)->Clone();
		tot2_err[0][eta]  = (TH1F *)effdata2_tot->ProjectionX("", eta, eta)->Clone();
		stat2_err[0][eta] = (TH1F *)effdata2_stat->ProjectionX("", eta, eta)->Clone();
		fixHistogramError(pt2[0][eta],     tot2_err[0][eta]);	
		fixHistogramError(pt2_tmp[0][eta], stat2_err[0][eta]);	

	   	// MC
	   	pt2[1][eta]       = (TH1F *)effmc2->ProjectionX("", eta, eta)->Clone();
	   	pt2_tmp[1][eta]   = (TH1F *)effmc2->ProjectionX("", eta, eta)->Clone();
	   	tot2_err[1][eta]  = (TH1F *)effmc2_tot->ProjectionX("", eta, eta)->Clone();
	   	stat2_err[1][eta] = (TH1F *)effmc2_stat->ProjectionX("", eta, eta)->Clone();
	   	fixHistogramError(pt2[1][eta],     tot2_err[1][eta]);
	   	fixHistogramError(pt2_tmp[1][eta], stat2_err[1][eta]);

		// SF
		pt2[2][eta]       = (TH1F *)sf2->ProjectionX("", eta, eta)->Clone();
		pt2_tmp[2][eta]   = (TH1F *)sf2->ProjectionX("", eta, eta)->Clone();
		tot2_err[2][eta]  = (TH1F *)sf2_tot->ProjectionX("", eta, eta)->Clone();
		stat2_err[2][eta] = (TH1F *)sf2_stat->ProjectionX("", eta, eta)->Clone();	
		fixHistogramError(pt2[2][eta],     tot2_err[2][eta]);	
		fixHistogramError(pt2_tmp[2][eta], stat2_err[2][eta]);	
	}

//--------------------------------------------------

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

    float high, low;
    FindOptimalRange(high, low, pt1[0][eta], pt2[0][eta]);
    pad1_Y_max = high;
    if (low < 0.)
        pad1_Y_min = 0.;
    else
        pad1_Y_min = low;

    // Set titles, maximum and minimum of axes
    pt1[0][eta]->GetXaxis()->SetTitle(pad1_X_title);
    pt1[0][eta]->GetYaxis()->SetTitle(pad1_Y_title);
    pt1[0][eta]->SetMaximum(pad1_Y_max);
   	pt1[0][eta]->SetMinimum(pad1_Y_min);

   	// file1
    // Data efficiency
	pt1[0][eta]->SetLineColor(kBlue);
	pt1[0][eta]->SetLineWidth(1);
	pt1[0][eta]->SetMarkerColor(kBlue);
	pt1[0][eta]->SetMarkerSize(1);
	pt1[0][eta]->SetMarkerStyle(kFullCircle);
	pt1[0][eta]->GetXaxis()->SetRangeUser(7000, 200000);
   	pt1[0][eta]->Draw("E1");
	// MC efficiency
    pt1[1][eta]->SetLineColor(kBlue);
   	pt1[1][eta]->SetLineWidth(1);
   	pt1[1][eta]->SetMarkerColor(kBlue);
   	pt1[1][eta]->SetMarkerSize(1);
   	pt1[1][eta]->SetMarkerStyle(kOpenCircle);
   	pt1[1][eta]->Draw("E1,SAME");

    // file2
    // Data efficiency
	pt2[0][eta]->SetLineColor(kRed);
	pt2[0][eta]->SetLineWidth(1);
	pt2[0][eta]->SetMarkerColor(kRed);
	pt2[0][eta]->SetMarkerSize(1);
	pt2[0][eta]->SetMarkerStyle(kFullCircle);
	pt2[0][eta]->GetXaxis()->SetRangeUser(7000, 200000);
   	pt2[0][eta]->Draw("E1,SAME");
    // MC efficiency
   	pt2[1][eta]->SetLineColor(kRed);
   	pt2[1][eta]->SetLineWidth(1);
   	pt2[1][eta]->SetMarkerColor(kRed);
   	pt2[1][eta]->SetMarkerSize(1);
   	pt2[1][eta]->SetMarkerStyle(kOpenCircle);
   	pt2[1][eta]->Draw("E1,SAME");

	TLine *line = new TLine(7000, 1., 200000, 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("same");

    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    myText(0.2,0.69,  kBlack, const_cast<char *>(folder.Data()));

	char name[100];
	sprintf(&name[0], "%.2f < #eta < %.2f", 
			effdata1->GetYaxis()->GetBinLowEdge(eta),
			effdata1->GetYaxis()->GetBinUpEdge(eta));
	myText(0.2, 0.61, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.7, 0.65, 0.9, 0.9);
	leg->AddEntry(pt1[1][eta], "MC15a", "lp");
	leg->AddEntry(pt1[0][eta], "Data (HIGG2D1)", "lp");
	leg->AddEntry(pt2[1][eta], "MC15b", "lp");
	leg->AddEntry(pt2[0][eta], "Data (EGAM1)", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad

    FindOptimalRange(high, low, pt1[2][eta], pt2[2][eta]);
    pad2_Y_max = high;
    if (low < 0.)
        pad2_Y_min = 0.;
    else
        pad2_Y_min = low;

	TH1F *frame_left = pad2->DrawFrame(7000, pad2_Y_min, 200000, pad2_Y_max);
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

    // file1
	// SF with total uncertianty as color band
	pt1[2][eta]->SetLineColor(kBlue);
	pt1[2][eta]->SetLineWidth(1);
	pt1[2][eta]->SetMarkerColor(kBlue);
	pt1[2][eta]->SetMarkerSize(1);
	pt1[2][eta]->SetMarkerStyle(20);
	pt1[2][eta]->SetFillStyle(3005); // with color band
	pt1[2][eta]->SetFillColor(kBlue);
   	pt1[2][eta]->Draw("E1,SAME");

	// SF with statistical uncertianty as color band
	pt1_tmp[2][eta]->SetLineColor(kBlue);
	pt1_tmp[2][eta]->SetLineWidth(1);
	pt1_tmp[2][eta]->SetMarkerColor(kBlue);
	pt1_tmp[2][eta]->SetMarkerSize(1);
	pt1_tmp[2][eta]->SetMarkerStyle(20);
   	pt1_tmp[2][eta]->Draw("E0,SAME");

    // file2
	pt2[2][eta]->SetLineColor(kRed);
	pt2[2][eta]->SetLineWidth(1);
	pt2[2][eta]->SetMarkerColor(kRed);
	pt2[2][eta]->SetMarkerSize(1);
	pt2[2][eta]->SetMarkerStyle(20);
	pt2[2][eta]->SetFillStyle(3004); // with color band
	pt2[2][eta]->SetFillColor(kRed);
   	pt2[2][eta]->Draw("E1,SAME");

	pt2_tmp[2][eta]->SetLineColor(kRed);
	pt2_tmp[2][eta]->SetLineWidth(1);
	pt2_tmp[2][eta]->SetMarkerColor(kRed);
	pt2_tmp[2][eta]->SetMarkerSize(1);
	pt2_tmp[2][eta]->SetMarkerStyle(20);
   	pt2_tmp[2][eta]->Draw("E0,SAME");

	// Add legend
	TLegend *leg_bottom = new TLegend(0.2, 0.75, 0.75, 0.9);
	leg_bottom-> SetNColumns(4);
	leg_bottom->AddEntry(pt1[2][eta], "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(pt1_tmp[2][eta], "Stat only", "l");
	leg_bottom->AddEntry(pt2[2][eta], "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(pt2_tmp[2][eta], "Stat only", "l");
	leg_bottom->SetBorderSize(0);
	leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
	leg_bottom->Draw();

	TString etaLowEdge = TString::Format("%.f", effdata1->GetYaxis()->GetBinLowEdge(eta)*100.);
	TString etaUpEdge  = TString::Format("%.f", effdata1->GetYaxis()->GetBinUpEdge(eta)*100.);

	c1->SaveAs("plots/overlap_eta" + etaLowEdge + "-" + etaUpEdge + "_" + folder + ".pdf", "pdf");
}
