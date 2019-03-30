// This script is used to make isolation variables plots.
// We want to see the distributions of isolation variables so we cannot apply isolation requirement on the probe electrons.
// i.e. Only see the histograms under PlotVars_<menu>
// Make a plot of ptvarcone20 on the left and topoetcone20 on the right.
// MC is normalized to data.
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLegend.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

void myIsoVar(TString menu = "TightLLHMC15_v8")
{
    SetAtlasStyle();

    TString folder = "PlotVars_" + menu;

    TString path = "~/afsWorkingArea/private/TagAndProbe/MyTagAndProbe_test29/TagAndProbeFrame/util/mc15bd0z0/";
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc   = TFile::Open(path + "merged-hist-mc.root");

    // Loading the isolation variables from the data and MC root files.
/*
    TString h_pt           = "PlotVars_" + menu + "_h_el_pt";
    TString h_ptvarcone20  = "PlotVars_" + menu + "_h_el_ptvarcone20";
    TString h_topoetcone20 = "PlotVars_" + menu + "_h_el_topoetcone20";
    TString h_ptvarcone20_over_pt  = "PlotVars_" + menu + "_h_el_ptvarcone20_over_pt";
    TString h_topoetcone20_over_pt = "PlotVars_" + menu + "_h_el_topoetcone20_over_pt";
*/
    TString h_ptvarcone20_vs_pt    = "PlotVars_" + menu + "_h_el_ptvarcone20_vs_pt";
    TString h_topoetcone20_vs_pt   = "PlotVars_" + menu + "_h_el_topoetcone20_vs_pt";

	// Data
/*
    TH1F *data_pt           = (TH1F *)fdata->Get(folder + "/" + h_pt);
    TH1F *data_ptvarcone20  = (TH1F *)fdata->Get(folder + "/" + h_ptvarcone20);
    TH1F *data_topoetcone20 = (TH1F *)fdata->Get(folder + "/" + h_topoetcone20);
    TH1F *data_ptvarcone20_over_pt  = (TH1F *)fdata->Get(folder + "/" + h_ptvarcone20_over_pt);
    TH1F *data_topoetcone20_over_pt = (TH1F *)fdata->Get(folder + "/" + h_topoetcone20_over_pt);
*/
    TH2F *data_ptvarcone20_vs_pt    = (TH2F *)fdata->Get(folder + "/" + h_ptvarcone20_vs_pt);
    TH2F *data_topoetcone20_vs_pt   = (TH2F *)fdata->Get(folder + "/" + h_topoetcone20_vs_pt);
/*
    data_pt->Sumw2();
    data_ptvarcone20->Sumw2();
    data_topoetcone20->Sumw2();
    data_ptvarcone20_over_pt->Sumw2();
    data_topoetcone20_over_pt->Sumw2();
*/
    data_ptvarcone20_vs_pt->Sumw2();
    data_topoetcone20_vs_pt->Sumw2();

	// MC
/*
    TH1F *mc_pt           = (TH1F *)fmc->Get(folder + "/" + h_pt);
    TH1F *mc_ptvarcone20  = (TH1F *)fmc->Get(folder + "/" + h_ptvarcone20);
    TH1F *mc_topoetcone20 = (TH1F *)fmc->Get(folder + "/" + h_topoetcone20);
    TH1F *mc_ptvarcone20_over_pt  = (TH1F *)fmc->Get(folder + "/" + h_ptvarcone20_over_pt);
    TH1F *mc_topoetcone20_over_pt = (TH1F *)fmc->Get(folder + "/" + h_topoetcone20_over_pt);
*/
    TH2F *mc_ptvarcone20_vs_pt    = (TH2F *)fmc->Get(folder + "/" + h_ptvarcone20_vs_pt);
    TH2F *mc_topoetcone20_vs_pt   = (TH2F *)fmc->Get(folder + "/" + h_topoetcone20_vs_pt);
/*
    mc_pt->Sumw2();
    mc_ptvarcone20->Sumw2();
    mc_topoetcone20->Sumw2();
    mc_ptvarcone20_over_pt->Sumw2();
    mc_topoetcone20_over_pt->Sumw2();
*/
    mc_ptvarcone20_vs_pt->Sumw2();
    mc_topoetcone20_vs_pt->Sumw2();

    //------------------------------------------------------//

    // For 2-dim histograms:
    // x axis: pT (0 to 200000 MeV, 200 bins, i.e. 1000 MeV/bin = 1 GeV/bin)
    // y axis: isolation variables

    int firstxbin = 25; // pT > 25 GeV
    int lastxbin = 200;

    TH1F *h_data_ptvarcone20 = (TH1F *)data_ptvarcone20_vs_pt->ProjectionY("", firstxbin, lastxbin)->Clone();
    double xmin1 = h_data_ptvarcone20->GetXaxis()->GetXmin();
    double xmax1 = h_data_ptvarcone20->GetXaxis()->GetXmax();
    h_data_ptvarcone20->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);
    //h_data_ptvarcone20->Draw();

    TH1F *h_mc_ptvarcone20 = (TH1F *)mc_ptvarcone20_vs_pt->ProjectionY("", firstxbin, lastxbin)->Clone();
    double xmin2 = h_mc_ptvarcone20->GetXaxis()->GetXmin();
    double xmax2 = h_mc_ptvarcone20->GetXaxis()->GetXmax();
    h_mc_ptvarcone20->GetXaxis()->SetLimits(xmin2/1000, xmax2/1000);
    //h_mc_ptvarcone20->Draw();

    TH1F *h_data_topoetcone20 = (TH1F *)data_topoetcone20_vs_pt->ProjectionY("", firstxbin, lastxbin)->Clone();
    double xmin3 = h_data_topoetcone20->GetXaxis()->GetXmin();
    double xmax3 = h_data_topoetcone20->GetXaxis()->GetXmax();
    h_data_topoetcone20->GetXaxis()->SetLimits(xmin3/1000, xmax3/1000);
    //h_data_topoetcone20->Draw();

    TH1F *h_mc_topoetcone20 = (TH1F *)mc_topoetcone20_vs_pt->ProjectionY("", firstxbin, lastxbin)->Clone();
    double xmin4 = h_mc_topoetcone20->GetXaxis()->GetXmin();
    double xmax4 = h_mc_topoetcone20->GetXaxis()->GetXmax();
    h_mc_topoetcone20->GetXaxis()->SetLimits(xmin4/1000, xmax4/1000);
    //h_mc_topoetcone20->Draw();

    // Scale MC to data
    double data_area1 = h_data_ptvarcone20->Integral();
    double mc_area1   = h_mc_ptvarcone20->Integral();

    double data_area2 = h_data_topoetcone20->Integral();
    double mc_area2   = h_mc_topoetcone20->Integral();

    h_mc_ptvarcone20->Scale(data_area1 / mc_area1);
    h_mc_topoetcone20->Scale(data_area2 / mc_area2);

    //------------------------------------------------------//

    TCanvas *c1 = new TCanvas("c1", "c1", 1000, 500);
    c1->Divide(2, 1);

    c1->cd(1); // ptvarcone20 plots
    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    //pad1->SetGridy(); // grid lines
    pad1->Draw();

    // lower plot will be in pad2
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetGridy(); // grid lines
    pad2->Draw();

    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here
    pad1->SetLogy();

    h_data_ptvarcone20->SetXTitle("p_{T}^{varcone20} [GeV]");
    h_data_ptvarcone20->SetYTitle("Events");
    h_data_ptvarcone20->GetXaxis()->SetRangeUser(0, 20);
    h_data_ptvarcone20->SetMarkerColor(kBlack);
    h_data_ptvarcone20->SetMarkerStyle(kFullCircle);
    h_data_ptvarcone20->SetMarkerSize(0.7);
    h_data_ptvarcone20->SetLineColor(kBlack);
    h_data_ptvarcone20->Draw("e0");

    h_mc_ptvarcone20->SetMarkerColor(kRed);
    h_mc_ptvarcone20->SetMarkerStyle(kOpenTriangleUp);
    h_mc_ptvarcone20->SetMarkerSize(0.7);
    h_mc_ptvarcone20->SetLineColor(kRed);
    h_mc_ptvarcone20->Draw("e0,same");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    TLegend *leg_left = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg_left->AddEntry(h_data_ptvarcone20, "Data", "lp");
    leg_left->AddEntry(h_mc_ptvarcone20, "Z #rightarrow ee MC", "lp");
    leg_left->SetBorderSize(0);
    leg_left->SetTextFont(42);
    leg_left->SetTextSize(0.05);
    leg_left->SetFillColor(0);
    leg_left->SetFillStyle(0);
    leg_left->Draw();

    pad2->cd(); // pad2 becomes the current pad
    TH1F *frame_left = pad2->DrawFrame(0, 0, 20, 2.5);
    frame_left->GetXaxis()->SetNdivisions(505);
    frame_left->GetYaxis()->SetNdivisions(403);
    frame_left->SetLineWidth(1);
    frame_left->SetXTitle("p_{T}^{varcone20} [GeV]");
    frame_left->GetXaxis()->SetTitleSize(20);
    frame_left->GetXaxis()->SetTitleFont(47);
    frame_left->GetXaxis()->SetTitleOffset(3.0);
    frame_left->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame_left->GetXaxis()->SetLabelSize(16);
    frame_left->SetYTitle("Data/MC");
    frame_left->GetYaxis()->SetTitleSize(15);
    frame_left->GetYaxis()->SetTitleFont(43);
    frame_left->GetYaxis()->SetTitleOffset(2.0);
    frame_left->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame_left->GetYaxis()->SetLabelSize(16);
    frame_left->Draw();

    TH1F *data_over_mc_ptvarcone20 = (TH1F *)h_data_ptvarcone20->Clone();
    data_over_mc_ptvarcone20->Divide(h_mc_ptvarcone20);
    data_over_mc_ptvarcone20->SetMarkerColor(kBlack);
    data_over_mc_ptvarcone20->SetMarkerStyle(kFullCircle);
    data_over_mc_ptvarcone20->SetMarkerSize(0.7);
    data_over_mc_ptvarcone20->SetLineColor(kBlack);
    data_over_mc_ptvarcone20->Draw("e0,same");

    //------------------------------------------------------//

    c1->cd(2); // topoetcone20 plots
    //Upper plot will be in pad3
    TPad *pad3 = new TPad("pad3", "pad3", 0, 0.35, 1, 1.0);
    pad3->SetBottomMargin(0); // Upper and lower plot are joined
    //pad3->SetGridy(); // grid lines
    pad3->Draw();

    // lower plot will be in pad4
    TPad *pad4 = new TPad("pad4", "pad4", 0, 0.05, 1, 0.35);
    pad4->SetTopMargin(0);
    pad4->SetBottomMargin(0.3);
    pad4->SetGridy(); // grid lines
    pad4->Draw();

    pad3->cd(); // pad3 becomes the current pad
    //pad3->SetFrameLineWidth(2);

    // Draw curve here
    pad3->SetLogy();

    h_data_topoetcone20->SetXTitle("E_{T}^{topocone20} [GeV]");
    h_data_topoetcone20->SetYTitle("Events");
    h_data_topoetcone20->GetXaxis()->SetRangeUser(-10, 20);
    h_data_topoetcone20->SetMarkerColor(kBlack);
    h_data_topoetcone20->SetMarkerStyle(kFullCircle);
    h_data_topoetcone20->SetMarkerSize(0.7);
    h_data_topoetcone20->SetLineColor(kBlack);
    h_data_topoetcone20->Draw("e0");

    h_mc_topoetcone20->SetMarkerColor(kRed);
    h_mc_topoetcone20->SetMarkerStyle(kOpenTriangleUp);
    h_mc_topoetcone20->SetMarkerSize(0.7);
    h_mc_topoetcone20->SetLineColor(kRed);
    h_mc_topoetcone20->Draw("e0,same");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    TLegend *leg_right = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg_right->AddEntry(h_data_topoetcone20, "Data", "lp");
    leg_right->AddEntry(h_mc_topoetcone20, "Z #rightarrow ee MC", "lp");
    leg_right->SetBorderSize(0);
    leg_right->SetTextFont(42);
    leg_right->SetTextSize(0.05);
    leg_right->SetFillColor(0);
    leg_right->SetFillStyle(0);
    leg_right->Draw();

    pad4->cd(); // pad4 becomes the current pad
    TH1F *frame_right = pad4->DrawFrame(-10, 0., 20, 2.5);
    frame_right->GetXaxis()->SetNdivisions(505);
    frame_right->GetYaxis()->SetNdivisions(403);
    frame_right->SetLineWidth(1);
    frame_right->SetXTitle("E_{T}^{topocone20} [GeV]");
    frame_right->GetXaxis()->SetTitleSize(20);
    frame_right->GetXaxis()->SetTitleFont(47);
    frame_right->GetXaxis()->SetTitleOffset(3.0);
    frame_right->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame_right->GetXaxis()->SetLabelSize(16);
    frame_right->SetYTitle("Data/MC");
    frame_right->GetYaxis()->SetTitleSize(15);
    frame_right->GetYaxis()->SetTitleFont(43);
    frame_right->GetYaxis()->SetTitleOffset(2.0);
    frame_right->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame_right->GetYaxis()->SetLabelSize(16);
    frame_right->Draw();

    TH1F *data_over_mc_topoetcone20= (TH1F *)h_data_topoetcone20->Clone();
    data_over_mc_topoetcone20->Divide(h_mc_topoetcone20);
    data_over_mc_topoetcone20->SetMarkerColor(kBlack);
    data_over_mc_topoetcone20->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone20->SetMarkerSize(0.7);
    data_over_mc_topoetcone20->SetLineColor(kBlack);
    data_over_mc_topoetcone20->Draw("e0,same");

    c1->SaveAs("plots/iso_var_" + menu + ".pdf", "pdf");
}
