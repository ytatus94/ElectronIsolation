// This is used to make the plots of projection of scale factor on eta and pt axis.
// Usage: root myWeightedSF.C"(\"TightLLHMC15_v6\",\"isolTight\")
// 
// 
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"

#include <iostream>

void myWeightedSF(TString menu = "TightLLHMC15_v8",
				  TString iso = "isolTight")
{
	gROOT->Reset();

	SetAtlasStyle();

	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

	// 
	TString fileName0 = "../output/ScaleFactors.root";

	TH2F *sf0      = get13TeV2DHistogram(fileName0, menu, iso, "SF_CentralValue");
	TH2F *sf0_stat = get13TeV2DHistogram(fileName0, menu, iso, "SF_StatError");
	TH2F *sf0_syst = get13TeV2DHistogram(fileName0, menu, iso, "SF_SystError");
	TH2F *sf0_tot  = get13TeV2DHistogram(fileName0, menu, iso, "SF_TotalError");

	// Remider:
	// x: pt
	// y: eta

	// calculate weighted mean
	float weighted_mean, weighted_stat, weighted_syst, weight;
	
	// Get a empty 1D histogram which has the same structure as sf projection to Y axis.
	TH1F *weighted_sf_eta = (TH1F *)sf0->ProjectionY()->Clone();
	weighted_sf_eta->Reset();

	// Project on eta axis.
	// for central value
	for (int i = 1; i < sf0->GetYaxis()->GetNbins() + 1; i++) {
		weighted_mean = 0;
		weighted_stat = 0;
		weighted_syst = 0;
		weight = 0;
		//float etaLowEdge = sf0->GetYaxis()->GetBinLowEdge(i);
		for (int j = 1; j < sf0->GetXaxis()->GetNbins() + 1; j++) {
			//if (j == 13) continue; // skip the last pT bin
			float sf_value = sf0->GetBinContent(j, i);
			float sf_stat_value = sf0_stat->GetBinContent(j, i);
			float sf_syst_value = sf0_syst->GetBinContent(j, i);
			if (sf_stat_value > 1 || sf_stat_value <= 0) continue;
			weighted_mean += sf_value * (1 / sf_stat_value);
			weighted_stat += sf_stat_value * (1 / sf_stat_value);
			weighted_syst += sf_syst_value * (1 / sf_stat_value);
			weight += (1 / sf_stat_value);
		}
		weighted_sf_eta->SetBinContent(i, weighted_mean / weight);
		float weighted_tot = sqrt(pow(weighted_stat / weight, 2) + pow(weighted_syst / weight, 2));
		weighted_sf_eta->SetBinError(i, weighted_tot);
		
		weighted_sf_eta->SetXTitle("#eta");
		weighted_sf_eta->GetXaxis()->SetRangeUser(weighted_sf_eta->GetXaxis()->GetXmin(), weighted_sf_eta->GetXaxis()->GetXmax());
		weighted_sf_eta->SetYTitle("Scale Factors");
		weighted_sf_eta->SetMaximum(1.05);
		weighted_sf_eta->SetMinimum(0.95);
		weighted_sf_eta->SetLineColor(kBlack);
		weighted_sf_eta->SetLineWidth(1);
		weighted_sf_eta->SetMarkerStyle(20);
		weighted_sf_eta->SetMarkerSize(1);
		weighted_sf_eta->SetMarkerColor(kBlack);
	}

	// Get a empty 1D histogram which has the same structure as sf projection to X axis.
	TH1F *weighted_sf_pt  = (TH1F *)sf0->ProjectionX()->Clone();
	weighted_sf_pt->Reset();

	// Projection on pT axis.
	// for central value
	for (int i = 1; i < sf0->GetXaxis()->GetNbins() + 1; i++) {
		weighted_mean = 0;
		weighted_stat = 0;
		weighted_syst = 0;
		weight = 0;
		float ptLowEdge = sf0->GetXaxis()->GetBinLowEdge(i) / 1000.;
		if (ptLowEdge > 5.) {
			for (int j = 1; j < sf0->GetYaxis()->GetNbins() + 1; j++) {
				float sf_value = sf0->GetBinContent(i, j);
				float sf_stat_value = sf0_stat->GetBinContent(i, j);
				float sf_syst_value = sf0_syst->GetBinContent(i, j);
				if (sf_stat_value >1 || sf_stat_value <= 0) continue;
				weighted_mean += sf_value * (1 / sf_stat_value);
				weighted_stat += sf_stat_value * (1 / sf_stat_value);
				weighted_syst += sf_syst_value * (1 / sf_stat_value);
				weight += (1 / sf_stat_value);
			}
			weighted_sf_pt->SetBinContent(i, weighted_mean / weight);
			float weighted_tot = sqrt(pow(weighted_stat / weight, 2) + pow(weighted_syst / weight, 2));
			weighted_sf_pt->SetBinError(i, weighted_tot);

			weighted_sf_pt->SetXTitle("p_{T} [MeV]");
			weighted_sf_pt->GetXaxis()->SetRangeUser(5000, weighted_sf_pt->GetXaxis()->GetXmax());
			weighted_sf_pt->SetYTitle("Scale Factors");
			weighted_sf_pt->SetMaximum(1.05);
			weighted_sf_pt->SetMinimum(0.95);
			weighted_sf_pt->SetLineColor(kBlack);
			weighted_sf_pt->SetLineWidth(1);
			weighted_sf_pt->SetMarkerStyle(20);
			weighted_sf_pt->SetMarkerSize(1);
			weighted_sf_pt->SetMarkerColor(kBlack);
		}
	}

	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
	c1->Divide(2, 1);

	c1->cd(1);
	gPad->SetRightMargin(2);
	weighted_sf_eta->SetTitle(folder);
	weighted_sf_eta->Draw("e1");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

	c1->cd(2);
	gPad->SetRightMargin(2);
	weighted_sf_pt->SetTitle(folder);
	weighted_sf_pt->Draw("e0");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

/*
	TLegend *leg = new TLegend(0.3, 0.8, 0.7, 0.89);
	leg->AddEntry(weighted_presf, "pre-recommendation", "l");
	leg->AddEntry(weighted_sf, "13TeV 50ns data", "l");
	leg->SetTextSize(0.028);
	leg->Draw("same");
*/

	c1->SaveAs("plots/SF_projection_" + folder + ".pdf", "pdf");
}
