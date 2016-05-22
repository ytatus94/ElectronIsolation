// This script is used to make 1-dim ratio plots for single pT bin (project on eta axis).
// Usage: root -l myRatioPlotEta.C"(\"TightLLH_d0z0_v8\",\"isolTight\",2)"
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

void myRatioPlotEta(TString menu = "TightLLH_d0z0_v8",
					TString iso  = "isolTight",
					int pt = 2)
{
    // Set titles and axes scales for top pad (pad1)
    TString pad1_X_title = "#eta";
    //TString pad1_Y_title = "Efficiency";
    TString pad1_Y_title = "Electron isolation efficiency";
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad2)
    TString pad2_X_title = "#eta";
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

    TH1F* eta[3][30]; // keeps total uncertainties
    TH1F* eta_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot_err[3][30];
    TH1F* sys_err[3][30];
    TH1F* stat_err[3][30];

	// Fill the uncertainties to the histograms
    for (int pt = 0; pt < effdata->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
		// Data
		eta[0][pt]      = (TH1F *)effdata->ProjectionY("", pt, pt)->Clone();
		eta_tmp[0][pt]  = (TH1F *)effdata->ProjectionY("", pt, pt)->Clone();
		tot_err[0][pt]  = (TH1F *)effdata_tot->ProjectionY("", pt, pt)->Clone();
		stat_err[0][pt] = (TH1F *)effdata_stat->ProjectionY("", pt, pt)->Clone();
		fixHistogramError(eta[0][pt],     tot_err[0][pt]);	
		fixHistogramError(eta_tmp[0][pt], stat_err[0][pt]);	

	   	// MC
	   	eta[1][pt]      = (TH1F *)effmc->ProjectionY("", pt, pt)->Clone();
	   	eta_tmp[1][pt]  = (TH1F *)effmc->ProjectionY("", pt, pt)->Clone();
	   	tot_err[1][pt]  = (TH1F *)effmc_tot->ProjectionY("", pt, pt)->Clone();
	   	stat_err[1][pt] = (TH1F *)effmc_stat->ProjectionY("", pt, pt)->Clone();
	   	fixHistogramError(eta[1][pt],     tot_err[1][pt]);
	   	fixHistogramError(eta_tmp[1][pt], stat_err[1][pt]);

		// SF
		eta[2][pt]      = (TH1F *)sf->ProjectionY("", pt, pt)->Clone();
		eta_tmp[2][pt]  = (TH1F *)sf->ProjectionY("", pt, pt)->Clone();
		tot_err[2][pt]  = (TH1F *)sf_tot->ProjectionY("", pt, pt)->Clone();
		stat_err[2][pt] = (TH1F *)sf_stat->ProjectionY("", pt, pt)->Clone();	
		fixHistogramError(eta[2][pt],     tot_err[2][pt]);	
		fixHistogramError(eta_tmp[2][pt], stat_err[2][pt]);	
	}

