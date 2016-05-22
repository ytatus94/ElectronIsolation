// This script is used to make 1-dim projection plot. The selected pT bin is projected on the Eta axis.
// The plot compares the scale factors between with d0sig+z0 cuts and without d0sig+z0 cuts.
// Usage: root -l ompareSFWithAndWithougd0z0CutEta.C"(\"TightLLH\", \"isolTight\", 2)"
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

void compareSFWithAndWithougd0z0CutEta(TString menu = "TightLLH",
                                       TString iso  = "isolTight",
                                       int pt = 2)
{
	TString pad1_X_title = "#eta";
	TString pad1_Y_title = "Scale Factor";
	double pad1_Y_max = 1.10;
	double pad1_Y_min = 0.91;

	TString pad2_X_title = "#eta";
	TString pad2_Y_title = "w/(w/o)";
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

	TString fileName1 = "../output-SF/AF2d0z0_ScaleFactors.root";

	TH2F *effdata1      = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffData_CentralValue");
	TH2F *effdata1_tot  = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffData_TotalError");
	TH2F *effdata1_stat = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffData_StatError");

	TH2F *effmc1      = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffMC_CentralValue");
	TH2F *effmc1_tot  = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffMC_TotalError");
	TH2F *effmc1_stat = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffMC_StatError");

	TH2F *sf1      = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "SF_CentralValue");
	TH2F *sf1_tot  = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "SF_TotalError");
	TH2F *sf1_stat = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "SF_StatError");

    // Remider:
    // x: pt
    // y: eta

    TH1F* eta1[3][30]; // keeps total uncertainties
    TH1F* eta1_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot1_err[3][30];
    TH1F* sys1_err[3][30];
    TH1F* stat1_err[3][30];

	// Fill the uncertainties to the histograms
    for (int pt = 0; pt < effdata1->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
/*
		// Data
		eta1[0][pt]      = (TH1F *)effdata1->ProjectionY("", pt, pt)->Clone();
		eta1_tmp[0][pt]  = (TH1F *)effdata1->ProjectionY("", pt, pt)->Clone();
		tot1_err[0][pt]  = (TH1F *)effdata1_tot->ProjectionY("", pt, pt)->Clone();
		stat1_err[0][pt] = (TH1F *)effdata1_stat->ProjectionY("", pt, pt)->Clone();
		fixHistogramError(eta1[0][pt],     tot1_err[0][pt]);	
		fixHistogramError(eta1_tmp[0][pt], stat1_err[0][pt]);	

	   	// MC
	   	eta1[1][pt]      = (TH1F *)effmc1->ProjectionY("", pt, pt)->Clone();
	   	eta1_tmp[1][pt]  = (TH1F *)effmc1->ProjectionY("", pt, pt)->Clone();
	   	tot1_err[1][pt]  = (TH1F *)effmc1_tot->ProjectionY("", pt, pt)->Clone();
	   	stat1_err[1][pt] = (TH1F *)effmc1_stat->ProjectionY("", pt, pt)->Clone();
	   	fixHistogramError(eta1[1][pt],     tot1_err[1][pt]);
	   	fixHistogramError(eta1_tmp[1][pt], stat1_err[1][pt]);
*/
		// SF
		eta1[2][pt]      = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
		eta1_tmp[2][pt]  = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
		tot1_err[2][pt]  = (TH1F *)sf1_tot->ProjectionY("", pt, pt)->Clone();
		stat1_err[2][pt] = (TH1F *)sf1_stat->ProjectionY("", pt, pt)->Clone();	
		fixHistogramError(eta1[2][pt],     tot1_err[2][pt]);	
		fixHistogramError(eta1_tmp[2][pt], stat1_err[2][pt]);	
	}

