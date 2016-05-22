// This is used to make Mll plots for etach pT bins.
// Overlay denominator of MC to data. MC normalized to data integral
// Modified from Ximo's myPlot.C
// Usage: root myPlot6.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlusAndCaloIso\",true)"
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include <iostream>

void myPlot6(TString menu = "TightLLHMC15_v9",
			 TString iso = "isolTight",
			 TString tag = "TagTightLLHMC15_v8")
{
	SetAtlasStyle();

	gStyle->SetPadTopMargin(0.08);

	TFile *data_file = TFile::Open("../merged-hist-data.root");
	TFile *mc_file   = TFile::Open("../merged-hist-mc.root");
  
	if (iso != "") iso = "_" + iso;
	TString folder = menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag;

	TString data_histo = menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_Data_Den_Mll_3d";
	TString mc_histo   = menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_MCZee_NoFilter_Den_Mll_3d";

	TH3F *data_3d = (TH3F *)data_file->Get(folder + "/" + data_histo);
	TH3F *mc_3d   = (TH3F *)mc_file->Get(folder + "/" + mc_histo);

	// Remider:
	// x: pt
	// y: eta
	// z: mll
/*
	cout << "Number of bins in pt: "  << my3d->GetXaxis()->GetNbins() << endl;
	cout << "Number of bins in eta: " << my3d->GetYaxis()->GetNbins() << endl;
*/

	// Big Canvas
  	TCanvas *c1 = new TCanvas(menu + "_" + iso + "_" + tag, menu + "_" + iso + "_" + tag, 1600, 800);
	c1->Divide(6, 3);

	TH1F *data_mll_den[30];
	TH1F *mc_mll_den[30];

	for (int pt = 2; pt < data_3d->GetXaxis()->GetNbins() + 1; pt++){
		data_3d->GetXaxis()->SetRange(pt, pt);
		mc_3d->GetXaxis()->SetRange(pt, pt);

		data_mll_den[pt] = (TH1F *)data_3d->Project3D("z")->Clone();
		mc_mll_den[pt]   = (TH1F *)mc_3d->Project3D("z")->Clone();

		c1->cd(pt - 1);

		// Scale MC to data
		double data_area = data_mll_den[pt]->Integral();
		double mc_area   = mc_mll_den[pt]->Integral();

		mc_mll_den[pt]->Scale(data_area / mc_area);

		mc_mll_den[pt]->Draw("hist");
		data_mll_den[pt]->Draw("hist,same");

		cout << "MC: " << pt << "(" << mc_3d->GetXaxis()->GetBinLowEdge(pt) 
			 << "," << mc_3d->GetXaxis()->GetBinUpEdge(pt)
			 << "): " << mc_mll_den[pt]->GetEntries() << endl;
		cout << "Data: " << pt << "(" << data_3d->GetXaxis()->GetBinLowEdge(pt) 
			 << "," << data_3d->GetXaxis()->GetBinUpEdge(pt)
			 << "): " << data_mll_den[pt]->GetEntries() << endl;

		// Some cosmetics
		mc_mll_den[pt]->GetXaxis()->SetRangeUser(60, 140);
		mc_mll_den[pt]->SetMarkerSize(0.8);
		mc_mll_den[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
		mc_mll_den[pt]->GetYaxis()->SetTitle("Events");
		mc_mll_den[pt]->SetMarkerColor(kRed);
		mc_mll_den[pt]->SetLineColor(kRed);
		mc_mll_den[pt]->SetLineWidth(1);
		data_mll_den[pt]->SetLineStyle(1);
		data_mll_den[pt]->SetLineWidth(1);
		data_mll_den[pt]->SetMarkerSize(0.8);
		data_mll_den[pt]->SetMarkerColor(kBlue);
		data_mll_den[pt]->SetLineColor(kBlue);

		// Add pT range at the top of plot
		char name[100];
		sprintf(&name[0], "p_{T} bin: %d - %d GeV", 
				static_cast<int>(data_3d->GetXaxis()->GetBinLowEdge(pt) / 1000.), 
				static_cast<int>(data_3d->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
		myText(0.30, 0.95, kBlack, name, 0.068);

		myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
		myText(0.55, 0.66, kBlack, const_cast<char *>(tag.Data()) );

		TLegend *leg = new TLegend(0.55, 0.38, 0.9, 0.54);
		leg->AddEntry(data_mll_den[pt], "Data", "l");
		leg->AddEntry(mc_mll_den[pt], "MC", "l");
		leg->SetBorderSize(0);
		leg->SetFillColor(0);
		leg->SetFillStyle(0);
		leg->Draw();
	}

	c1->SaveAs("plots/Mll_den_" + menu + iso + "_" + tag + ".pdf", "pdf");
}
