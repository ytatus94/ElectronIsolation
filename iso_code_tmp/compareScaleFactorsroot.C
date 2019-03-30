// This script is used to compare the difference of the results between two config files:
// testLxplus2 uses ZmassSystematicsIsolation25ns
// testLxplus3 uses ZmassSystematicsIsolation25nsAlternative
// print out the value and see the difference
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>
#include <TAxis.h>

#include <iostream>

void compareScaleFactorsroot()
{
    TString dir1 = "/afs/cern.ch/user/y/yushen/public/ForSandrine/20151218/MC15b_recommendations/"; // old
    TString dir2 = "/afs/cern.ch/user/y/yushen/public/ForPhilip/20160208_v8/MC15b_recommendations/"; // new

	TFile *file1;
	TFile *file2;

	TString fileArray[24] = {
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolFixedCutLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolFixedCutTight.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolFixedCutTightTrackOnly.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolGradient.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolGradientLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolLooseTrackOnly.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolTight.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolFixedCutLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolFixedCutTight.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolFixedCutTightTrackOnly.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolGradient.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolGradientLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolLooseTrackOnly.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.MediumLLH_d0z0_v8_isolTight.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolFixedCutLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolFixedCutTight.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolFixedCutTightTrackOnly.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolGradient.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolGradientLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolLoose.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolLooseTrackOnly.2015.13TeV.rel20p0.25ns.v03.root",
		"efficiencySF.Isolation.TightLLH_d0z0_v8_isolTight.2015.13TeV.rel20p0.25ns.v03.root",
	};
	
	for (int n = 0; n < 24; n++) {
		cout << "Now compare " << fileArray[n] << endl;
		file1 = new TFile(dir1 + fileArray[n]);
		file2 = new TFile(dir2 + fileArray[n]);
		TH2F *h1 = (TH2F *)file1->Get("0_99999999999/FullSim_sf");
		TH2F *h2 = (TH2F *)file2->Get("0_99999999999/FullSim_sf");
/*
		cout << h1->GetXaxis()->GetNbins() << endl;
		cout << h1->GetYaxis()->GetNbins() << endl;
		cout << h2->GetXaxis()->GetNbins() << endl;
		cout << h2->GetYaxis()->GetNbins() << endl;
*/
    	for (int ix = 1; ix <= h1->GetXaxis()->GetNbins(); ix++) {
			for (int iy = 1; iy <= h1->GetYaxis()->GetNbins(); iy++) {
				float content1 = h1->GetBinContent(ix, iy);
				float content2 = h2->GetBinContent(ix, iy);
				if (content1 != content2)
					cout << "At bin (" << ix << "," << iy << "): " << content1 << "-" << content2 << "=" << content1 - content2 << endl;
			}
    	}
	}
}
