#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
/*
#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"
*/
#include <iostream>
using namespace std;

void mll()
{
    gStyle->SetOptStat(0);

    //bool debug = true;
    bool debug = false;

    TFile *data  = TFile::Open("data.root");
    TFile *AF2mc = TFile::Open("AF2mc.root");
    TFile *FSmc  = TFile::Open("FullSimmc.root");

    TString folder = "LooseAndBLayerLLH_d0z0_Smooth_v11_isolLoose_TemplRun2Variation1AndPassTrackQuality_TagTightLLH_v11";

    TH3F *hdata_den = (TH3F *)data->Get(folder + "/" + folder + "_Data_Den_Mll_3d");
    TH3F *hdata_num = (TH3F *)data->Get(folder + "/" + folder + "_Data_Num_Mll_3d");
    TH3F *hAF2mc_den = (TH3F *)AF2mc->Get(folder + "/" + folder + "_MCZee_NoFilter_Den_Mll_3d");
    TH3F *hAF2mc_num = (TH3F *)AF2mc->Get(folder + "/" + folder + "_MCZee_NoFilter_Num_Mll_3d");
    TH3F *hFSmc_den = (TH3F *)FSmc->Get(folder + "/" + folder + "_MCZee_NoFilter_Den_Mll_3d");
    TH3F *hFSmc_num = (TH3F *)FSmc->Get(folder + "/" + folder + "_MCZee_NoFilter_Num_Mll_3d");

    if (debug) {
        cout << hdata_den->GetName() << " at " << hdata_den << endl;
        cout << hdata_num->GetName() << " at " << hdata_num << endl;
        cout << hAF2mc_den->GetName() << " at " << hAF2mc_den << endl;
        cout << hAF2mc_num->GetName() << " at " << hAF2mc_num << endl;
        cout << hFSmc_den->GetName() << " at " << hFSmc_den << endl;
        cout << hFSmc_num->GetName() << " at " << hFSmc_num << endl;
    }

    // low pT: 7 GeV < pT < 10 GeV
    TH1F *hdata_den_1D_low_pT = (TH1F *)hdata_den->ProjectionZ("", 2, 2)->Clone();
    TH1F *hdata_num_1D_low_pT = (TH1F *)hdata_num->ProjectionZ("", 2, 2)->Clone();
    TH1F *hAF2mc_den_1D_low_pT = (TH1F *)hAF2mc_den->ProjectionZ("", 2, 2)->Clone();
    TH1F *hAF2mc_num_1D_low_pT = (TH1F *)hAF2mc_num->ProjectionZ("", 2, 2)->Clone();
    TH1F *hFSmc_den_1D_low_pT = (TH1F *)hFSmc_den->ProjectionZ("", 2, 2)->Clone();
    TH1F *hFSmc_num_1D_low_pT = (TH1F *)hFSmc_num->ProjectionZ("", 2, 2)->Clone();

    double data_den_area_low_pT = hdata_den_1D_low_pT->Integral(21, 41); // bin 21 lower edge = 80 GeV
    double data_num_area_low_pT = hdata_num_1D_low_pT->Integral(21, 41); // bin 41 lower edge = 100 GeV
    double AF2mc_den_area_low_pT = hAF2mc_den_1D_low_pT->Integral(21, 41);
    double AF2mc_num_area_low_pT = hAF2mc_num_1D_low_pT->Integral(21, 41);
    double FSmc_den_area_low_pT = hFSmc_den_1D_low_pT->Integral(21, 41);
    double FSmc_num_area_low_pT = hFSmc_num_1D_low_pT->Integral(21, 41);

    hAF2mc_den_1D_low_pT->Scale(data_den_area_low_pT / AF2mc_den_area_low_pT);
    hAF2mc_num_1D_low_pT->Scale(data_num_area_low_pT / AF2mc_num_area_low_pT);
    hFSmc_den_1D_low_pT->Scale(data_den_area_low_pT / FSmc_den_area_low_pT);
    hFSmc_num_1D_low_pT->Scale(data_num_area_low_pT / FSmc_num_area_low_pT);

    int low_pT_low_edge = hdata_den->GetXaxis()->GetBinLowEdge(2) / 1000;
    int low_pT_up_edge = hdata_den->GetXaxis()->GetBinUpEdge(2) / 1000;
    TString low_pT_range = TString::Format("%d", static_cast<int>(low_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(low_pT_up_edge)) + " GeV";

    if (debug) {
        cout << hdata_den_1D_low_pT << endl;
        cout << hdata_num_1D_low_pT << endl;
        cout << hAF2mc_den_1D_low_pT << endl;
        cout << hAF2mc_num_1D_low_pT << endl;
        cout << hFSmc_den_1D_low_pT << endl;
        cout << hFSmc_num_1D_low_pT << endl;
        cout << low_pT_low_edge << endl;
        cout << low_pT_up_edge << endl;
    }

    // medium pT: 35 GeV < pT < 40 GeV
    TH1F *hdata_den_1D_medium_pT = (TH1F *)hdata_den->ProjectionZ("", 8, 8)->Clone();
    TH1F *hdata_num_1D_medium_pT = (TH1F *)hdata_num->ProjectionZ("", 8, 8)->Clone();
    TH1F *hAF2mc_den_1D_medium_pT = (TH1F *)hAF2mc_den->ProjectionZ("", 8, 8)->Clone();
    TH1F *hAF2mc_num_1D_medium_pT = (TH1F *)hAF2mc_num->ProjectionZ("", 8, 8)->Clone();
    TH1F *hFSmc_den_1D_medium_pT = (TH1F *)hFSmc_den->ProjectionZ("", 8, 8)->Clone();
    TH1F *hFSmc_num_1D_medium_pT = (TH1F *)hFSmc_num->ProjectionZ("", 8, 8)->Clone();

    double data_den_area_medium_pT = hdata_den_1D_medium_pT->Integral(21, 41);
    double data_num_area_medium_pT = hdata_num_1D_medium_pT->Integral(21, 41);
    double AF2mc_den_area_medium_pT = hAF2mc_den_1D_medium_pT->Integral(21, 41);
    double AF2mc_num_area_medium_pT = hAF2mc_num_1D_medium_pT->Integral(21, 41);
    double FSmc_den_area_medium_pT = hFSmc_den_1D_medium_pT->Integral(21, 41);
    double FSmc_num_area_medium_pT = hFSmc_num_1D_medium_pT->Integral(21, 41);

    hAF2mc_den_1D_medium_pT->Scale(data_den_area_medium_pT / AF2mc_den_area_medium_pT);
    hAF2mc_num_1D_medium_pT->Scale(data_num_area_medium_pT / AF2mc_num_area_medium_pT);
    hFSmc_den_1D_medium_pT->Scale(data_den_area_medium_pT / FSmc_den_area_medium_pT);
    hFSmc_num_1D_medium_pT->Scale(data_num_area_medium_pT / FSmc_num_area_medium_pT);

    int medium_pT_low_edge = hdata_den->GetXaxis()->GetBinLowEdge(8) / 1000;
    int medium_pT_up_edge = hdata_den->GetXaxis()->GetBinUpEdge(8) / 1000;
    TString medium_pT_range = TString::Format("%d", static_cast<int>(medium_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(medium_pT_up_edge)) + " GeV";

    if (debug) {
        cout << hdata_den_1D_medium_pT << endl;
        cout << hdata_num_1D_medium_pT << endl;
        cout << hAF2mc_den_1D_medium_pT << endl;
        cout << hAF2mc_num_1D_medium_pT << endl;
        cout << hFSmc_den_1D_medium_pT << endl;
        cout << hFSmc_num_1D_medium_pT << endl;
        cout << medium_pT_low_edge << endl;
        cout << medium_pT_up_edge << endl;
    }

    // high pT: 60 GeV < pT < 80 GeV
    TH1F *hdata_den_1D_high_pT = (TH1F *)hdata_den->ProjectionZ("", 13, 13)->Clone();
    TH1F *hdata_num_1D_high_pT = (TH1F *)hdata_num->ProjectionZ("", 13, 13)->Clone();
    TH1F *hAF2mc_den_1D_high_pT = (TH1F *)hAF2mc_den->ProjectionZ("", 13, 13)->Clone();
    TH1F *hAF2mc_num_1D_high_pT = (TH1F *)hAF2mc_num->ProjectionZ("", 13, 13)->Clone();
    TH1F *hFSmc_den_1D_high_pT = (TH1F *)hFSmc_den->ProjectionZ("", 13, 13)->Clone();
    TH1F *hFSmc_num_1D_high_pT = (TH1F *)hFSmc_num->ProjectionZ("", 13, 13)->Clone();

    double data_den_area_high_pT = hdata_den_1D_high_pT->Integral(21, 41);
    double data_num_area_high_pT = hdata_num_1D_high_pT->Integral(21, 41);
    double AF2mc_den_area_high_pT = hAF2mc_den_1D_high_pT->Integral(21, 41);
    double AF2mc_num_area_high_pT = hAF2mc_num_1D_high_pT->Integral(21, 41);
    double FSmc_den_area_high_pT = hFSmc_den_1D_high_pT->Integral(21, 41);
    double FSmc_num_area_high_pT = hFSmc_num_1D_high_pT->Integral(21, 41);

    hAF2mc_den_1D_high_pT->Scale(data_den_area_high_pT / AF2mc_den_area_high_pT);
    hAF2mc_num_1D_high_pT->Scale(data_num_area_high_pT / AF2mc_num_area_high_pT);
    hFSmc_den_1D_high_pT->Scale(data_den_area_high_pT / FSmc_den_area_high_pT);
    hFSmc_num_1D_high_pT->Scale(data_num_area_high_pT / FSmc_num_area_high_pT);

    int high_pT_low_edge = hdata_den->GetXaxis()->GetBinLowEdge(13) / 1000;
    int high_pT_up_edge = hdata_den->GetXaxis()->GetBinUpEdge(13) / 1000;
    TString high_pT_range = TString::Format("%d", static_cast<int>(high_pT_low_edge)) + " GeV < p_{T} < " + TString::Format("%d", static_cast<int>(high_pT_up_edge)) + " GeV";

    if (debug) {
        cout << hdata_den_1D_high_pT << endl;
        cout << hdata_num_1D_high_pT << endl;
        cout << hAF2mc_den_1D_high_pT << endl;
        cout << hAF2mc_num_1D_high_pT << endl;
        cout << hFSmc_den_1D_high_pT << endl;
        cout << hFSmc_num_1D_high_pT << endl;
        cout << high_pT_low_edge << endl;
        cout << high_pT_up_edge << endl;
    }

    TCanvas *c1 = new TCanvas("c1", "M_{ll}", 1200, 400);
    c1->Divide(3, 1);
    c1->cd(1);
    //Upper plot will be in pad1up
    TPad *pad1up = new TPad("pad1up", "pad1up", 0, 0.35, 1, 1.0);
    pad1up->SetBottomMargin(0); // Upper and lower plot are joined
    pad1up->Draw();
    // lower plot will be in pad1down
    TPad *pad1down = new TPad("pad1down", "pad1down", 0, 0.05, 1, 0.35);
    pad1down->SetTopMargin(0);
    pad1down->SetBottomMargin(0.3);
    pad1down->SetGridy(); // grid lines
    pad1down->Draw();
    //
    // pad1up: top pad
    //
    pad1up->cd(); // pad1up becomes the current pad
    // Draw curve here
    hdata_den_1D_low_pT->SetTitle(low_pT_range);
    hdata_den_1D_low_pT->GetXaxis()->SetTitle("M_{ll} [GeV]");
    hdata_den_1D_low_pT->GetYaxis()->SetTitle("Events");
    hdata_den_1D_low_pT->SetMarkerStyle(kFullCircle);
    hdata_den_1D_low_pT->SetMarkerColor(kBlack);
    hdata_den_1D_low_pT->SetMarkerSize(0.7);
    hdata_den_1D_low_pT->SetLineColor(kBlack);
    hdata_den_1D_low_pT->GetXaxis()->SetRangeUser(60, 120);
    hdata_den_1D_low_pT->Draw();

    hAF2mc_den_1D_low_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2mc_den_1D_low_pT->SetMarkerColor(kRed);
    hAF2mc_den_1D_low_pT->SetMarkerSize(0.7);
    hAF2mc_den_1D_low_pT->SetLineColor(kRed);
    hAF2mc_den_1D_low_pT->Draw("same");

    hFSmc_den_1D_low_pT->SetMarkerStyle(kFullTriangleDown);
    hFSmc_den_1D_low_pT->SetMarkerColor(kBlue);
    hFSmc_den_1D_low_pT->SetMarkerSize(0.7);
    hFSmc_den_1D_low_pT->SetLineColor(kBlue);
    hFSmc_den_1D_low_pT->Draw("same");

    //ATLASLabel(0.1, 0.85,"Internal");

    TLegend *legend1 = new TLegend(0.6, 0.7, 0.89, 0.89);
    legend1->SetBorderSize(0);
    legend1->SetFillColor(0);
    legend1->SetFillStyle(0);
    legend1->AddEntry(hdata_den_1D_low_pT, "Data");
    legend1->AddEntry(hAF2mc_den_1D_low_pT, "AF2 MC");
    legend1->AddEntry(hFSmc_den_1D_low_pT, "FullSim MC");
    legend1->Draw();

    //
    // pad1down: bottom pad
    //
    pad1down->cd(); // pad1down becomes the current pad

    TH1F *frame1 = pad1down->DrawFrame(60, 0., 120, 1.99);
    frame1->GetXaxis()->SetNdivisions(510);
    frame1->GetYaxis()->SetNdivisions(405);
    frame1->SetLineWidth(1);
    frame1->SetXTitle("M_{ll} [GeV]");
    frame1->GetXaxis()->SetTitleSize(12);
    frame1->GetXaxis()->SetTitleFont(47);
    frame1->GetXaxis()->SetTitleOffset(3.5);
    frame1->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1->GetXaxis()->SetLabelSize(12);
    frame1->SetYTitle("MC/data");
    frame1->GetYaxis()->SetTitleSize(12);
    frame1->GetYaxis()->SetTitleFont(43);
    frame1->GetYaxis()->SetTitleOffset(1.5);
    frame1->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1->GetYaxis()->SetLabelSize(10);
    frame1->Draw();

    // Calculate the ratio between data and MC
    hdata_den_1D_low_pT->Sumw2();
    hAF2mc_den_1D_low_pT->Sumw2();
    hFSmc_den_1D_low_pT->Sumw2();
    TH1F *ratio1_low_pT = (TH1F *)hAF2mc_den_1D_low_pT->Clone();
    TH1F *ratio2_low_pT = (TH1F *)hFSmc_den_1D_low_pT->Clone();
    ratio1_low_pT->Divide(hdata_den_1D_low_pT);
    ratio2_low_pT->Divide(hdata_den_1D_low_pT);

    ratio1_low_pT->SetLineColor(kRed);
    ratio1_low_pT->SetLineWidth(1);
    ratio1_low_pT->SetMarkerColor(kRed);
    ratio1_low_pT->SetMarkerSize(0.7);
    ratio1_low_pT->SetMarkerStyle(20);
    ratio1_low_pT->Draw("E1,same");

    ratio2_low_pT->SetLineColor(kBlue);
    ratio2_low_pT->SetLineWidth(1);
    ratio2_low_pT->SetMarkerColor(kBlue);
    ratio2_low_pT->SetMarkerSize(0.7);
    ratio2_low_pT->SetMarkerStyle(20);
    ratio2_low_pT->Draw("E1,same");

    c1->cd(2);
    //Upper plot will be in pad2up
    TPad *pad2up = new TPad("pad2up", "pad2up", 0, 0.35, 1, 1.0);
    pad2up->SetBottomMargin(0); // Upper and lower plot are joined
    pad2up->Draw();
    // lower plot will be in pad2down
    TPad *pad2down = new TPad("pad2down", "pad2down", 0, 0.05, 1, 0.35);
    pad2down->SetTopMargin(0);
    pad2down->SetBottomMargin(0.3);
    pad2down->SetGridy(); // grid lines
    pad2down->Draw();
    //
    // pad2up: top pad
    //
    pad2up->cd(); // pad2up becomes the current pad
    // Draw curve here
    hdata_den_1D_medium_pT->SetTitle(medium_pT_range);
    hdata_den_1D_medium_pT->GetXaxis()->SetTitle("M_{ll} [GeV]");
    hdata_den_1D_medium_pT->GetYaxis()->SetTitle("Events");
    hdata_den_1D_medium_pT->SetMarkerStyle(kFullCircle);
    hdata_den_1D_medium_pT->SetMarkerColor(kBlack);
    hdata_den_1D_medium_pT->SetMarkerSize(0.7);
    hdata_den_1D_medium_pT->SetLineColor(kBlack);
    hdata_den_1D_medium_pT->GetXaxis()->SetRangeUser(60, 120);
    hdata_den_1D_medium_pT->Draw();

    hAF2mc_den_1D_medium_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2mc_den_1D_medium_pT->SetMarkerColor(kRed);
    hAF2mc_den_1D_medium_pT->SetMarkerSize(0.7);
    hAF2mc_den_1D_medium_pT->SetLineColor(kRed);
    hAF2mc_den_1D_medium_pT->Draw("same");

    hFSmc_den_1D_medium_pT->SetMarkerStyle(kFullTriangleDown);
    hFSmc_den_1D_medium_pT->SetMarkerColor(kBlue);
    hFSmc_den_1D_medium_pT->SetLineColor(kBlue);
    hFSmc_den_1D_medium_pT->SetMarkerSize(0.7);
    hFSmc_den_1D_medium_pT->Draw("same");

    //ATLASLabel(0.1, 0.85,"Internal");

    TLegend *legend2 = new TLegend(0.6, 0.7, 0.89, 0.89);
    legend2->SetBorderSize(0);
    legend2->SetFillColor(0);
    legend2->SetFillStyle(0);
    legend2->AddEntry(hdata_den_1D_medium_pT, "Data");
    legend2->AddEntry(hAF2mc_den_1D_medium_pT, "AF2 MC");
    legend2->AddEntry(hFSmc_den_1D_medium_pT, "FullSim MC");
    legend2->Draw();

    //
    // pad2down: bottom pad
    //
    pad2down->cd(); // pad2down becomes the current pad

    TH1F *frame2 = pad2down->DrawFrame(60, 0., 120, 1.99);
    frame2->GetXaxis()->SetNdivisions(510);
    frame2->GetYaxis()->SetNdivisions(405);
    frame2->SetLineWidth(1);
    frame2->SetXTitle("M_{ll} [GeV]");
    frame2->GetXaxis()->SetTitleSize(12);
    frame2->GetXaxis()->SetTitleFont(47);
    frame2->GetXaxis()->SetTitleOffset(3.5);
    frame2->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2->GetXaxis()->SetLabelSize(12);
    frame2->SetYTitle("MC/data");
    frame2->GetYaxis()->SetTitleSize(12);
    frame2->GetYaxis()->SetTitleFont(43);
    frame2->GetYaxis()->SetTitleOffset(1.5);
    frame2->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2->GetYaxis()->SetLabelSize(10);
    frame2->Draw();

    // Calculate the ratio between hOld and hNew
    hdata_den_1D_medium_pT->Sumw2();
    hAF2mc_den_1D_medium_pT->Sumw2();
    hFSmc_den_1D_medium_pT->Sumw2();
    TH1F *ratio1_medium_pT = (TH1F *)hAF2mc_den_1D_medium_pT->Clone();
    TH1F *ratio2_medium_pT = (TH1F *)hFSmc_den_1D_medium_pT->Clone();
    ratio1_medium_pT->Divide(hdata_den_1D_medium_pT);
    ratio2_medium_pT->Divide(hdata_den_1D_medium_pT);

    ratio1_medium_pT->SetLineColor(kRed);
    ratio1_medium_pT->SetLineWidth(1);
    ratio1_medium_pT->SetMarkerColor(kRed);
    ratio1_medium_pT->SetMarkerSize(0.7);
    ratio1_medium_pT->SetMarkerStyle(20);
    ratio1_medium_pT->Draw("E1,same");

    ratio2_medium_pT->SetLineColor(kBlue);
    ratio2_medium_pT->SetLineWidth(1);
    ratio2_medium_pT->SetMarkerColor(kBlue);
    ratio2_medium_pT->SetMarkerSize(0.7);
    ratio2_medium_pT->SetMarkerStyle(20);
    ratio2_medium_pT->Draw("E1,same");

    c1->cd(3);
    //Upper plot will be in pad3up
    TPad *pad3up = new TPad("pad3up", "pad3up", 0, 0.35, 1, 1.0);
    pad3up->SetBottomMargin(0); // Upper and lower plot are joined
    pad3up->Draw();
    // lower plot will be in pad3down
    TPad *pad3down = new TPad("pad3down", "pad3down", 0, 0.05, 1, 0.35);
    pad3down->SetTopMargin(0);
    pad3down->SetBottomMargin(0.3);
    pad3down->SetGridy(); // grid lines
    pad3down->Draw();
    //
    // pad3up: top pad
    //
    pad3up->cd(); // pad3up becomes the current pad
    // Draw curve here
    hdata_den_1D_high_pT->SetTitle(high_pT_range);
    hdata_den_1D_high_pT->GetXaxis()->SetTitle("M_{ll} [GeV]");
    hdata_den_1D_high_pT->GetYaxis()->SetTitle("Events");
    hdata_den_1D_high_pT->SetMarkerStyle(kFullCircle);
    hdata_den_1D_high_pT->SetMarkerColor(kBlack);
    hdata_den_1D_high_pT->SetMarkerSize(0.7);
    hdata_den_1D_high_pT->SetLineColor(kBlack);
    hdata_den_1D_high_pT->GetXaxis()->SetRangeUser(60, 120);
    hdata_den_1D_high_pT->Draw();

    hAF2mc_den_1D_high_pT->SetMarkerStyle(kFullTriangleUp);
    hAF2mc_den_1D_high_pT->SetMarkerColor(kRed);
    hAF2mc_den_1D_high_pT->SetMarkerSize(0.7);
    hAF2mc_den_1D_high_pT->SetLineColor(kRed);
    hAF2mc_den_1D_high_pT->Draw("same");

    hFSmc_den_1D_high_pT->SetMarkerStyle(kFullTriangleDown);
    hFSmc_den_1D_high_pT->SetMarkerColor(kBlue);
    hFSmc_den_1D_high_pT->SetMarkerSize(0.7);
    hFSmc_den_1D_high_pT->SetLineColor(kBlue);
    hFSmc_den_1D_high_pT->Draw("same");

    //ATLASLabel(0.1, 0.85,"Internal");

    TLegend *legend3 = new TLegend(0.6, 0.7, 0.89, 0.89);
    legend3->SetBorderSize(0);
    legend3->SetFillColor(0);
    legend3->SetFillStyle(0);
    legend3->AddEntry(hdata_den_1D_high_pT, "Data");
    legend3->AddEntry(hAF2mc_den_1D_high_pT, "AF2 MC");
    legend3->AddEntry(hFSmc_den_1D_high_pT, "FullSim MC");
    legend3->Draw();

    //
    // pad3down: bottom pad
    //
    pad3down->cd(); // pad3down becomes the current pad

    TH1F *frame3 = pad3down->DrawFrame(60, 0., 120, 1.99);
    frame3->GetXaxis()->SetNdivisions(510);
    frame3->GetYaxis()->SetNdivisions(405);
    frame3->SetLineWidth(1);
    frame3->SetXTitle("M_{ll} [GeV]");
    frame3->GetXaxis()->SetTitleSize(12);
    frame3->GetXaxis()->SetTitleFont(47);
    frame3->GetXaxis()->SetTitleOffset(3.5);
    frame3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame3->GetXaxis()->SetLabelSize(12);
    frame3->SetYTitle("MC/data");
    frame3->GetYaxis()->SetTitleSize(12);
    frame3->GetYaxis()->SetTitleFont(43);
    frame3->GetYaxis()->SetTitleOffset(1.5);
    frame3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame3->GetYaxis()->SetLabelSize(10);
    frame3->Draw();

    // Calculate the ratio between hOld and hNew
    hdata_den_1D_high_pT->Sumw2();
    hAF2mc_den_1D_high_pT->Sumw2();
    hFSmc_den_1D_high_pT->Sumw2();
    TH1F *ratio1_high_pT = (TH1F *)hAF2mc_den_1D_high_pT->Clone();
    TH1F *ratio2_high_pT = (TH1F *)hFSmc_den_1D_high_pT->Clone();
    ratio1_high_pT->Divide(hdata_den_1D_high_pT);
    ratio2_high_pT->Divide(hdata_den_1D_high_pT);

    ratio1_high_pT->SetLineColor(kRed);
    ratio1_high_pT->SetLineWidth(1);
    ratio1_high_pT->SetMarkerColor(kRed);
    ratio1_high_pT->SetMarkerSize(0.7);
    ratio1_high_pT->SetMarkerStyle(20);
    ratio1_high_pT->Draw("E1,same");

    ratio2_high_pT->SetLineColor(kBlue);
    ratio2_high_pT->SetLineWidth(1);
    ratio2_high_pT->SetMarkerColor(kBlue);
    ratio2_high_pT->SetMarkerSize(0.7);
    ratio2_high_pT->SetMarkerStyle(20);
    ratio2_high_pT->Draw("E1,same");

    c1->Print("plots/Mll_distributions.pdf");
}
