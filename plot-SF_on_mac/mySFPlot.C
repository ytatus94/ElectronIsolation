// This is used to make 2-dim SF plots and SF uncertainties plots
// Modified from Ximo's mySFPlot.C
// Usage: root mySFPlot.C"(\"TightLLHMC15_v6\",\"isolTight\")"
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include <iostream>
using namespace std;

void mySFPlot(TString menu = "TightLLHMC15_v9",
              TString iso  = "isolTight")
{
	SetAtlasStyle();

 	gStyle->SetPalette(1);
	gStyle->SetPadRightMargin(0.15);

	TFile *_file0;
	_file0 = TFile::Open("../output-SF/ScaleFactors.root");

	TString folder = menu + "_" + iso;
	TString histoEffData, histoEffMC, histoSF;
	histoEffData = "EffData_CentralValue_" + menu + "_" + iso;
	histoEffMC   = "EffMC_CentralValue_" + menu + "_" + iso;
	histoSF      = "SF_CentralValue_" + menu + "_" + iso;

	cout << folder + "/" + histoEffData << endl;

	TH2F *myEffData = (TH2F *)_file0->Get(folder + "/" + histoEffData);
	TH2F *myEffMC   = (TH2F *)_file0->Get(folder + "/" + histoEffMC);
	TH2F *mySF      = (TH2F *)_file0->Get(folder + "/" + histoSF);

	// Remider:
	// x: pt
	// y: eta

	cout << "Number of bins in pt: "  << mySF->GetXaxis()->GetNbins() << endl;
	cout << "Number of bins in eta: " << mySF->GetYaxis()->GetNbins() << endl;

	myEffData->GetXaxis()->SetTitle("Electron p_{T} [MeV]");
 	myEffData->GetYaxis()->SetTitle("Electron #eta  ");

	myEffMC->GetXaxis()->SetTitle("Electron p_{T} [MeV]");
	myEffMC->GetYaxis()->SetTitle("Electron #eta  ");

 	mySF->GetXaxis()->SetTitle("Electron p_{T} [MeV]");
  	mySF->GetYaxis()->SetTitle("Electron #eta  ");

  	// Big Canvas
  	TCanvas *c1 = new TCanvas(menu + "_" + iso, menu + "_" + iso, 1400, 400);
  	c1->Divide(3, 1);

  	c1->cd(1);
	//myEffData->GetZaxis()->SetRangeUser(0.79, 1.0);
	gPad->SetLogx();
	myEffData->SetMinimum(0.79);
  	myEffData->Draw("colz");
  
  	char name[100];
  	sprintf(&name[0], "Data");
  	myText(0.12, 0.96, kBlack, name);
  	myText(0.35, 0.96, kBlack, const_cast<char *>(menu.Data()) );
  	myText(0.7,  0.96, kBlack, const_cast<char *>(iso.Data()) );

  	c1->cd(2);
	//myEffMC->GetZaxis()->SetRangeUser(0.79, 1.0);
	gPad->SetLogx();
	myEffMC->SetMinimum(0.79);
  	myEffMC->Draw("colz");

  	sprintf(&name[0], "Z#rightarrow ee MC");
  	myText(0.12, 0.96, kBlack, name);
  	myText(0.35, 0.96, kBlack, const_cast<char *>(menu.Data()) );
  	myText(0.7,  0.96, kBlack, const_cast<char *>(iso.Data()) );

  	c1->cd(3);
	//mySF->GetZaxis()->SetRangeUser(0.79, 1.0);
	gPad->SetLogx();
	mySF->SetMinimum(0.79);
  	mySF->Draw("colz");

  	sprintf(&name[0], "SF (Central value)");
  	myText(0.05, 0.96, kBlack, name);
  	myText(0.35, 0.96, kBlack, const_cast<char *>(menu.Data()) );
  	myText(0.7,  0.96, kBlack, const_cast<char *>(iso.Data()) );
  
  	c1->SaveAs("plots/" + menu + "_" + iso + "_SF.pdf", "pdf");

  	//--------------------------------------------------//
  	// Plotting SF uncertainties

	TString histoSF_stat, histoSF_syst, histoSF_tot;
  	histoSF_stat = "SF_StatError_" + menu + "_" + iso;
  	histoSF_syst = "SF_SystError_" + menu + "_" + iso;
  	histoSF_tot  = "SF_TotalError_" + menu + "_" + iso;

  	TH2F *mySF_stat = (TH2F *)_file0->Get(folder + "/" + histoSF_stat);
  	TH2F *mySF_syst = (TH2F *)_file0->Get(folder + "/" + histoSF_syst);
  	TH2F *mySF_tot  = (TH2F *)_file0->Get(folder + "/" + histoSF_tot);

  	mySF_stat->GetXaxis()->SetTitle("Electron p_{T}");
  	mySF_stat->GetYaxis()->SetTitle("Electron #eta  ");

  	mySF_syst->GetXaxis()->SetTitle("Electron p_{T}");
  	mySF_syst->GetYaxis()->SetTitle("Electron #eta  ");

  	mySF_tot->GetXaxis()->SetTitle("Electron p_{T}");
  	mySF_tot->GetYaxis()->SetTitle("Electron #eta  ");

  	// Big Canvas
  	TCanvas *c2 = new TCanvas(menu + "_" + iso + "_unc", menu + "_" + iso + "_unc", 1400, 400);
	c2->Divide(3, 1);

  	c2->cd(1);
	gPad->SetLogx();
  	mySF_stat->Draw("colz");
  	mySF_stat->SetMaximum(0.2);
  	sprintf(&name[0], "SF (stat unc.)");
  	myText(0.05, 0.96, kBlack, name);
  	myText(0.35, 0.96, kBlack, const_cast<char *>(menu.Data()) );
  	myText(0.7,  0.96, kBlack, const_cast<char *>(iso.Data()) );

  	c2->cd(2);
	gPad->SetLogx();
  	mySF_syst->Draw("colz");
  	mySF_syst->SetMaximum(0.2);
  	sprintf(&name[0], "SF (syst unc.)");
  	myText(0.05, 0.96, kBlack, name);
  	myText(0.35, 0.96, kBlack, const_cast<char *>(menu.Data()) );
  	myText(0.7,  0.96, kBlack, const_cast<char *>(iso.Data()) );

  	c2->cd(3);
	gPad->SetLogx();
  	mySF_tot->Draw("colz");
  	mySF_tot->SetMaximum(0.2);
  	sprintf(&name[0], "SF (total unc.)");
  	myText(0.05, 0.96, kBlack, name);
  	myText(0.35, 0.96, kBlack, const_cast<char *>(menu.Data()) );
  	myText(0.7,  0.96, kBlack, const_cast<char *>(iso.Data()) );

  	c2->SaveAs("plots/" + menu + "_" + iso + "_SFunc.pdf", "pdf");
}
