#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include "plot-SF/AtlasStyle/AtlasStyle.C"
#include "plot-SF/AtlasStyle/AtlasLabels.C"
#include "plot-SF/AtlasStyle/AtlasUtils.C"

#include <iostream>
using namespace std;

//
// Correct the error of histogram
//
void fixHistogramError(TH1F *h1, TH1F *herr)
{
    for (Int_t ik = 1; ik <= h1->GetXaxis()->GetNbins(); ik++) {
        float err = herr->GetBinContent(ik);
        h1->SetBinError(ik, err);
    }
}

//
// make 1 dimension projection ratio plots
//
void make_ratio_plot(TString xtitle, TString ytitle, TString canvas_name, TString range, float low_edge, float up_edge,
                     TH1F *hData, TH1F *hMC, TH1F *hSF, TH1F *hSF_stat)
{
    gStyle->SetOptStat(0);
    //SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    TString pad1_X_title = xtitle;
    //float pad1_X_max = hData->GetXaxis()->GetXmax();
    //float pad1_X_min = hData->GetXaxis()->GetXmin();
    float pad1_X_max = 0;
    float pad1_X_min = 0;
    if (xtitle.Contains("eta")) { // projection on eta axis
        pad1_X_max = hData->GetXaxis()->GetXmax();
        pad1_X_min = hData->GetXaxis()->GetXmin();
    }
    else { // projection on pt axis
        pad1_X_max = 35.;
        pad1_X_min = 1.;
    }
    TString pad1_Y_title = ytitle;
    double pad1_Y_max = 1.05;
    double pad1_Y_min = 0.95;
    TString pad2_X_title = xtitle;
    float pad2_X_max = pad1_X_max;
    float pad2_X_min = pad1_X_min;
    TString pad2_Y_title = "Data / MC";
    double pad2_Y_max = 1.02;
    double pad2_Y_min = 0.98;
    if (debug) {
        cout << "(pad1_X_min, pad1_X_max)=(" << pad1_X_min << ", " << pad1_X_max << ")" << endl;
        cout << "(pad2_X_min, pad2_X_max)=(" << pad2_X_min << ", " << pad2_X_max << ")" << endl;
    }
/*
    float high, low;
    FindOptimalRange(high, low, hData, hMC);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        pad1_Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (pad1_Y_max < 1.10)
        pad1_Y_max = 1.10;
    else
        pad1_Y_max = high;
    if (pad1_Y_min > 0.91)
        pad1_Y_min = 0.91;
    else
        pad1_Y_min = low;
    if (debug)
        cout << "(pad1_Y_min, pad1_Y_max)=(" << pad1_Y_min << ", " << pad1_Y_max << ")" << endl;
    FindOptimalRange(high, low, hSF);
    if (debug)
        cout << "(low, high)=(" << low << ", " << high << ")" << endl;
    if (low < 0.0)
        pad2_Y_min = 0.0;
    if (low > high) {
        low = 0.0;
        high = 2.0;
    }
    if (pad2_Y_max < 1.10)
        pad2_Y_max = 1.10;
    else
        pad2_Y_max = high;
    if (pad2_Y_min > 0.91)
        pad2_Y_min = 0.91;
    else
        pad2_Y_min = low;
    if (debug)
        cout << "(pad2_Y_min, pad2_Y_max)=(" << pad2_Y_min << ", " << pad2_Y_max << ")" << endl;
*/
    // Big Canvas
    TCanvas *c1 = new TCanvas(canvas_name, canvas_name, 800, 800);

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0.03); // Upper and lower plot are joined
    //pad1->SetGridy(); // grid lines
    pad1->SetTickx();
    pad1->SetTicky();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0.03);
    pad2->SetBottomMargin(0.3);
    pad2->SetGridy(); // grid lines
    pad2->SetTickx();
    pad2->SetTicky();
    pad2->Draw();

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here

    // Set titles, maximum and minimum of axes
    //hData->SetTitle(canvas_name);
    hData->SetTitle("");
    hData->GetXaxis()->SetTitle(pad1_X_title);
    hData->GetYaxis()->SetTitle(pad1_Y_title);
    if (!xtitle.Contains("eta")) { // projection on pt axis
        hData->GetXaxis()->SetRangeUser(pad1_X_min, pad1_X_max);
    }
    hData->SetMaximum(pad1_Y_max);
    hData->SetMinimum(pad1_Y_min);
    hData->GetXaxis()->SetLabelSize(0); // Remove the x lable in the top pad
    hData->GetYaxis()->SetTitleSize(0.07);
    hData->GetYaxis()->SetTitleOffset(0.60);
    hData->GetYaxis()->SetLabelSize(0.04);
    hData->GetYaxis()->SetLabelOffset(0.005);
    // Data with total uncertianty as color band
    hData->SetLineColor(kBlue);
    hData->SetLineWidth(1);
    hData->SetMarkerColor(kBlue);
    hData->SetMarkerSize(1);
    hData->SetMarkerStyle(kFullCircle);
    hData->Draw("E0");
    // MC
    hMC->SetLineColor(kRed);
    hMC->SetLineWidth(1);
    hMC->SetMarkerColor(kRed);
    hMC->SetMarkerSize(1);
    hMC->SetMarkerStyle(kOpenCircle);
    hMC->Draw("E0,SAME");
    // Add line
    TLine *line = new TLine(pad1_X_min, 1., pad1_X_max, 1.);
    line->SetLineColor(kBlack);
    line->SetLineStyle(2);
    line->SetLineWidth(1);
    line->Draw("SAME");
    // Add legend
    TLegend *leg_top = new TLegend(0.15, 0.5, 0.3, 0.70);
    leg_top->AddEntry(hMC, "Z #rightarrow ee MC", "lp");
    leg_top->AddEntry(hData, "Data", "lp");
    leg_top->SetBorderSize(0);
    leg_top->SetTextFont(42);
    leg_top->SetTextSize(0.04);
    leg_top->SetFillColor(0);
    leg_top->SetFillStyle(0);
    leg_top->Draw();

    ATLASLabel(0.15, 0.85,"Internal");
    myText(0.15, 0.77, kBlack, "#sqrt{s} = 13 TeV, 33.925 fb^{-1}");
    myText(0.15, 0.70, kBlack, const_cast<char *>(range.Data()));
    myText(0.5, 0.77, kBlack, "TightLLH");
    myText(0.5, 0.70, kBlack, "isol" + canvas_name);

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    TH1F *frame = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle(pad2_X_title);
    frame->GetXaxis()->SetTitleSize(30);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(3.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(20);
    frame->SetYTitle(pad2_Y_title);
    frame->GetYaxis()->SetTitleSize(30);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(1.1);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(20);
    frame->Draw();
/*
    // SF with total uncertianty as color band
    hSF->SetLineColor(kOrange-3);
    hSF->SetLineWidth(1);
    hSF->SetMarkerColor(kBlack);
    hSF->SetMarkerSize(1);
    hSF->SetMarkerStyle(kFullCircle);
    hSF->SetFillStyle(1001); // with color band
    hSF->SetFillColor(kOrange-3);
    hSF->Draw("E2,SAME");
*/
    // SF with statistical uncertianty as color band
    hSF_stat->SetLineColor(kBlack);
    hSF_stat->SetLineWidth(1);
    hSF_stat->SetMarkerColor(kBlack);
    hSF_stat->SetMarkerSize(1);
    hSF_stat->SetMarkerStyle(kFullCircle);
    hSF_stat->Draw("E0,SAME");
/*
    // Add legend
    TLegend *leg_bottom = new TLegend(0.4, 0.8, 0.7, 0.95);
    leg_bottom-> SetNColumns(2);
    leg_bottom->AddEntry(hSF, "Stat #oplus Syst", "pf");
    leg_bottom->AddEntry(hSF_stat, "Stat only", "l");
    leg_bottom->SetBorderSize(0);
    leg_bottom->SetTextFont(42);
    leg_bottom->SetTextSize(0.08);
    leg_bottom->SetFillColor(0);
    leg_bottom->SetFillStyle(0);
    leg_bottom->Draw();

    if (xtitle.Contains("eta")) { // projection on eta axis
        TString pt_low_edge = TString::Format("%d", static_cast<int>(low_edge));
        TString pt_up_edge  = TString::Format("%d", static_cast<int>(up_edge));
        c1->Print("plots/ratio_pt" + pt_low_edge + "_" + pt_up_edge + "_" + canvas_name + ".pdf");
    }
    else { // projection on pt axis
        TString eta_low_edge = TString::Format("%d", static_cast<int>(low_edge * 100.));
        TString eta_up_edge  = TString::Format("%d", static_cast<int>(up_edge * 100.));
        c1->Print("plots/ratio_eta" + eta_low_edge + "_" + eta_up_edge + "_" + canvas_name + ".pdf");
    }
*/
    c1->Print("SF_vs_Nvtx_" + canvas_name + ".pdf");
}

