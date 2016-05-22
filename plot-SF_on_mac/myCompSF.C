// This script is used to compare SF with and without background subtraction for single pT bin.
// Usage: root -l myCompSF.C"(\"TightLLHMC15_v9\",\"isolTight\")"
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"

#include <iostream>

void myCompSF(TString menu = "TightLLHMC15_v9",
			  TString iso  = "isolTight",
			  int pt = 2)
{
    SetAtlasStyle();

    TString folder;
    if (iso != "")
		folder = menu + "_" + iso;
    else
		folder = menu;

	TString fileName1 = "../output-SF/ScaleFactors.root";

	TH2F *sf1      = get13TeV2DHistogram(fileName1, menu, iso, "SF_CentralValue");
	TH2F *sf1_tot  = get13TeV2DHistogram(fileName1, menu, iso, "SF_TotalError");
	TH2F *sf1_stat = get13TeV2DHistogram(fileName1, menu, iso, "SF_StatError");

    TH1F* eta1[2][30]; // keeps total uncertainties
    TH1F* eta1_tmp[2][30]; // keeps statistical uncertainties
    TH1F* tot1_err[2][30];
    TH1F* sys1_err[2][30];
    TH1F* stat1_err[2][30];

    for (int pt = 0; pt < sf1->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
		eta1[0][pt]      = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
		eta1_tmp[0][pt]  = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
		tot1_err[0][pt]  = (TH1F *)sf1_tot->ProjectionY("", pt, pt)->Clone();
		stat1_err[0][pt] = (TH1F *)sf1_stat->ProjectionY("", pt, pt)->Clone();	
		fixHistogramError(eta1[0][pt],     tot1_err[0][pt]);	
		fixHistogramError(eta1_tmp[0][pt], stat1_err[0][pt]);	
	}

	TString fileName2 = "../output-simpleSF/ScaleFactors.root";

	TH2F *sf2      = get13TeV2DHistogram(fileName2, menu, iso, "SF_CentralValue");
	TH2F *sf2_tot  = get13TeV2DHistogram(fileName2, menu, iso, "SF_TotalError");
	TH2F *sf2_stat = get13TeV2DHistogram(fileName2, menu, iso, "SF_StatError");

    TH1F* eta2[2][30]; // keeps total uncertainties
    TH1F* eta2_tmp[2][30]; // keeps statistical uncertainties
    TH1F* tot2_err[2][30];
    TH1F* sys2_err[2][30];
    TH1F* stat2_err[2][30];

    for (int pt = 0; pt < sf2->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
		eta2[0][pt]      = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
		eta2_tmp[0][pt]  = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
		tot2_err[0][pt]  = (TH1F *)sf2_tot->ProjectionY("", pt, pt)->Clone();
		stat2_err[0][pt] = (TH1F *)sf2_stat->ProjectionY("", pt, pt)->Clone();	
		fixHistogramError(eta2[0][pt],     tot2_err[0][pt]);	
		fixHistogramError(eta2_tmp[0][pt], stat2_err[0][pt]);	
	}

	TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
	//int pt = 2; // pT = 7-10 GeV
	//int pt = 3; // pT = 10-15 GeV
	//int pt = 4; // pT = 15-20 GeV
	//int pt = 8; // pT = 35-40 GeV
	//int pt = 13; // pT = 80-150 GeV

	// simpleSF
	eta2[0][pt]->SetXTitle("#eta");
	eta2[0][pt]->SetYTitle("Scale Factor");
	if (pt == 2) eta2[0][pt]->SetMaximum(1.8);
   	if (pt == 2) eta2[0][pt]->SetMinimum(0.6);
	if (pt == 3) eta2[0][pt]->SetMaximum(1.2);
   	if (pt == 3) eta2[0][pt]->SetMinimum(0.8);
	if (pt > 3)  eta2[0][pt]->SetMaximum(1.05);
   	if (pt > 3)  eta2[0][pt]->SetMinimum(0.95);
	eta2[0][pt]->SetMarkerStyle(kFullTriangleUp);
	eta2[0][pt]->SetMarkerColor(kRed);
	eta2[0][pt]->SetLineColor(kRed);
	eta2[0][pt]->Draw("e0");

	// SF
	eta1[0][pt]->SetMarkerStyle(kOpenCircle);
	eta1[0][pt]->SetMarkerColor(kBlue);
	eta1[0][pt]->SetLineColor(kBlue);
	eta1[0][pt]->Draw("e0,same");

	myText(0.4, 0.85, kBlack, const_cast<char*>(folder.Data()));

	char name[100];
	sprintf(&name[0], "p_{T} bin: %d - %d GeV",
			static_cast<int>(sf1->GetXaxis()->GetBinLowEdge(pt) / 1000.),
			static_cast<int>(sf1->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
	myText(0.4, 0.77, kBlack, name);

	TLegend *leg = new TLegend(0.4, 0.6, 0.7, 0.75);
	leg->AddEntry(eta1[0][pt], "Data w/ bkg subtraction", "lp");
	leg->AddEntry(eta2[0][pt], "Data w/o bkg subtraction", "lp");
	leg->SetBorderSize(0);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	int ptLowEdge = static_cast<int>(sf1->GetXaxis()->GetBinLowEdge(pt) / 1000.);
	int ptUpEdge  = static_cast<int>(sf1->GetXaxis()->GetBinUpEdge(pt) / 1000.);

	c1->SaveAs("plots/CompSF_pT" + TString::Itoa(ptLowEdge,10) + "-" + TString::Itoa(ptUpEdge,10) + "_" + folder + ".pdf", "pdf");
}
