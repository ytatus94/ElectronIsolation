#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>

using namespace std;

void comparePlots()
{
    TString dir1 = "/afs/cern.ch/user/y/yushen/public/ForSandrine/20151218/MC15b_recommendations/"; // old
    TString dir2 = "/afs/cern.ch/user/y/yushen/public/ForPhilip/20160208_v8/MC15b_recommendations/"; // new

	TFile *file1 = new TFile(dir1 + "/efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolFixedCutLoose.2015.13TeV.rel20p0.25ns.v03.root");
	TFile *file2 = new TFile(dir2 + "/efficiencySF.Isolation.LooseAndBLayerLLH_d0z0_v8_isolFixedCutLoose.2015.13TeV.rel20p0.25ns.v03.root");

	TH2F *h1 = (TH2F *)file1->Get("0_99999999999/FullSim_sf");
	TH2F *h2 = (TH2F *)file2->Get("0_99999999999/FullSim_sf");

	TH1F *h3 = (TH1F *)h1->ProjectionY("", 2, 2)->Clone();
	TH1F *h4 = (TH1F *)h2->ProjectionY("", 2, 2)->Clone();

	h3->SetXTitle("#eta");
	h3->SetYTitle("Scale Factor");
	h3->SetLineColor(kBlue);
	h3->SetMarkerColor(kBlue);
	h3->SetMarkerStyle(kFullCircle);
	h3->Draw("e1");

	h4->SetLineColor(kRed);
	h4->SetMarkerColor(kRed);
	h4->SetMarkerStyle(kOpenCircle);
	h4->Draw("e1,same");

	TLegend *leg = new TLegend(0.2, 0.7, 0.4, 0.85);
	leg->AddEntry(h3, "MC15b (20151218)", "lp");
	leg->AddEntry(h4, "MC15b (20160208_v8)", "lp");
	leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
	leg->Draw();

}
