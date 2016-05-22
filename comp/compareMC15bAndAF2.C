// This script makes a 1-dim plot. Project SF on the eta axis.
// Compare the SF values between ElectronEfficiencyCorrection tool and my version of recommendations.
//
//int pt_bin = 2; // pt = 7-10 GeV
//int pt_bin = 3; // pT = 10-15 GeV
//int pt_bin = 4; // pT = 15-20 GeV
//int pt_bin = 8; // pT = 35-40 GeV
//int pt_bin = 13; // pT = 80-150 GeV
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

#include <iostream>
using namespace std;

void compareMC15bAndAF2(int pt_bin = 2)
{
	TString pad1_X_title = "#eta";
	TString pad1_Y_title = "Scale Factor";
	double pad1_Y_max = 1.30;
	double pad1_Y_min = 0.851;

	TString pad2_X_title = "#eta";
	TString pad2_Y_title = "FullSim/AF2";
	double pad2_Y_max = 1.05;
	double pad2_Y_min = 0.95;

	SetAtlasStyle();

	// Moriond recommendations
	TString fileName1  = "~/test/ElectronEfficiencyCorrection-00-01-42/data/isolations/efficiencySF.Isolation.TightLLH_d0z0_v8_isolGradientLoose.2015.13TeV.rel20p0.25ns.v04.root";
	TFile   *file1     = TFile::Open(fileName1);

	TH2F *mc15b_sf   = (TH2F *)file1->Get("0_9999999/FullSim_sf");
	TH2F *mc15b_stat = (TH2F *)file1->Get("0_9999999/FullSim_stat");
	TH2F *mc15b_tot  = (TH2F *)file1->Get("0_9999999/FullSim_tot");
	TH2F *mc15b_eig  = (TH2F *)file1->Get("0_9999999/FullSim_eig");

	TH2F *af2_sf   = (TH2F *)file1->Get("0_9999999/AtlFast2_sf");
	TH2F *af2_stat = (TH2F *)file1->Get("0_9999999/AtlFast2_stat");
	TH2F *af2_tot  = (TH2F *)file1->Get("0_9999999/AtlFast2_tot");
	TH2F *af2_eig  = (TH2F *)file1->Get("0_9999999/AtlFast2_eig");

	// Remider:
	// x: pt
	// y: eta

	TH1F* eta[4][30]; // keeps total uncertainties
	TH1F* tot_err[4][30];

	// MC15b SF
	for (int pt_bin = 0; pt_bin < mc15b_sf->GetXaxis()->GetNbins() + 1; pt_bin++) {
		if (pt_bin == 0) continue; // underflow bin
		//if (pt_bin < 2) continue; // The plots are empty when pt_bin=1 // The first bin in Moriond recommendation is 7~10 GeV.
		eta[0][pt_bin]     = (TH1F *)mc15b_sf->ProjectionY("", pt_bin, pt_bin)->Clone();
		tot_err[0][pt_bin] = (TH1F *)mc15b_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
		fixHistogramError(eta[0][pt_bin], tot_err[0][pt_bin]);
	}

	// AF2 SF
	for (int pt_bin = 0; pt_bin < af2_sf->GetXaxis()->GetNbins() + 1; pt_bin++) {
		if (pt_bin == 0) continue; // uncerflow bin
		//if (pt_bin < 2) continue; // The plots are empty when pt_bin=1; // The first bin in Moriond recommendation is 7~10 GeV.
		eta[1][pt_bin]     = (TH1F *)af2_sf->ProjectionY("", pt_bin, pt_bin)->Clone();
		tot_err[1][pt_bin] = (TH1F *)af2_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
		fixHistogramError(eta[1][pt_bin], tot_err[1][pt_bin]);
	}

	//--------------------------------------------------//
    
	// My verison of recommendations (MC15b)
	TString fileName2 = "~/public/ForSandrine/20151218/MC15b_recommendations/efficiencySF.Isolation.TightLLH_d0z0_v8_isolGradientLoose.2015.13TeV.rel20p0.25ns.v03.root";
	TFile *file2      = TFile::Open(fileName2);
	TH2F *mc15b_sf2   = (TH2F *)file2->Get("0_99999999999/FullSim_sf");

	// MC15b SF
	for (int pt_bin = 0; pt_bin < mc15b_sf2->GetXaxis()->GetNbins() + 1; pt_bin++) {
		if (pt_bin == 0) continue; // underflow bin
		if (pt_bin < 2) continue; // The plots are empty when pt_bin=1 // The first bin in my recommendation is 4~7 GeV.
		eta[2][pt_bin] = (TH1F *)mc15b_sf2->ProjectionY("", pt_bin, pt_bin)->Clone();
	}

	//--------------------------------------------------//

	// My version of recommendations (AF2)
	TString fileName3 = "~/public/ForSandrine/20151218/AF2_recommendations/efficiencySF.Isolation.TightLLH_d0z0_v8_isolGradientLoose.2015.13TeV.rel20p0.25ns.v03.root";
	TFile *file3      = TFile::Open(fileName3);
	TH2F *af2_sf2     = (TH2F *)file2->Get("0_99999999999/FullSim_sf");

	// AF2 SF
	for (int pt_bin = 0; pt_bin < af2_sf2->GetXaxis()->GetNbins() + 1; pt_bin++) {
		if (pt_bin == 0) continue; // uncerflow bin
		if (pt_bin < 2) continue; // The plots are empty when pt_bin=1;
		eta[3][pt_bin] = (TH1F *)af2_sf2->ProjectionY("", pt_bin, pt_bin)->Clone();
	}

	//--------------------------------------------------//
    
	// Big Canvas
	TCanvas* c1 = new TCanvas("c1", "Compare MC15b and AF2", 600, 600);

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
	eta[0][pt_bin]->SetXTitle(pad1_X_title);
	eta[0][pt_bin]->SetYTitle(pad1_Y_title);
	eta[0][pt_bin]->SetMaximum(pad1_Y_max);
   	eta[0][pt_bin]->SetMinimum(pad1_Y_min);

	// SF vs eta
	// MC15b SF in Moriond recommendations
	eta[0][pt_bin]->SetLineColor(kBlue);
	eta[0][pt_bin]->SetLineWidth(1);
	eta[0][pt_bin]->SetMarkerColor(kBlue);
	eta[0][pt_bin]->SetMarkerSize(1);
	eta[0][pt_bin]->SetMarkerStyle(kFullCircle);
   	eta[0][pt_bin]->Draw("E1");

	// AF2 SF in Moriond recommendations
	eta[1][pt_bin]->SetLineColor(kRed);
	eta[1][pt_bin]->SetLineWidth(1);
	eta[1][pt_bin]->SetMarkerColor(kRed);
	eta[1][pt_bin]->SetMarkerSize(1);
	eta[1][pt_bin]->SetMarkerStyle(kFullCircle);
   	eta[1][pt_bin]->Draw("E1,SAME");

	// MC15b SF in my recommendations
	// The first bin in my recommendation is 4-7 GeV
	// so I need to shift one bin in order to match the correct bin in the tool.
	eta[2][pt_bin+1]->SetLineColor(kBlue);
	eta[2][pt_bin+1]->SetLineWidth(1);
	eta[2][pt_bin+1]->SetMarkerColor(kBlue);
	eta[2][pt_bin+1]->SetMarkerSize(1);
	eta[2][pt_bin+1]->SetMarkerStyle(kOpenTriangleUp);
   	eta[2][pt_bin+1]->Draw("E1,SAME");
    
	// AF2 SF in my recommendations
	eta[3][pt_bin+1]->SetLineColor(kRed);
	eta[3][pt_bin+1]->SetLineWidth(1);
	eta[3][pt_bin+1]->SetMarkerColor(kRed);
	eta[3][pt_bin+1]->SetMarkerSize(1);
	eta[3][pt_bin+1]->SetMarkerStyle(kOpenTriangleDown);
   	eta[3][pt_bin+1]->Draw("E1,SAME");
    
	TLine *line = new TLine(eta[0][pt_bin]->GetXaxis()->GetXmin(), 1.,
                                eta[0][pt_bin]->GetXaxis()->GetXmax(), 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");

	//myText(0.2, 0.85, kBlack, const_cast<char *>(fileName.Data()));
/*
	myText(0.2, 0.85, kBlack, const_cast<char *>(menu.Data()));
	if (menu.Contains("LooseAndBLayer")) {
    	myText(0.5, 0.85, kBlack, const_cast<char *>(iso.Data()));
	}
	else {
		myText(0.4, 0.85, kBlack, const_cast<char *>(iso.Data()));
	}
*/
	char name[100];
	sprintf(&name[0], "%d GeV < p_{T} < %d GeV", 
                static_cast<int>(mc15b_sf->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.),
                static_cast<int>(mc15b_sf->GetXaxis()->GetBinUpEdge(pt_bin)  / 1000.) );
	myText(0.2, 0.78, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.2, 0.50, 0.6, 0.75);
	leg->AddEntry(eta[0][pt_bin], "MC15b (v04)", "lp");
	leg->AddEntry(eta[1][pt_bin], "AF2 (v04)",   "lp");
	leg->AddEntry(eta[2][pt_bin+1], "MC15b (v03)", "lp");
	leg->AddEntry(eta[3][pt_bin+1], "AF2 (v03)",   "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.05);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad
	TH1F *frame_left;
	frame_left = pad2->DrawFrame(eta[0][pt_bin]->GetXaxis()->GetXmin(), pad2_Y_min,
                                     eta[0][pt_bin]->GetXaxis()->GetXmax(), pad2_Y_max);

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

	// Calculate the ratio between MC15b and AF2
	TH1F *ratio1 = (TH1F *)eta[0][pt_bin]->Clone();
	ratio1->Divide(eta[1][pt_bin]);

	ratio1->SetLineColor(kBlack);
	ratio1->SetLineWidth(1);
	ratio1->SetMarkerColor(kBlack);
	ratio1->SetMarkerSize(1);
	ratio1->SetMarkerStyle(kFullCircle);
	ratio1->Draw("E1,SAME");

	TH1F *ratio2 = (TH1F *)eta[2][pt_bin+1]->Clone();
	ratio2->Divide(eta[3][pt_bin+1]);

	ratio2->SetLineColor(kBlack);
	ratio2->SetLineWidth(1);
	ratio2->SetMarkerColor(kBlack);
	ratio2->SetMarkerSize(1);
	ratio2->SetMarkerStyle(kOpenCircle);
	ratio2->Draw("E1,SAME");

	TString ptLowEdge = TString::Format("%d", static_cast<int>(mc15b_sf->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.) );
	TString ptUpEdge  = TString::Format("%d", static_cast<int>(mc15b_sf->GetXaxis()->GetBinUpEdge(pt_bin)  / 1000.) );

	c1->SaveAs("plots/comp_MC15b_and_AF2_pT" + ptLowEdge + "-" + ptUpEdge + ".pdf", "pdf");
}
