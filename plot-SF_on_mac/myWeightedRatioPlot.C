// This is used to make the weighted ratio plots
// Usage: root myWeightedRatioPlot.C"(\"TightLLHMC15_v6\",\"isolTight\")
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
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"

#include <iostream>

void myWeightedRatioPlot(TString menu = "TightLLHMC15_v8",
						 TString iso = "isolTight")
{
	gROOT->Reset();

	SetAtlasStyle();

	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

    // 25 ns
	TString fileName0 = "../output/ScaleFactors.root";

	TH2F *effdata0      = get13TeV2DHistogram(fileName0, menu, iso, "EffData_CentralValue");
	TH2F *effdata0_stat = get13TeV2DHistogram(fileName0, menu, iso, "EffData_StatError");
	TH2F *effdata0_syst = get13TeV2DHistogram(fileName0, menu, iso, "EffData_SystError");
	TH2F *effdata0_tot  = get13TeV2DHistogram(fileName0, menu, iso, "EffData_TotalError");

	TH2F *effmc0      = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_CentralValue");
	TH2F *effmc0_stat = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_StatError");
	TH2F *effmc0_syst = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_SystError");
	TH2F *effmc0_tot  = get13TeV2DHistogram(fileName0, menu, iso, "EffMC_TotalError");

	TH2F *sf0      = get13TeV2DHistogram(fileName0, menu, iso, "SF_CentralValue");
	TH2F *sf0_stat = get13TeV2DHistogram(fileName0, menu, iso, "SF_StatError");
	TH2F *sf0_syst = get13TeV2DHistogram(fileName0, menu, iso, "SF_SystError");
	TH2F *sf0_tot  = get13TeV2DHistogram(fileName0, menu, iso, "SF_TotalError");

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

		weighted_effdata_eta->SetXTitle("#eta");
		weighted_effdata_eta->GetXaxis()->SetRangeUser(weighted_effdata_eta->GetXaxis()->GetXmin(), weighted_effdata_eta->GetXaxis()->GetXmax());
		weighted_effdata_eta->SetYTitle("Efficiency");
		weighted_effdata_eta->SetMaximum(1.05);
		weighted_effdata_eta->SetMinimum(0.901);
		weighted_effdata_eta->SetLineColor(kBlue);
		weighted_effdata_eta->SetLineWidth(1);
		weighted_effdata_eta->SetMarkerStyle(20);
		weighted_effdata_eta->SetMarkerSize(1);
		weighted_effdata_eta->SetMarkerColor(kBlue);
	}

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

		weighted_effmc_eta->SetXTitle("#eta");
		weighted_effmc_eta->GetXaxis()->SetRangeUser(weighted_effmc_eta->GetXaxis()->GetXmin(), weighted_effmc_eta->GetXaxis()->GetXmax());
		weighted_effmc_eta->SetYTitle("Efficiency");
		weighted_effmc_eta->SetMaximum(1.05);
		weighted_effmc_eta->SetMinimum(0.901);
		weighted_effmc_eta->SetLineColor(kOrange-3);
		weighted_effmc_eta->SetLineWidth(1);
		weighted_effmc_eta->SetMarkerStyle(20);
		weighted_effmc_eta->SetMarkerSize(1);
		weighted_effmc_eta->SetMarkerColor(kOrange-3);
	}

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

			weighted_effdata_pt->SetXTitle("p_{T} [MeV]");
			weighted_effdata_pt->GetXaxis()->SetRangeUser(5000, weighted_effdata_pt->GetXaxis()->GetXmax());
			weighted_effdata_pt->SetYTitle("Efficiency");
			weighted_effdata_pt->SetMaximum(1.05);
			weighted_effdata_pt->SetMinimum(0.901);
			weighted_effdata_pt->SetLineColor(kBlue);
			weighted_effdata_pt->SetLineWidth(1);
			weighted_effdata_pt->SetMarkerStyle(20);
			weighted_effdata_pt->SetMarkerSize(1);
			weighted_effdata_pt->SetMarkerColor(kBlue);
		}
	}

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

			weighted_effmc_pt->SetXTitle("p_{T} [MeV]");
			weighted_effmc_pt->GetXaxis()->SetRangeUser(5000, weighted_effmc_pt->GetXaxis()->GetXmax());
			weighted_effmc_pt->SetYTitle("Efficiency");
			weighted_effmc_pt->SetMaximum(1.05);
			weighted_effmc_pt->SetMinimum(0.901);
			weighted_effmc_pt->SetLineColor(kOrange-3);
			weighted_effmc_pt->SetLineWidth(1);
			weighted_effmc_pt->SetMarkerStyle(20);
			weighted_effmc_pt->SetMarkerSize(1);
			weighted_effmc_pt->SetMarkerColor(kOrange-3);
		}
	}
