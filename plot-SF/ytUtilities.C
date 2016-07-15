#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include <iostream>
using namespace std;

// Global variables
const TString menu[3] = {"TightLLH", "MediumLLH", "LooseAndBLayerLLH"};
const TString isol[11] = {"isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose",
                          "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose",
                          "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"};

//
// Find the best y axis range of a plot.
//
void FindOptimalRange(Float_t& high, Float_t& low, TH1F *h1, TH1F *h2 = NULL)
{
	high = -99;
	low  = 99;

	float content;
	float error;

	// h1
	for (int b = 1; b < h1->GetXaxis()->GetNbins(); b++){
		content = h1->GetBinContent(b);
		error   = h1->GetBinError(b);
		// exclude the very large unreasonable vlaue
		if (error > 10000.) continue;
		if (content + error > high)
			high = content + error;
		if (content - error < low)
			low = content - error;
	}

	// h2
	if (h2 != NULL) {
		for (int b = 1; b < h2->GetXaxis()->GetNbins(); b++) {
			content = h2->GetBinContent(b);
			error   = h2->GetBinError(b);
			// exclude the very large unreasonable vlaue
			if (error > 10000.) continue;
			if(content + error > high)
				high = content + error;
			if(content - error < low)
				low = content - error;
		}
	}

	// Keep the (high - low) = 50% of the figure.
	// Keep 40% space at the top of plots and 10% space at the bottom of the plots.
	float plot_y_size = (high - low) / 0.5;
	high += plot_y_size * 0.4;
	low  -= plot_y_size * 0.1;
}

//
// Correct the error of histogram
//
void fixHistogramError(TH1F *h1, TH1F *herr)
{
	for (Int_t ik = 1; ik <= h1->GetXaxis()->GetNbins(); ik++) {
		float err = herr->GetBinContent(ik);
		h1->SetBinError(ik, err);
	}
}
/*
void fix1DHistogramError(TH1F *h1,TH1F *herr)
{
	for (int ik = 1; ik < h1->GetSize(); ik++) {
		float err = herr->GetBinContent(ik);
		h1->SetBinError(ik, err);
	}
}

void fix2DHistogramError(TH2F *h1,TH2F *herr)
{
	for (int ik = 1; ik < h1->GetSize(); ik++) {
		float err = herr->GetBinContent(ik);
		h1->SetBinError(ik, err);
	}
}
*/

