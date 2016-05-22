// This script is used to make 1-dim ratio plots for single pT bin (project on eta axis).
// Compare MC and data efficiency of two files at the top pad and SFs at the bottom pad.
// The plot will include data and MC efficiency (for both files) at the top pad and SF (for both files) at the bottom pad.
// Usage: root -l myOverlapTwoFilesEta.C"(\"TightLLHMC15_v9\",\"isolTight\")"
//
//
//int pt = 2; // pT = 7-10 GeV
//int pt = 3; // pT = 10-15 GeV
//int pt = 4; // pT = 15-20 GeV
//int pt = 8; // pT = 35-40 GeV
//int pt = 13; // pT = 80-150 GeV
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
using namespace std;

void myOverlapTwoFilesEta(TString menu = "TightLLH_d0z0_v10",
                          TString iso  = "isolFixedCutLoose",
                          int pt = 2)
{
    // Set titles and axes scales for top pad (pad1)
    TString pad1_X_title = "#eta";
    TString pad1_Y_title = "Efficiency";
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad2)
    TString pad2_X_title = "#eta";
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

		// SF
		eta1[2][pt]      = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
		eta1_tmp[2][pt]  = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
		tot1_err[2][pt]  = (TH1F *)sf1_tot->ProjectionY("", pt, pt)->Clone();
		stat1_err[2][pt] = (TH1F *)sf1_stat->ProjectionY("", pt, pt)->Clone();	
		fixHistogramError(eta1[2][pt],     tot1_err[2][pt]);	
		fixHistogramError(eta1_tmp[2][pt], stat1_err[2][pt]);	
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

    TH1F* eta2[3][30]; // keeps total uncertainties
    TH1F* eta2_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot2_err[3][30];
    TH1F* sys2_err[3][30];
    TH1F* stat2_err[3][30];

    for (int pt = 0; pt < effdata2->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
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

		// SF
		eta2[2][pt]      = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
		eta2_tmp[2][pt]  = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
		tot2_err[2][pt]  = (TH1F *)sf2_tot->ProjectionY("", pt, pt)->Clone();
		stat2_err[2][pt] = (TH1F *)sf2_stat->ProjectionY("", pt, pt)->Clone();	
		fixHistogramError(eta2[2][pt],     tot2_err[2][pt]);	
		fixHistogramError(eta2_tmp[2][pt], stat2_err[2][pt]);	
	}

