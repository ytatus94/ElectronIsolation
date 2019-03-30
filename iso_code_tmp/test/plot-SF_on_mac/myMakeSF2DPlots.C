// This is used to make 2-dim SF plots for recommendations.
// Usage: root -l myMakeSF2DPlots.C
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>
#include <TCanvas.h>

void myMakeSF2DPlots()
{
	// v6
	//TString menu[3] = {"TightLH", "MediumLH", "LooseAndBLayerLH"};
	// EOYE recommendations && Moriond recommendations
	//TString menu[3] = {"TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"};
	// v10
	TString menu[1] = {"TightLLH_d0z0_v10"};
	TString iso[11] = {"Tight", "Loose", "LooseTrackOnly", "Gradient", "GradientLoose",
                           "FixedCutTightTrackOnly", "FixedCutTight", "FixedCutLoose",
                           "PhFixedCutTightCaloOnly", "PhFixedCutTight", "PhFixedCutLoose"};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			// v6
			//TString filename = "efficiencySF.Isolation." + iso[j] + "." + menu[i] + ".2015.13TeV.rel20p0.v04.root";
			// EOYE recommendations
			//TString filename = "efficiencySF.Isolation." + menu[i] + "_isol" + iso[j] + ".2015.13TeV.rel20p0.25ns.v04.root";
			// v10
			TString filename = "efficiencySF.Isolation." + menu[i] + "_isol" + iso[j] + ".2015.13TeV.rel20p0.25ns.v05.root";
			TFile *f = TFile::Open("recommendations/" + filename);
			TH2F *sf = (TH2F *)f->Get("0_99999999999/FullSim_sf");
			gStyle->SetPaintTextFormat(".3f");
			gStyle->SetOptStat(0);
			TCanvas *c1 = new TCanvas("c1", "c1", 2000, 1000);
			c1->SetLogx();
			TString title = "SF_CentralValue_" + menu[i] + "_isol" + iso[j];
			sf->SetTitle(title);
			sf->SetMarkerSize(0.8);
			sf->SetXTitle("p_{T} [MeV]");
			sf->SetYTitle("#eta");
			sf->GetXaxis()->SetRangeUser(7000, 150000);
			sf->Draw("colz,texte");
			c1->SaveAs("plots/SF2D_" + menu[i] + "_isol" + iso[j] + ".pdf", "pdf");
			f->Close();
		}
	}
}
