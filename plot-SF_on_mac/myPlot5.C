// This is used to make data and MC Mll plots comparison for low pT bins.
// Modified from Ximo's myPlot.C
// Usage: root myPlot5.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlusAndCaloIso\",true)"
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

void myPlot5(TString menu = "TightLLHMC15_v9",
			 TString iso = "isolTight",
			 TString tag = "TagTightLLHMC15_v8")
{
	SetAtlasStyle();

	if (iso != "") iso = "_" + iso;
	TString folder = menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag;

	TFile *_file0 = TFile::Open("../merged-hist-data.root");

	TString histoDen_data =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_Data_Den_Mll_3d";
	TString histoNum_data =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_Data_Num_Mll_3d";

	TH3F *my3dDen_data = (TH3F *)_file0->Get(folder + "/" + histoDen_data);
	TH3F *my3dNum_data = (TH3F *)_file0->Get(folder + "/" + histoNum_data);

	TH1F *den_data[30];
	TH1F *num_data[30];

	int pt = 2; // pT = 7-10 GeV
	//int pt = 3; // pT = 10-15 GeV

	my3dDen_data->GetXaxis()->SetRange(pt, pt);
	my3dNum_data->GetXaxis()->SetRange(pt, pt);
	den_data[pt] = (TH1F *)my3dDen_data->Project3D("z")->Clone();
	num_data[pt] = (TH1F *)my3dNum_data->Project3D("z")->Clone();

	TFile *_file1 = TFile::Open("../merged-hist-mc.root");

	TString histoDen_mc   =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_MCZee_NoFilter_Den_Mll_3d";
	TString histoNum_mc   =  menu + iso + "_TemplVariation1AndPassTrackQuality_" + tag + "_MCZee_NoFilter_Num_Mll_3d";

	TH3F *my3dDen_mc   = (TH3F *)_file1->Get(folder + "/" + histoDen_mc);
	TH3F *my3dNum_mc   = (TH3F *)_file1->Get(folder + "/" + histoNum_mc);

	TH1F *den_mc[30];
	TH1F *num_mc[30];

	my3dDen_mc->GetXaxis()->SetRange(pt, pt);
	my3dNum_mc->GetXaxis()->SetRange(pt, pt);
	den_mc[pt] = (TH1F *)my3dDen_mc->Project3D("z")->Clone();
	num_mc[pt] = (TH1F *)my3dNum_mc->Project3D("z")->Clone();

	// Remider:
	// x: pt
	// y: eta
	// z: mll

	// Big Canvas
  	TCanvas *c1 = new TCanvas(menu + "_" + iso + "_" + tag, menu + "_" + iso + "_" + tag, 1000, 500);
	c1->Divide(2, 1);
	c1->cd(1);
	den_data[pt]->Draw("hist");
	num_data[pt]->Draw("hist,same");

	// Some cosmetics
	den_data[pt]->GetXaxis()->SetRangeUser(60, 140);
	den_data[pt]->SetMarkerSize(0.8);
	den_data[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
	den_data[pt]->GetYaxis()->SetTitle("Events");
	den_data[pt]->GetXaxis()->SetLabelSize(0.04);
	den_data[pt]->GetYaxis()->SetLabelSize(0.04);
	den_data[pt]->SetMarkerColor(kRed);
	den_data[pt]->SetLineColor(kRed);
	den_data[pt]->SetLineWidth(1);
	num_data[pt]->SetLineStyle(1);
	num_data[pt]->SetLineWidth(1);
	num_data[pt]->SetMarkerSize(0.8);
	num_data[pt]->SetMarkerColor(kBlue);
	num_data[pt]->SetLineColor(kBlue);

	char name[100];
	sprintf(&name[0], "p_{T} bin: %d - %d GeV", 
			static_cast<int>(my3dDen_data->GetXaxis()->GetBinLowEdge(pt) / 1000.), 
			static_cast<int>(my3dDen_data->GetXaxis()->GetBinLowEdge(pt + 1) / 1000.) );
	myText(0.55, 0.88, kBlack, name);

	myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
	myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
	myText(0.55, 0.66, kBlack, const_cast<char *>(tag.Data()) );

	sprintf(&name[0], "Data");
	myText(0.25, 0.88, kBlack, name);

	// Dump some integrals 80<mll<100
	sprintf(&name[0], "Num (80-100 GeV): %3.0f",
			num_data[pt]->Integral(num_data[pt]->GetXaxis()->FindBin(80),
			num_data[pt]->GetXaxis()->FindBin(100)) );
	myText(0.55, 0.57, kBlue, name);

	sprintf(&name[0], "Den (80-100 GeV): %3.0f",
			den_data[pt]->Integral(den_data[pt]->GetXaxis()->FindBin(80),
			den_data[pt]->GetXaxis()->FindBin(100)) );
	myText(0.55, 0.50, kRed, name);


	c1->cd(2);
	den_mc[pt]->Draw("hist");
	num_mc[pt]->Draw("hist,same");

	// Some cosmetics
	den_mc[pt]->GetXaxis()->SetRangeUser(60, 140);
	den_mc[pt]->SetMarkerSize(0.8);
	den_mc[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
	den_mc[pt]->GetYaxis()->SetTitle("Events");
	den_mc[pt]->GetXaxis()->SetLabelSize(0.04);
	den_mc[pt]->GetYaxis()->SetLabelSize(0.04);
	den_mc[pt]->SetMarkerColor(kRed);
	den_mc[pt]->SetLineColor(kRed);
	den_mc[pt]->SetLineWidth(1);
	num_mc[pt]->SetLineStyle(1);
	num_mc[pt]->SetLineWidth(1);
	num_mc[pt]->SetMarkerSize(0.8);
	num_mc[pt]->SetMarkerColor(kBlue);
	num_mc[pt]->SetLineColor(kBlue);

	char name_mc[100];
	sprintf(&name_mc[0], "p_{T} bin: %d - %d GeV", 
			static_cast<int>(my3dDen_mc->GetXaxis()->GetBinLowEdge(pt) / 1000.), 
			static_cast<int>(my3dDen_mc->GetXaxis()->GetBinLowEdge(pt + 1) / 1000.) );
	myText(0.55, 0.88, kBlack, name_mc);

	myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
	myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
	myText(0.55, 0.66, kBlack, const_cast<char *>(tag.Data()) );

	sprintf(&name_mc[0], "Z#rightarrow ee MC");
	myText(0.25, 0.88, kBlack, name_mc);

	// Dump some integrals 80<mll<100
	sprintf(&name_mc[0], "Num (80-100 GeV): %3.0f",
			num_mc[pt]->Integral(num_mc[pt]->GetXaxis()->FindBin(80),
			num_mc[pt]->GetXaxis()->FindBin(100)) );
	myText(0.55, 0.57, kBlue, name_mc);

	sprintf(&name[0], "Den (80-100 GeV): %3.0f",
			den_mc[pt]->Integral(den_mc[pt]->GetXaxis()->FindBin(80),
			den_mc[pt]->GetXaxis()->FindBin(100)) );
	myText(0.55, 0.50, kRed, name);

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
