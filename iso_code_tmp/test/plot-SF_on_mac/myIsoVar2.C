// This script is used to make isolation variables plots.
// We want to see the distributions of isolation variables so we cannot apply isolation requirement on the probe electrons.
// i.e. Only see the histograms under PlotVars_<menu>
// Make plots of topoetcone40 and topoetcone40/pt project on x, y, and z axis
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

void myIsoVar2(TString menu = "TightLLH_d0z0_v8")
{
    SetAtlasStyle();

    TString folder = "PlotVars_" + menu;

    TString path = "~/Desktop/topoetcone40/";
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc   = TFile::Open(path + "merged-hist-mc.root");

    // Loading the isolation variables from the data and MC root files.
    TString h_3D_el_topoetcone40 = "PlotVars_" + menu + "_h_3D_el_topoetcone40";
    TString h_3D_el_topoetcone40_over_pt = "PlotVars_" + menu + "_h_3D_el_topoetcone40_over_pt";

    TH3F *data_3D_el_topoetcone40 = (TH3F *)fdata->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *data_3D_el_topoetcone40_over_pt = (TH3F *)fdata->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);

    data_3D_el_topoetcone40->Sumw2();
    data_3D_el_topoetcone40_over_pt->Sumw2();

    TH3F *mc_3D_el_topoetcone40 = (TH3F *)fmc->Get(folder + "/" + h_3D_el_topoetcone40);
    TH3F *mc_3D_el_topoetcone40_over_pt = (TH3F *)fmc->Get(folder + "/" + h_3D_el_topoetcone40_over_pt);

    mc_3D_el_topoetcone40->Sumw2();
    mc_3D_el_topoetcone40_over_pt->Sumw2();

    //------------------------------------------------------//

    // For 2-dim histograms:
    // x axis: pT (0 to 200000 MeV, 80 bins, i.e. 2500 MeV/bin = 2.5 GeV/bin)
    // y axis: fabs(eta) (0 to 2.5, 250 bins, i.e. 0.01/bin)
    // z axis: isolation variables
    // for topoetcone40: -10000 to 30000, 200 bins, i.e. 200 MeV/bin = 0.2 GeV/bin
    // for topoetcone40/pt: -0.25 to 1, 125 bins

    int firstxbin = 0; // pT > 25 GeV
    int lastxbin = -1;
    int firstybin = 0;
    int lastybin = -1;
    int firstzbin = 0;
    int lastzbin = -1;

    // Data
    TH1F *h_data_topoetcone40_project_on_pt_axis = (TH1F *)data_3D_el_topoetcone40->ProjectionX("", firstybin, lastybin, firstzbin, lastzbin)->Clone();
    double xmin1 = h_data_topoetcone40_project_on_pt_axis->GetXaxis()->GetXmin();
    double xmax1 = h_data_topoetcone40_project_on_pt_axis->GetXaxis()->GetXmax();
    h_data_topoetcone40_project_on_pt_axis->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);
    //h_data_topoetcone40_project_on_pt_axis->Draw();

    TH1F *h_data_topoetcone40_project_on_eta_axis = (TH1F *)data_3D_el_topoetcone40->ProjectionY("", firstxbin, lastxbin, firstzbin, lastzbin)->Clone();
    //h_data_topoetcone40_project_on_eta_axis->Draw();

    TH1F *h_data_topoetcone40_project_on_z_axis = (TH1F *)data_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    double xmin2 = h_data_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
    double xmax2 = h_data_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
    h_data_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin2/1000, xmax2/1000);
    //h_data_topoetcone40_project_on_z_axis->Draw();

    TH1F *h_data_topoetcone40_over_pt_project_on_pt_axis = (TH1F *)data_3D_el_topoetcone40_over_pt->ProjectionX("", firstybin, lastybin, firstzbin, lastzbin)->Clone();
    double xmin3 = h_data_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->GetXmin();
    double xmax3 = h_data_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->GetXmax();
    h_data_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->SetLimits(xmin3/1000, xmax3/1000);
    //h_data_topoetcone40_over_pt_project_on_pt_axis->Draw();

    TH1F *h_data_topoetcone40_over_pt_project_on_eta_axis = (TH1F *)data_3D_el_topoetcone40_over_pt->ProjectionY("", firstxbin, lastxbin, firstzbin, lastzbin)->Clone();
    //h_data_topoetcone40_over_pt_project_on_eta_axis->Draw();

    TH1F *h_data_topoetcone40_over_pt_project_on_z_axis = (TH1F *)data_3D_el_topoetcone40_over_pt->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    //h_data_topoetcone40_over_pt_project_on_z_axis->Draw();

    // MC
    TH1F *h_mc_topoetcone40_project_on_pt_axis = (TH1F *)mc_3D_el_topoetcone40->ProjectionX("", firstybin, lastybin, firstzbin, lastzbin)->Clone();
    double xmin4 = h_mc_topoetcone40_project_on_pt_axis->GetXaxis()->GetXmin();
    double xmax4 = h_mc_topoetcone40_project_on_pt_axis->GetXaxis()->GetXmax();
    h_mc_topoetcone40_project_on_pt_axis->GetXaxis()->SetLimits(xmin4/1000, xmax4/1000);
    //h_mc_topoetcone40_project_on_pt_axis->Draw();

    TH1F *h_mc_topoetcone40_project_on_eta_axis = (TH1F *)mc_3D_el_topoetcone40->ProjectionY("", firstxbin, lastxbin, firstzbin, lastzbin)->Clone();
    //h_mc_topoetcone40_project_on_eta_axis->Draw();

    TH1F *h_mc_topoetcone40_project_on_z_axis = (TH1F *)mc_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    double xmin5 = h_mc_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
    double xmax5 = h_mc_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
    h_mc_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin5/1000, xmax5/1000);
    //h_mc_topoetcone40_project_on_z_axis->Draw();

    TH1F *h_mc_topoetcone40_over_pt_project_on_pt_axis = (TH1F *)mc_3D_el_topoetcone40_over_pt->ProjectionX("", firstybin, lastybin, firstzbin, lastzbin)->Clone();
    double xmin6 = h_mc_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->GetXmin();
    double xmax6 = h_mc_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->GetXmax();
    h_mc_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->SetLimits(xmin6/1000, xmax6/1000);
    //h_mc_topoetcone40_over_pt_project_on_pt_axis->Draw();

    TH1F *h_mc_topoetcone40_over_pt_project_on_eta_axis = (TH1F *)mc_3D_el_topoetcone40_over_pt->ProjectionY("", firstxbin, lastxbin, firstzbin, lastzbin)->Clone();
    //h_mc_topoetcone40_over_pt_project_on_eta_axis->Draw();

    TH1F *h_mc_topoetcone40_over_pt_project_on_z_axis = (TH1F *)mc_3D_el_topoetcone40_over_pt->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
    //h_mc_topoetcone40_over_pt_project_on_z_axis->Draw();

    // Scale MC to data
    double data_area1 = h_data_topoetcone40_project_on_pt_axis->Integral();
    double mc_area1   = h_mc_topoetcone40_project_on_pt_axis->Integral();

    double data_area2 = h_data_topoetcone40_project_on_eta_axis->Integral();
    double mc_area2   = h_mc_topoetcone40_project_on_eta_axis->Integral();

    double data_area3 = h_data_topoetcone40_project_on_z_axis->Integral();
    double mc_area3   = h_mc_topoetcone40_project_on_z_axis->Integral();

    double data_area4 = h_data_topoetcone40_over_pt_project_on_pt_axis->Integral();
    double mc_area4   = h_mc_topoetcone40_over_pt_project_on_pt_axis->Integral();

    double data_area5 = h_data_topoetcone40_over_pt_project_on_eta_axis->Integral();
    double mc_area5   = h_mc_topoetcone40_over_pt_project_on_eta_axis->Integral();

    double data_area6 = h_data_topoetcone40_over_pt_project_on_z_axis->Integral();
    double mc_area6   = h_mc_topoetcone40_over_pt_project_on_z_axis->Integral();

    h_mc_topoetcone40_project_on_pt_axis->Scale(data_area1 / mc_area1);
    h_mc_topoetcone40_project_on_eta_axis->Scale(data_area2 / mc_area2);
    h_mc_topoetcone40_project_on_z_axis->Scale(data_area3 / mc_area3);
    h_mc_topoetcone40_over_pt_project_on_pt_axis->Scale(data_area4 / mc_area4);
    h_mc_topoetcone40_over_pt_project_on_eta_axis->Scale(data_area5 / mc_area5);
    h_mc_topoetcone40_over_pt_project_on_z_axis->Scale(data_area6 / mc_area6);

    //------------------------------------------------------//

    TCanvas *c1 = new TCanvas("c1", "c1", 1500, 500);
    c1->Divide(3, 1);

    c1->cd(1); // topoetcone40 plots (project on pt axis)
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

    h_data_topoetcone40_project_on_pt_axis->SetXTitle("E_{T} [GeV]");
    h_data_topoetcone40_project_on_pt_axis->SetYTitle("Events");
    h_data_topoetcone40_project_on_pt_axis->GetXaxis()->SetRangeUser(7, 200);
    h_data_topoetcone40_project_on_pt_axis->SetMarkerColor(kBlack);
    h_data_topoetcone40_project_on_pt_axis->SetMarkerStyle(kFullCircle);
    h_data_topoetcone40_project_on_pt_axis->SetMarkerSize(0.7);
    h_data_topoetcone40_project_on_pt_axis->SetLineColor(kBlack);
    h_data_topoetcone40_project_on_pt_axis->Draw("E0");

    h_mc_topoetcone40_project_on_pt_axis->SetMarkerColor(kRed);
    h_mc_topoetcone40_project_on_pt_axis->SetMarkerStyle(kOpenTriangleUp);
    h_mc_topoetcone40_project_on_pt_axis->SetMarkerSize(0.7);
    h_mc_topoetcone40_project_on_pt_axis->SetLineColor(kRed);
    h_mc_topoetcone40_project_on_pt_axis->Draw("E0,SAME");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    TLegend *leg_left = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg_left->AddEntry(h_data_topoetcone40_project_on_pt_axis, "Data", "lp");
    leg_left->AddEntry(h_mc_topoetcone40_project_on_pt_axis, "Z #rightarrow ee MC", "lp");
    leg_left->SetBorderSize(0);
    leg_left->SetTextFont(42);
    leg_left->SetTextSize(0.05);
    leg_left->SetFillColor(0);
    leg_left->SetFillStyle(0);
    leg_left->Draw();

    pad2->cd(); // pad2 becomes the current pad
    double pad2_X_max = 200;
    double pad2_X_min = 7;
    double pad2_Y_max = 2.1;
    double pad2_Y_min = 0;
    TH1F *frame_left = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame_left->GetXaxis()->SetNdivisions(505);
    frame_left->GetYaxis()->SetNdivisions(403);
    frame_left->SetLineWidth(1);
    frame_left->SetXTitle("E_{T} [GeV]");
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

    TH1F *data_over_mc_topoetcone40_project_on_pt_axis = (TH1F *)h_data_topoetcone40_project_on_pt_axis->Clone();
    data_over_mc_topoetcone40_project_on_pt_axis->Divide(h_mc_topoetcone40_project_on_pt_axis);
    data_over_mc_topoetcone40_project_on_pt_axis->SetMarkerColor(kBlack);
    data_over_mc_topoetcone40_project_on_pt_axis->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone40_project_on_pt_axis->SetMarkerSize(0.7);
    data_over_mc_topoetcone40_project_on_pt_axis->SetLineColor(kBlack);
    data_over_mc_topoetcone40_project_on_pt_axis->Draw("E0,SAME");

    //------------------------------------------------------//

    c1->cd(2); // topoetcone40 plots (project on eta axis)
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

    h_data_topoetcone40_project_on_eta_axis->SetXTitle("|#eta|");
    h_data_topoetcone40_project_on_eta_axis->SetYTitle("Events");
    h_data_topoetcone40_project_on_eta_axis->GetXaxis()->SetRangeUser(0, 2.5);
    h_data_topoetcone40_project_on_eta_axis->SetMaximum(10000000);
    h_data_topoetcone40_project_on_eta_axis->SetMarkerColor(kBlack);
    h_data_topoetcone40_project_on_eta_axis->SetMarkerStyle(kFullCircle);
    h_data_topoetcone40_project_on_eta_axis->SetMarkerSize(0.7);
    h_data_topoetcone40_project_on_eta_axis->SetLineColor(kBlack);
    h_data_topoetcone40_project_on_eta_axis->Draw("E0");

    h_mc_topoetcone40_project_on_eta_axis->SetMarkerColor(kRed);
    h_mc_topoetcone40_project_on_eta_axis->SetMarkerStyle(kOpenTriangleUp);
    h_mc_topoetcone40_project_on_eta_axis->SetMarkerSize(0.7);
    h_mc_topoetcone40_project_on_eta_axis->SetLineColor(kRed);
    h_mc_topoetcone40_project_on_eta_axis->Draw("E0,SAME");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    TLegend *leg1_middle = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg1_middle->AddEntry(h_data_topoetcone40_project_on_eta_axis, "Data", "lp");
    leg1_middle->AddEntry(h_mc_topoetcone40_project_on_eta_axis, "Z #rightarrow ee MC", "lp");
    leg1_middle->SetBorderSize(0);
    leg1_middle->SetTextFont(42);
    leg1_middle->SetTextSize(0.05);
    leg1_middle->SetFillColor(0);
    leg1_middle->SetFillStyle(0);
    leg1_middle->Draw();

    pad4->cd(); // pad4 becomes the current pad
    double pad4_X_max = h_data_topoetcone40_project_on_eta_axis->GetXaxis()->GetXmax(); // 2.5
    double pad4_X_min = h_data_topoetcone40_project_on_eta_axis->GetXaxis()->GetXmin(); // 0
    double pad4_Y_max = 2.1;
    double pad4_Y_min = 0;
    TH1F *frame1_middle = pad4->DrawFrame(pad4_X_min, pad4_Y_min, pad4_X_max, pad4_Y_max);
    frame1_middle->GetXaxis()->SetNdivisions(505);
    frame1_middle->GetYaxis()->SetNdivisions(403);
    frame1_middle->SetLineWidth(1);
    frame1_middle->SetXTitle("|#eta|");
    frame1_middle->GetXaxis()->SetTitleSize(20);
    frame1_middle->GetXaxis()->SetTitleFont(47);
    frame1_middle->GetXaxis()->SetTitleOffset(3.0);
    frame1_middle->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1_middle->GetXaxis()->SetLabelSize(16);
    frame1_middle->SetYTitle("Data/MC");
    frame1_middle->GetYaxis()->SetTitleSize(15);
    frame1_middle->GetYaxis()->SetTitleFont(43);
    frame1_middle->GetYaxis()->SetTitleOffset(2.0);
    frame1_middle->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1_middle->GetYaxis()->SetLabelSize(16);
    frame1_middle->Draw();

    TH1F *data_over_mc_topoetcone40_project_on_eta_axis = (TH1F *)h_data_topoetcone40_project_on_eta_axis->Clone();
    data_over_mc_topoetcone40_project_on_eta_axis->Divide(h_mc_topoetcone40_project_on_eta_axis);
    data_over_mc_topoetcone40_project_on_eta_axis->SetMarkerColor(kBlack);
    data_over_mc_topoetcone40_project_on_eta_axis->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone40_project_on_eta_axis->SetMarkerSize(0.7);
    data_over_mc_topoetcone40_project_on_eta_axis->SetLineColor(kBlack);
    data_over_mc_topoetcone40_project_on_eta_axis->Draw("E0,SAME");

    //------------------------------------------------------//

    c1->cd(3); // topoetcone40 plots (project on z axis)
    //Upper plot will be in pad5
    TPad *pad5 = new TPad("pad5", "pad5", 0, 0.35, 1, 1.0);
    pad5->SetBottomMargin(0); // Upper and lower plot are joined
    //pad5->SetGridy(); // grid lines
    pad5->Draw();

    // lower plot will be in pad6
    TPad *pad6 = new TPad("pad6", "pad6", 0, 0.05, 1, 0.35);
    pad6->SetTopMargin(0);
    pad6->SetBottomMargin(0.3);
    pad6->SetGridy(); // grid lines
    pad6->Draw();

    pad5->cd(); // pad5 becomes the current pad
    //pad5->SetFrameLineWidth(2);

    // Draw curve here
    pad5->SetLogy();

    h_data_topoetcone40_project_on_z_axis->SetXTitle("E_{T}^{topocone40} [GeV]");
    h_data_topoetcone40_project_on_z_axis->SetYTitle("Events");
    h_data_topoetcone40_project_on_z_axis->GetXaxis()->SetRangeUser(-10, 30);
    h_data_topoetcone40_project_on_z_axis->SetMarkerColor(kBlack);
    h_data_topoetcone40_project_on_z_axis->SetMarkerStyle(kFullCircle);
    h_data_topoetcone40_project_on_z_axis->SetMarkerSize(0.7);
    h_data_topoetcone40_project_on_z_axis->SetLineColor(kBlack);
    h_data_topoetcone40_project_on_z_axis->Draw("E0");

    h_mc_topoetcone40_project_on_z_axis->SetMarkerColor(kRed);
    h_mc_topoetcone40_project_on_z_axis->SetMarkerStyle(kOpenTriangleUp);
    h_mc_topoetcone40_project_on_z_axis->SetMarkerSize(0.7);
    h_mc_topoetcone40_project_on_z_axis->SetLineColor(kRed);
    h_mc_topoetcone40_project_on_z_axis->Draw("E0,SAME");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    TLegend *leg1_right = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg1_right->AddEntry(h_data_topoetcone40_project_on_eta_axis, "Data", "lp");
    leg1_right->AddEntry(h_mc_topoetcone40_project_on_eta_axis, "Z #rightarrow ee MC", "lp");
    leg1_right->SetBorderSize(0);
    leg1_right->SetTextFont(42);
    leg1_right->SetTextSize(0.05);
    leg1_right->SetFillColor(0);
    leg1_right->SetFillStyle(0);
    leg1_right->Draw();
    
    pad6->cd(); // pad6 becomes the current pad
    double pad6_X_max = 30;
    double pad6_X_min = -10;
    double pad6_Y_max = 2.1;
    double pad6_Y_min = 0;
    TH1F *frame1_right = pad4->DrawFrame(pad6_X_min, pad6_Y_min, pad6_X_max, pad6_Y_max);
    frame1_right->GetXaxis()->SetNdivisions(505);
    frame1_right->GetYaxis()->SetNdivisions(403);
    frame1_right->SetLineWidth(1);
    frame1_right->SetXTitle("E_{T}^{topocone40} [GeV]");
    frame1_right->GetXaxis()->SetTitleSize(20);
    frame1_right->GetXaxis()->SetTitleFont(47);
    frame1_right->GetXaxis()->SetTitleOffset(3.0);
    frame1_right->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1_right->GetXaxis()->SetLabelSize(16);
    frame1_right->SetYTitle("Data/MC");
    frame1_right->GetYaxis()->SetTitleSize(15);
    frame1_right->GetYaxis()->SetTitleFont(43);
    frame1_right->GetYaxis()->SetTitleOffset(2.0);
    frame1_right->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1_right->GetYaxis()->SetLabelSize(16);
    frame1_right->Draw();
    
    TH1F *data_over_mc_topoetcone40_project_on_z_axis = (TH1F *)h_data_topoetcone40_project_on_z_axis->Clone();
    data_over_mc_topoetcone40_project_on_z_axis->Divide(h_mc_topoetcone40_project_on_z_axis);
    data_over_mc_topoetcone40_project_on_z_axis->SetMarkerColor(kBlack);
    data_over_mc_topoetcone40_project_on_z_axis->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone40_project_on_z_axis->SetMarkerSize(0.7);
    data_over_mc_topoetcone40_project_on_z_axis->SetLineColor(kBlack);
    data_over_mc_topoetcone40_project_on_z_axis->Draw("E0,SAME");

    c1->SaveAs("plots/iso_var_topoetcone40_" + menu + ".pdf", "pdf");

    //------------------------------------------------------//
    //------------------------------------------------------//
    //------------------------------------------------------//

    TCanvas *c2 = new TCanvas("c2", "c2", 1500, 500);
    c2->Divide(3, 1);

    c2->cd(1); // topoetcone40/pt plots (project on pt axis)
    //Upper plot will be in pad7
    TPad *pad7 = new TPad("pad7", "pad7", 0, 0.35, 1, 1.0);
    pad7->SetBottomMargin(0); // Upper and lower plot are joined
    //pad7->SetGridy(); // grid lines
    pad7->Draw();

    // lower plot will be in pad8
    TPad *pad8 = new TPad("pad8", "pad8", 0, 0.05, 1, 0.35);
    pad8->SetTopMargin(0);
    pad8->SetBottomMargin(0.3);
    pad8->SetGridy(); // grid lines
    pad8->Draw();

    pad7->cd(); // pad7 becomes the current pad
    //pad5->SetFrameLineWidth(2);

    // Draw curve here
    pad7->SetLogy();

    h_data_topoetcone40_over_pt_project_on_pt_axis->SetXTitle("E_{T} [GeV]");
    h_data_topoetcone40_over_pt_project_on_pt_axis->SetYTitle("Events");
    h_data_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->SetRangeUser(7, 200);
    h_data_topoetcone40_over_pt_project_on_pt_axis->SetMarkerColor(kBlack);
    h_data_topoetcone40_over_pt_project_on_pt_axis->SetMarkerStyle(kFullCircle);
    h_data_topoetcone40_over_pt_project_on_pt_axis->SetMarkerSize(0.7);
    h_data_topoetcone40_over_pt_project_on_pt_axis->SetLineColor(kBlack);
    h_data_topoetcone40_over_pt_project_on_pt_axis->Draw("E0");

    h_mc_topoetcone40_over_pt_project_on_pt_axis->SetMarkerColor(kRed);
    h_mc_topoetcone40_over_pt_project_on_pt_axis->SetMarkerStyle(kOpenTriangleUp);
    h_mc_topoetcone40_over_pt_project_on_pt_axis->SetMarkerSize(0.7);
    h_mc_topoetcone40_over_pt_project_on_pt_axis->SetLineColor(kRed);
    h_mc_topoetcone40_over_pt_project_on_pt_axis->Draw("E0,SAME");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    TLegend *leg2_left = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg2_left->AddEntry(h_data_topoetcone40_over_pt_project_on_pt_axis, "Data", "lp");
    leg2_left->AddEntry(h_mc_topoetcone40_over_pt_project_on_pt_axis, "Z #rightarrow ee MC", "lp");
    leg2_left->SetBorderSize(0);
    leg2_left->SetTextFont(42);
    leg2_left->SetTextSize(0.05);
    leg2_left->SetFillColor(0);
    leg2_left->SetFillStyle(0);
    leg2_left->Draw();

    pad8->cd(); // pad6 becomes the current pad
    double pad8_X_max = h_data_topoetcone40_over_pt_project_on_pt_axis->GetXaxis()->GetXmax(); // 200
    double pad8_X_min = 7;
    double pad8_Y_max = 2.1;
    double pad8_Y_min = 0;
    TH1F *frame2_left = pad8->DrawFrame(pad8_X_min, pad8_Y_min, pad8_X_max, pad8_Y_max);
    frame2_left->GetXaxis()->SetNdivisions(505);
    frame2_left->GetYaxis()->SetNdivisions(403);
    frame2_left->SetLineWidth(1);
    frame2_left->SetXTitle("E_{T} [GeV]");
    frame2_left->GetXaxis()->SetTitleSize(20);
    frame2_left->GetXaxis()->SetTitleFont(47);
    frame2_left->GetXaxis()->SetTitleOffset(3.0);
    frame2_left->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2_left->GetXaxis()->SetLabelSize(16);
    frame2_left->SetYTitle("Data/MC");
    frame2_left->GetYaxis()->SetTitleSize(15);
    frame2_left->GetYaxis()->SetTitleFont(43);
    frame2_left->GetYaxis()->SetTitleOffset(2.0);
    frame2_left->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2_left->GetYaxis()->SetLabelSize(16);
    frame2_left->Draw();

    TH1F *data_over_mc_topoetcone40_over_pt_project_on_pt_axis = (TH1F *)h_data_topoetcone40_over_pt_project_on_pt_axis->Clone();
    data_over_mc_topoetcone40_over_pt_project_on_pt_axis->Divide(h_mc_topoetcone40_over_pt_project_on_pt_axis);
    data_over_mc_topoetcone40_over_pt_project_on_pt_axis->SetMarkerColor(kBlack);
    data_over_mc_topoetcone40_over_pt_project_on_pt_axis->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone40_over_pt_project_on_pt_axis->SetMarkerSize(0.7);
    data_over_mc_topoetcone40_over_pt_project_on_pt_axis->SetLineColor(kBlack);
    data_over_mc_topoetcone40_over_pt_project_on_pt_axis->Draw("E0,SAME");

    //------------------------------------------------------//

    c2->cd(2); // topoetcone40 plots (project on eta axis)
    //Upper plot will be in pad9
    TPad *pad9 = new TPad("pad9", "pad9", 0, 0.35, 1, 1.0);
    pad9->SetBottomMargin(0); // Upper and lower plot are joined
    //pad9->SetGridy(); // grid lines
    pad9->Draw();

    // lower plot will be in pad4
    TPad *pad10 = new TPad("pad10", "pad10", 0, 0.05, 1, 0.35);
    pad10->SetTopMargin(0);
    pad10->SetBottomMargin(0.3);
    pad10->SetGridy(); // grid lines
    pad10->Draw();
    
    pad9->cd(); // pad9 becomes the current pad
    //pad9->SetFrameLineWidth(2);
    
    // Draw curve here
    pad9->SetLogy();
    
    h_data_topoetcone40_over_pt_project_on_eta_axis->SetXTitle("|#eta|");
    h_data_topoetcone40_over_pt_project_on_eta_axis->SetYTitle("Events");
    h_data_topoetcone40_over_pt_project_on_eta_axis->GetXaxis()->SetRangeUser(0, 2.5);
    h_data_topoetcone40_over_pt_project_on_eta_axis->SetMaximum(10000000);
    h_data_topoetcone40_over_pt_project_on_eta_axis->SetMarkerColor(kBlack);
    h_data_topoetcone40_over_pt_project_on_eta_axis->SetMarkerStyle(kFullCircle);
    h_data_topoetcone40_over_pt_project_on_eta_axis->SetMarkerSize(0.7);
    h_data_topoetcone40_over_pt_project_on_eta_axis->SetLineColor(kBlack);
    h_data_topoetcone40_over_pt_project_on_eta_axis->Draw("E0");
    
    h_mc_topoetcone40_over_pt_project_on_eta_axis->SetMarkerColor(kRed);
    h_mc_topoetcone40_over_pt_project_on_eta_axis->SetMarkerStyle(kOpenTriangleUp);
    h_mc_topoetcone40_over_pt_project_on_eta_axis->SetMarkerSize(0.7);
    h_mc_topoetcone40_over_pt_project_on_eta_axis->SetLineColor(kRed);
    h_mc_topoetcone40_over_pt_project_on_eta_axis->Draw("E0,SAME");
    
    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    
    TLegend *leg2_middle = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg2_middle->AddEntry(h_data_topoetcone40_over_pt_project_on_eta_axis, "Data", "lp");
    leg2_middle->AddEntry(h_mc_topoetcone40_over_pt_project_on_eta_axis, "Z #rightarrow ee MC", "lp");
    leg2_middle->SetBorderSize(0);
    leg2_middle->SetTextFont(42);
    leg2_middle->SetTextSize(0.05);
    leg2_middle->SetFillColor(0);
    leg2_middle->SetFillStyle(0);
    leg2_middle->Draw();
    
    pad10->cd(); // pad4 becomes the current pad
    double pad10_X_max = h_data_topoetcone40_over_pt_project_on_eta_axis->GetXaxis()->GetXmax(); // 2.5
    double pad10_X_min = h_data_topoetcone40_over_pt_project_on_eta_axis->GetXaxis()->GetXmin(); // 0
    double pad10_Y_max = 2.1;
    double pad10_Y_min = 0;
    TH1F *frame2_middle = pad10->DrawFrame(pad10_X_min, pad10_Y_min, pad10_X_max, pad10_Y_max);
    frame2_middle->GetXaxis()->SetNdivisions(505);
    frame2_middle->GetYaxis()->SetNdivisions(403);
    frame2_middle->SetLineWidth(1);
    frame2_middle->SetXTitle("|#eta|");
    frame2_middle->GetXaxis()->SetTitleSize(20);
    frame2_middle->GetXaxis()->SetTitleFont(47);
    frame2_middle->GetXaxis()->SetTitleOffset(3.0);
    frame2_middle->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2_middle->GetXaxis()->SetLabelSize(16);
    frame2_middle->SetYTitle("Data/MC");
    frame2_middle->GetYaxis()->SetTitleSize(15);
    frame2_middle->GetYaxis()->SetTitleFont(43);
    frame2_middle->GetYaxis()->SetTitleOffset(2.0);
    frame2_middle->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2_middle->GetYaxis()->SetLabelSize(16);
    frame2_middle->Draw();
    
    TH1F *data_over_mc_topoetcone40_over_pt_project_on_eta_axis = (TH1F *)h_data_topoetcone40_over_pt_project_on_eta_axis->Clone();
    data_over_mc_topoetcone40_over_pt_project_on_eta_axis->Divide(h_mc_topoetcone40_over_pt_project_on_eta_axis);
    data_over_mc_topoetcone40_over_pt_project_on_eta_axis->SetMarkerColor(kBlack);
    data_over_mc_topoetcone40_over_pt_project_on_eta_axis->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone40_over_pt_project_on_eta_axis->SetMarkerSize(0.7);
    data_over_mc_topoetcone40_over_pt_project_on_eta_axis->SetLineColor(kBlack);
    data_over_mc_topoetcone40_over_pt_project_on_eta_axis->Draw("E0,SAME");

    //------------------------------------------------------//

    c2->cd(3); // topoetcone40 plots (project on z axis)
    //Upper plot will be in pad11
    TPad *pad11 = new TPad("pad11", "pad11", 0, 0.35, 1, 1.0);
    pad11->SetBottomMargin(0); // Upper and lower plot are joined
    //pad11->SetGridy(); // grid lines
    pad11->Draw();

    // lower plot will be in pad4
    TPad *pad12 = new TPad("pad12", "pad12", 0, 0.05, 1, 0.35);
    pad12->SetTopMargin(0);
    pad12->SetBottomMargin(0.3);
    pad12->SetGridy(); // grid lines
    pad12->Draw();

    pad11->cd(); // pad9 becomes the current pad
    //pad9->SetFrameLineWidth(2);

    // Draw curve here
    pad11->SetLogy();

    h_data_topoetcone40_over_pt_project_on_z_axis->SetXTitle("E{T}^{topocone40}/p{T}");
    h_data_topoetcone40_over_pt_project_on_z_axis->SetYTitle("Events");
    h_data_topoetcone40_over_pt_project_on_z_axis->GetXaxis()->SetRangeUser(-10, 30);
    h_data_topoetcone40_over_pt_project_on_z_axis->SetMarkerColor(kBlack);
    h_data_topoetcone40_over_pt_project_on_z_axis->SetMarkerStyle(kFullCircle);
    h_data_topoetcone40_over_pt_project_on_z_axis->SetMarkerSize(0.7);
    h_data_topoetcone40_over_pt_project_on_z_axis->SetLineColor(kBlack);
    h_data_topoetcone40_over_pt_project_on_z_axis->Draw("E0");

    h_mc_topoetcone40_over_pt_project_on_z_axis->SetMarkerColor(kRed);
    h_mc_topoetcone40_over_pt_project_on_z_axis->SetMarkerStyle(kOpenTriangleUp);
    h_mc_topoetcone40_over_pt_project_on_z_axis->SetMarkerSize(0.7);
    h_mc_topoetcone40_over_pt_project_on_z_axis->SetLineColor(kRed);
    h_mc_topoetcone40_over_pt_project_on_z_axis->Draw("E0,SAME");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    TLegend *leg2_right = new TLegend(0.55, 0.6, 0.80, 0.76);
    leg2_right->AddEntry(h_data_topoetcone40_over_pt_project_on_eta_axis, "Data", "lp");
    leg2_right->AddEntry(h_mc_topoetcone40_over_pt_project_on_eta_axis, "Z #rightarrow ee MC", "lp");
    leg2_right->SetBorderSize(0);
    leg2_right->SetTextFont(42);
    leg2_right->SetTextSize(0.05);
    leg2_right->SetFillColor(0);
    leg2_right->SetFillStyle(0);
    leg2_right->Draw();

    pad12->cd(); // pad4 becomes the current pad
    double pad12_X_max = 1;
    double pad12_X_min = -0.25;
    double pad12_Y_max = 2.1;
    double pad12_Y_min = 0;
    TH1F *frame2_right = pad12->DrawFrame(pad12_X_min, pad12_Y_min, pad12_X_max, pad12_Y_max);
    frame2_right->GetXaxis()->SetNdivisions(505);
    frame2_right->GetYaxis()->SetNdivisions(403);
    frame2_right->SetLineWidth(1);
    frame2_right->SetXTitle("E_{T}^{topocone40}/p_{T}");
    frame2_right->GetXaxis()->SetTitleSize(20);
    frame2_right->GetXaxis()->SetTitleFont(47);
    frame2_right->GetXaxis()->SetTitleOffset(3.0);
    frame2_right->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2_right->GetXaxis()->SetLabelSize(16);
    frame2_right->SetYTitle("Data/MC");
    frame2_right->GetYaxis()->SetTitleSize(15);
    frame2_right->GetYaxis()->SetTitleFont(43);
    frame2_right->GetYaxis()->SetTitleOffset(2.0);
    frame2_right->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2_right->GetYaxis()->SetLabelSize(16);
    frame2_right->Draw();

    TH1F *data_over_mc_topoetcone40_over_pt_project_on_z_axis = (TH1F *)h_data_topoetcone40_over_pt_project_on_z_axis->Clone();
    data_over_mc_topoetcone40_over_pt_project_on_z_axis->Divide(h_mc_topoetcone40_over_pt_project_on_z_axis);
    data_over_mc_topoetcone40_over_pt_project_on_z_axis->SetMarkerColor(kBlack);
    data_over_mc_topoetcone40_over_pt_project_on_z_axis->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone40_over_pt_project_on_z_axis->SetMarkerSize(0.7);
    data_over_mc_topoetcone40_over_pt_project_on_z_axis->SetLineColor(kBlack);
    data_over_mc_topoetcone40_over_pt_project_on_z_axis->Draw("E0,SAME");

    c2->SaveAs("plots/iso_var_topoetcone40_over_pt_" + menu + ".pdf", "pdf");
}
