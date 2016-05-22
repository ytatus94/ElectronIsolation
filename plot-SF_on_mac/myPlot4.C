// This is used to make Mll plots for one pT bins. To show the bump at when pT > 120GeV is coming from difference bin size.
// normalizing those bins by their bin with: contents = contenst/bin_width (then the y-axis is "Events/GeV")
// Modified from Ximo's myPlot.C
// Usage: root myPlot4.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlusAndCaloIso\",true)"
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

void myPlot4(TString menu = "TightLLHMC15_v9",
			 TString iso = "isolTight",
			 TString tag = "TagTightLLHMC15_v8",
			 bool isData = true)
{
	SetAtlasStyle();

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
	cout << "my3d=" << my3d << endl;
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
  	TCanvas *c1 = new TCanvas(menu + "_" + iso + "_" + tag, menu + "_" + iso + "_" + tag, 1000, 500);
	//c1->Divide(4, 3);
	c1->Divide(2, 1);

	TH1F *mllDen[30];
	TH1F *mllNum[30];
	TH1F *den;
	TH1F *num;
	//for (int pt = 4; pt < my3d->GetXaxis()->GetNbins() + 1; pt++){
	//for (int pt = 2; pt < my3d->GetXaxis()->GetNbins() + 1; pt++){
	int pt = 12;
		my3d->GetXaxis()->SetRange(pt, pt);
		my3dNum->GetXaxis()->SetRange(pt, pt);

		mllDen[pt] = (TH1F *)my3d->Project3D("z")->Clone();
		mllNum[pt] = (TH1F *)my3dNum->Project3D("z")->Clone();
		//cout << mllDen[pt]->GetXaxis()->GetNbins() << endl;
		//cout << mllNum[pt]->GetXaxis()->GetNbins() << endl;
		den = (TH1F *)mllDen[pt]->Clone();
		num = (TH1F *)mllNum[pt]->Clone();
		den->Reset();
		num->Reset();
		for (int i = 0; i < mllDen[pt]->GetXaxis()->GetNbins() + 1; i++) {
			den->SetBinContent(i, mllDen[pt]->GetBinContent(i)/mllDen[pt]->GetXaxis()->GetBinWidth(i));
			num->SetBinContent(i, mllNum[pt]->GetBinContent(i)/mllNum[pt]->GetXaxis()->GetBinWidth(i));
		}
		c1->cd(1);
		//c1->cd(pt - 3);
		//c1->cd(pt - 1);
		mllDen[pt]->Draw("hist");
		mllNum[pt]->Draw("hist,same");

		// Some cosmetics
		mllDen[pt]->GetXaxis()->SetRangeUser(60, 140);
		mllDen[pt]->SetMarkerSize(0.8);
		mllDen[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
		mllDen[pt]->GetYaxis()->SetTitle("Events");
		mllDen[pt]->GetXaxis()->SetLabelSize(0.04);
		mllDen[pt]->GetYaxis()->SetLabelSize(0.04);
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
		myText(0.55, 0.88, kBlack, name);

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

		c1->cd(2);
		den->Draw("hist");
		num->Draw("hist,same");
		cout << pt << "(" << my3d->GetXaxis()->GetBinLowEdge(pt) << "," << my3d->GetXaxis()->GetBinLowEdge(pt + 1) 
			 << "): " << mllNum[pt]->GetEntries() 
			 << " / " << mllDen[pt]->GetEntries() 
			 << endl;


		// Some cosmetics
		den->GetXaxis()->SetRangeUser(60, 140);
		den->SetMarkerSize(0.8);
		den->GetXaxis()->SetTitle("m_{ll} [GeV]");
		den->GetYaxis()->SetTitle("Events/#Delta(m_{ll}) [GeV]");
		den->GetXaxis()->SetLabelSize(0.04);
		den->GetYaxis()->SetLabelSize(0.04);
		den->SetMarkerColor(kRed);
		den->SetLineColor(kRed);
		den->SetLineWidth(1);
		num->SetLineStyle(1);
		num->SetLineWidth(1);
		num->SetMarkerSize(0.8);
		num->SetMarkerColor(kBlue);
		num->SetLineColor(kBlue);

		char name1[100];
		sprintf(&name1[0], "p_{T} bin: %d - %d GeV", 
				static_cast<int>(my3d->GetXaxis()->GetBinLowEdge(pt) / 1000.), 
				static_cast<int>(my3d->GetXaxis()->GetBinLowEdge(pt + 1) / 1000.) );
		myText(0.55, 0.88, kBlack, name1);

		myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
		myText(0.55, 0.66, kBlack, const_cast<char *>(tag.Data()) );

		if (isData)
			sprintf(&name1[0], "Data");
		else
			sprintf(&name1[0], "Z#rightarrow ee MC");
		myText(0.25, 0.88, kBlack, name1);

		// Dump some integrals 80<mll<100
		sprintf(&name1[0], "Num (80-100 GeV): %3.0f",
				mllNum[pt]->Integral(mllNum[pt]->GetXaxis()->FindBin(80),
				mllNum[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.57, kBlue, name1);
		sprintf(&name1[0], "Den (80-100 GeV): %3.0f",
				mllDen[pt]->Integral(mllDen[pt]->GetXaxis()->FindBin(80),
				mllDen[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.50, kRed, name1);

//	}
/*
	if(isData){
		//c1->SaveAs("plots/"+menu+iso+"_"+tag+"_data.png", "png");
		c1->SaveAs("plots/Mll_" + menu + iso + "_" + tag + "_data.pdf", "pdf");
	}
	else{
		//c1->SaveAs("plots/"+menu+iso+"_"+tag+"_mc.png", "png");
		c1->SaveAs("plots/Mll_" + menu + iso + "_" + tag + "_mc.pdf", "pdf");
	}
*/
}