void plot_SF_vs_Nvtx(TString string)
{
    TString iso = "isol" + string;

    TFile *f1 = TFile::Open("output/ScaleFactors.root");
    TH2F *EffData_2D = (TH2F *)f1->Get("TightLLH_d0z0_Smooth_v11_" + iso + "/EffData_CentralValue_TightLLH_d0z0_Smooth_v11_" + iso);
    TH2F *EffMC_2D   = (TH2F *)f1->Get("TightLLH_d0z0_Smooth_v11_" + iso + "/EffMC_CentralValue_TightLLH_d0z0_Smooth_v11_" + iso);
    TH2F *SF_2D      = (TH2F *)f1->Get("TightLLH_d0z0_Smooth_v11_" + iso + "/SF_CentralValue_TightLLH_d0z0_Smooth_v11_" + iso);

    TH2F *EffData_StatErr_2D = (TH2F *)f1->Get("TightLLH_d0z0_Smooth_v11_" + iso + "/EffData_StatError_TightLLH_d0z0_Smooth_v11_" + iso);
    TH2F *EffMC_StatErr_2D   = (TH2F *)f1->Get("TightLLH_d0z0_Smooth_v11_" + iso + "/EffMC_StatError_TightLLH_d0z0_Smooth_v11_" + iso);
    TH2F *SF_StatErr_2D      = (TH2F *)f1->Get("TightLLH_d0z0_Smooth_v11_" + iso + "/SF_StatError_TightLLH_d0z0_Smooth_v11_" + iso);

    TH1F *EffData         = (TH1F *)EffData_2D->ProjectionY("", 7, 7)->Clone();
    TH1F *EffData_StatErr = (TH1F *)EffData_StatErr_2D->ProjectionY("", 7, 7)->Clone();
    fixHistogramError(EffData, EffData_StatErr);

    TH1F *EffMC         = (TH1F *)EffMC_2D->ProjectionY("", 7, 7)->Clone();
    TH1F *EffMC_StatErr = (TH1F *)EffMC_StatErr_2D->ProjectionY("", 7, 7)->Clone();
    fixHistogramError(EffMC, EffMC_StatErr);

    TH1F *SF         = (TH1F *)SF_2D->ProjectionY("", 7, 7)->Clone();
    TH1F *SF_StatErr = (TH1F *)SF_StatErr_2D->ProjectionY("", 7, 7)->Clone();
    fixHistogramError(SF, SF_StatErr);

    TH1F *SF_clone = (TH1F *)SF->Clone();

    int range_low = static_cast<int>(SF_2D->GetXaxis()->GetBinLowEdge(7)) / 1000;
    int range_up = static_cast<int>(SF_2D->GetXaxis()->GetBinUpEdge(7)) / 1000;
    TString range = TString::Format("%d", range_low) + " GeV < p_{T} < " + TString::Format("%d", range_up) + " GeV";

    make_ratio_plot("Number of primary vertices", "Efficiency", string, range, 5, 5,
                    EffData, EffMC, SF, SF_clone);
}