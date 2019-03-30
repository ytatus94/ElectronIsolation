// This script is used to compare two topoetcone40 variables with and withoug applying data driven shifts.
//
//
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include <iostream>
using namespace std;

void makePlot(TH1 *, TH1 *);
void makeComparisonPlot(TH1 *, TH1*);

void makePlot(TH1 *h1, TH1 *h2)
{
    
}

void makeComparisonPlot(TH1 *h1, TH1*h2)
{
    
}


void myIsoVar7(TString menu = "TightLLH_d0z0_v8")
{
    //SetAtlasStyle();

    TString folder = "PlotVars_" + menu;

    // Loading the isolation variables from the data and MC root files.
    TString h_3D_el_topoetcone40 = "PlotVars_" + menu + "_h_3D_el_topoetcone40";
    TString h_3D_el_topoetcone40_over_pt = "PlotVars_" + menu + "_h_3D_el_topoetcone40_over_pt";

    TString path1 = "~/Desktop/tL1/";
    TFile *fdata1 = TFile::Open(path1 + "hist-data15_13TeV.00284484.physics_Main.merge.DAOD_EGAM1.f644_m1518_p2470.root");
    TFile *fmc1   = TFile::Open(path1 + "hist-mc15_13TeV.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee.merge.DAOD_EGAM1.e3601_s2576_s2132_r7267_p2470.root");

    TH3F *data1_3D_el_topoetcone40 = (TH3F *)fdata1->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *data1_3D_el_topoetcone40_over_pt = (TH3F *)fdata1->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);

    data1_3D_el_topoetcone40->Sumw2();
    data1_3D_el_topoetcone40_over_pt->Sumw2();

    TH3F *mc1_3D_el_topoetcone40 = (TH3F *)fmc1->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *mc1_3D_el_topoetcone40_over_pt = (TH3F *)fmc1->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);

    mc1_3D_el_topoetcone40->Sumw2();
    mc1_3D_el_topoetcone40_over_pt->Sumw2();

    //------------------------------------------------------//

    TString path2 = "~/Desktop/tL5/";
    TFile *fdata2 = TFile::Open(path2 + "hist-data15_13TeV.00284484.physics_Main.merge.DAOD_EGAM1.f644_m1518_p2470.root");
    TFile *fmc2   = TFile::Open(path2 + "hist-mc15_13TeV.361106.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee.merge.DAOD_EGAM1.e3601_s2576_s2132_r7267_p2470.root");

    TH3F *data2_3D_el_topoetcone40 = (TH3F *)fdata2->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *data2_3D_el_topoetcone40_over_pt = (TH3F *)fdata2->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);

    data2_3D_el_topoetcone40->Sumw2();
    data2_3D_el_topoetcone40_over_pt->Sumw2();

    TH3F *mc2_3D_el_topoetcone40 = (TH3F *)fmc2->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *mc2_3D_el_topoetcone40_over_pt = (TH3F *)fmc2->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);

    mc2_3D_el_topoetcone40->Sumw2();
    mc2_3D_el_topoetcone40_over_pt->Sumw2();

    //------------------------------------------------------//

    // For 2-dim histograms:
    // x axis: pT (0 to 200000 MeV, 80 bins, i.e. 2500 MeV/bin = 2.5 GeV/bin)
    // y axis: fabs(eta) (0 to 2.5, 250 bins, i.e. 0.01/bin)
    // z axis: isolation variables
    // for topoetcone40: -10000 to 30000, 200 bins, i.e. 200 MeV/bin = 0.2 GeV/bin
    // for topoetcone40/pt: -0.25 to 1, 125 bins

    int firstxbin = 25;
    int lastxbin  = 50;
    int firstybin = 0;
    int lastybin  = -1;
    int firstzbin = 0;
    int lastzbin  = -1;
    
	// file1
    TH1F *h_data1_topoetcone40_project_on_z_axis = (TH1F *)data1_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    double xmin1 = h_data1_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
    double xmax1 = h_data1_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
    h_data1_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);
    //h_data1_topoetcone40_project_on_z_axis->Draw();

    TH1F *h_data1_topoetcone40_over_pt_project_on_z_axis = (TH1F *)data1_3D_el_topoetcone40_over_pt->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    //h_data1_topoetcone40_over_pt_project_on_z_axis->Draw();

    TH1F *h_mc1_topoetcone40_project_on_z_axis = (TH1F *)mc1_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    double xmin2 = h_mc1_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
    double xmax2 = h_mc1_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
    h_mc1_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin2/1000, xmax2/1000);
    //h_mc1_topoetcone40_project_on_z_axis->Draw();

    TH1F *h_mc1_topoetcone40_over_pt_project_on_z_axis = (TH1F *)mc1_3D_el_topoetcone40_over_pt->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    //h_mc1_topoetcone40_over_pt_project_on_z_axis->Draw();

    double data1_area1 = h_data1_topoetcone40_project_on_z_axis->Integral();
    double mc1_area1   = h_mc1_topoetcone40_project_on_z_axis->Integral();
    double data1_area2 = h_data1_topoetcone40_over_pt_project_on_z_axis->Integral();
    double mc1_area2   = h_mc1_topoetcone40_over_pt_project_on_z_axis->Integral();

    h_mc1_topoetcone40_project_on_z_axis->Scale(data1_area1 / mc1_area1);
    h_mc1_topoetcone40_over_pt_project_on_z_axis->Scale(data1_area2 / mc1_area2);

	// file2
    TH1F *h_data2_topoetcone40_project_on_z_axis = (TH1F *)data2_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    double xmin3 = h_data2_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
    double xmax3 = h_data2_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
    h_data2_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin3/1000, xmax3/1000);
    //h_data2_topoetcone40_project_on_z_axis->Draw();

    TH1F *h_data2_topoetcone40_over_pt_project_on_z_axis = (TH1F *)data2_3D_el_topoetcone40_over_pt->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    //h_data2_topoetcone40_over_pt_project_on_z_axis->Draw();

    TH1F *h_mc2_topoetcone40_project_on_z_axis = (TH1F *)mc2_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    double xmin4 = h_mc2_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
    double xmax4 = h_mc2_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
    h_mc2_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin4/1000, xmax4/1000);
    //h_mc2_topoetcone40_project_on_z_axis->Draw();

    TH1F *h_mc2_topoetcone40_over_pt_project_on_z_axis = (TH1F *)mc2_3D_el_topoetcone40_over_pt->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    //h_mc2_topoetcone40_over_pt_project_on_z_axis->Draw();

    double data2_area1 = h_data2_topoetcone40_project_on_z_axis->Integral();
    double mc2_area1   = h_mc2_topoetcone40_project_on_z_axis->Integral();
    double data2_area2 = h_data2_topoetcone40_over_pt_project_on_z_axis->Integral();
    double mc2_area2   = h_mc2_topoetcone40_over_pt_project_on_z_axis->Integral();

    h_mc2_topoetcone40_project_on_z_axis->Scale(data2_area1 / mc2_area1);
    h_mc2_topoetcone40_over_pt_project_on_z_axis->Scale(data2_area2 / mc2_area2);

	h_data1_topoetcone40_project_on_z_axis->SetLineColor(kBlue);
	h_data1_topoetcone40_project_on_z_axis->SetMarkerSize(1);
	h_data1_topoetcone40_project_on_z_axis->SetMarkerColor(kBlue);
	h_data1_topoetcone40_project_on_z_axis->SetMarkerStyle(kFullCircle);
	//h_data1_topoetcone40_project_on_z_axis->Draw("E1");

	h_mc1_topoetcone40_project_on_z_axis->SetLineColor(kRed);
	h_mc1_topoetcone40_project_on_z_axis->SetMarkerSize(1);
	h_mc1_topoetcone40_project_on_z_axis->SetMarkerColor(kRed);
	h_mc1_topoetcone40_project_on_z_axis->SetMarkerStyle(kFullCircle);
	//h_mc1_topoetcone40_project_on_z_axis->Draw("E1,SAME");
	h_mc1_topoetcone40_project_on_z_axis->Draw("E1");

	h_data2_topoetcone40_project_on_z_axis->SetLineColor(kGreen);
	h_data2_topoetcone40_project_on_z_axis->SetMarkerSize(1);
	h_data2_topoetcone40_project_on_z_axis->SetMarkerColor(kGreen);
	h_data2_topoetcone40_project_on_z_axis->SetMarkerStyle(kOpenTriangleUp);
	//h_data2_topoetcone40_project_on_z_axis->Draw("E1,SAME");

	h_mc2_topoetcone40_project_on_z_axis->SetLineColor(kYellow);
	h_mc2_topoetcone40_project_on_z_axis->SetMarkerSize(1);
	h_mc2_topoetcone40_project_on_z_axis->SetMarkerColor(kYellow);
	h_mc2_topoetcone40_project_on_z_axis->SetMarkerStyle(kOpenTriangleUp);
	h_mc2_topoetcone40_project_on_z_axis->Draw("E1,SAME");
}
