//
// This is used to compare the central values of scale factors in ScaleFactors.root and in tool.
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"

#include <iostream>
using namespace std;

void makePlot(TH1F *, TH1F *);

void compareSFPlot4(TString menu = "TightLLH_d0z0_v8",
                    TString iso  = "isolTight",
                    int pt_bin = 3)
{
	// ElectronEfficiencyCorrection Tool
	TString fileName1 = "~/test/ElectronEfficiencyCorrection-00-01-42/data/isolations/efficiencySF.Isolation.TightLLH_d0z0_v8_isolTight.2015.13TeV.rel20p0.25ns.v04.root";
	TFile *file1 = TFile::Open(fileName1);
	TH2F *h_FullSim_sf = (TH2F*)file1->Get("0_9999999/FullSim_sf");
	TH1F *h_FullSim_sf_project_on_eta = (TH1F*)h_FullSim_sf->ProjectionY("", pt_bin, pt_bin)->Clone();
	//h_FullSim_sf->Draw("colz,text");
	//double pt_low = h_FullSim_sf->GetXaxis()->GetBinLowEdge(pt_bin) / 1000.;
	//double pt_up  = h_FullSim_sf->GetXaxis()->GetBinUpEdge(pt_bin) / 1000.;
	//cout << "pt_low=" << pt_low << ", pt_up=" << pt_up << endl;
	//h_FullSim_sf_project_on_eta->Draw();

	//--------------------------------------------------//
	
	// ScaleFactors.root
	TString fileName2 = "~/MC15bd0z0_ScaleFactors.root";
	TFile *file2 = TFile::Open(fileName2);
	TH2F *h_sf      = get13TeV2DHistogram(fileName2, menu, iso, "SF_CentralValue");
	TH2F *h_sf_tot  = get13TeV2DHistogram(fileName2, menu, iso, "SF_TotalError");
	TH1F *h_sf_project_on_eta     = (TH1F*)h_sf->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	TH1F *h_sf_tot_project_on_eta = (TH1F*)h_sf_tot->ProjectionY("", pt_bin+1, pt_bin+1)->Clone();
	fixHistogramError(h_sf_project_on_eta, h_sf_tot_project_on_eta);
	//h_sf->Draw("colz,text");
	//h_sf_tot->Draw("colz,text");
	//double pt_low = h_sf->GetXaxis()->GetBinLowEdge(pt_bin+1) / 1000.;
	//double pt_up  = h_sf->GetXaxis()->GetBinUpEdge(pt_bin+1) / 1000.;
	//cout << "pt_low=" << pt_low << ", pt_up=" << pt_up << endl;
	//h_sf_project_on_eta->Draw();

	// Make a plot
	makePlot(h_FullSim_sf_project_on_eta, h_sf_project_on_eta);
}

void makePlot(TH1F *h1, TH1F *h2)
{
	TCanvas *c1 = new TCanvas("c1", "Compare SF central values");
	gStyle->SetOptStat(0);

	h1->SetTitle("Scale Factors project on #eta axis");
	h1->SetXTitle("#eta");
	h1->SetYTitle("Efficiency");
	h1->SetMaximum(1.02);
	h1->SetMinimum(0.98);

	h1->SetLineColor(kBlue);
	h1->SetMarkerSize(1);
	h1->SetMarkerStyle(kFullCircle);
	h1->SetMarkerColor(kBlue);
	h1->Draw("E1");

	h2->SetLineColor(kRed);
	h2->SetMarkerSize(1);
	h2->SetMarkerStyle(kFullTriangleUp);
	h2->SetMarkerColor(kRed);
	h2->Draw("E1,SAME");

	TLine *line = new TLine(h1->GetXaxis()->GetXmin(), 1., h1->GetXaxis()->GetXmax(), 1.);
	line->SetLineColor(kBlack);
	line->SetLineStyle(2);
	line->SetLineWidth(1);
	line->Draw("SAME");

	TLegend *legend = new TLegend(0.3, 0.75, 0.7, 0.9);
	legend->AddEntry(h1, "ElectronEfficiencyCorrection", "lp");
	legend->AddEntry(h2, "ScaleFactors.root", "lp");
	legend->SetBorderSize(0);
	legend->SetFillColor(0);
	legend->SetFillStyle(0);
	legend->Draw();
}