//--------------------

	//int pt = 2; // pT = 7-10 GeV
	//int pt = 3; // pT = 10-15 GeV
	//int pt = 4; // pT = 15-20 GeV
	//int pt = 8; // pT = 35-40 GeV
	//int pt = 13; // pT = 80-150 GeV

    // Big Canvas
    TCanvas* c1 = new TCanvas(folder, folder, 600, 600);

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

    float high, low;
    FindOptimalRange(high, low, eta[0][pt], eta[1][pt]);
    pad1_Y_max = high;
    if (low < 0.) {
        pad1_Y_min = 0.;
    }
    else {
        pad1_Y_min = low;
    }

	// Set titles, maximum and minimum of axes
	eta[0][pt]->GetXaxis()->SetTitle(pad1_X_title);
   	eta[0][pt]->GetYaxis()->SetTitle(pad1_Y_title);
	//eta[0][pt]->SetMaximum(pad1_Y_max);
   	//eta[0][pt]->SetMinimum(pad1_Y_min);
	eta[0][pt]->SetMaximum(1.2);
   	eta[0][pt]->SetMinimum(0.8);

    // Data
	eta[0][pt]->SetLineColor(kBlue);
	eta[0][pt]->SetLineWidth(1);
	eta[0][pt]->SetMarkerColor(kBlue);
	eta[0][pt]->SetMarkerSize(1);
	eta[0][pt]->SetMarkerStyle(kFullCircle);
   	eta[0][pt]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.

	// MC
   	eta[1][pt]->SetLineColor(kRed);
   	eta[1][pt]->SetLineWidth(2);
   	eta[1][pt]->SetMarkerColor(kRed);
   	eta[1][pt]->SetMarkerSize(1);
   	eta[1][pt]->SetMarkerStyle(kOpenCircle);
   	eta[1][pt]->Draw("E0,SAME");

	TLine *line = new TLine(eta[0][pt]->GetXaxis()->GetXmin(), 1.,
                            eta[0][pt]->GetXaxis()->GetXmax(), 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");

	//myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
	ATLASLabel(0.2, 0.85,"Internal");
	myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

	char name[100];
	sprintf(&name[0], "%d GeV < E_{T} < %d GeV",
			static_cast<int>(effdata->GetXaxis()->GetBinLowEdge(pt) / 1000.),
			static_cast<int>(effdata->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
	myText(0.2,0.70, kBlack, name);
    
	// Add legend
	TLegend *leg = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg->AddEntry(eta[0][pt], "Data", "lp");
	leg->AddEntry(eta[1][pt], "Z #rightarrow ee MC", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad

    FindOptimalRange(high, low, eta[2][pt], eta_tmp[2][pt]);
    pad2_Y_max = high;
    if (low < 0.) {
        pad2_Y_min = 0.;
    }
    else {
        pad2_Y_min = low;
    }

	TH1F *frame_left;
	frame_left = pad2->DrawFrame(eta[2][pt]->GetXaxis()->GetXmin(), pad2_Y_min,
					 		     eta[2][pt]->GetXaxis()->GetXmax(), pad2_Y_max);
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
	eta[2][pt]->SetLineColor(kOrange-3);
	eta[2][pt]->SetLineWidth(1);
	eta[2][pt]->SetMarkerColor(kBlack);
	eta[2][pt]->SetMarkerSize(1);
	eta[2][pt]->SetMarkerStyle(20);
	eta[2][pt]->SetFillStyle(1001); // with color band
	eta[2][pt]->SetFillColor(kOrange-3);
   	eta[2][pt]->Draw("E2,SAME"); // E2: Draw error bars with rectangles.

	// SF with statistical uncertianty as color band
	eta_tmp[2][pt]->SetLineColor(kBlack);
	eta_tmp[2][pt]->SetLineWidth(1);
	eta_tmp[2][pt]->SetMarkerColor(kBlack);
	eta_tmp[2][pt]->SetMarkerSize(1);
	eta_tmp[2][pt]->SetMarkerStyle(20);
   	eta_tmp[2][pt]->Draw("E0,SAME");

	// Add legend
	TLegend *leg_bottom = new TLegend(0.4, 0.82, 0.7, 0.95);
	leg_bottom-> SetNColumns(2);
	leg_bottom->AddEntry(eta[2][pt], "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(eta_tmp[2][pt], "Stat only", "l");
	leg_bottom->SetBorderSize(0);
	leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
	leg_bottom->Draw();

	int ptLowEdge = static_cast<int>(effdata->GetXaxis()->GetBinLowEdge(pt) / 1000.);
	int ptUpEdge  = static_cast<int>(effdata->GetXaxis()->GetBinUpEdge(pt) / 1000.);

	c1->SaveAs("plots/ratio_pT" + TString::Itoa(ptLowEdge, 10) + "-" + TString::Itoa(ptUpEdge, 10) + "_" + folder + ".pdf", "pdf");
}
