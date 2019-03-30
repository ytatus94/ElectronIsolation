// 
//
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
#include "FindOptimalRange.C"

#include <iostream>

void compareSFWithFilesInTools(TString menu = "TightLLH_d0z0_v8",
                               TString iso = "isolTight",
                               int pt = 2)
{
	TString pad1_X_title = "#eta";
	TString pad1_Y_title = "Scale Factor";
	double pad1_Y_max = 1.10;
	double pad1_Y_min = 0.91;

	TString pad2_X_title = "#eta";
	TString pad2_Y_title = "v10/Tool";
	double pad2_Y_max = 1.05;
	double pad2_Y_min = 0.95;

	SetAtlasStyle();

	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

	// ElectronEfficiencyCorrection Tool
	TString fileName1 = "~/test/ElectronEfficiencyCorrection-00-01-42/data/isolations/efficiencySF.Isolation.TightLLH_d0z0_v8_isolTight.2015.13TeV.rel20p0.25ns.v04.root";
	TFile *file1 = TFile::Open(fileName1);

	TH2F *sf1     = (TH2F *)file1->Get("0_9999999/FullSim_sf");
	TH2F *sf1_tot = (TH2F *)file1->Get("0_9999999/FullSim_tot");
	TH2F *sf2     = (TH2F *)file1->Get("0_9999999/AtlFast2_sf");
	TH2F *sf2_tot = (TH2F *)file1->Get("0_9999999/AtlFast2_tot");

	// Remider:
	// x: pt
	// y: eta

	cout << "sf1 bin low edge=" << sf1->GetXaxis()->GetBinLowEdge(5) / 1000. << endl;
	cout << "sf1 bin up edge="  << sf1->GetXaxis()->GetBinUpEdge(5)  / 1000. << endl;
	cout << "sf2 bin low edge=" << sf2->GetXaxis()->GetBinLowEdge(5) / 1000. << endl;
	cout << "sf2 bin up edge="  << sf2->GetXaxis()->GetBinUpEdge(5)  / 1000. << endl;

	TH1F *eta1 = (TH1F *)sf1->ProjectionY("", 5, 5)->Clone();
	TH1F *eta2 = (TH1F *)sf2->ProjectionY("", 5, 5)->Clone();
/*
    TH1F* eta1[0][30]; // keeps total uncertainties
    TH1F* tot1_err[0][30];

	// Fill the uncertainties to the histograms
    for (int pt = 0; pt < sf1->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		if (pt < 2) continue; // The plots are empty when pt=1
		// SF
        cout << pt << endl;
		eta1[0][pt]      = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
		tot1_err[0][pt]  = (TH1F *)sf1_tot->ProjectionY("", pt, pt)->Clone();
		fixHistogramError(eta1[0][pt],     tot1_err[0][pt]);
	}
*/
//--------------------

	// ScaleFactors.root
	TString fileName2 = "~/Desktop/myMC15b_efficiencySF.Isolation.TightLLH_d0z0_v10_isolTight.2015.13TeV.rel20p0.25ns.v05.root";
	TFile *file2 = TFile::Open(fileName2);
	TH2F *sf3    = (TH2F *)file2->Get("0_99999999999/FullSim_sf");
	cout << "sf3 bin low edge=" << sf3->GetXaxis()->GetBinLowEdge(6) / 1000. << endl;
	cout << "sf3 bin up edge=" << sf3->GetXaxis()->GetBinUpEdge(6) / 1000. << endl;
    TH1F* eta3 = (TH1F *)sf3->ProjectionY("", 6, 6)->Clone();
/*
    TH1F* eta2[0][30]; // keeps total uncertainties

    for (int pt = 0; pt < sf2->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		if (pt < 2) continue; // The plots are empty when pt=1
		// SF
		eta2[0][pt] = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
	}
*/
    TString fileName3 = "~/Desktop/myAF2_efficiencySF.Isolation.TightLLH_d0z0_v10_isolTight.2015.13TeV.rel20p0.25ns.v05.root";
    TFile *file3 = TFile::Open(fileName3);
    TH2F *sf4 = (TH2F *)file3->Get("0_99999999999/FullSim_sf");
	cout << "sf4 bin low edge=" << sf4->GetXaxis()->GetBinLowEdge(6) / 1000. << endl;
	cout << "sf4 bin up edge=" << sf4->GetXaxis()->GetBinUpEdge(6) / 1000. << endl;
    TH1F* eta4 = (TH1F *)sf4->ProjectionY("", 6, 6)->Clone();
/*
    TH1F* eta3[0][30]; // keeps total uncertainties
    for (int pt = 0; pt < sf3->GetXaxis()->GetNbins() + 1; pt++) {
        if (pt == 0) continue; // underflow bin
        if (pt < 2) continue; // The plots are empty when pt=1
        // SF
        eta3[0][pt] = (TH1F *)sf3->ProjectionY("", pt, pt)->Clone();
    }
*/


//------------

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
    FindOptimalRange(high, low, eta1, eta2);
    pad1_Y_max = high;
    if (low < 0.)
        pad1_Y_min = 0.;
    else
        pad1_Y_min = low;

    FindOptimalRange(high, low, eta1, eta3);
    if (high > pad1_Y_max)
        pad1_Y_max = high;
    if (low < pad1_Y_min)
        pad1_Y_min = low;
    if (low < 0)
        pad1_Y_min = 0.;

	// Set titles, maximum and minimum of axes
	eta1->SetXTitle(pad1_X_title);
	eta1->SetYTitle(pad1_Y_title);
    eta1->SetMaximum(pad1_Y_max);
   	eta1->SetMinimum(pad1_Y_min);

	// SF vs eta
	// fileName1
	eta1->SetLineColor(kBlue);
	eta1->SetLineWidth(1);
	eta1->SetMarkerColor(kBlue);
	eta1->SetMarkerSize(1);
	eta1->SetMarkerStyle(20);
   	eta1->Draw("E1");

    eta2->SetLineColor(kRed);
    eta2->SetLineWidth(1);
    eta2->SetMarkerColor(kRed);
    eta2->SetMarkerSize(1);
    eta2->SetMarkerStyle(kFullTriangleUp);
   	eta2->Draw("E1,SAME");

	// fileName2
    eta3->SetLineColor(kBlue);
    eta3->SetLineWidth(1);
    eta3->SetMarkerColor(kBlue);
    eta3->SetMarkerSize(1);
    eta3->SetMarkerStyle(kOpenCircle);
   	eta3->Draw("E1,SAME");
    
    // fileName3
    eta4->SetLineColor(kRed);
    eta4->SetLineWidth(1);
    eta4->SetMarkerColor(kRed);
    eta4->SetMarkerSize(1);
    eta4->SetMarkerStyle(kOpenTriangleUp);
   	eta4->Draw("E1,SAME");


	TLine *line = new TLine(eta1->GetXaxis()->GetXmin(), 1.,
                            eta1->GetXaxis()->GetXmax(), 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("same");

	myText(0.2, 0.85, kBlack, const_cast<char *>(menu.Data()));
	if (menu.Contains("LooseAndBLayer")) {
    	myText(0.5, 0.85, kBlack, const_cast<char *>(iso.Data()));
	}
	else {
		myText(0.6, 0.85, kBlack, const_cast<char *>(iso.Data()));
	}

	char name[100];
	sprintf(&name[0], "%d GeV < p_{T} < %d GeV", 
			static_cast<int>(sf1->GetXaxis()->GetBinLowEdge(5) / 1000.),
			static_cast<int>(sf1->GetXaxis()->GetBinUpEdge(5) / 1000.) );
	myText(0.2, 0.78, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.2, 0.60, 0.6, 0.75);
	leg->AddEntry(eta1, "FullSim v10 (Tool)", "lp");
	leg->AddEntry(eta2, "AtlasFast 2 v10 (Tool)", "lp");
	leg->AddEntry(eta3, "MC15b (v10)", "lp");
    leg->AddEntry(eta4, "AF2 (v10)", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad
	TH1F *frame_left;
	frame_left = pad2->DrawFrame(eta1->GetXaxis()->GetXmin(), pad2_Y_min,
					 		     eta1->GetXaxis()->GetXmax(), pad2_Y_max);

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
	TH1F *ratio1 = (TH1F *)eta1->Clone();
	ratio1->Divide(eta3);

	ratio1->SetLineColor(kBlue);
	ratio1->SetLineWidth(1);
	ratio1->SetMarkerColor(kBlue);
	ratio1->SetMarkerSize(1);
	ratio1->SetMarkerStyle(20);
	ratio1->Draw("E1,same");

    TH1F *ratio2 = (TH1F *)eta2->Clone();
    ratio2->Divide(eta4);
    
    ratio2->SetLineColor(kRed);
    ratio2->SetLineWidth(1);
    ratio2->SetMarkerColor(kRed);
    ratio2->SetMarkerSize(1);
    ratio2->SetMarkerStyle(kFullTriangleUp);
    ratio2->Draw("E1,same");
    
	int ptLowEdge = static_cast<int>(sf1->GetXaxis()->GetBinLowEdge(pt) / 1000.);
	int ptUpEdge  = static_cast<int>(sf1->GetXaxis()->GetBinUpEdge(pt) / 1000.);

	//c1->SaveAs("plots/comp_d0z0_AF2_pT" + TString::Itoa(ptLowEdge,10) + "-" + TString::Itoa(ptUpEdge,10) + "_" + folder + ".pdf", "pdf");
 
}
