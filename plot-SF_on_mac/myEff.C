// This is used to make 1-dim efficiency plots with uncertainty for single pT bin.
// Usage: root -l myEff.C"(\"TightLLHMC15_v6\",\"isolTight\")"
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

void makePlot(TH1F *, TH1F *, TH1F *, TH1F *);

void myEff(TString menu = "TightLLH_d0z0_v8",
           TString iso  = "isolTight",
           int pt_bin   = 2)
{
	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

	TString fileName = "~/MC15bd0z0_ScaleFactors.root";

	TH2F *effdata      = get13TeV2DHistogram(fileName, menu, iso, "EffData_CentralValue");
	TH2F *effdata_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffData_TotalError");
	TH2F *effdata_stat = get13TeV2DHistogram(fileName, menu, iso, "EffData_StatError");

	TH2F *effmc      = get13TeV2DHistogram(fileName, menu, iso, "EffMC_CentralValue");
	TH2F *effmc_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffMC_TotalError");
	TH2F *effmc_stat = get13TeV2DHistogram(fileName, menu, iso, "EffMC_StatError");

	// Remider:
	// x: pt
	// y: eta

	TH1F* eta[2][30]; // keeps total uncertainties
	TH1F* eta_tmp[2][30]; // keeps statistical uncertainties
	TH1F* tot_err[2][30];
	TH1F* sys_err[2][30];
	TH1F* stat_err[2][30];

	// Fill the uncertainties to the histograms
	for (int pt_bin = 0; pt_bin < effdata->GetXaxis()->GetNbins() + 1; pt_bin++) {
		if (pt_bin == 0) continue; // underflow bin
		//if (pt_bin < 4) continue; // The plots are empty when pt_bin=1, 2, 3
		if (pt_bin < 2) continue; // The plots are empty when pt_bin=1
		// Data
		eta[0][pt_bin]      = (TH1F *)effdata->ProjectionY("", pt_bin, pt_bin)->Clone();
		eta_tmp[0][pt_bin]  = (TH1F *)effdata->ProjectionY("", pt_bin, pt_bin)->Clone();
		tot_err[0][pt_bin]  = (TH1F *)effdata_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
		stat_err[0][pt_bin] = (TH1F *)effdata_stat->ProjectionY("", pt_bin, pt_bin)->Clone();
		fixHistogramError(eta[0][pt_bin],     tot_err[0][pt_bin]);	
		fixHistogramError(eta_tmp[0][pt_bin], stat_err[0][pt_bin]);	

	   	// MC
	   	eta[1][pt_bin]      = (TH1F *)effmc->ProjectionY("", pt_bin, pt_bin)->Clone();
	   	eta_tmp[1][pt_bin]  = (TH1F *)effmc->ProjectionY("", pt_bin, pt_bin)->Clone();
	   	tot_err[1][pt_bin]  = (TH1F *)effmc_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
	   	stat_err[1][pt_bin] = (TH1F *)effmc_stat->ProjectionY("", pt_bin, pt_bin)->Clone();
	   	fixHistogramError(eta[1][pt_bin],     tot_err[1][pt_bin]);
	   	fixHistogramError(eta_tmp[1][pt_bin], stat_err[1][pt_bin]);
	}
 
	makePlot(eta[0][pt_bin], eta[1][pt_bin], eta_tmp[0][pt_bin], eta_tmp[1][pt_bin]);

	// This may cause problem becuse the canvas is variable defined in makePlot().
	myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));

	int pt_bin_low = static_cast<int>(effdata->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.);
	int pt_bin_up  = static_cast<int>(effdata->GetXaxis()->GetBinUpEdge(pt_bin)  / 1000.);
	char name[100];
	sprintf(&name[0], "%d < p_{T} < %d GeV", pt_bin_low, pt_bin_up);
	myText(0.2,0.77, kBlack, name);

	//c1->SaveAs("plots/Eff_pT" + TString::Itoa(pt_bin_low, 10) + "-" + TString::Itoa(pt_bin_up, 10) + "_" + folder + ".pdf", "pdf");
}

void makePlot(TH1F *hData, TH1F *hMC, TH1F* hData_stat, TH1F *hMC_stat)
{
	//SetAtlasStyle();

	// Big Canvas
	TCanvas* c1 = new TCanvas("c1");
	gStyle->SetOptStat(0);

	TString X_title = "#eta";
	float X_max = hData->GetXaxis()->GetXmax();
	float X_min = hData->GetXaxis()->GetXmin();

	TString Y_title = "Efficiency";
	double Y_max = 1.10;
	double Y_min = 0.91;

	float high, low;
	FindOptimalRange(high, low, hData, hMC);
	Y_max = high;
	if (low < 0.)
		Y_min = 0.;
	else
		Y_min = low;

	hData->SetTitle("");
	hData->SetXTitle(X_title);
	hData->SetYTitle(Y_title);
	//hData->GetXaxis()->SetRangeUser(X_min, X_max);
	hData->SetMaximum(Y_max);
	hData->SetMinimum(Y_min);

	// Data with total uncertainties
	hData->SetLineWidth(1);
	hData->SetLineColor(kYellow);
	hData->SetMarkerSize(1);
	hData->SetMarkerStyle(kFullCircle);
	hData->SetMarkerColor(kBlue);
	hData->SetFillStyle(1001); // Use total error as color band
	hData->SetFillColor(kYellow);
	hData->Draw("E2");

	// MC with total uncertainties
	hMC->SetLineWidth(1);
	hMC->SetLineColor(kRed);   	   	
   	hMC->SetMarkerSize(1);
   	hMC->SetMarkerStyle(kOpenCircle);
	hMC->SetMarkerColor(kRed);
   	hMC->Draw("SAME");

	// Data with statistical uncertainties
	hData_stat->SetLineWidth(1);
	hData_stat->SetLineColor(kBlue);
	hData_stat->SetMarkerSize(1);
	hData_stat->SetMarkerStyle(kFullCircle);
	hData_stat->SetMarkerColor(kBlue);
   	hData_stat->Draw("E1,SAME");

	// MC with statistical uncertainties
	hMC_stat->SetLineWidth(1);
	hMC_stat->SetLineColor(kRed);
   	hMC_stat->SetMarkerSize(1);
   	hMC_stat->SetMarkerStyle(kFullCircle);
	hMC_stat->SetMarkerColor(kRed);
   	hMC_stat->Draw("E1,same");

	TLine *line = new TLine(X_min, 1., X_max,1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");
/*
	myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));

	int pt_bin_low = static_cast<int>(effdata->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.);
	int pt_bin_up  = static_cast<int>(effdata->GetXaxis()->GetBinUpEdge(pt_bin)  / 1000.);
	char name[100];
	sprintf(&name[0], "%d < p_{T} < %d GeV", pt_bin_low, pt_bin_up);
	myText(0.2,0.77, kBlack, name);
*/
	// Add legend
	TLegend *legend = new TLegend(0.2, 0.6, 0.7, 0.75);
	legend->AddEntry(hMC, "Z #rightarrow ee MC", "lp");
	legend->AddEntry(hData, "Data (total. uncert.)", "pf");
	legend->AddEntry(hData_stat, "stat. uncert.", "lp");
	legend->SetBorderSize(0);
	legend->SetTextFont(42);
	legend->SetTextSize(0.04);
	legend->SetFillColor(0);
	legend->SetFillStyle(0);
	legend->Draw();
}
