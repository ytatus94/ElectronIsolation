#include <TROOT.h>
#include <TFile.h>
#include <TString.h>

#include "get13TeV2DHistogram.C"

void myMakeInputSF(TString menu = "TightLLHMC15_v6",
				   TString iso = "isolTight")
{
    TH2F *sf = get13TeV2DHistogram(menu, iso, "SF_CentralValue");
    TH2F *sf_tot = get13TeV2DHistogram(menu, iso, "SF_TotalError"); 

	cout << "Number of bins in SF_CentralValue is " << sf->GetSize() << endl;
	cout << "Number of bins in SF_TotalError is " << sf_tot->GetSize() << endl;

	TH2F *sf_final = (TH2F *)sf->Clone("FullSim_sf");

	for (int ik = 1; ik < sf->GetSize(); ik++) {
		float err = sf_tot->GetBinContent(ik);	
		sf_final->SetBinError(ik, err);	
	}

	TString mIDlab;
	if (menu == "TightLLHMC15_v6") mIDlab = "TightLH";
	else if (menu == "MediumLLHMC15_v6") mIDlab = "MediumLH";

	TString mIsollab;
	if (iso == "isolTight") mIsollab = "Tight";
	else if (iso == "isolLoose") mIsollab = "Loose";
	else if (iso == "isolLooseTrackOnly") mIsollab = "LooseTrackOnly";
	else if (iso == "isolGradient") mIsollab = "Gradient";
	else if (iso == "isolGradientLoose") mIsollab = "GradientLoose";


	TString runRangeValidity = "0_99999999999";
    TString output_filename = "recommendations/efficiencySF.Isolation." + mIsollab + "." + mIDlab + ".2015.13TeV.rel20p0.v02.root";
	TFile *foutput = new TFile(output_filename, "RECREATE");
	foutput->mkdir(runRangeValidity.Data());
	foutput->cd(runRangeValidity.Data());
	sf_final->Write();
	foutput->Close();
}