//
// Get the correct histogram in the file.
//
TH2F* get2DHistogram(TString fileName = "../output-SF/ScaleFactors.root",
                     TString menu = "TightLLHMC15_v6",
                     TString iso  = "isolTight",
                     TString histName = "EffData_CentralValue")
{
	//bool debug = true;
	bool debug = false;

	TFile *file = TFile::Open(fileName);

	TString folder;
	if (iso != "")
		folder = menu + "_" + iso;
	else
		folder = menu;

	// Get EffData histograms
	TString h_effdata      = "EffData_CentralValue_" + folder;
	TString h_effdata_tot  = "EffData_TotalError_" + folder;
	TString h_effdata_stat = "EffData_StatError_"  + folder;
	TString h_effdata_syst = "EffData_SystError_"  + folder;

	if (debug) {
		cout << h_effdata << endl;
		cout << h_effdata_tot << endl;
		cout << h_effdata_stat << endl;
		cout << h_effdata_syst << endl;
	}

	TH2F *effdata      = (TH2F *)file->Get(folder + "/" + h_effdata);
	TH2F *effdata_tot  = (TH2F *)file->Get(folder + "/" + h_effdata_tot);
	TH2F *effdata_stat = (TH2F *)file->Get(folder + "/" + h_effdata_stat);
	TH2F *effdata_syst = (TH2F *)file->Get(folder + "/" + h_effdata_syst);
	
	// Get EffMC histograms
	TString h_effmc      = "EffMC_CentralValue_" + folder;
	TString h_effmc_tot  = "EffMC_TotalError_" + folder;
	TString h_effmc_stat = "EffMC_StatError_"  + folder;
	TString h_effmc_syst = "EffMC_SystError_"  + folder;

	if (debug) {
		cout << h_effmc << endl;
		cout << h_effmc_tot << endl;
		cout << h_effmc_stat << endl;
		cout << h_effmc_syst << endl;
	}

	TH2F *effmc      = (TH2F *)file->Get(folder + "/" + h_effmc);
	TH2F *effmc_tot  = (TH2F *)file->Get(folder + "/" + h_effmc_tot);
	TH2F *effmc_stat = (TH2F *)file->Get(folder + "/" + h_effmc_stat);
	TH2F *effmc_syst = (TH2F *)file->Get(folder + "/" + h_effmc_syst);

	// Get SF histograms
	TString h_sf      = "SF_CentralValue_" + folder;
	TString h_sf_tot  = "SF_TotalError_" + folder;
	TString h_sf_stat = "SF_StatError_"  + folder;
	TString h_sf_syst = "SF_SystError_"  + folder;

	if (debug) {
		cout << h_sf << endl;
		cout << h_sf_tot << endl;
		cout << h_sf_stat << endl;
		cout << h_sf_syst << endl;
	}

	TH2F *sf      = (TH2F *)file->Get(folder + "/" + h_sf);
	TH2F *sf_tot  = (TH2F *)file->Get(folder + "/" + h_sf_tot);
	TH2F *sf_stat = (TH2F *)file->Get(folder + "/" + h_sf_stat);
	TH2F *sf_syst = (TH2F *)file->Get(folder + "/" + h_sf_syst);

	if (debug) {
		cout << "effdata = " << effdata << endl;
		cout << "effmc = " << effmc << endl;
		cout << "sf = " << sf << endl;
	}

	TH2F *hist = new TH2F;	
	if (histName == "EffData_CentralValue") 
		hist = effdata;
	else if (histName == "EffData_TotalError")
		hist = effdata_tot;
	else if (histName == "EffData_StatError")
		hist = effdata_stat;
	else if (histName == "EffData_SystError")
		hist = effdata_syst;
	else if (histName == "EffMC_CentralValue")
		hist = effmc;
	else if (histName == "EffMC_TotalError")
		hist = effmc_tot;
	else if (histName == "EffMC_StatError")
		hist = effmc_stat;
	else if (histName == "EffMC_SystError")
		hist = effmc_syst;
	else if (histName == "SF_CentralValue")
		hist = sf;
	else if (histName == "SF_TotalError")
		hist = sf_tot;
	else if (histName == "SF_StatError")
		hist = sf_stat;
	else if (histName == "SF_SystError")
		hist = sf_syst;

	return hist;
}

//
// This script is used to show the number of bins in the 2 dim histograms.
// Remember to check the number of bins before run other scripts.
// Usage: root -l showNBins.C"(\"output/ScaleFactors.root\",\"TightLLH_d0z0_v8\",\"isolTight\")"
//
void showNBins(TString fileName,
               TString menu,
               TString iso)
{
	cout << fileName << ":" << endl;
 
	TH2F *effdata      = get2DHistogram(fileName, menu, iso, "EffData_CentralValue");
	TH2F *effdata_tot  = get2DHistogram(fileName, menu, iso, "EffData_TotalError");
	TH2F *effdata_stat = get2DHistogram(fileName, menu, iso, "EffData_StatError");

	TH2F *effmc      = get2DHistogram(fileName, menu, iso, "EffMC_CentralValue");
	TH2F *effmc_tot  = get2DHistogram(fileName, menu, iso, "EffMC_TotalError");
	TH2F *effmc_stat = get2DHistogram(fileName, menu, iso, "EffMC_StatError");

	TH2F *sf      = get2DHistogram(fileName, menu, iso, "SF_CentralValue");
	TH2F *sf_tot  = get2DHistogram(fileName, menu, iso, "SF_TotalError");
	TH2F *sf_stat = get2DHistogram(fileName, menu, iso, "SF_StatError");

	// Remider:
	// x: pt
	// y: eta

	cout << "For Eff Data:" << endl;
	cout << "Number of bins in pt: "  << effdata->GetXaxis()->GetNbins() << endl;
	cout << "Number of bins in eta: " << effdata->GetYaxis()->GetNbins() << endl;

	cout << "For Eff MC:" << endl;
	cout << "Number of bins in pt: "  << effmc->GetXaxis()->GetNbins() << endl;
	cout << "Number of bins in eta: " << effmc->GetYaxis()->GetNbins() << endl;

	cout << "For SF:" << endl;
	cout << "Number of bins in pt: " << sf->GetXaxis()->GetNbins() << endl;
	cout << "Number of bins in eta: " << sf->GetYaxis()->GetNbins() << endl;
}

