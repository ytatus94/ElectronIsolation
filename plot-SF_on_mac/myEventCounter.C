// This is used to compare the number in each bin between two root files.
// Usage: root -l myEventCounter.C"(\"TightLLHMC15_v6\",\"isolTight\",\"TagTightPlusPlusAndCaloIso\",true)"
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

void myEventCounter(TString menu = "LooseAndBLayerLLH_d0z0_v8",
                    TString iso  = "isolLoose",
                    TString tag  = "TagTightLLHMC15_v8",
                    bool isData  = false)
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

	// pT starts from 15 GeV to 20 GeV, this is pT bin = 4.
	// eta and mll starts from first bin. (bin = 0 is underflow)

	cout << "Denominator:" << endl;
	cout << "pT has "  << my3d_0->GetXaxis()->GetNbins() << " bins." << endl;
	cout << "eta has " << my3d_0->GetYaxis()->GetNbins() << " bins." << endl;
	cout << "mll has " << my3d_0->GetZaxis()->GetNbins() << " bins." << endl;
	for (int pt = 4; pt < my3d_0->GetXaxis()->GetNbins() + 1; pt++) {
        	for (int eta = 1; eta < my3d_0->GetYaxis()->GetNbins() + 1; eta++) {
			for (int mll = 1; mll < my3d_0->GetZaxis()->GetNbins() + 1; mll++) {
				int diff = my3d_0->GetBinContent(pt, eta, mll) - my3d_1->GetBinContent(pt, eta, mll);
				if (diff != 0)
					cout << "(" << pt << "," << eta << "," << mll << "): " << diff << endl;
			}
		}
    	}

	cout << "Numerator:" << endl;
	cout << "pT has "  << my3dNum_0->GetXaxis()->GetNbins() << " bins." << endl;
	cout << "eta has " << my3dNum_0->GetYaxis()->GetNbins() << " bins." << endl;
	cout << "mll has " << my3dNum_0->GetZaxis()->GetNbins() << " bins." << endl;
	for (int pt = 4; pt < my3dNum_0->GetXaxis()->GetNbins() + 1; pt++) {
        	for (int eta = 1; eta < my3dNum_0->GetYaxis()->GetNbins() + 1; eta++) {
			for (int mll = 1; mll < my3dNum_0->GetZaxis()->GetNbins() + 1; mll++) {
				int diff = my3d_0->GetBinContent(pt, eta, mll) - my3d_1->GetBinContent(pt, eta, mll);
				if (diff != 0)
					cout << "(" << pt << "," << eta << "," << mll << "): " << diff << endl;
			}
		}
    	}
}
