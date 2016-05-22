#include <iostream>

using namespace std;

#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

// Global variables
const TString menu[3] = {"TightLLH", "MediumLLH", "LooseAndBLayerLLH"}
const isol[11] = {"isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose", 
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
