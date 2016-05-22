// This script is used to compare the difference of the FullSim_sf between two recommendation files:
// Make plot to compare.
// The recommendation files are my version (not Philip's version).
// The name of recommendation files should be the same.
// NOT FINISH YET!!!
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#include <TLine.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "FindOptimalRange.C"

#include <iostream>
using namespace std;

void makePlots(TString, double, double, TH1F*, TH1F*);

void compareSFPlot2()
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

	TH2F *h1[arrayLength];
	TH2F *h2[arrayLength];
    
	//for (int n = 0; n < arrayLength; n++) {
	for (int n = 0; n < 2; n++) {
		cout << fileArray[n] << endl;
		file1 = new TFile(dir1 + fileArray[n]);
		file2 = new TFile(dir2 + fileArray[n]);
		TH2F *h1 = (TH2F *)file1->Get("0_99999999999/FullSim_sf");
		TH2F *h2 = (TH2F *)file2->Get("0_99999999999/FullSim_sf");
		int h1_NbinsX = h1->GetXaxis()->GetNbins();
		int h1_NbinsY = h1->GetYaxis()->GetNbins();
		int h2_NbinsX = h2->GetXaxis()->GetNbins();
		int h2_NbinsY = h2->GetYaxis()->GetNbins();
		if ((h1_NbinsX != h2_NbinsX) || (h1_NbinsY != h2_NbinsY)) {
			cout << "Number of bins are different in two histograms" << endl;
			cout << "(h1_NbinsX, h1_NbinsY)=(" << h1_NbinsX << ", " << h1_NbinsY << endl;
            		cout << "(h2_NbinsX, h2_NbinsY)=(" << h2_NbinsX << ", " << h2_NbinsY << endl;
		}
        
		TH1F* pt[2][h1_NbinsY];
		TH1F* eta[2][h1_NbinsX];
        
        // For h1
        // SF projects on x-axis (pt-axis)
        for (int iy = 1; iy <= h1_NbinsY; iy ++) {
            if (iy == 0) continue; // underflow bin
            pt[0][iy] = (TH1F *)h1->ProjectionX("", iy, iy)->Clone();
        }
        // SF projects on y-axis (eta-axis)
        for (int ix = 1; ix <= h1_NbinsX; ix++) {
            if (ix == 0) continue; // underflow bin
            eta[0][ix] = (TH1F *)h1->ProjectionY("", ix, ix)->Clone();
        }
        
        // For h2
        // SF projects on x-axis (pt-axis)
        for (int iy = 1; iy <= h2_NbinsY; iy ++) {
            if (iy == 0) continue; // underflow bin
            pt[1][iy] = (TH1F *)h2->ProjectionX("", iy, iy)->Clone();
        }
        // SF projects on y-axis (eta-axis)
        for (int ix = 1; ix <= h2_NbinsX; ix++) {
            if (ix == 0) continue; // underflow bin
            eta[1][ix] = (TH1F *)h2->ProjectionY("", ix, ix)->Clone();
        }

        // make plots
        //for (int iy = 1; iy <= h1_NbinsY; iy ++) {
        for (int iy = 1; iy <= 2; iy ++) {
            double upper = h1->GetYaxis()->GetBinLowEdge(iy);
            double lower = h1->GetYaxis()->GetBinUpEdge(iy);
            makePlots("pt", upper, lower, pt[0][iy], pt[1][iy]);
        }
        for (int ix = 1; ix <= h2_NbinsX; ix++) {
            double upper = h1->GetXaxis()->GetBinLowEdge(ix) / 1000.;
            double lower = h1->GetXaxis()->GetBinUpEdge(ix) / 1000.;
            //makePlots("eta", ix, eta[0][ix], eta[1][ix]);
        }
    }
}

void makePlots(TString plotType, double upper, double lower, TH1F* h1, TH1F* h2) {
    /*float low = 99;
    float high = -99;
    
    FindOptimalRange(low, high, h1, h2);
    double y_max = high;
    double y_min = low;
    */double y_max = 1.2;
    double y_min = 0.8;
    
    // Set titles, maximum and minimum of axes
    if (plotType.EqualTo("pt"))
        h1->SetXTitle("E_{T} [MeV]");
    else if (plotType.EqualTo("eta"))
        h1->SetXTitle("#eta");
    h1->SetYTitle("Scale Factor");
    h1->SetMaximum(y_max);
   	h1->SetMinimum(y_min);
    
    TCanvas *c1 = new TCanvas("c1");
    gStyle->SetOptStat(0); // no stat box
    
    h1->SetLineColor(kBlue);
    h1->SetLineWidth(1);
    h1->SetMarkerColor(kBlue);
    h1->SetMarkerSize(1);
    h1->SetMarkerStyle(kFullCircle);
    if (plotType.EqualTo("pt"))
        h1->GetXaxis()->SetRangeUser(7000, 150000);
   	h1->Draw("E1");
    /*
    h2->SetLineColor(kRed);
    h2->SetLineWidth(1);
    h2->SetMarkerColor(kRed);
    h2->SetMarkerSize(1);
    h2->SetMarkerStyle(kOpenCircle);
    if (plotType.EqualTo("pt"))
        h2->GetXaxis()->SetRangeUser(7000, 150000);
   	h2->Draw("E1,SAME");
    */
    TLine *line;
    if (plotType.EqualTo("pt")) {
        line = new TLine(7000, 1., 200000, 1.);
    }
    else if (plotType.EqualTo("eta")) {
        line = new TLine(h1->GetXaxis()->GetXmin(), 1.,
                         h1->GetXaxis()->GetXmax(), 1.);
    }
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->Draw("same");
    
    char name[100];
    if (plotType.EqualTo("pt")) {
        sprintf(&name[0], "%.2f < #eta < %.2f", upper, lower);
    }
    else if (plotType.EqualTo("eta")) {
        sprintf(&name[0], "%d GeV < E_{T} < %d GeV", static_cast<int>(upper), static_cast<int>(lower));
    }
    myText(0.2,0.70, kBlack, name);
    
}
