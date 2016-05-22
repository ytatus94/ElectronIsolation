// pt bins:
//  2-4: 7 < pT < 20 GeV
//  5-8: 20 < pT < 40 GeV
//  9-11: 40 < pT < 60 GeV
//  12-12: 60 < pT < 80 GeV
//  13-13: 80 < pT < 125 GeV
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

void myRatioPlotDeltaR(TString menu, TString iso, int pt_bin)
{
	gStyle->SetOptStat(0);
//    SetAtlasStyle();
    bool debug = true;
    //bool debug = false;

    TString folder;
    if (iso.Contains("isolPhFixedCut"))
		folder = menu + "MC15_v8_" + iso;
    else
		folder = menu + "_d0z0_v8_" + iso;

    TFile *file = TFile::Open("../ScaleFactors_rebin.root");

	TH2F *effdata     = (TH2F*)file->Get(folder + "/" + "EffData_CentralValue_minDeltaR_" + folder);
    TH2F *effdata_tot = (TH2F*)file->Get(folder + "/" + "EffData_TotalError_minDeltaR_" + folder);
    TH2F *effmc       = (TH2F*)file->Get(folder + "/" + "EffMC_CentralValue_minDeltaR_" + folder);
    TH2F *effmc_tot   = (TH2F*)file->Get(folder + "/" + "EffMC_TotalError_minDeltaR_" + folder);
    TH2F *sf          = (TH2F*)file->Get(folder + "/" + "SF_CentralValue_minDeltaR_" + folder);
    TH2F *sf_tot      = (TH2F*)file->Get(folder + "/" + "SF_TotalError_minDeltaR_" + folder);
    TH2F *sf_stat     = (TH2F*)file->Get(folder + "/" + "SF_StatError_minDeltaR_" + folder);

    if (debug) {
        cout << effdata << endl;
        cout << effdata_tot << endl;
        cout << effmc << endl;
        cout << effmc_tot << endl;
        cout << sf << endl;
        cout << sf_tot << endl;

        effdata->GetXaxis()->SetRangeUser(7000, 125000);
        effdata->Draw("colz");
    }

    // Remider:
    // x: pt
    // y: deltaR

    TH1F *effdata_project_on_minDeltaR_pt_bin = 0, *effdata_tot_project_on_minDeltaR_pt_bin = 0,
         *effmc_project_on_minDeltaR_pt_bin = 0,   *effmc_tot_project_on_minDeltaR_pt_bin = 0,
         *sf_project_on_minDeltaR_pt_bin = 0,      *sf_tot_project_on_minDeltaR_pt_bin = 0,
         *sf_tmp_project_on_minDeltaR_pt_bin = 0,  *sf_stat_project_on_minDeltaR_pt_bin = 0;

    effdata_project_on_minDeltaR_pt_bin = (TH1F *)effdata->ProjectionY("", pt_bin, pt_bin)->Clone();
    effdata_tot_project_on_minDeltaR_pt_bin = (TH1F *)effdata_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
    fixHistogramError(effdata_project_on_minDeltaR_pt_bin, effdata_tot_project_on_minDeltaR_pt_bin);

    effmc_project_on_minDeltaR_pt_bin = (TH1F *)effmc->ProjectionY("", pt_bin, pt_bin)->Clone();
    effmc_tot_project_on_minDeltaR_pt_bin = (TH1F *)effmc_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
    fixHistogramError(effmc_project_on_minDeltaR_pt_bin, effmc_tot_project_on_minDeltaR_pt_bin);

    sf_project_on_minDeltaR_pt_bin = (TH1F *)sf->ProjectionY("", pt_bin, pt_bin)->Clone();
    sf_tot_project_on_minDeltaR_pt_bin = (TH1F *)sf_tot->ProjectionY("", pt_bin, pt_bin)->Clone();
    fixHistogramError(sf_project_on_minDeltaR_pt_bin, sf_tot_project_on_minDeltaR_pt_bin);

    sf_tmp_project_on_minDeltaR_pt_bin = (TH1F *)sf->ProjectionY("", pt_bin, pt_bin)->Clone();
    sf_stat_project_on_minDeltaR_pt_bin = (TH1F *)sf_stat->ProjectionY("", pt_bin, pt_bin)->Clone();
    fixHistogramError(sf_tmp_project_on_minDeltaR_pt_bin, sf_stat_project_on_minDeltaR_pt_bin);

    if (debug) {
        cout << effdata_project_on_minDeltaR_pt_bin << endl;
        cout << effdata_tot_project_on_minDeltaR_pt_bin << endl;
        cout << effmc_project_on_minDeltaR_pt_bin << endl;
        cout << effmc_tot_project_on_minDeltaR_pt_bin << endl;
        cout << sf_project_on_minDeltaR_pt_bin << endl;
        cout << sf_tot_project_on_minDeltaR_pt_bin << endl;
		
    }

    // Set titles and axes scales for top pad (pad1)
    TString pad1_X_title = "#Delta R";
    TString pad1_Y_title = "Efficiency";
    double pad1_Y_max = 1.20;
    double pad1_Y_min = 0.81;

    // Set titles and axes scales for bottom pad (pad2)
    TString pad2_X_title = "#Delta R";
    TString pad2_Y_title = "Data / MC";
    double pad2_Y_max = 1.20;
    double pad2_Y_min = 0.81;

//--------------------------------------------------//

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
/*
    float high = 0, low = 0;
    FindOptimalRange(high, low, effdata_project_on_minDeltaR_pt_bin, effmc_project_on_minDeltaR_pt_bin);
    if (high < 1.2)
        pad1_Y_max = high;
    else
        pad1_Y_max = 1.2;

    if (low < 0.) {
        pad1_Y_min = 0.;
    }
    else {
        pad1_Y_min = low;
    }
*/

    // Set titles, maximum and minimum of axes
	effdata_project_on_minDeltaR_pt_bin->GetXaxis()->SetTitle(pad1_X_title);
   	effdata_project_on_minDeltaR_pt_bin->GetYaxis()->SetTitle(pad1_Y_title);
	effdata_project_on_minDeltaR_pt_bin->GetXaxis()->SetRangeUser(0.2, 1.0);
	effdata_project_on_minDeltaR_pt_bin->SetMaximum(pad1_Y_max);
   	effdata_project_on_minDeltaR_pt_bin->SetMinimum(pad1_Y_min);

    // Data
	effdata_project_on_minDeltaR_pt_bin->SetLineColor(kBlue);
	effdata_project_on_minDeltaR_pt_bin->SetLineWidth(1);
	effdata_project_on_minDeltaR_pt_bin->SetMarkerColor(kBlue);
	effdata_project_on_minDeltaR_pt_bin->SetMarkerSize(1);
	effdata_project_on_minDeltaR_pt_bin->SetMarkerStyle(20);
   	effdata_project_on_minDeltaR_pt_bin->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.

	// MC
   	effmc_project_on_minDeltaR_pt_bin->SetLineColor(kRed);
   	effmc_project_on_minDeltaR_pt_bin->SetLineWidth(1);
   	effmc_project_on_minDeltaR_pt_bin->SetMarkerColor(kRed);
   	effmc_project_on_minDeltaR_pt_bin->SetMarkerSize(1);
   	effmc_project_on_minDeltaR_pt_bin->SetMarkerStyle(kOpenCircle);
   	effmc_project_on_minDeltaR_pt_bin->Draw("E0,SAME");

    double xmin = effdata_project_on_minDeltaR_pt_bin->GetXaxis()->GetXmin();
    double xmax = effdata_project_on_minDeltaR_pt_bin->GetXaxis()->GetXmax();
    //TLine *line = new TLine(xmin, 1., xmax, 1.);
    TLine *line = new TLine(0.2, 1., 1.0, 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");

	//myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
	ATLASLabel(0.2, 0.85,"Internal");
	myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

	char name[100];
	sprintf(&name[0], "%d < p_{T} < %d",
            static_cast<int>(effdata->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.),
            static_cast<int>(effdata->GetXaxis()->GetBinUpEdge(pt_bin) / 1000.));
	myText(0.2,0.70, kBlack, name);

	// Add legend
	TLegend *leg = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg->AddEntry(effdata_project_on_minDeltaR_pt_bin, "Data", "lp");
	leg->AddEntry(effmc_project_on_minDeltaR_pt_bin, "Z #rightarrow ee MC", "lp");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
    leg->SetTextSize(0.05);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

	pad2->cd(); // pad2 becomes the current pad
/*
    FindOptimalRange(high, low, pt[2][deltaR], pt_tmp[2][deltaR]);
    pad2_Y_max = high;
    if (low < 0.) {
        pad2_Y_min = 0.;
    }
    else {
        pad2_Y_min = low;
    }
*/
	//TH1F *frame_left = pad2->DrawFrame(0, pad2_Y_min, 10, pad2_Y_max);
	TH1F *frame_left = pad2->DrawFrame(0.2, pad2_Y_min, 1.0, pad2_Y_max);
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
	frame_left->GetYaxis()->SetTitleOffset(1.5);
	frame_left->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	frame_left->GetYaxis()->SetLabelSize(16);
	frame_left->Draw();

	// SF with total uncertianty as color band
	sf_project_on_minDeltaR_pt_bin->SetLineColor(kOrange-3);
	sf_project_on_minDeltaR_pt_bin->SetLineWidth(1);
	sf_project_on_minDeltaR_pt_bin->SetMarkerColor(kBlack);
	sf_project_on_minDeltaR_pt_bin->SetMarkerSize(1);
	sf_project_on_minDeltaR_pt_bin->SetMarkerStyle(20);
	sf_project_on_minDeltaR_pt_bin->SetFillStyle(1001); // with color band
	sf_project_on_minDeltaR_pt_bin->SetFillColor(kOrange-3);
   	sf_project_on_minDeltaR_pt_bin->Draw("E2,SAME"); // E2: Draw error bars with rectangles.

	// SF with statistical uncertianty as color band
	sf_tmp_project_on_minDeltaR_pt_bin->SetLineColor(kBlack);
	sf_tmp_project_on_minDeltaR_pt_bin->SetLineWidth(1);
	sf_tmp_project_on_minDeltaR_pt_bin->SetMarkerColor(kBlack);
	sf_tmp_project_on_minDeltaR_pt_bin->SetMarkerSize(1);
	sf_tmp_project_on_minDeltaR_pt_bin->SetMarkerStyle(20);
   	sf_tmp_project_on_minDeltaR_pt_bin->Draw("E0,SAME");

	// Add legend
	TLegend *leg_bottom = new TLegend(0.4, 0.8, 0.7, 0.95);
	leg_bottom-> SetNColumns(2);
	leg_bottom->AddEntry(sf_project_on_minDeltaR_pt_bin, "Stat #oplus Syst", "pf");
	leg_bottom->AddEntry(sf_tmp_project_on_minDeltaR_pt_bin, "Stat only", "l");
	leg_bottom->SetBorderSize(0);
	leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
	leg_bottom->Draw();

	TString ptLowEdge = TString::Format("%d", static_cast<int>(effdata->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.)); 
	TString ptUpEdge  = TString::Format("%d", static_cast<int>(effdata->GetXaxis()->GetBinUpEdge(pt_bin) / 1000.));
    TString plot_name = "plots/ratio_pT" + ptLowEdge + "-" + ptUpEdge + "_" + folder + ".pdf";

	c1->Print(plot_name);

}
