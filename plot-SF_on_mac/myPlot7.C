// This is used to make Mll plots for each pT bins.
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

void myPlot7(TString menu = "LooseAndBLayerLLH_d0z0_v8",
			TString iso = "isolLoose",
			TString tag = "TagTightLLHMC15_v8",
			bool isData = false)
{
	SetAtlasStyle();

	gStyle->SetPadTopMargin(0.06);

	TFile *_file0 = TFile::Open("/afs/cern.ch/work/y/yushen/private/TagAndProbe/MyTagAndProbe_test18/for_Egamma_workshop/testGridd0z0/merged-hist-mc.root");
	TFile *_file1 = TFile::Open("/afs/cern.ch/work/y/yushen/private/TagAndProbe/MyTagAndProbe_test18/for_derivations/testHIGG2D1d0z0/merged-hist-mc.root");
  
	if (iso != "") iso = "_" + iso;
	TString folder = menu + iso + "_TemplRun2Variation1AndPassTrackQuality_" + tag;
 
	TString histo, histoNum; 
	if (isData) {
		histo = folder + "_Data_Den_Mll_3d";
		histoNum = folder + "_Data_Num_Mll_3d";
	}
	else { // MC
		histo = folder + "_MCZee_NoFilter_Den_Mll_3d";
		histoNum = folder + "_MCZee_NoFilter_Num_Mll_3d";
	}
		
	TH3F *my3d_0 = (TH3F *)_file0->Get(folder + "/" + histo);
	TH3F *my3d_1 = (TH3F *)_file1->Get(folder + "/" + histo);

	TH3F *my3dNum_0 = (TH3F *)_file0->Get(folder + "/" + histoNum);
	TH3F *my3dNum_1 = (TH3F *)_file1->Get(folder + "/" + histoNum);

	// Remider:
	// x: pt
	// y: eta
	// z: mll

	// Big Canvas
  	TCanvas *c1 = new TCanvas(menu + "_" + iso + "_" + tag, menu + "_" + iso + "_" + tag, 1600, 800);
	c1->Divide(4, 3);
	//c1->Divide(3, 3);

	TH1F *mllDen_0[30];
	TH1F *mllDen_1[30];
	//TH1F *mllNum_0[30];
	//TH1F *mllNum_1[30];

	//for (int pt = 4; pt < my3d->GetXaxis()->GetNbins() + 1; pt++){
	//for (int pt = 4; pt < my3d_0->GetXaxis()->GetNbins() + 1; pt++){
	for (int pt = 2; pt < 6; pt++){
		my3d_0->GetXaxis()->SetRange(pt, pt);
		my3d_1->GetXaxis()->SetRange(pt, pt);
		//my3dNum_0->GetXaxis()->SetRange(pt, pt);
		//my3dNum_1->GetXaxis()->SetRange(pt, pt);

		mllDen_0[pt] = (TH1F *)my3d_0->Project3D("z")->Clone();
		mllDen_1[pt] = (TH1F *)my3d_1->Project3D("z")->Clone();
		//mllNum_0[pt] = (TH1F *)my3dNum_0->Project3D("z")->Clone();
		//mllNum_1[pt] = (TH1F *)my3dNum_0->Project3D("z")->Clone();

		//c1->cd(pt - 3);
		c1->cd(pt - 1);

		//mllDen_0[pt]->Draw("hist");
		//mllDen_1[pt]->Draw("hist,same");
		//mllNum_0[pt]->Draw("hist,same");
		//mllNum_1[pt]->Draw("hist,same");
		mllDen_1[pt]->Draw("hist");
		mllDen_0[pt]->Draw("hist,same");

		// Some cosmetics
		mllDen_0[pt]->GetXaxis()->SetRangeUser(60, 140);
		mllDen_0[pt]->SetMarkerSize(0.8);
		mllDen_0[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
		mllDen_0[pt]->GetYaxis()->SetTitle("Events");
		mllDen_0[pt]->SetMarkerColor(kRed);
		mllDen_0[pt]->SetLineColor(kRed);
		mllDen_0[pt]->SetLineWidth(1);
		mllDen_0[pt]->SetFillColor(kRed);
		mllDen_0[pt]->SetFillStyle(3004);
		mllDen_1[pt]->SetLineStyle(1);
		mllDen_1[pt]->SetLineWidth(1);
		mllDen_1[pt]->SetMarkerSize(0.8);
		mllDen_1[pt]->SetMarkerColor(kBlue);
		mllDen_1[pt]->SetLineColor(kBlue);
		mllDen_1[pt]->SetFillColor(kBlue);
		mllDen_1[pt]->SetFillStyle(3005);

		// Add pT range at the top of plot
		char name[100];
		sprintf(&name[0], "p_{T} bin: %d - %d GeV", 
				static_cast<int>(my3d_0->GetXaxis()->GetBinLowEdge(pt) / 1000.), 
				static_cast<int>(my3d_0->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
		myText(0.30, 0.95, kBlack, name, 0.068);

		myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
		myText(0.55, 0.66, kBlack, const_cast<char *>(tag.Data()) );

		if (isData)
			sprintf(&name[0], "Data");
		else
			sprintf(&name[0], "Z#rightarrow ee MC");
		myText(0.25, 0.88, kBlack, name);

/*
		// Dump some integrals 80<mll<100
		sprintf(&name[0], "Num (80-100 GeV): %3.0f",
				mllNum[pt]->Integral(mllNum[pt]->GetXaxis()->FindBin(80),
				mllNum[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.57, kBlue, name);
		sprintf(&name[0], "Den (80-100 GeV): %3.0f",
				mllDen[pt]->Integral(mllDen[pt]->GetXaxis()->FindBin(80),
				mllDen[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.50, kRed, name);
*/
	}
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
