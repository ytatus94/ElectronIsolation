// This is used to make the weighted efficiency plots
// Usage: root myWeightedEff.C"(\"TightLLHMC15_v6\",\"isolTight\")
// 
// 
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"

#include <iostream>
using namespace std;

void myWeightedEff(TString menu = "TightLLH_d0z0_v8",
				   TString iso  = "isolTight")
{
	gROOT->Reset();

	SetAtlasStyle();

	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

    // 25 ns
	TString fileName0 = "~/MC15bd0z0_ScaleFactors.root";

	TH2F *effdata0      = get13TeV2DHistogram(fileName0, menu, iso, "EffData_CentralValue");
	TH2F *effdata0_stat = get13TeV2DHistogram(fileName0, menu, iso, "EffData_StatError");
	TH2F *effdata0_syst = get13TeV2DHistogram(fileName0, menu, iso, "EffData_SystError");
	TH2F *effdata0_tot  = get13TeV2DHistogram(fileName0, menu, iso, "EffData_TotalError");

	TH2F *effmc0      = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_CentralValue");
	TH2F *effmc0_stat = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_StatError");
	TH2F *effmc0_syst = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_SystError");
	TH2F *effmc0_tot  = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_TotalError");

	// Remider:
	// x: pt
	// y: eta

	// calculate weighted mean
	float weighted_mean, weighted_stat, weighted_syst, weight;
	
	// Efficiencies

	// Get a empty 1D histogram which has the same structure as efficiencies projection to Y axis.
	TH1F *weighted_effdata_eta = (TH1F *)effdata0->ProjectionY()->Clone();
	weighted_effdata_eta->Reset();

	TH1F *weighted_effmc_eta = (TH1F *)effmc0->ProjectionY()->Clone();
	weighted_effmc_eta->Reset();

	// Project on eta axis.
	// for central value
	for (int i = 1; i < effdata0->GetYaxis()->GetNbins() + 1; i++) {
		weighted_mean = 0;
		weighted_stat = 0;
		weighted_syst = 0;
		weight = 0;
		for (int j = 1; j < effdata0->GetYaxis()->GetNbins() + 1; j++) {
			float effdata_value = effdata0->GetBinContent(j, i);
			float effdata_stat_value = effdata0_stat->GetBinContent(j, i);
			float effdata_syst_value = effdata0_syst->GetBinContent(j, i);
			if (effdata_stat_value > 1 || effdata_stat_value <= 0) continue;
			weighted_mean += effdata_value * (1 / effdata_stat_value);
			weighted_stat += effdata_stat_value * (1 / effdata_stat_value);
			weighted_syst += effdata_stat_value * (1 / effdata_stat_value);
			weight += (1 / effdata_stat_value);
		}
		weighted_effdata_eta->SetBinContent(i, weighted_mean / weight);
		float weighted_tot = sqrt(pow(weighted_stat / weight, 2) + pow(weighted_syst / weight, 2));
		weighted_effdata_eta->SetBinError(i, weighted_tot);
    }
    
    weighted_effdata_eta->SetXTitle("#eta");
    weighted_effdata_eta->SetYTitle("Efficiency");
    weighted_effdata_eta->SetMaximum(1.05);
    weighted_effdata_eta->SetMinimum(0.90);
    weighted_effdata_eta->GetXaxis()->SetRangeUser(weighted_effdata_eta->GetXaxis()->GetXmin(), weighted_effdata_eta->GetXaxis()->GetXmax());
    weighted_effdata_eta->SetLineColor(kBlue);
    weighted_effdata_eta->SetLineWidth(1);
    weighted_effdata_eta->SetMarkerStyle(kFullCircle);
    weighted_effdata_eta->SetMarkerSize(1);
    weighted_effdata_eta->SetMarkerColor(kBlue);

	for (int i = 1; i < effmc0->GetYaxis()->GetNbins() + 1; i++) {
		weighted_mean = 0;
		weighted_stat = 0;
		weighted_syst = 0;
		weight = 0;
		for (int j = 1; j < effmc0->GetYaxis()->GetNbins() + 1; j++) {
			float effmc_value = effmc0->GetBinContent(j, i);
			float effmc_stat_value = effmc0_stat->GetBinContent(j, i);
			float effmc_syst_value = effmc0_syst->GetBinContent(j, i);
			if (effmc_stat_value > 1 || effmc_stat_value <= 0) continue;
			weighted_mean += effmc_value * (1 / effmc_stat_value);
			weighted_stat += effmc_stat_value * (1 / effmc_stat_value);
			weighted_syst += effmc_stat_value * (1 / effmc_stat_value);
			weight += (1 / effmc_stat_value);
		}
		weighted_effmc_eta->SetBinContent(i, weighted_mean / weight);
		float weighted_tot = sqrt(pow(weighted_stat / weight, 2) + pow(weighted_syst / weight, 2));
		weighted_effmc_eta->SetBinError(i, weighted_tot);
    }
    
    weighted_effmc_eta->SetXTitle("#eta");
    weighted_effmc_eta->SetYTitle("Efficiency");
    weighted_effmc_eta->SetMaximum(1.05);
    weighted_effmc_eta->SetMinimum(0.90);
    weighted_effmc_eta->GetXaxis()->SetRangeUser(weighted_effmc_eta->GetXaxis()->GetXmin(), weighted_effmc_eta->GetXaxis()->GetXmax());
    weighted_effmc_eta->SetLineColor(kRed);
    weighted_effmc_eta->SetLineWidth(1);
    weighted_effmc_eta->SetMarkerStyle(kFullCircle);
    weighted_effmc_eta->SetMarkerSize(1);
    weighted_effmc_eta->SetMarkerColor(kRed);
    weighted_effmc_eta->Draw();

    //--------------------------------------------------//

	// Get a empty 1D histogram which has the same structure as efficiencies projection to X axis.
	TH1F *weighted_effdata_pt  = (TH1F *)effdata0->ProjectionX()->Clone();
	weighted_effdata_pt->Reset();

	TH1F *weighted_effmc_pt  = (TH1F *)effmc0->ProjectionX()->Clone();
	weighted_effmc_pt->Reset();

	// Projection on pT axis.
	// for central value
	for (int i = 1; i < effdata0->GetXaxis()->GetNbins() + 1; i++) {
		weighted_mean = 0;
		weighted_stat = 0;
		weighted_syst = 0;
		weight = 0;
		float ptLowEdge = effdata0->GetXaxis()->GetBinLowEdge(i) / 1000.;
		if (ptLowEdge > 5.) {
			for (int j = 1; j < effdata0->GetYaxis()->GetNbins() + 1; j++) {
				float effdata_value = effdata0->GetBinContent(i, j);
				float effdata_stat_value = effdata0_stat->GetBinContent(i, j);
				float effdata_syst_value = effdata0_syst->GetBinContent(i, j);
				if (effdata_stat_value >1 || effdata_stat_value <= 0) continue;
				weighted_mean += effdata_value * (1 / effdata_stat_value);
				weighted_stat += effdata_stat_value * (1 / effdata_stat_value);
				weighted_syst += effdata_syst_value * (1 / effdata_stat_value);
				weight += (1 / effdata_stat_value);
			}
			weighted_effdata_pt->SetBinContent(i, weighted_mean / weight);
			float weighted_tot = sqrt(pow(weighted_stat / weight, 2) + pow(weighted_syst / weight, 2));
			weighted_effdata_pt->SetBinError(i, weighted_tot);
        }
    }

    weighted_effdata_pt->SetXTitle("p_{T} [MeV]");
    weighted_effdata_pt->SetYTitle("Efficiency");
    weighted_effdata_pt->GetXaxis()->SetRangeUser(5000, weighted_effdata_pt->GetXaxis()->GetXmax());
    weighted_effdata_pt->SetMaximum(1.05);
    weighted_effdata_pt->SetMinimum(0.90);
    weighted_effdata_pt->SetLineColor(kBlue);
    weighted_effdata_pt->SetLineWidth(1);
    weighted_effdata_pt->SetMarkerStyle(kFullCircle);
    weighted_effdata_pt->SetMarkerSize(1);
    weighted_effdata_pt->SetMarkerColor(kBlue);
    //weighted_effdata_pt->Draw();

	for (int i = 1; i < effmc0->GetXaxis()->GetNbins() + 1; i++) {
		weighted_mean = 0;
		weighted_stat = 0;
		weighted_syst = 0;
		weight = 0;
		float ptLowEdge = effmc0->GetXaxis()->GetBinLowEdge(i) / 1000.;
		if (ptLowEdge > 5.) {
			for (int j = 1; j < effmc0->GetYaxis()->GetNbins() + 1; j++) {
				float effmc_value = effmc0->GetBinContent(i, j);
				float effmc_stat_value = effmc0_stat->GetBinContent(i, j);
				float effmc_syst_value = effmc0_syst->GetBinContent(i, j);
				if (effmc_stat_value >1 || effmc_stat_value <= 0) continue;
				weighted_mean += effmc_value * (1 / effmc_stat_value);
				weighted_stat += effmc_stat_value * (1 / effmc_stat_value);
				weighted_syst += effmc_syst_value * (1 / effmc_stat_value);
				weight += (1 / effmc_stat_value);
			}
			weighted_effmc_pt->SetBinContent(i, weighted_mean / weight);
			float weighted_tot = sqrt(pow(weighted_stat / weight, 2) + pow(weighted_syst / weight, 2));
			weighted_effmc_pt->SetBinError(i, weighted_tot);
        }
    }

    weighted_effmc_pt->SetXTitle("p_{T} [MeV]");
    weighted_effmc_pt->SetYTitle("Efficiency");
	weighted_effmc_pt->GetXaxis()->SetRangeUser(5000, weighted_effmc_pt->GetXaxis()->GetXmax());
	weighted_effmc_pt->SetMaximum(1.05);
	weighted_effmc_pt->SetMinimum(0.90);
	weighted_effmc_pt->SetLineColor(kRed);
	weighted_effmc_pt->SetLineWidth(1);
	weighted_effmc_pt->SetMarkerStyle(kFullCircle);
	weighted_effmc_pt->SetMarkerSize(1);
	weighted_effmc_pt->SetMarkerColor(kRed);
    //weighted_effmc_pt->Draw();

    //--------------------------------------------------//
/*
	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
	c1->Divide(2, 1);

	c1->cd(1);
	gPad->SetRightMargin(2);
	weighted_effdata_eta->SetTitle(folder);
	weighted_effdata_eta->Draw("E1");
	weighted_effmc_eta->Draw("E1,SAME");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

	TLine *line1 = new TLine(weighted_effdata_eta->GetXaxis()->GetXmin(), 1.,
                             weighted_effdata_eta->GetXaxis()->GetXmax(), 1.);
	line1->SetLineColor(kBlack);
	line1->SetLineStyle(2);
	line1->SetLineWidth(1);
	line1->Draw("SAME");

	c1->cd(2);
	gPad->SetRightMargin(2);
	weighted_effdata_pt->SetTitle(folder);
	weighted_effmc_pt->Draw("e0");
	weighted_effdata_pt->Draw("e0,same");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

	TLine *line2 = new TLine(weighted_effdata_pt->GetXaxis()->GetXmin(), 1.,
                             weighted_effdata_pt->GetXaxis()->GetXmax(), 1.);
	line2->SetLineColor(kBlack);
	line2->SetLineStyle(2);
	line2->SetLineWidth(1);
	line2->Draw("same");
*/
	//c1->SaveAs("plots/Eff_projection_" + folder + ".pdf", "pdf");

}
