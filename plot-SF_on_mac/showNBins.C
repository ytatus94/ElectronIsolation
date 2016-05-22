// This script is used to show the number of bins in the 2 dim histograms.
// Remember to check the number of bins before run other scripts.
// Usage: root -l showNBins.C"(\"output/ScaleFactors.root\",\"TightLLH_d0z0_v8\",\"isolTight\")"
//
#include <TROOT.h>
#include <TFile.h>
#include <TH2.h>
//#include "get2DHistogram.C"
#include "ytUtilities.C"
#include <iostream>
using namespace std;

void showNBins(TString fileName,
               TString menu,
               TString iso)
{
	//TString fileName = "../output-SF/ScaleFactors.root";
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
