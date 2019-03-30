#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>
#include <TCanvas.h>

void myMakeSF2DPlots()
{
	TString menu[3] = {"TightLH", "MediumLH", "LooseAndBLayerLH"};
	TString iso[11] = {"Tight", "Loose", "LooseTrackOnly", "Gradient", "GradientLoose",
					   "FixedCutTightTrackOnly", "FixedCutTight", "FixedCutLoose",
					   "PhFixedCutTightCaloOnly", "PhFixedCutTight", "PhFixedCutLoose"};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 11; j++) {
			TString filename = "efficiencySF.Isolation." + iso[j] + "." + menu[i] + ".2015.13TeV.rel20p0.v04.root";
			TFile *f = TFile::Open("recommendations/" + filename);
			TH2F *sf = (TH2F *)f->Get("0_99999999999/FullSim_sf");
			gStyle->SetPaintTextFormat(".3f");
			TCanvas *c1 = new TCanvas("c1", "c1", 2000, 1000);
			gPad->SetLogx();
			sf->SetMarkerSize(0.8);
			sf->SetXTitle("p_{T} [MeV]");
			sf->SetYTitle("#eta");
			sf->GetXaxis()->SetRangeUser(7000,150000);
			sf->SetStats(0);
			sf->Draw("colz,texte");
        	c1->SaveAs("SF2D_" + menu[i] + "." + iso[j] + ".pdf", "pdf");
			f->Close();
		}
	}
}
