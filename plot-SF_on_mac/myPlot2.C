// This is used to make Mll plots for pT = 35-40 GeV.
// Usage: root myPlot2.C"(\"TightLLHMC15_v6\",\"TagTightPlusPlusAndCaloIso\",true)"
//
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
using namespace std;

void myPlot2(TString menu = "TightLLHMC15_v9",
			 TString tag  = "TagTightLLHMC15_v8",
			 bool isData  = true)
{
	SetAtlasStyle();
  
	TFile *_file0;
	if (isData)
		_file0 = TFile::Open("../merged-hist-data.root");
	else
		_file0 = TFile::Open("../merged-hist-mc.root");

	//TString iso[5] = {"isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose"};
	TString iso[11] = {"isolTight", "isolLoose", "isolLooseTrackOnly", "isolGradient", "isolGradientLoose",
					   "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose",
					   "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"};

	// For 50 ns study
	//TString bkg_template = "TemplVariation1AndPassTrackQuality";
	// For Run2 25 ns study
	TString bkg_template = "TemplRun2Variation1AndPassTrackQuality";
	//TString bkg_template = "TemplRun2Variation2AndPassTrackQuality";

	// Big Canvas
	TCanvas *c1 = new TCanvas("c1", "c1", 1600, 800);
	c1->Divide(4, 3);

	//for (int i = 0; i < 5; i++) {
	for (int i = 0; i < sizeof(iso)/sizeof(iso[0]); i++) {
		TString folder = menu + "_" + iso[i] + "_" + bkg_template + "_" + tag;
    
		TString histo;
		if (isData)
			histo =  menu + "_" + iso[i] + "_" + bkg_template + "_" + tag + "_Data_Den_Mll_3d";
		else
			histo =  menu + "_" + iso[i] + "_" + bkg_template + "_" + tag + "_MCZee_NoFilter_Den_Mll_3d";
		cout << "TH3 Den to get: " << folder + "/" + histo << endl;
		TH3F *my3d = (TH3F *)_file0->Get(folder + "/" + histo);

		TString histoNum;
		if (isData)
			histoNum =  menu + "_" + iso[i] + "_" + bkg_template + "_" + tag + "_Data_Num_Mll_3d";
		else
			histoNum =  menu + "_" + iso[i] + "_" + bkg_template + "_" + tag + "_MCZee_NoFilter_Num_Mll_3d";
		cout << "TH3 Num to get: " << folder + "/" + histoNum << endl;
		TH3F *my3dNum = (TH3F *)_file0->Get(folder + "/" + histoNum);

    	// Remider:
    	// x: pt
    	// y: eta
    	// z: mll

    	cout << "Number of bins in pt: "  << my3d->GetXaxis()->GetNbins() << endl;
    	cout << "Number of bins in eta: " << my3d->GetYaxis()->GetNbins() << endl;

    	int pt_bin = 8; // pT 35 to pT 40

    	my3d->GetXaxis()->SetRange(pt_bin, pt_bin);
    	my3dNum->GetXaxis()->SetRange(pt_bin, pt_bin);
  
    	TH1F *mllDen = (TH1F *)my3d->Project3D("z")->Clone();
    	TH1F *mllNum = (TH1F *)my3dNum->Project3D("z")->Clone();
    	c1->cd(i + 1);
    	mllDen->Draw("hist");
    	mllNum->Draw("hist,same");
    	cout << pt_bin << "(" << my3d->GetXaxis()->GetBinLowEdge(pt_bin) << "," << my3d->GetXaxis()->GetBinLowEdge(pt_bin + 1)
	 		 << "): " << mllNum->GetEntries()
	 		 << " / " << mllDen->GetEntries()
	 		 << endl;
    
    	// Some cosmetics
    	mllDen->GetXaxis()->SetRangeUser(60, 140);
    	mllDen->SetMarkerSize(0.8);
    	mllDen->GetXaxis()->SetTitle("m_{ll} [GeV]");
    	mllDen->GetYaxis()->SetTitle("Events");
    	mllDen->SetMarkerColor(kRed);
    	mllDen->SetLineColor(kRed);
    	mllDen->SetLineWidth(1);
    	mllNum->SetLineStyle(1);
    	mllNum->SetMarkerSize(0.8);
    	mllNum->SetMarkerColor(kBlue);
    	mllNum->SetLineColor(kBlue);
    	mllNum->SetLineWidth(1);

    	char name[100];
    	sprintf(&name[0],"p_{T} bin: %d - %d GeV", 
				static_cast<int>(my3d->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.), 
				static_cast<int>(my3d->GetXaxis()->GetBinLowEdge(pt_bin + 1) / 1000.) );
    	myText(0.55, 0.88, kBlack, name);

    	myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
    	myText(0.55, 0.72, kBlack, const_cast<char *>(iso[i].Data()) );
    	myText(0.55, 0.66, kBlack, const_cast<char *>(tag.Data()) );

    	if (isData)
			sprintf(&name[0], "Data");
    	else
			sprintf(&name[0], "Z#rightarrow ee MC");
		myText(0.25, 0.88, kBlack, name);

    	// Dump some integrals 80<mll<100
    	sprintf(&name[0], "Num (80-100 GeV): %3.0f",
				mllNum->Integral(mllNum->GetXaxis()->FindBin(80),
				mllNum->GetXaxis()->FindBin(100)) );
    	myText(0.55, 0.57, kBlue, name);
    	sprintf(&name[0], "Den (80-100 GeV): %3.0f",
				mllDen->Integral(mllDen->GetXaxis()->FindBin(80),
				mllDen->GetXaxis()->FindBin(100)) );
    	myText(0.55, 0.50, kRed, name);
  	}

	if (isData){
		c1->SaveAs("plots/Mll_pT35-40_" + menu + "_" + tag + "_data.pdf", "pdf");
	}
	else{
   		c1->SaveAs("plots/Mll_pT35-40_" + menu + "_" + tag + "_mc.pdf", "pdf");
  	}
}
