// This is used to make Mll plots for etach pT bins.
// Modified from Ximo's myPlot.C
// Usage: root myPlot.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlusAndCaloIso\",true)"
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

void myPlot(TString menu = "TightLLHMC15_v9",
			TString iso = "isolTight",
			TString tag = "TagTightLLHMC15_v8",
			bool isData = true)
{
	SetAtlasStyle();

	gStyle->SetPadTopMargin(0.06);

	TFile *_file0;
	if (isData)
		_file0 = TFile::Open("../merged-hist-data.root");
	else
		_file0 = TFile::Open("../merged-hist-mc.root");
  
	if (iso != "") iso = "_" + iso;
	TString folder = menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag;
  
	TString histo;
	if (isData)
		histo =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_Data_Den_Mll_3d";
	else
		histo =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_MCZee_NoFilter_Den_Mll_3d";
	cout << "TH3 Den to get: " << folder + "/" + histo << endl;
	TH3F *my3d = (TH3F *)_file0->Get(folder + "/" + histo);

  	TString histoNum;
	if (isData)
		histoNum =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_Data_Num_Mll_3d";
	else
		histoNum =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_MCZee_NoFilter_Num_Mll_3d";
	cout << "TH3 Num to get: " << folder + "/" + histoNum << endl;
	TH3F *my3dNum = (TH3F *)_file0->Get(folder + "/" + histoNum);

	// Remider:
	// x: pt
	// y: eta
	// z: mll

	cout << "Number of bins in pt: "  << my3d->GetXaxis()->GetNbins() << endl;
	cout << "Number of bins in eta: " << my3d->GetYaxis()->GetNbins() << endl;

	// Big Canvas
  	TCanvas *c1 = new TCanvas(menu + "_" + iso + "_" + tag, menu + "_" + iso + "_" + tag, 1600, 800);
	c1->Divide(6, 3);

	TH1F *mllDen[30];
	TH1F *mllNum[30];
	//for (int pt = 4; pt < my3d->GetXaxis()->GetNbins() + 1; pt++){
	for (int pt = 2; pt < my3d->GetXaxis()->GetNbins() + 1; pt++){
		my3d->GetXaxis()->SetRange(pt, pt);
		my3dNum->GetXaxis()->SetRange(pt, pt);

		mllDen[pt] = (TH1F *)my3d->Project3D("z")->Clone();
		mllNum[pt] = (TH1F *)my3dNum->Project3D("z")->Clone();
		//c1->cd(pt - 3);
		c1->cd(pt - 1);
		mllDen[pt]->Draw("hist");
		mllNum[pt]->Draw("hist,same");
		cout << pt << "(" << my3d->GetXaxis()->GetBinLowEdge(pt) << "," << my3d->GetXaxis()->GetBinLowEdge(pt + 1) 
			 << "): " << mllNum[pt]->GetEntries() 
			 << " / " << mllDen[pt]->GetEntries() 
			 << endl;

		// Some cosmetics
		mllDen[pt]->GetXaxis()->SetRangeUser(60, 140);
		mllDen[pt]->SetMarkerSize(0.8);
		mllDen[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
		mllDen[pt]->GetYaxis()->SetTitle("Events");
		mllDen[pt]->SetMarkerColor(kRed);
		mllDen[pt]->SetLineColor(kRed);
		mllDen[pt]->SetLineWidth(1);
		mllNum[pt]->SetLineStyle(1);
		mllNum[pt]->SetLineWidth(1);
		mllNum[pt]->SetMarkerSize(0.8);
		mllNum[pt]->SetMarkerColor(kBlue);
		mllNum[pt]->SetLineColor(kBlue);

		char name[100];
		sprintf(&name[0], "p_{T} bin: %d - %d GeV", 
				static_cast<int>(my3d->GetXaxis()->GetBinLowEdge(pt) / 1000.), 
				static_cast<int>(my3d->GetXaxis()->GetBinLowEdge(pt + 1) / 1000.) );
		myText(0.30, 0.95, kBlack, name, 0.068);

		myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
		myText(0.55, 0.66, kBlack, const_cast<char *>(tag.Data()) );

		if (isData)
			sprintf(&name[0], "Data");
		else
			sprintf(&name[0], "Z#rightarrow ee MC");
		myText(0.25, 0.88, kBlack, name);

		// Dump some integrals 80<mll<100
		sprintf(&name[0], "Num (80-100 GeV): %3.0f",
				mllNum[pt]->Integral(mllNum[pt]->GetXaxis()->FindBin(80),
				mllNum[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.57, kBlue, name);
		sprintf(&name[0], "Den (80-100 GeV): %3.0f",
				mllDen[pt]->Integral(mllDen[pt]->GetXaxis()->FindBin(80),
				mllDen[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.50, kRed, name);
	}

	if(isData){
		//c1->SaveAs("plots/"+menu+iso+"_"+tag+"_data.png", "png");
		c1->SaveAs("plots/Mll_" + menu + iso + "_" + tag + "_data.pdf", "pdf");
	}
	else{
		//c1->SaveAs("plots/"+menu+iso+"_"+tag+"_mc.png", "png");
		c1->SaveAs("plots/Mll_" + menu + iso + "_" + tag + "_mc.pdf", "pdf");
	}
}
