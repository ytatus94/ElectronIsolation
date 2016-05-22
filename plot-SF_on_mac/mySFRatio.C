// This script is used to make ratio plots for EOYE recommendations SF and fixed-leakage-correction new SF results
// Usage: root -l mySFRatio.C"(\"TightLLHMC15_v9\",\"isolTight\")"
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

#include <iostream>
void mySFRatio(TString menu = "TightLLH_d0z0_v8",
			   TString iso  = "isolTight",
			   int eta = 1)
{
    SetAtlasStyle();

    TString folder;
    if (iso != "")
		folder = menu + "_" + iso;
    else
		folder = menu;

	TString fileName1 = "../EOYE/ScaleFactors.root";
	TString fileName2 = "../output-SF/ScaleFactors.root";

	TH2F *sf1      = get13TeV2DHistogram(fileName1, menu, iso, "SF_CentralValue");
	TH2F *sf1_tot  = get13TeV2DHistogram(fileName1, menu, iso, "SF_TotalError");
	TH2F *sf1_stat = get13TeV2DHistogram(fileName1, menu, iso, "SF_StatError");

	TH2F *sf2      = get13TeV2DHistogram(fileName2, menu, iso, "SF_CentralValue");
	TH2F *sf2_tot  = get13TeV2DHistogram(fileName2, menu, iso, "SF_TotalError");
	TH2F *sf2_stat = get13TeV2DHistogram(fileName2, menu, iso, "SF_StatError");

    // Remider:
    // x: pt
    // y: eta

    TH1F* pt[2][30]; // keeps total uncertainties
    //TH1F* pt_tmp[2][30]; // keeps statistical uncertainties
    TH1F* tot_err[2][30];
    TH1F* sys_err[2][30];
    TH1F* stat_err[2][30];

	// Fill the uncertainties to the histograms
    for (int eta = 0; eta < sf1->GetYaxis()->GetNbins() + 1; eta++) {
		if (eta == 0) continue; // underflow bin
		// SF of EOYE recommendations
		pt[0][eta]       = (TH1F *)sf1->ProjectionX("", eta, eta)->Clone();
		//pt_tmp[0][eta]   = (TH1F *)sf1->ProjectionX("", eta, eta)->Clone();
		tot_err[0][eta]  = (TH1F *)sf1_tot->ProjectionX("", eta, eta)->Clone();
		//stat_err[0][eta] = (TH1F *)sf1_stat->ProjectionX("", eta, eta)->Clone();
		fixHistogramError(pt[0][eta],     tot_err[0][eta]);	
		//fixHistogramError(pt_tmp[0][eta], stat_err[0][eta]);	

	   	// SF of new results (fixed leakage correction)
	   	pt[1][eta]       = (TH1F *)sf2->ProjectionX("", eta, eta)->Clone();
	   	//pt_tmp[1][eta]   = (TH1F *)sf2->ProjectionX("", eta, eta)->Clone();
	   	tot_err[1][eta]  = (TH1F *)sf2_tot->ProjectionX("", eta, eta)->Clone();
	   	//stat_err[1][eta] = (TH1F *)sf2_stat->ProjectionX("", eta, eta)->Clone();
	   	fixHistogramError(pt[1][eta],     tot_err[1][eta]);
	   	//fixHistogramError(pt_tmp[1][eta], stat_err[1][eta]);
	}

	// New/Old
	TH1F* SF_ratio = (TH1F *)pt[1][eta]->Clone();
	TH1F *old_SF_uncertainties = (TH1F *)tot_err[0][eta]->Clone();
	SF_ratio->Sumw2();
	SF_ratio->Divide(pt[0][eta]);
	// Use old scale factor uncertainties to fill the uncertainties of the SF_ratio
    for (int bin = 0; bin < SF_ratio->GetXaxis()->GetNbins() + 1; bin++) {
		if (bin == 0) continue; // underflow bin
		fixHistogramError(SF_ratio, old_SF_uncertainties);
	}

	//int eta = 12; // eta = 0.1-0.6
	//int eta = 15; // eta = 1.15-1.37
	//int eta = 18; // eta = 1.81-2.01
	//int eta = 19; // eta = 2.01-2.37

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

	// SF of EOEY recommendations
	pt[0][eta]->GetXaxis()->SetTitle("E_{T} [GeV]");
   	pt[0][eta]->GetYaxis()->SetTitle("Scale Factor");
	pt[0][eta]->SetMaximum(1.05);
   	pt[0][eta]->SetMinimum(0.951);
	pt[0][eta]->SetLineColor(kBlue);
	pt[0][eta]->SetLineWidth(1);
	pt[0][eta]->SetMarkerColor(kBlue);
	pt[0][eta]->SetMarkerSize(1.0);
	pt[0][eta]->SetMarkerStyle(20);
	pt[0][eta]->GetXaxis()->SetRangeUser(7000, 150000);
	pt[0][eta]->GetYaxis()->SetNdivisions(505);
   	pt[0][eta]->Draw("e1");

	// SF of new results (fixed leakage correction)
   	pt[1][eta]->SetLineColor(kRed);
   	pt[1][eta]->SetLineWidth(1);
   	pt[1][eta]->SetMarkerColor(kRed);
   	pt[1][eta]->SetMarkerSize(1.0);
   	pt[1][eta]->SetMarkerStyle(kOpenCircle);
   	pt[1][eta]->Draw("e1,same");

	TLine *line = new TLine(7000, 1., 150000, 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("same");

	myText(0.5,0.85,  kBlack, const_cast<char *>(folder.Data()));

	ATLASLabel(0.2,0.85,"Internal");
	myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.34 fb^{-1}");

	char name[100];
	sprintf(&name[0], "%.2f < #eta < %.2f", 
			sf1->GetYaxis()->GetBinLowEdge(eta),
			sf1->GetYaxis()->GetBinUpEdge(eta));
	myText(0.5,0.77, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.5, 0.6, 0.9, 0.75);
	leg->AddEntry(pt[0][eta], "Old (EOYE)", "lp");
	leg->AddEntry(pt[1][eta], "New (fixed)", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad
	TH1F *frame_left = pad2->DrawFrame(7000, 0.96, 150000, 1.039);
	frame_left->GetXaxis()->SetNdivisions(510);
	frame_left->GetYaxis()->SetNdivisions(405);
	frame_left->SetLineWidth(1);
	frame_left->SetXTitle("E_{T} [GeV]");
	frame_left->GetXaxis()->SetTitleSize(20);
	frame_left->GetXaxis()->SetTitleFont(47);
	frame_left->GetXaxis()->SetTitleOffset(3.0);
	frame_left->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame_left->GetXaxis()->SetLabelSize(16);
	frame_left->SetYTitle("New/Old");
	frame_left->GetYaxis()->SetTitleSize(17);
	frame_left->GetYaxis()->SetTitleFont(43);
	frame_left->GetYaxis()->SetTitleOffset(2.0);
	frame_left->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame_left->GetYaxis()->SetLabelSize(16);
	frame_left->Draw();

	// SF with total uncertianty as color band
	SF_ratio->SetLineColor(kOrange-3);
	SF_ratio->SetLineWidth(1);
	SF_ratio->SetMarkerColor(kBlack);
	SF_ratio->SetMarkerSize(1.0);
	SF_ratio->SetMarkerStyle(20);
	SF_ratio->SetFillStyle(1001); // with color band
	SF_ratio->SetFillColor(kOrange-3);
   	SF_ratio->Draw("e2,same");

	// Add legend
	TLegend *leg_bottom = new TLegend(0.4, 0.8, 0.7, 0.95);
	leg_bottom-> SetNColumns(2);
	leg_bottom->AddEntry(SF_ratio, "Old scale factor uncertainty", "f");
	leg_bottom->SetBorderSize(0);
	leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
	leg_bottom->Draw();

	TString etaLowEdge = TString::Format("%.f", sf1->GetYaxis()->GetBinLowEdge(eta)*100.);
	TString etaUpEdge  = TString::Format("%.f", sf1->GetYaxis()->GetBinUpEdge(eta)*100.);

	c1->SaveAs("plots/SF_ratio_eta" + etaLowEdge + "-" + etaUpEdge + "_" + folder + ".pdf", "pdf");
	c1->SaveAs("plots/SF_ratio_eta" + etaLowEdge + "_" + etaUpEdge + "_" + folder + ".C", "C");
}
