// This script is used to compare the difference of the FullSim_sf between two recommendation files:
// print out the value and see the difference
// The recommendation files are my version (not Philip's version).
// The name of recommendation files should be the same.
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>
#include <TAxis.h>

#include <iostream>
using namespace std;

void compareScaleFactors2()
{
    TString dir1 = "/Users/ytshen/Desktop/v10/20160131/MC15b_recommendations/"; // old
    TString dir2 = "/Users/ytshen/Desktop/v10/20160131/AF2_recommendations/"; // new

    TFile *file1;
    TFile *file2;

    TString fileArray[11] = {
        "efficiencySF.Isolation.TightLLHMC15_v10_isolPhFixedCutLoose.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLHMC15_v10_isolPhFixedCutTight.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLHMC15_v10_isolPhFixedCutTightCaloOnly.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolFixedCutLoose.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolFixedCutTight.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolFixedCutTightTrackOnly.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolGradient.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolGradientLoose.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolLoose.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolLooseTrackOnly.2015.13TeV.rel20p0.25ns.v05.root",
        "efficiencySF.Isolation.TightLLH_d0z0_v10_isolTight.2015.13TeV.rel20p0.25ns.v05.root"
    };
 
    //cout << sizeof(fileArray) / sizeof(TString) << endl;
    int arrayLength = sizeof(fileArray) / sizeof(TString);

    for (int n = 0; n < arrayLength; n++) {
        cout << fileArray[n] << endl;
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
                    cout << content1 << "-" << content2 << "=" << content1 - content2 << endl;
            }
        }
    }
}