/*
	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
	c1->Divide(2, 1);

	c1->cd(1);
	gPad->SetRightMargin(2);
	weighted_effdata_eta->SetTitle(folder);
	weighted_effmc_eta->Draw("e0");
	weighted_effdata_eta->Draw("e0,same");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

	TLine *line1 = new TLine(weighted_effdata_eta->GetXaxis()->GetXmin(), 1., weighted_effdata_eta->GetXaxis()->GetXmax(),1.);
	line1->SetLineColor(kBlack);
	line1->SetLineStyle(2);
	line1->SetLineWidth(1);
	line1->Draw("same");

	c1->cd(2);
	gPad->SetRightMargin(2);
	weighted_effdata_pt->SetTitle(folder);
	weighted_effmc_pt->Draw("e0");
	weighted_effdata_pt->Draw("e0,same");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

	TLine *line2 = new TLine(weighted_effdata_pt->GetXaxis()->GetXmin(), 1., weighted_effdata_pt->GetXaxis()->GetXmax(),1.);
	line2->SetLineColor(kBlack);
	line2->SetLineStyle(2);
	line2->SetLineWidth(1);
	line2->Draw("same");
*/
	// Scale factors

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
/*
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
*/
/*
	TLegend *leg = new TLegend(0.3, 0.8, 0.7, 0.89);
	leg->AddEntry(weighted_presf, "pre-recommendation", "l");
	leg->AddEntry(weighted_sf, "13TeV 50ns data", "l");
	leg->SetTextSize(0.028);
	leg->Draw("same");
*/

	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
	c1->Divide(2, 1);

	c1->cd(1);
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
	pad1->SetFrameLineWidth(2);

	// Draw curve here
	
	weighted_effdata_eta->SetTitle(folder);
	weighted_effmc_eta->Draw("e0");
	weighted_effdata_eta->Draw("e0,same");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

	TLine *line1 = new TLine(weighted_effdata_eta->GetXaxis()->GetXmin(), 1., weighted_effdata_eta->GetXaxis()->GetXmax(),1.);
	line1->SetLineColor(kBlack);
	line1->SetLineStyle(2);
	line1->SetLineWidth(1);
	line1->Draw("same");

	pad2->cd(); // pad2 becomes the current pad
	pad2->SetFrameLineWidth(1);

	TH1F *frame_left = pad2->DrawFrame(weighted_sf_eta->GetXaxis()->GetXmin(), 0.95, weighted_sf_eta->GetXaxis()->GetXmax(), 1.049);
	frame_left->GetYaxis()->SetNdivisions(405);
	frame_left->SetLineWidth(1);
	frame_left->SetXTitle("#eta");
	frame_left->GetXaxis()->SetTitleSize(20);
	frame_left->GetXaxis()->SetTitleFont(47);
	frame_left->GetXaxis()->SetTitleOffset(3.0);
	frame_left->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame_left->GetXaxis()->SetLabelSize(16);
	frame_left->SetYTitle("Data/MC");
	frame_left->GetYaxis()->SetTitleSize(17);
	frame_left->GetYaxis()->SetTitleFont(43);
	frame_left->GetYaxis()->SetTitleOffset(2.0);
	frame_left->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame_left->GetYaxis()->SetLabelSize(16);
	frame_left->Draw();

	weighted_sf_eta->Draw("e0,same");

	c1->cd(2);
	//Upper plot will be in pad1
	TPad *pad1_right = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
	pad1_right->SetBottomMargin(0); // Upper and lower plot are joined
	pad1_right->SetRightMargin(1);
	//pad1_right->SetGridy(); // grid lines
	pad1_right->Draw();

	// lower plot will be in pad
	TPad *pad2_right = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
	pad2_right->SetTopMargin(0);
	pad2_right->SetBottomMargin(0.3);
	pad2_right->SetRightMargin(1);
	pad2_right->SetGridy(); // grid lines
	pad2_right->Draw();

	pad1_right->cd(); // pad1 becomes the current pad
	pad1_right->SetFrameLineWidth(2);

	// Draw curve here
	
	weighted_effdata_pt->SetTitle(folder);
	weighted_effmc_pt->Draw("e0");
	weighted_effdata_pt->Draw("e0,same");
	myText(0.2, 0.87, kBlack, const_cast<char*>(folder.Data()));

	TLine *line2 = new TLine(weighted_effdata_pt->GetXaxis()->GetXmin(), 1., weighted_effdata_pt->GetXaxis()->GetXmax(),1.);
	line2->SetLineColor(kBlack);
	line2->SetLineStyle(2);
	line2->SetLineWidth(1);
	line2->Draw("same");

	pad2_right->cd(); // pad2 becomes the current pad
	pad2_right->SetFrameLineWidth(1);

	TH1F *frame_right = pad2->DrawFrame(weighted_sf_pt->GetXaxis()->GetXmin(), 0.95, weighted_sf_pt->GetXaxis()->GetXmax(), 1.049);
	frame_right->GetYaxis()->SetNdivisions(405);
	frame_right->SetLineWidth(1);
	frame_right->SetXTitle("p_{T} [MeV]");
	frame_right->GetXaxis()->SetTitleSize(20);
	frame_right->GetXaxis()->SetTitleFont(47);
	frame_right->GetXaxis()->SetTitleOffset(3.2);
	frame_right->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame_right->GetXaxis()->SetLabelSize(16);
	frame_right->SetYTitle("Data/MC");
	frame_right->GetYaxis()->SetTitleSize(17);
	frame_right->GetYaxis()->SetTitleFont(43);
	frame_right->GetYaxis()->SetTitleOffset(2.0);
	frame_right->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame_right->GetYaxis()->SetLabelSize(16);
	frame_right->Draw();

	weighted_sf_pt->Draw("e0,same");

	
	c1->SaveAs("plots/ratio_" + folder + ".pdf", "pdf");
}