//--------------------------------------------------

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
    FindOptimalRange(high, low, eta1[0][pt], eta2[0][pt]);
    pad1_Y_max = high;
    if (low < 0.)
        pad1_Y_min = 0.;
    else
        pad1_Y_min = low;

	// Set titles, maximum and minimum of axes
	eta1[0][pt]->GetXaxis()->SetTitle(pad1_X_title);
   	eta1[0][pt]->GetYaxis()->SetTitle(pad1_Y_title);
	eta1[0][pt]->SetMaximum(pad1_Y_max);
   	eta1[0][pt]->SetMinimum(pad1_Y_min);

    // file1
    // Data efficiency
	eta1[0][pt]->SetLineColor(kBlue);
	eta1[0][pt]->SetLineWidth(1);
	eta1[0][pt]->SetMarkerColor(kBlue);
	eta1[0][pt]->SetMarkerSize(1);
	eta1[0][pt]->SetMarkerStyle(kFullCircle);
   	eta1[0][pt]->Draw("E1");
	// MC efficiency
   	eta1[1][pt]->SetLineColor(kBlue);
   	eta1[1][pt]->SetLineWidth(1);
   	eta1[1][pt]->SetMarkerColor(kBlue);
   	eta1[1][pt]->SetMarkerSize(1);
   	eta1[1][pt]->SetMarkerStyle(kOpenCircle);
   	eta1[1][pt]->Draw("E1,SAME");

    // file2
    // Data efficiency
	eta2[0][pt]->SetLineColor(kRed);
	eta2[0][pt]->SetLineWidth(1);
	eta2[0][pt]->SetMarkerColor(kRed);
	eta2[0][pt]->SetMarkerSize(1);
	eta2[0][pt]->SetMarkerStyle(kFullCircle);
   	eta2[0][pt]->Draw("E1,SAME");
    // MC efficiency
   	eta2[1][pt]->SetLineColor(kRed);
   	eta2[1][pt]->SetLineWidth(1);
   	eta2[1][pt]->SetMarkerColor(kRed);
   	eta2[1][pt]->SetMarkerSize(1);
   	eta2[1][pt]->SetMarkerStyle(kOpenCircle);
   	eta2[1][pt]->Draw("E1,SAME");

	TLine *line = new TLine(eta1[0][pt]->GetXaxis()->GetXmin(), 1.,
                            eta1[0][pt]->GetXaxis()->GetXmax(), 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");

    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
	myText(0.2, 0.69,  kBlack, const_cast<char *>(folder.Data()));

	char name[100];
	sprintf(&name[0], "%d GeV < E_{T} < %d GeV",
			static_cast<int>(effdata1->GetXaxis()->GetBinLowEdge(pt) / 1000.),
			static_cast<int>(effdata1->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
	myText(0.2, 0.61, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.7, 0.65, 0.9, 0.9);
	leg->AddEntry(eta1[1][pt], "MC15a", "lp");
	leg->AddEntry(eta1[0][pt], "Data (HIGG2D1)", "lp");
	leg->AddEntry(eta2[1][pt], "MC15b", "lp");
	leg->AddEntry(eta2[0][pt], "Data (EGAM1)", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad

    FindOptimalRange(high, low, eta1[2][pt], eta2[2][pt]);
    pad2_Y_max = high;
    if (low < 0.)
        pad2_Y_min = 0.;
    else
        pad2_Y_min = low;

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

    // file1
	// SF with total uncertianty as color band
	eta1[2][pt]->SetLineColor(kBlue);
	eta1[2][pt]->SetLineWidth(1);
	eta1[2][pt]->SetMarkerColor(kBlue);
	eta1[2][pt]->SetMarkerSize(1);
	eta1[2][pt]->SetMarkerStyle(kFullCircle);
	eta1[2][pt]->SetFillStyle(3005); // with color band
	eta1[2][pt]->SetFillColor(kBlue);
   	eta1[2][pt]->Draw("E2,SAME");

	// SF with statistical uncertianty as color band
	eta1_tmp[2][pt]->SetLineColor(kBlue);
	eta1_tmp[2][pt]->SetLineWidth(1);
	eta1_tmp[2][pt]->SetMarkerColor(kBlue);
	eta1_tmp[2][pt]->SetMarkerSize(1);
	eta1_tmp[2][pt]->SetMarkerStyle(kFullCircle);
   	eta1_tmp[2][pt]->Draw("E0,SAME");

    // file2
	eta2[2][pt]->SetLineColor(kRed);
	eta2[2][pt]->SetLineWidth(1);
	eta2[2][pt]->SetMarkerColor(kRed);
	eta2[2][pt]->SetMarkerSize(1);
	eta2[2][pt]->SetMarkerStyle(kFullCircle);
	eta2[2][pt]->SetFillStyle(3004); // with color band
	eta2[2][pt]->SetFillColor(kRed);
   	eta2[2][pt]->Draw("E2,SAME");

	eta2_tmp[2][pt]->SetLineColor(kRed);
	eta2_tmp[2][pt]->SetLineWidth(1);
	eta2_tmp[2][pt]->SetMarkerColor(kRed);
	eta2_tmp[2][pt]->SetMarkerSize(1);
	eta2_tmp[2][pt]->SetMarkerStyle(kFullCircle);
   	eta2_tmp[2][pt]->Draw("E0,SAME");

	// Add legend
	TLegend *leg_bottom = new TLegend(0.2, 0.75, 0.75, 0.9);
	leg_bottom-> SetNColumns(4);
	leg_bottom->AddEntry(eta1[2][pt], "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(eta1_tmp[2][pt], "Stat only", "l");
	leg_bottom->AddEntry(eta2[2][pt], "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(eta2_tmp[2][pt], "Stat only", "l");
	leg_bottom->SetBorderSize(0);
	leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
	leg_bottom->Draw();

	int ptLowEdge = static_cast<int>(effdata1->GetXaxis()->GetBinLowEdge(pt) / 1000.);
	int ptUpEdge  = static_cast<int>(effdata1->GetXaxis()->GetBinUpEdge(pt) / 1000.);

	c1->SaveAs("plots/overlap_pT" + TString::Itoa(ptLowEdge,10) + "-" + TString::Itoa(ptUpEdge,10) + "_" + folder + ".pdf", "pdf");
}