//
// make 2 dimension plots
//
void make_2D_plots(TString xtitle, TString ytitle, TH2 *hist)
{
    gStyle->SetOptStat(0);
    //SetAtlasStyle();
    bool debug = true;
    //bool debug = false;
    TString name = hist->GetName();
    if (debug) cout << name << endl;
    TCanvas *c1 = new TCanvas(name, name, 800, 800);
    c1->SetRightMargin(0.15);
    hist->SetXTitle(xtitle);
    hist->SetYTitle(ytitle);
    hist->Draw("colz");
    c1->Print("plots/2D_" + name + ".pdf");
}

//
// make 1 dimension projection plots
//
void make_1D_plot(TString xtitle, TString ytitle, TString canvas_name, TString range, float low_edge, float up_edge,
                  TH1F *hData, TH1F* hData_stat, TH1F *hMC = NULL, TH1F *hMC_stat = NULL)
{
    gStyle->SetOptStat(0);
    //SetAtlasStyle();
    
    //bool debug = true;
    bool debug = false;
    TCanvas *c1 = new TCanvas(canvas_name, canvas_name, 800, 800);
    
    TString X_title = xtitle;
    float X_max = hData->GetXaxis()->GetXmax();
    float X_min = hData->GetXaxis()->GetXmin();
    TString Y_title = ytitle;
    double Y_max = 1.10;
    double Y_min = 0.91;
    
    float high, low;
    FindOptimalRange(high, low, hData, hMC);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (Y_max < 1.10)
        Y_max = 1.10;
    else
        Y_max = high;
    if (Y_min > 0.91)
        Y_min = 0.91;
    else
        Y_min = low;
    if (debug)
        cout << "(Y_min, Y_max)=(" << Y_min << ", " << Y_max << ")" << endl;

    hData->SetTitle(canvas_name);
    hData->SetXTitle(X_title);
    hData->SetYTitle(Y_title);
    //hData->GetXaxis()->SetRangeUser(X_min, X_max);
    hData->SetMaximum(Y_max);
    hData->SetMinimum(Y_min);
    
    // Data with total uncertainties
    hData->SetLineWidth(1);
    hData->SetLineColor(kOrange);
    hData->SetMarkerSize(1);
    hData->SetMarkerStyle(kFullCircle);
    hData->SetMarkerColor(kBlue);
    hData->SetFillStyle(1001); // Use total error as color band
    hData->SetFillColor(kOrange);
    hData->Draw("E2");
    // MC with total uncertainties
    if (hMC != NULL) {
        hMC->SetLineWidth(1);
        hMC->SetLineColor(kRed);
        hMC->SetMarkerSize(1);
        hMC->SetMarkerStyle(kFullCircle);
        hMC->SetMarkerColor(kRed);
        hMC->Draw("E1,SAME");
    }
    // Data with statistical uncertainties
    hData_stat->SetLineWidth(1);
    hData_stat->SetLineColor(kBlue);
    hData_stat->SetMarkerSize(1);
    hData_stat->SetMarkerStyle(kFullCircle);
    hData_stat->SetMarkerColor(kBlue);
    hData_stat->Draw("E1,SAME");
    /*
     // MC with statistical uncertainties
     hMC_stat->SetLineWidth(1);
     hMC_stat->SetLineColor(kRed);
     hMC_stat->SetMarkerSize(1);
     hMC_stat->SetMarkerStyle(kFullCircle);
     hMC_stat->SetMarkerColor(kRed);
     hMC_stat->Draw("E1,same");
     */
    TLine *line = new TLine(X_min, 1., X_max,1.);
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->Draw("SAME");
    // Add legend
    TLegend *legend = new TLegend(0.2, 0.7, 0.7, 0.80);
    if (ytitle.Contains("Efficiency"))
        legend->AddEntry(hMC, "Z #rightarrow ee MC with total uncert.", "lp");
    legend->AddEntry(hData, "Data (total uncert.)", "pf");
    legend->AddEntry(hData_stat, "Data (stat uncert.)", "lp");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();
    
    //myText(0.2, 0.85, kBlack, const_cast<char *>(canvas_name.Data()));
    myText(0.2, 0.85, kBlack, const_cast<char *>(range.Data()));
    
    if (xtitle.Contains("eta")) { // projection on eta axis
        TString pt_low_edge = TString::Format("%d", static_cast<int>(low_edge));
        TString pt_up_edge  = TString::Format("%d", static_cast<int>(up_edge));
        if (ytitle.Contains("Efficiency")) // Efficiency plot
            c1->Print("plots/1D_Eff_pt" + pt_low_edge + "_" + pt_up_edge + "_" + canvas_name + ".pdf");
        else // Scale factors plot
            c1->Print("plots/1D_SF_pt" + pt_low_edge + "_" + pt_up_edge + "_" + canvas_name + ".pdf");
    }
    else { // projection on pt axis
        TString eta_low_edge = TString::Format("%d", static_cast<int>(low_edge * 100.));
        TString eta_up_edge  = TString::Format("%d", static_cast<int>(up_edge * 100.));
        if (ytitle.Contains("Efficiency")) // Efficiency plot
            c1->Print("plots/1D_Eff_eta" + eta_low_edge + "_" + eta_up_edge + "_" + canvas_name + ".pdf");
        else // Scale factors plot
            c1->Print("plots/1D_SF_eta" + eta_low_edge + "_" + eta_up_edge + "_" + canvas_name + ".pdf");
    }
}

