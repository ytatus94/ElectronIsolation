// This is used to make 1-dim scale factor plots with uncertainty for single pT bin.
// Usage: root -l mySF.C"(\"TightLLHMC15_v6\",\"isolTight\")"
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
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
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

void makePlot(TH1F *, TH1F *);

void mySF(TString menu = "TightLLH_d0z0_v8",
          TString iso  = "isolTight",
          int pt_bin   = 2)
{
	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

	TString fileName = "~/MC15bd0z0_ScaleFactors.root";

	TH2F *sf      = get13TeV2DHistogram(fileName, menu, iso, "SF_CentralValue");
	TH2F *sf_tot  = get13TeV2DHistogram(fileName, menu, iso, "SF_TotalError");
	TH2F *sf_stat = get13TeV2DHistogram(fileName, menu, iso, "SF_StatError");

	// Remider:
	// x: pt
	// y: eta

	TH1F* eta[2][30]; // keeps total uncertainties
	TH1F* eta_tmp[2][30]; // keeps statistical uncertainties
	TH1F* tot_err[2][30];
	TH1F* sys_err[2][30];
	TH1F* stat_err[2][30];

	// Fill the uncertainties to the histograms
	for (int pt_bin = 0; pt_bin < sf->GetXaxis()->GetNbins() + 1; pt_bin++) {
		if (pt_bin == 0) continue; // underflow bin
		//if (pt_bin < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt_bin < 2) continue; // The plots are empty when pt=1
		eta[0][pt_bin]      = (TH1F *)sf->ProjectionY("", pt_bin, pt_bin)->Clone();
		eta_tmp[0][pt_bin]  = (TH1F *)sf->ProjectionY("", pt_bin, pt_bin)->Clone();
		tot_err[0][pt_bin]  = (TH1F *)sf_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
		stat_err[0][pt_bin] = (TH1F *)sf_stat->ProjectionY("", pt_bin, pt_bin)->Clone();	
		fixHistogramError(eta[0][pt_bin],     tot_err[0][pt_bin]);	
		fixHistogramError(eta_tmp[0][pt_bin], stat_err[0][pt_bin]);	
	}

	makePlot(eta[0][pt_bin], eta_tmp[0][pt_bin]);

	// This may cause problem becuse the canvas is variable defined in makePlot().
	myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));

	int pt_bin_low = static_cast<int>(sf->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.);
	int pt_bin_up  = static_cast<int>(sf->GetXaxis()->GetBinUpEdge(pt_bin)  / 1000.);
	char name[100];
	sprintf(&name[0], "%d < p_{T} < %d GeV", pt_bin_low, pt_bin_up);
	myText(0.2,0.77, kBlack, name);

	//c1->SaveAs("plots/SF_pT" + TString::Itoa(pt_bin_low, 10) + "-" + TString::Itoa(pt_bin_up, 10) + "_" + folder + ".pdf", "pdf");
}

void makePlot(TH1F *hSF, TH1F *hSF_stat)
{
	// Big Canvas
	TCanvas* c1 = new TCanvas("c1");
	gStyle->SetOptStat(0);

	TString X_title = "#eta";
	float X_max = hSF->GetXaxis()->GetXmax();
	float X_min = hSF->GetXaxis()->GetXmin();

	TString Y_title = "Scale Facotr";
	double Y_max = 1.10;
	double Y_min = 0.91;

	float high, low;
	FindOptimalRange(high, low, hSF);
	Y_max = high;
	if (low < 0.)
		Y_min = 0.;
	else
		Y_min = low;

	hSF->SetTitle("");
	hSF->SetXTitle(X_title);
	hSF->SetYTitle(Y_title);
	//hSF->GetXaxis()->SetRangeUser(X_min, X_max);
	hSF->SetMaximum(Y_max);
	hSF->SetMinimum(Y_min);

	// SF with total uncertainties
	hSF->SetLineWidth(1);
	hSF->SetLineColor(kYellow);
	hSF->SetMarkerSize(1);
	hSF->SetMarkerStyle(kFullCircle);
	hSF->SetMarkerColor(kBlue);
	hSF->SetFillStyle(1001); // Use total error as color band
	hSF->SetFillColor(kYellow);
	hSF->Draw("E2");

	// SF with statistical uncertainties
	hSF_stat->SetLineWidth(1);
	hSF_stat->SetLineColor(kBlue);
	hSF_stat->SetMarkerSize(1);
	hSF_stat->SetMarkerStyle(kFullCircle);
	hSF_stat->SetMarkerColor(kBlue);
   	hSF_stat->Draw("E1,SAME");

	TLine *line = new TLine(X_min, 1., X_max,1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");
/*
	myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));

	int pt_bin_low = static_cast<int>(sf->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.);
	int pt_bin_up  = static_cast<int>(sf->GetXaxis()->GetBinUpEdge(pt_bin)  / 1000.);
	char name[100];
	sprintf(&name[0], "%d < p_{T} < %d GeV", pt_bin_low, pt_bin_up);
	myText(0.2,0.77, kBlack, name);
*/
	// Add legend
	TLegend *legend = new TLegend(0.2, 0.6, 0.7, 0.75);
	legend->AddEntry(hSF, "Data (total. uncert.)", "pf");
	legend->AddEntry(hSF_stat, "stat. uncert.", "l");
	legend->SetBorderSize(0);
	legend->SetTextFont(42);
	legend->SetTextSize(0.04);
	legend->SetFillColor(0);
	legend->SetFillStyle(0);
	legend->Draw();
}
