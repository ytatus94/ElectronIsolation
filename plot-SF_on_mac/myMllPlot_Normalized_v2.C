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

void myMllPlot_Normalized_v2(TString menu = "TightLLH",
                             TString iso  = "isolLoose",
                             bool isMC  = true)
{
    SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    // load the denominator and numerator histograms in both data and mc.
    TFile *data_file = TFile::Open("../merged-hist-data.root");
    TFile *mc_file = TFile::Open("../merged-hist-mc.root");

	TString background_template[2] ={"TemplRun2Variation1AndPassTrackQuality", "TemplRun2Variation2AndPassTrackQuality"};
    TString tag[3] = {"TagTightLLHMC15_v8", "TagTightLLHMC15_v8_Iso", "TagMediumLLHMC15_v8_Iso"};

    TString data_folder, data_den, data_num, mc_folder, mc_den, mc_num;
    // use TemplRun2Variation1AndPassTrackQuality and TagTightLLHMC15_v8 by default
    if (iso.Contains("isolPhFixedCut")) {
        data_folder = menu + "MC15_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        data_den    = data_folder + "/" + data_folder + "_Data_Den_Mll_3d_minDeltaR";
        data_num    = data_folder + "/" + data_folder + "_Data_Num_Mll_3d_minDeltaR";

        mc_folder = menu + "MC15_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        mc_den    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Den_Mll_3d_minDeltaR";
        mc_num    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Num_Mll_3d_minDeltaR";
    }
    else {
        data_folder = menu + "_d0z0_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        data_den    = data_folder + "/" + data_folder + "_Data_Den_Mll_3d_minDeltaR";
        data_num    = data_folder + "/" + data_folder + "_Data_Num_Mll_3d_minDeltaR";

        mc_folder = menu + "_d0z0_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        mc_den    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Den_Mll_3d_minDeltaR";
        mc_num    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Num_Mll_3d_minDeltaR";
    }

    if (debug) {
        cout << data_den << endl;
        cout << data_num << endl;
        cout << mc_den << endl;
        cout << mc_num << endl;
    }

    TH3F *h_data_den, *h_data_num, *h_mc_den, *h_mc_num;
    h_data_den = (TH3F*)data_file->Get(data_den);
    h_data_num = (TH3F*)data_file->Get(data_num);
    h_mc_den   = (TH3F*)mc_file->Get(mc_den);
    h_mc_num   = (TH3F*)mc_file->Get(mc_num); 

    if (debug) {
        cout << h_data_den << endl;
        cout << h_data_num << endl;
        cout << h_mc_den << endl;
        cout << h_mc_num << endl;
    }

    TString folder;
    TH3F *h_den, *h_num;
    if (isMC) {
        folder = mc_folder;
        h_den = h_mc_den;
        h_num = h_mc_num;
    }
    else {
        folder = data_folder;
        h_den = h_data_den;
        h_num = h_data_num;
    }

    if (debug) {
	    cout << "Den: number of bins in pt=" << h_den->GetXaxis()->GetNbins() << endl;
	    cout << "Den: number of bins in deltaR=" << h_den->GetYaxis()->GetNbins() << endl;
	    cout << "Num: number of bins in pt=" << h_num->GetXaxis()->GetNbins() << endl;
	    cout << "Num: number of bins in deltaR=" << h_num->GetYaxis()->GetNbins() << endl;
    }

	// Remider:
	// x: pt
	// y: minDeltaR
	// z: mll

    int number_of_pt_bins = h_den->GetXaxis()->GetNbins();
    TH1F *h_mll_den[20] = {0}, *h_mll_num[20] = {0},
         *h_mll_den_normalized[20] = {0}, *h_mll_num_normalized[20] = {0};
    for (int pt = 2; pt < number_of_pt_bins + 1; pt++) {
        h_mll_den[pt] = (TH1F*)h_den->ProjectionZ("", pt, pt)->Clone();
        h_mll_num[pt] = (TH1F*)h_num->ProjectionZ("", pt, pt)->Clone();

        // Normalize bins by their bin width
        h_mll_den_normalized[pt] = (TH1F*)h_mll_den[pt]->Clone();
        h_mll_num_normalized[pt] = (TH1F*)h_mll_num[pt]->Clone();
        h_mll_den_normalized[pt]->Reset();
        h_mll_num_normalized[pt]->Reset();
		for (int i = 0; i < h_mll_den[pt]->GetXaxis()->GetNbins() + 1; i++) {
			h_mll_den_normalized[pt]->SetBinContent(i, h_mll_den[pt]->GetBinContent(i) / h_mll_den[pt]->GetXaxis()->GetBinWidth(i));
		}
		for (int i = 0; i < h_mll_num[pt]->GetXaxis()->GetNbins() + 1; i++) {
			h_mll_num_normalized[pt]->SetBinContent(i, h_mll_num[pt]->GetBinContent(i) / h_mll_num[pt]->GetXaxis()->GetBinWidth(i));
		}
    }

	// Big Canvas
    TCanvas *c1 = new TCanvas(folder, folder, 1600, 800);
    c1->Divide(3, 2);
    for (int pt = 2; pt < 8; pt++) {
        if (debug) {
		    cout << pt << "(" << h_mll_den_normalized[pt]->GetXaxis()->GetBinLowEdge(pt) << "," 
                              << h_mll_den_normalized[pt]->GetXaxis()->GetBinUpEdge(pt) << "): "
                              << h_mll_num_normalized[pt]->GetEntries() << " / " << h_mll_den_normalized[pt]->GetEntries() << endl;
        }
        c1->cd(pt - 1);
		h_mll_den_normalized[pt]->GetXaxis()->SetRangeUser(60, 140);
		h_mll_den_normalized[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
		h_mll_den_normalized[pt]->GetYaxis()->SetTitle("Events");
		h_mll_den_normalized[pt]->SetLineColor(kBlue);
        h_mll_den_normalized[pt]->SetLineStyle(1);
		h_mll_den_normalized[pt]->SetLineWidth(1);
        h_mll_den_normalized[pt]->Draw("hist");

		h_mll_num_normalized[pt]->SetLineColor(kRed);
		h_mll_num_normalized[pt]->SetLineStyle(1);
		h_mll_num_normalized[pt]->SetLineWidth(1);
        h_mll_num_normalized[pt]->Draw("hist,same");

		char name[100];
		sprintf(&name[0], "%d < p_{T} < %d GeV",
			static_cast<int>(h_den->GetXaxis()->GetBinLowEdge(pt) / 1000.),
			static_cast<int>(h_den->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
		myText(0.55, 0.88, kBlack, name);

		myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
		myText(0.55, 0.66, kBlack, const_cast<char *>(tag[0].Data()) );

		if (isMC)
			sprintf(&name[0], "Z#rightarrow ee MC");
		else
			sprintf(&name[0], "Data");
		myText(0.25, 0.88, kBlack, name);

		// Dump some integrals 80<mll<100
		sprintf(&name[0], "Num (80-100 GeV): %3.0f",
			h_mll_num[pt]->Integral(h_mll_num[pt]->GetXaxis()->FindBin(80), h_mll_num[pt]->GetXaxis()->FindBin(100)) );
			myText(0.55, 0.57, kRed, name);
		sprintf(&name[0], "Den (80-100 GeV): %3.0f",
			h_mll_den[pt]->Integral(h_mll_den[pt]->GetXaxis()->FindBin(80), h_mll_den[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.50, kBlue, name);
    }
    if (isMC)
		c1->Print("plots/Mll_" + menu + iso + "_" + tag[0] + "_data_1.pdf");
    else
		c1->Print("plots/Mll_" + menu + iso + "_" + tag[0] + "_data_1.pdf");
    
    for (int pt = 8; pt < 14; pt++) {
        if (debug) {
		    cout << pt << "(" << h_mll_den_normalized[pt]->GetXaxis()->GetBinLowEdge(pt) << "," 
                              << h_mll_den_normalized[pt]->GetXaxis()->GetBinUpEdge(pt) << "): "
                              << h_mll_num_normalized[pt]->GetEntries() << " / " << h_mll_den_normalized[pt]->GetEntries() << endl;
        }
        c1->cd(pt - 7);
		h_mll_den_normalized[pt]->GetXaxis()->SetRangeUser(60, 140);
		h_mll_den_normalized[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
		h_mll_den_normalized[pt]->GetYaxis()->SetTitle("Events");
		h_mll_den_normalized[pt]->SetLineColor(kBlue);
        h_mll_den_normalized[pt]->SetLineStyle(1);
		h_mll_den_normalized[pt]->SetLineWidth(1);
        h_mll_den_normalized[pt]->Draw("hist");

		h_mll_num_normalized[pt]->SetLineColor(kRed);
		h_mll_num_normalized[pt]->SetLineStyle(1);
		h_mll_num_normalized[pt]->SetLineWidth(1);
        h_mll_num_normalized[pt]->Draw("hist,same");

		char name[100];
		sprintf(&name[0], "%d < p_{T} < %d GeV",
			static_cast<int>(h_den->GetXaxis()->GetBinLowEdge(pt) / 1000.),
			static_cast<int>(h_den->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
		myText(0.55, 0.88, kBlack, name);

		myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
		myText(0.55, 0.66, kBlack, const_cast<char *>(tag[0].Data()) );

		if (isMC)
			sprintf(&name[0], "Z#rightarrow ee MC");
		else
			sprintf(&name[0], "Data");
		myText(0.25, 0.88, kBlack, name);

		// Dump some integrals 80<mll<100
		sprintf(&name[0], "Num (80-100 GeV): %3.0f",
			h_mll_num[pt]->Integral(h_mll_num[pt]->GetXaxis()->FindBin(80), h_mll_num[pt]->GetXaxis()->FindBin(100)) );
			myText(0.55, 0.57, kRed, name);
		sprintf(&name[0], "Den (80-100 GeV): %3.0f",
			h_mll_den[pt]->Integral(h_mll_den[pt]->GetXaxis()->FindBin(80), h_mll_den[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.50, kBlue, name);
    }
    if (isMC)
		c1->Print("plots/Mll_" + menu + iso + "_" + tag[0] + "_data_2.pdf");
    else
		c1->Print("plots/Mll_" + menu + iso + "_" + tag[0] + "_data_2.pdf");

    for (int pt = 14; pt < 20; pt++) {
        if (debug) {
		    cout << pt << "(" << h_mll_den_normalized[pt]->GetXaxis()->GetBinLowEdge(pt) << "," 
                              << h_mll_den_normalized[pt]->GetXaxis()->GetBinUpEdge(pt) << "): "
                              << h_mll_num_normalized[pt]->GetEntries() << " / " << h_mll_den_normalized[pt]->GetEntries() << endl;
        }
        c1->cd(pt - 13);
		h_mll_den_normalized[pt]->GetXaxis()->SetRangeUser(60, 140);
		h_mll_den_normalized[pt]->GetXaxis()->SetTitle("m_{ll} [GeV]");
		h_mll_den_normalized[pt]->GetYaxis()->SetTitle("Events");
		h_mll_den_normalized[pt]->SetLineColor(kBlue);
        h_mll_den_normalized[pt]->SetLineStyle(1);
		h_mll_den_normalized[pt]->SetLineWidth(1);
        h_mll_den_normalized[pt]->Draw("hist");

		h_mll_num_normalized[pt]->SetLineColor(kRed);
		h_mll_num_normalized[pt]->SetLineStyle(1);
		h_mll_num_normalized[pt]->SetLineWidth(1);
        h_mll_num_normalized[pt]->Draw("hist,same");

		char name[100];
		sprintf(&name[0], "%d < p_{T} < %d GeV",
			static_cast<int>(h_den->GetXaxis()->GetBinLowEdge(pt) / 1000.),
			static_cast<int>(h_den->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
		myText(0.55, 0.88, kBlack, name);

		myText(0.55, 0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55, 0.72, kBlack, const_cast<char *>(iso.Data()) );
		myText(0.55, 0.66, kBlack, const_cast<char *>(tag[0].Data()) );

		if (isMC)
			sprintf(&name[0], "Z#rightarrow ee MC");
		else
			sprintf(&name[0], "Data");
		myText(0.25, 0.88, kBlack, name);

		// Dump some integrals 80<mll<100
		sprintf(&name[0], "Num (80-100 GeV): %3.0f",
			h_mll_num[pt]->Integral(h_mll_num[pt]->GetXaxis()->FindBin(80), h_mll_num[pt]->GetXaxis()->FindBin(100)) );
			myText(0.55, 0.57, kRed, name);
		sprintf(&name[0], "Den (80-100 GeV): %3.0f",
			h_mll_den[pt]->Integral(h_mll_den[pt]->GetXaxis()->FindBin(80), h_mll_den[pt]->GetXaxis()->FindBin(100)) );
		myText(0.55, 0.50, kBlue, name);
    }
    if (isMC)
		c1->Print("plots/Mll_" + menu + iso + "_" + tag[0] + "_data_3.pdf");
    else
		c1->Print("plots/Mll_" + menu + iso + "_" + tag[0] + "_data_3.pdf");
}
