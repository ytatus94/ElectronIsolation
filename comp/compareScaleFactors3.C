// This script is used to compare the difference of the scale factors between ScaleFactors.root and Philip's recommendations
// print out the values of each bin and see the difference
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>

#include <iostream>
using namespace std;

void compareScaleFactors3()
{
	TString fileName1 = "~/Desktop/Philip_efficiencySF.Isolation.TightLLH_d0z0_v10_isolTight.2015.13TeV.rel20p0.25ns.v05.root";
	TString fileName2 = "~/Desktop/myMC15b_efficiencySF.Isolation.TightLLH_d0z0_v10_isolTight.2015.13TeV.rel20p0.25ns.v05.root";
	TString fileName3 = "~/Desktop/myAF2_efficiencySF.Isolation.TightLLH_d0z0_v10_isolTight.2015.13TeV.rel20p0.25ns.v05.root";

	TFile *file1 = TFile::Open(fileName1);
	TFile *file2 = TFile::Open(fileName2);
	TFile *file3 = TFile::Open(fileName3);

	// Get the 2-dim scale factors histograms
	// file1
	TH2F *toolFullSim_sf  = (TH2F *)file1->Get("0_9999999/FullSim_sf");
	TH2F *toolAtlFast2_sf = (TH2F *)file1->Get("0_9999999/AtlFast2_sf");
	// file2
	TH2F *myFullSim_sf  = (TH2F *)file2->Get("0_99999999999/FullSim_sf");
	// file3
	TH2F *myAtlFast2_sf = (TH2F *)file3->Get("0_99999999999/FullSim_sf");

	// Show the number of bins
	// file1
	cout << "In " << fileName1 << endl;
	cout << "For FullSim_sf" << endl;
	cout << "NXbins=" << toolFullSim_sf->GetXaxis()->GetNbins() << endl; // 14
	cout << "NYbins=" << toolFullSim_sf->GetYaxis()->GetNbins() << endl; // 20
	cout << "For AtlFast2" << endl;
	cout << "NXbins=" << toolAtlFast2_sf->GetXaxis()->GetNbins() << endl; // 14
	cout << "NYbins=" << toolAtlFast2_sf->GetYaxis()->GetNbins() << endl; // 20
	// file2
	cout << "In " << fileName2 << endl;
	cout << "NXbins=" << myFullSim_sf->GetXaxis()->GetNbins() << endl; // 19
	cout << "NYbins=" << myFullSim_sf->GetYaxis()->GetNbins() << endl; // 20
	// file3
	cout << "In " << fileName3 << endl;
	cout << "NXbins=" << myAtlFast2_sf->GetXaxis()->GetNbins() << endl; // 19
	cout << "NYbins=" << myAtlFast2_sf->GetYaxis()->GetNbins() << endl; // 20

	// Show the bin contents
	// For full sim
	cout << "For FullSim:" << endl;
	for (int ix = 1; ix <= toolFullSim_sf->GetXaxis()->GetNbins(); ix++) {
		for (int iy = 1; iy <= toolFullSim_sf->GetYaxis()->GetNbins(); iy++) {
			float ptLowEdge  = toolFullSim_sf->GetXaxis()->GetBinLowEdge(ix) / 1000.;
			float ptUpEdge   = toolFullSim_sf->GetXaxis()->GetBinUpEdge(ix) / 1000.;
			float etaLowEdge = toolFullSim_sf->GetYaxis()->GetBinLowEdge(iy);
			float etaUpEdge  = toolFullSim_sf->GetYaxis()->GetBinUpEdge(iy);
			//cout << myFullSim_sf->GetXaxis()->GetBinLowEdge(ix+1) / 1000. << endl;
			//cout << myFullSim_sf->GetXaxis()->GetBinUpEdge(ix+1) / 1000. << endl;
			//cout << myFullSim_sf->GetYaxis()->GetBinLowEdge(iy) << endl;
			//cout << myFullSim_sf->GetYaxis()->GetBinUpEdge(iy) << endl;
			double tool_SF_Centeral_value = toolFullSim_sf->GetBinContent(ix, iy);
			double my_SF_Centeral_value = myFullSim_sf->GetBinContent(ix+1, iy);
			double difference = tool_SF_Centeral_value - my_SF_Centeral_value;
			cout << "(" << ptLowEdge << "<pT<" << ptUpEdge << ", " << etaLowEdge << "<eta<" << etaUpEdge << "): "
			     << tool_SF_Centeral_value << " : " << my_SF_Centeral_value << " : " << difference << endl;
			if (difference > 0.01) cout << "******************** Above this line, the difference too large. ********************" << endl;
		}
	}
	// For AtlFast2
	cout << "For AtlFast2:" << endl;
	for (int ix = 1; ix <= toolAtlFast2_sf->GetXaxis()->GetNbins(); ix++) {
		for (int iy = 1; iy <= toolAtlFast2_sf->GetYaxis()->GetNbins(); iy++) {
			float ptLowEdge  = toolAtlFast2_sf->GetXaxis()->GetBinLowEdge(ix) / 1000.;
			float ptUpEdge   = toolAtlFast2_sf->GetXaxis()->GetBinUpEdge(ix) / 1000.;
			float etaLowEdge = toolAtlFast2_sf->GetYaxis()->GetBinLowEdge(iy);
			float etaUpEdge  = toolAtlFast2_sf->GetYaxis()->GetBinUpEdge(iy);
			//cout << myAtlFast2_sf->GetXaxis()->GetBinLowEdge(ix+1) / 1000. << endl;
			//cout << myAtlFast2_sf->GetXaxis()->GetBinUpEdge(ix+1) / 1000. << endl;
			//cout << myAtlFast2_sf->GetYaxis()->GetBinLowEdge(iy) << endl;
			//cout << myAtlFast2_sf->GetYaxis()->GetBinUpEdge(iy) << endl;
			double tool_SF_Centeral_value = toolAtlFast2_sf->GetBinContent(ix, iy);
			double my_SF_Centeral_value = myAtlFast2_sf->GetBinContent(ix+1, iy);
			double difference = tool_SF_Centeral_value - my_SF_Centeral_value;
			cout << "(" << ptLowEdge << "<pT<" << ptUpEdge << ", " << etaLowEdge << "<eta<" << etaUpEdge << "): "
			     << tool_SF_Centeral_value << " : " << my_SF_Centeral_value << " : " << difference << endl;
			if (difference > 0.01) cout << "******************** Above this line, the difference too large. ********************" << endl;
		}
	}
}