//------------

	TString fileName2 = "../output-SF/AF2_ScaleFactors.root";

	TH2F *effdata2      = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "EffData_CentralValue");
	TH2F *effdata2_tot  = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "EffData_TotalError");
	TH2F *effdata2_stat = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "EffData_StatError");

	TH2F *effmc2      = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "EffMC_CentralValue");
	TH2F *effmc2_tot  = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "EffMC_TotalError");
	TH2F *effmc2_stat = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "EffMC_StatError");

	TH2F *sf2      = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "SF_CentralValue");
	TH2F *sf2_tot  = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "SF_TotalError");
	TH2F *sf2_stat = get13TeV2DHistogram(fileName2, menu + "MC15_v8", iso, "SF_StatError");

    TH1F* eta2[3][30]; // keeps total uncertainties
    TH1F* eta2_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot2_err[3][30];
    TH1F* sys2_err[3][30];
    TH1F* stat2_err[3][30];

    for (int pt = 0; pt < effdata2->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
/*
		// Data
		eta2[0][pt]      = (TH1F *)effdata2->ProjectionY("", pt, pt)->Clone();
		eta2_tmp[0][pt]  = (TH1F *)effdata2->ProjectionY("", pt, pt)->Clone();
		tot2_err[0][pt]  = (TH1F *)effdata2_tot->ProjectionY("", pt, pt)->Clone();
		stat2_err[0][pt] = (TH1F *)effdata2_stat->ProjectionY("", pt, pt)->Clone();
		fixHistogramError(eta2[0][pt],     tot2_err[0][pt]);	
		fixHistogramError(eta2_tmp[0][pt], stat2_err[0][pt]);	

	   	// MC
	   	eta2[1][pt]      = (TH1F *)effmc2->ProjectionY("", pt, pt)->Clone();
	   	eta2_tmp[1][pt]  = (TH1F *)effmc2->ProjectionY("", pt, pt)->Clone();
	   	tot2_err[1][pt]  = (TH1F *)effmc2_tot->ProjectionY("", pt, pt)->Clone();
	   	stat2_err[1][pt] = (TH1F *)effmc2_stat->ProjectionY("", pt, pt)->Clone();
	   	fixHistogramError(eta2[1][pt],     tot2_err[1][pt]);
	   	fixHistogramError(eta2_tmp[1][pt], stat2_err[1][pt]);
*/
		// SF
		eta2[2][pt]      = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
		eta2_tmp[2][pt]  = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
		tot2_err[2][pt]  = (TH1F *)sf2_tot->ProjectionY("", pt, pt)->Clone();
		stat2_err[2][pt] = (TH1F *)sf2_stat->ProjectionY("", pt, pt)->Clone();	
		fixHistogramError(eta2[2][pt],     tot2_err[2][pt]);	
		fixHistogramError(eta2_tmp[2][pt], stat2_err[2][pt]);	
	}

//------------

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

	// Set titles, maximum and minimum of axes
	eta1[2][pt]->SetXTitle(pad1_X_title);
	eta1[2][pt]->SetYTitle(pad1_Y_title);
    eta1[2][pt]->SetMaximum(pad1_Y_max);
   	eta1[2][pt]->SetMinimum(pad1_Y_min);

	// SF vs eta
	// with d0sig+z0 cuts
	eta1[2][pt]->SetLineColor(kBlue);
	eta1[2][pt]->SetLineWidth(1);
	eta1[2][pt]->SetMarkerColor(kBlue);
	eta1[2][pt]->SetMarkerSize(1);
	eta1[2][pt]->SetMarkerStyle(20);
   	eta1[2][pt]->Draw("e1");

	// without d0sig+z0 cuts
	eta2[2][pt]->SetLineColor(kRed);
	eta2[2][pt]->SetLineWidth(1);
	eta2[2][pt]->SetMarkerColor(kRed);
	eta2[2][pt]->SetMarkerSize(1);
	eta2[2][pt]->SetMarkerStyle(20);
   	eta2[2][pt]->Draw("e1,same");

	TLine *line = new TLine(eta1[2][pt]->GetXaxis()->GetXmin(), 1.,
                            eta1[2][pt]->GetXaxis()->GetXmax(), 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("same");

	myText(0.2, 0.85, kBlack, const_cast<char *>(menu.Data()));
	if (menu.Contains("LooseAndBLayer")) {
    	myText(0.5, 0.85, kBlack, const_cast<char *>(iso.Data()));
	}
	else {
		myText(0.4, 0.85, kBlack, const_cast<char *>(iso.Data()));
	}

	char name[100];
	sprintf(&name[0], "%d GeV < p_{T} < %d GeV", 
			static_cast<int>(effdata1->GetXaxis()->GetBinLowEdge(pt) / 1000.),
			static_cast<int>(effdata1->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
	myText(0.2, 0.78, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.2, 0.60, 0.6, 0.75);
	leg->AddEntry(eta1[2][pt], "w/ d0sig+z0 cuts", "lp");
	leg->AddEntry(eta2[2][pt], "w/o d0sig+z0 cuts", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad
	TH1F *frame_left;
	frame_left = pad2->DrawFrame(eta1[2][pt]->GetXaxis()->GetXmin(), pad2_Y_min, 
					 		     eta1[2][pt]->GetXaxis()->GetXmax(), pad2_Y_max);

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

	// Calculate the ratio between with and without d0sig+z0 cuts
	TH2F *ratio = (TH2F *)eta1[2][pt]->Clone();
	ratio->Divide(eta2[2][pt]);

	ratio->SetLineColor(kBlack);
	ratio->SetLineWidth(1);
	ratio->SetMarkerColor(kBlack);
	ratio->SetMarkerSize(1);
	ratio->SetMarkerStyle(20);
	ratio->Draw("E1,same");

	int ptLowEdge = static_cast<int>(effdata1->GetXaxis()->GetBinLowEdge(pt) / 1000.);
	int ptUpEdge  = static_cast<int>(effdata1->GetXaxis()->GetBinUpEdge(pt) / 1000.);

	c1->SaveAs("plots/comp_d0z0_AF2_pT" + TString::Itoa(ptLowEdge,10) + "-" + TString::Itoa(ptUpEdge,10) + "_" + folder + ".pdf", "pdf");
}