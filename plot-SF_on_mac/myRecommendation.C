// This script is used to prepare recommendations.
// Set SF centeral value to 1 and uncertainty to 0 if:
// 1. MC stat = 0 (EffMC_CentralValue=1 and error = 0)
// 2. Uncertainties of SF is too big.
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>

#include "iostream"
#include "get13TeV2DHistogram.C"

using namespace std;

void myRecommendation(TString menu = "TightLLH_d0z0_v10",
                      TString iso = "isolTight")
{
	TString inupt_filemame = "ScaleFactors.root";

	// Create SF recommdnation and fill the central value and total error.
	TH2F *sf     = get13TeV2DHistogram(inupt_filemame, menu, iso, "SF_CentralValue");
	TH2F *sf_tot = get13TeV2DHistogram(inupt_filemame, menu, iso, "SF_TotalError");

	//cout << "Number of bins in SF_CentralValue is " << sf->GetSize() << endl;
	//cout << "Number of bins in SF_TotalError is " << sf_tot->GetSize() << endl;

	TH2F *sf_recommendation = (TH2F *)sf->Clone("FullSim_sf");

	for (int ik = 1; ik < sf->GetSize(); ik++) {
		float err = sf_tot->GetBinContent(ik);
		sf_recommendation->SetBinError(ik, err);
	}

/*
	for (int pt_bin = 1; pt_bin <= sf_recommendation->GetNbinsX(); pt_bin++) {
		for (int eta_bin = 1; eta_bin <= sf_recommendation->GetNbinsY(); eta_bin++) {
			if (pt_bin >= 15) {
				cout << "(" << pt_bin << ", " << eta_bin << "): SF="
				     << sf_recommendation->GetBinContent(pt_bin, eta_bin) << "+-" 
				     << sf_recommendation->GetBinError(pt_bin, eta_bin) << endl;
			}
		}
	}
	//cout << sf_recommendation->GetBinContent(17, 17) << endl;
	//cout << sf_recommendation->GetBinError(17, 17) << endl;
	sf_recommendation->Draw("colz,texte");
*/

	// We don't provide SF if MC stat is 0, so we need to do some correction on SF recommendation.
	cout << "Correcting SF recommendation..." << endl;
	TH2F *eff_MC_central_value = get13TeV2DHistogram(inupt_filemame, menu, iso, "EffData_CentralValue");
	TH2F *eff_MC_stat_error    = get13TeV2DHistogram(inupt_filemame, menu, iso, "EffMC_StatError");
	TH2F *eff_MC_syst_error    = get13TeV2DHistogram(inupt_filemame, menu, iso, "EffMC_SystError");
	TH2F *eff_MC_total_error   = get13TeV2DHistogram(inupt_filemame, menu, iso, "EffMC_TotalError");

	int nbins_pt  = eff_MC_central_value->GetNbinsX();
	int nbins_eta = eff_MC_central_value->GetNbinsY();

	for (int pt_bin = 1; pt_bin <= nbins_pt; pt_bin++) {
		for (int eta_bin = 1; eta_bin <= nbins_eta; eta_bin++) {
			double pt_bin_low_edge = eff_MC_central_value->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.;
			//double pt_bin_up_edge  = eff_MC_central_value->GetXaxis()->GetBinUpEdge(pt_bin) / 1000.;
			//double eta_bin_low_edge = eff_MC_central_value->GetYaxis()->GetBinLowEdge(eta_bin);
			//double eta_bin_up_edge  = eff_MC_central_value->GetYaxis()->GetBinUpEdge(eta_bin);

			if (pt_bin_low_edge >= 200.){
				//cout << "pt_bin_low_edge=" << pt_bin_low_edge << endl;
				double mc_central_value = eff_MC_central_value->GetBinContent(pt_bin, eta_bin);
				double mc_stat_error    = eff_MC_stat_error->GetBinContent(pt_bin, eta_bin);
				double mc_syst_error    = eff_MC_syst_error->GetBinContent(pt_bin, eta_bin);
				double mc_tot_error     = eff_MC_total_error->GetBinContent(pt_bin, eta_bin);
				if (mc_central_value == 1. &&
				    mc_stat_error == 0. &&
				    mc_syst_error == 0. &&
				    mc_tot_error == 0.) {
					sf_recommendation->SetBinContent(pt_bin, eta_bin, 1.);
					sf_recommendation->SetBinError(pt_bin, eta_bin, 0.);
				}
			}

			// If the uncertainties are too big, then set it to zero
			if (sf_recommendation->GetBinError(pt_bin, eta_bin) >= 10.) {
				sf_recommendation->SetBinContent(pt_bin, eta_bin, 1.);
				sf_recommendation->SetBinError(pt_bin, eta_bin, 0.);
			}
		}
	}
/*
	cout << eff_MC_central_value->GetBinContent(17, 2) << endl;
	cout << eff_MC_stat_error->GetBinContent(17, 2) << endl;
	cout << eff_MC_syst_error->GetBinContent(17, 2) << endl;
	cout << eff_MC_total_error->GetBinContent(17, 2) << endl;
	cout << sf_recommendation->GetBinContent(17, 2) << endl;
	cout << sf_recommendation->GetBinError(17, 2) << endl;

	gStyle->SetPaintTextFormat(".3f");
	sf_recommendation->Draw("colz,texte");
	gPad->SetLogx(1);
*/

	// Prepare recommendation root file
	TString output_filename;

	if (menu.Contains("v6")) {
		TString mIDlab;
		if (menu == "TightLLHMC15_v6") mIDlab = "TightLH";
		else if (menu == "MediumLLHMC15_v6") mIDlab = "MediumLH";

		TString mIsollab;
		if (iso == "isolTight") mIsollab = "Tight";
		else if (iso == "isolLoose") mIsollab = "Loose";
		else if (iso == "isolLooseTrackOnly") mIsollab = "LooseTrackOnly";
		else if (iso == "isolGradient") mIsollab = "Gradient";
		else if (iso == "isolGradientLoose") mIsollab = "GradientLoose";

		output_filename = "recommendations/efficiencySF.Isolation." + mIsollab + "." + mIDlab + ".2015.13TeV.rel20p0.v02.root";
		// I provide v02 but Kristin changes the version to v03.
	}
	else if (menu.Contains("v8")) {
/*
		TString mIDlab;
		if (menu == "TightLLH_d0z0_v8") mIDlab = "TightLH";
		else if (menu == "MediumLLH_d0z0_v8") mIDlab = "MediumLH";
		else if (menu == "LooseLLH_d0z0_v8") mIDlab = "LooseLH";
		else if (menu == "LooseAndBLayerLLH_d0z0_v8") mIDlab = "LooseAndBLayerLH";

		if (menu == "TightLLHMC15_v8") mIDlab = "TightLH";
		else if (menu == "MediumLLHMC15_v8") mIDlab = "MediumLH";
		else if (menu == "LooseLLHMC15_v8") mIDlab = "LooseLH";
		else if (menu == "LooseAndBLayerLLHMC15_v8") mIDlab = "LooseAndBLayerLH";

		TString mIsollab;
		if (iso == "isolTight") mIsollab = "Tight";
		else if (iso == "isolLoose") mIsollab = "Loose";
		else if (iso == "isolLooseTrackOnly") mIsollab = "LooseTrackOnly";
		else if (iso == "isolGradient") mIsollab = "Gradient";
		else if (iso == "isolGradientLoose") mIsollab = "GradientLoose";
		else if (iso == "isolFixedCutTightTrackOnly") mIsollab = "FixedCutTightTrackOnly";
		else if (iso == "isolFixedCutTight") mIsollab = "FixedCutTight";
		else if (iso == "isolFixedCutLoose") mIsollab = "FixedCutLoose";
		else if (iso == "isolPhFixedCutTightCaloOnly") mIsollab = "PhFixedCutTightCaloOnly";
		else if (iso == "isolPhFixedCutTight") mIsollab = "PhFixedCutTight";
		else if (iso == "isolPhFixedCutLoose") mIsollab = "PhFixedCutLoose";
 
		//output_filename = "recommendations/efficiencySF.Isolation." + mIsollab + "." + mIDlab + ".2015.13TeV.rel20p0.25ns.v03.root";
*/
		output_filename = "recommendations/efficiencySF.Isolation." + menu + "_" + iso + ".2015.13TeV.rel20p0.25ns.v03.root";
		// I provide v03 but Philip changes the version to v04.
	}
	else if (menu.Contains("v10")) {
		output_filename = "recommendations/efficiencySF.Isolation." + menu + "_" + iso + ".2015.13TeV.rel20p0.25ns.v05.root";
	}

	TString runRangeValidity = "0_99999999999";
	TFile *foutput = new TFile(output_filename, "RECREATE");
	foutput->mkdir(runRangeValidity.Data());
	foutput->cd(runRangeValidity.Data());
	sf_recommendation->Write();
	foutput->Close();
}