//
// make 1 dimension projection ratio plots
//
void make_ratio_plot(TString xtitle, TString ytitle, TString canvas_name, TString range, float low_edge, float up_edge,
                  TH1F *hData, TH1F *hMC, TH1F *hSF, TH1F *hSF_stat)
{
    gStyle->SetOptStat(0);
    //SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    TString pad1_X_title = xtitle;
    //float pad1_X_max = hData->GetXaxis()->GetXmax();
    //float pad1_X_min = hData->GetXaxis()->GetXmin();
    float pad1_X_max = 0;
    float pad1_X_min = 0;
    if (xtitle.Contains("eta")) { // projection on eta axis
        pad1_X_max = hData->GetXaxis()->GetXmax();
        pad1_X_min = hData->GetXaxis()->GetXmin();
    }
    else { // projection on pt axis
        pad1_X_max = 200000.;
        pad1_X_min = 7000.;
    }
    TString pad1_Y_title = ytitle;
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;
    TString pad2_X_title = xtitle;
    float pad2_X_max = pad1_X_max;
    float pad2_X_min = pad1_X_min;
    TString pad2_Y_title = "Data / MC";
    double pad2_Y_max = 1.10;
    double pad2_Y_min = 0.91;
    if (debug) {
        cout << "(pad1_X_min, pad1_X_max)=(" << pad1_X_min << ", " << pad1_X_max << ")" << endl;
        cout << "(pad2_X_min, pad2_X_max)=(" << pad2_X_min << ", " << pad2_X_max << ")" << endl;
    }

    float high, low;
    FindOptimalRange(high, low, hData, hMC);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        pad1_Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (pad1_Y_max < 1.10)
        pad1_Y_max = 1.10;
    else
        pad1_Y_max = high;
    if (pad1_Y_min > 0.91)
        pad1_Y_min = 0.91;
    else
        pad1_Y_min = low;
    if (debug)
        cout << "(pad1_Y_min, pad1_Y_max)=(" << pad1_Y_min << ", " << pad1_Y_max << ")" << endl;
    FindOptimalRange(high, low, hSF);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        pad2_Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (pad2_Y_max < 1.10)
        pad2_Y_max = 1.10;
    else
        pad2_Y_max = high;
    if (pad2_Y_min > 0.91)
        pad2_Y_min = 0.91;
    else
        pad2_Y_min = low;
    if (debug)
        cout << "(pad2_Y_min, pad2_Y_max)=(" << pad2_Y_min << ", " << pad2_Y_max << ")" << endl;
    
    // Big Canvas
    TCanvas *c1 = new TCanvas(canvas_name, canvas_name, 800, 800);

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

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here

    // Set titles, maximum and minimum of axes
    hData->SetTitle(canvas_name);
    hData->GetXaxis()->SetTitle(pad1_X_title);
    hData->GetYaxis()->SetTitle(pad1_Y_title);
    if (!xtitle.Contains("eta")) { // projection on pt axis
        hData->GetXaxis()->SetRangeUser(pad1_X_min, pad1_X_max);
    }
    hData->SetMaximum(pad1_Y_max);
    hData->SetMinimum(pad1_Y_min);
    // Data with total uncertianty as color band
    hData->SetLineColor(kBlue);
    hData->SetLineWidth(1);
    hData->SetMarkerColor(kBlue);
    hData->SetMarkerSize(1);
    hData->SetMarkerStyle(kFullCircle);
    hData->Draw("E0");
    // MC
    hMC->SetLineColor(kRed);
    hMC->SetLineWidth(1);
    hMC->SetMarkerColor(kRed);
    hMC->SetMarkerSize(1);
    hMC->SetMarkerStyle(kOpenCircle);
    hMC->Draw("E0,SAME");
    // Add line
    TLine *line = new TLine(pad1_X_min, 1., pad1_X_max, 1.);
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->Draw("SAME");
    // Add legend
    TLegend *leg_top = new TLegend(0.2, 0.5, 0.7, 0.70);
    leg_top->AddEntry(hMC, "Z #rightarrow ee MC", "lp");
    leg_top->AddEntry(hData, "Data", "lp");
    leg_top->SetBorderSize(0);
    leg_top->SetTextFont(42);
    leg_top->SetTextSize(0.04);
    leg_top->SetFillColor(0);
    leg_top->SetFillStyle(0);
    leg_top->Draw();

    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 6.9 fb^{-1}");
    myText(0.2, 0.70, kBlack, const_cast<char *>(range.Data()));

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    TH1F *frame = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle(pad2_X_title);
    frame->GetXaxis()->SetTitleSize(20);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(3.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(16);
    frame->SetYTitle(pad2_Y_title);
    frame->GetYaxis()->SetTitleSize(17);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(2.0);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(16);
    frame->Draw();
    // SF with total uncertianty as color band
    hSF->SetLineColor(kOrange-3);
    hSF->SetLineWidth(1);
    hSF->SetMarkerColor(kBlack);
    hSF->SetMarkerSize(1);
    hSF->SetMarkerStyle(kFullCircle);
    hSF->SetFillStyle(1001); // with color band
    hSF->SetFillColor(kOrange-3);
    hSF->Draw("E2,SAME");
    // SF with statistical uncertianty as color band
    hSF_stat->SetLineColor(kBlack);
    hSF_stat->SetLineWidth(1);
    hSF_stat->SetMarkerColor(kBlack);
    hSF_stat->SetMarkerSize(1);
    hSF_stat->SetMarkerStyle(kFullCircle);
    hSF_stat->Draw("E0,SAME");
    // Add legend
    TLegend *leg_bottom = new TLegend(0.4, 0.8, 0.7, 0.95);
    leg_bottom-> SetNColumns(2);
    leg_bottom->AddEntry(hSF, "Stat #oplus Syst", "pf");
    leg_bottom->AddEntry(hSF_stat, "Stat only", "l");
    leg_bottom->SetBorderSize(0);
    leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
    leg_bottom->Draw();

    if (xtitle.Contains("eta")) { // projection on eta axis
        TString pt_low_edge = TString::Format("%d", static_cast<int>(low_edge));
        TString pt_up_edge  = TString::Format("%d", static_cast<int>(up_edge));
        c1->Print("plots/ratio_pt" + pt_low_edge + "_" + pt_up_edge + "_" + canvas_name + ".pdf");
    }
    else { // projection on pt axis
        TString eta_low_edge = TString::Format("%d", static_cast<int>(low_edge * 100.));
        TString eta_up_edge  = TString::Format("%d", static_cast<int>(up_edge * 100.));
        c1->Print("plots/ratio_eta" + eta_low_edge + "_" + eta_up_edge + "_" + canvas_name + ".pdf");
    }
}

//
// make 1 dimension projection comparison plots
//
void make_compare_plot(TString xtitle, TString ytitle, TString canvas_name, TString range, float low_edge, float up_edge,
                       TString old_legend, TString new_legend, TH1F *hOld, TH1F *hNew)
{
    gStyle->SetOptStat(0);
    //SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    TString X_title = xtitle;
    float X_max = 0;
    float X_min = 0;
    if (xtitle.Contains("eta")) { // projection on eta axis
        X_max = hOld->GetXaxis()->GetXmax();
        X_min = hOld->GetXaxis()->GetXmin();
    }
    else { // projection on pt axis
        X_max = 200000.;
        X_min = 7000.;
    }
    TString Y_title = ytitle;
    double Y_max = 1.10;
    double Y_min = 0.91;
    if (debug) {
        cout << "(X_min, X_max)=(" << X_min << ", " << X_max << ")" << endl;
    }

    float high, low;
    FindOptimalRange(high, low, hOld, hNew);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (Y_max < 1.10)
        Y_max = 1.10;
    else
        Y_max = high;
    if (Y_min > 0.91)
        Y_min = 0.91;
    else
        Y_min = low;
    if (debug)
        cout << "(Y_min, Y_max)=(" << Y_min << ", " << Y_max << ")" << endl;

    // Big Canvas
    TCanvas *c1 = new TCanvas(canvas_name, canvas_name, 800, 800);

    // Set titles, maximum and minimum of axes
    hOld->SetTitle(canvas_name);
    hOld->GetXaxis()->SetTitle(X_title);
    hOld->GetYaxis()->SetTitle(Y_title);
    if (!xtitle.Contains("eta")) { // projection on pt axis
        hOld->GetXaxis()->SetRangeUser(X_min, X_max);
    }
    hOld->SetMaximum(Y_max);
    hOld->SetMinimum(Y_min);
    // Old histogram
    hOld->SetLineColor(kBlue);
    hOld->SetLineWidth(1);
    hOld->SetMarkerColor(kBlue);
    hOld->SetMarkerSize(1);
    hOld->SetMarkerStyle(kFullCircle);
    hOld->Draw("E0");
    // New histogram
    hNew->SetLineColor(kRed);
    hNew->SetLineWidth(1);
    hNew->SetMarkerColor(kRed);
    hNew->SetMarkerSize(1);
    hNew->SetMarkerStyle(kOpenCircle);
    hNew->Draw("E0,SAME");
    // Add line
    TLine *line = new TLine(X_min, 1., X_max, 1.);
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->Draw("SAME");
    // Add legend
    TLegend *leg = new TLegend(0.2, 0.5, 0.7, 0.70);
    leg->AddEntry(hOld, old_legend, "lp");
    leg->AddEntry(hNew, new_legend, "lp");
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();
    
    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 6.9 fb^{-1}");
    myText(0.2, 0.70, kBlack, const_cast<char *>(range.Data()));

    if (xtitle.Contains("eta")) { // projection on eta axis
        TString pt_low_edge = TString::Format("%d", static_cast<int>(low_edge));
        TString pt_up_edge  = TString::Format("%d", static_cast<int>(up_edge));
        c1->Print("plots/comparison_pt" + pt_low_edge + "_" + pt_up_edge + "_" + canvas_name + ".pdf");
    }
    else { // projection on pt axis
        TString eta_low_edge = TString::Format("%d", static_cast<int>(low_edge * 100.));
        TString eta_up_edge  = TString::Format("%d", static_cast<int>(up_edge * 100.));
        c1->Print("plots/comparison_eta" + eta_low_edge + "_" + eta_up_edge + "_" + canvas_name + ".pdf");
    }
}

//
// make 1 dimension projection comparison ratio plots
//
void make_compare_ratio_plot(TString xtitle, TString ytitle, TString canvas_name, TString range, float low_edge, float up_edge,
                             TString old_legend, TString new_legend, TH1F *hOld, TH1F *hNew)
{
    gStyle->SetOptStat(0);
    //SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    TString pad1_X_title = xtitle;
    float pad1_X_max = 0;
    float pad1_X_min = 0;
    if (xtitle.Contains("eta")) { // projection on eta axis
        pad1_X_max = hOld->GetXaxis()->GetXmax();
        pad1_X_min = hOld->GetXaxis()->GetXmin();
    }
    else { // projection on pt axis
        pad1_X_max = 200000.;
        pad1_X_min = 7000.;
    }
    TString pad1_Y_title = ytitle;
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;
    TString pad2_X_title = xtitle;
    float pad2_X_max = pad1_X_max;
    float pad2_X_min = pad1_X_min;
    TString pad2_Y_title = "DS1.3 / pre-recom";
    double pad2_Y_max = 1.10;
    double pad2_Y_min = 0.91;
    if (debug) {
        cout << "(pad1_X_min, pad1_X_max)=(" << pad1_X_min << ", " << pad1_X_max << ")" << endl;
        cout << "(pad2_X_min, pad2_X_max)=(" << pad2_X_min << ", " << pad2_X_max << ")" << endl;
    }

    float high, low;
    FindOptimalRange(high, low, hOld, hNew);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        pad1_Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (pad1_Y_max < 1.10)
        pad1_Y_max = 1.10;
    else
        pad1_Y_max = high;
    if (pad1_Y_min > 0.91)
        pad1_Y_min = 0.91;
    else
        pad1_Y_min = low;
    if (debug)
        cout << "(pad1_Y_min, pad1_Y_max)=(" << pad1_Y_min << ", " << pad1_Y_max << ")" << endl;

    // Calculate the ratio between hOld and hNew
    hOld->Sumw2();
    hNew->Sumw2();
    //TH1F *ratio = (TH1F *)hNew->Clone();
    //ratio->Divide(hOld);
    // Philip modify the histograms in the recommendation, so the number of bins in my histograms are different from recommendation.
    TH1F *ratio;
	if (xtitle.Contains("eta")) { // projection on eta axis
    	ratio = (TH1F *)hNew->Clone();
    	ratio->Divide(hOld);
    }
	else { // projection on pt axis
		// because hOld and hNew have different number of bins
		// the Divide() doesn't work. I need to calculate by myself.
		ratio = (TH1F *)hOld->Clone();
		ratio->Reset();
    	for (int i = 1; i <= ratio->GetNbinsX(); i++) {
			double new_central = hNew->GetBinContent(i + 1); // The first bin is 4 to 7 GeV, we need to start from second bin 7 to 10 GeV.
			double new_error   = hNew->GetBinError(i + 1);
			double old_central = hOld->GetBinContent(i); // The first bin in recommendation is 7 to 10 GeV.
			double old_error   = hOld->GetBinError(i);
			double ratio_central = new_central / old_central;
			// Error propagation: Dz/Z = sqrt( (Dx/X)^2 + (Dy/Y)^2 )
			double ratio_error = ratio_central * sqrt(pow(new_error / new_central, 2) + pow(old_error / old_central, 2));
			ratio->SetBinContent(i, ratio_central);
			ratio->SetBinError(i, ratio_error);
		}
	}
    FindOptimalRange(high, low, ratio);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        pad2_Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (pad2_Y_max < 1.10)
        pad2_Y_max = 1.10;
    else
        pad2_Y_max = high;
    if (pad2_Y_min > 0.91)
        pad2_Y_min = 0.91;
    else
        pad2_Y_min = low;
    if (debug)
        cout << "(pad2_Y_min, pad2_Y_max)=(" << pad2_Y_min << ", " << pad2_Y_max << ")" << endl;

    // Big Canvas
    TCanvas *c1 = new TCanvas(canvas_name, canvas_name, 800, 800);

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

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here

    // Set titles, maximum and minimum of axes
    hOld->SetTitle(canvas_name);
    hOld->GetXaxis()->SetTitle(pad1_X_title);
    hOld->GetYaxis()->SetTitle(pad1_Y_title);
    if (!xtitle.Contains("eta")) { // projection on pt axis
        hOld->GetXaxis()->SetRangeUser(pad1_X_min, pad1_X_max);
    }
    hOld->SetMaximum(pad1_Y_max);
    hOld->SetMinimum(pad1_Y_min);
    // Old histogram
    hOld->SetLineColor(kBlue);
    hOld->SetLineWidth(1);
    hOld->SetMarkerColor(kBlue);
    hOld->SetMarkerSize(1);
    hOld->SetMarkerStyle(kFullCircle);
    hOld->Draw("E0");
    // New histogram
    hNew->SetLineColor(kRed);
    hNew->SetLineWidth(1);
    hNew->SetMarkerColor(kRed);
    hNew->SetMarkerSize(1);
    hNew->SetMarkerStyle(kOpenCircle);
    hNew->Draw("E0,SAME");
    // Add line
    TLine *line = new TLine(pad1_X_min, 1., pad1_X_max, 1.);
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->Draw("SAME");
    // Add legend
    TLegend *leg_top = new TLegend(0.2, 0.5, 0.7, 0.70);
    leg_top->AddEntry(hOld, old_legend, "lp");
    leg_top->AddEntry(hNew, new_legend, "lp");
    leg_top->SetBorderSize(0);
    leg_top->SetTextFont(42);
    leg_top->SetTextSize(0.04);
    leg_top->SetFillColor(0);
    leg_top->SetFillStyle(0);
    leg_top->Draw();

    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 6.9 fb^{-1}");
    myText(0.2, 0.70, kBlack, const_cast<char *>(range.Data()));

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    TH1F *frame = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle(pad2_X_title);
    frame->GetXaxis()->SetTitleSize(20);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(3.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(16);
    frame->SetYTitle(pad2_Y_title);
    frame->GetYaxis()->SetTitleSize(17);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(2.0);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(16);
    frame->Draw();

    ratio->SetLineColor(kBlack);
    ratio->SetLineWidth(1);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerSize(1);
    ratio->SetMarkerStyle(20);
    ratio->Draw("E1,same");
    
    if (xtitle.Contains("eta")) { // projection on eta axis
        TString pt_low_edge = TString::Format("%d", static_cast<int>(low_edge));
        TString pt_up_edge  = TString::Format("%d", static_cast<int>(up_edge));
        c1->Print("plots/comparison_ratio_pt" + pt_low_edge + "_" + pt_up_edge + "_" + canvas_name + ".pdf");
    }
    else { // projection on pt axis
        TString eta_low_edge = TString::Format("%d", static_cast<int>(low_edge * 100.));
        TString eta_up_edge  = TString::Format("%d", static_cast<int>(up_edge * 100.));
        c1->Print("plots/comparison_ratio_eta" + eta_low_edge + "_" + eta_up_edge + "_" + canvas_name + ".pdf");
    }
}
