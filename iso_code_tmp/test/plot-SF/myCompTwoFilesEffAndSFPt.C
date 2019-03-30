// This script is used to make 1-dim ratio plots for single eta bin (project on eta axis).
//
//
//
////int eta = 11; // eta = 0-0.1
//int eta = 12; // eta = 0.1-0.6
////int eta = 13; // eta = 0.6-0.8
//int eta = 15; // eta = 1.15-1.37
//int eta = 18; // eta = 1.81-2.01
//int eta = 19; // eta = 2.01-2.37
//
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

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"
#include "FindOptimalRange.C"

#include <iostream>

void myCompTwoFilesEffAndSFPt(TString menu = "TightLLH",
                               TString iso  = "isolTight",
                               int eta = 12)
{
    // Data
    // Set titles and axes scales for top pad (pad1)
    TString pad1_X_title = "E_{T} [MeV]";
    TString pad1_Y_title = "Data Efficiency";
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad2)
    TString pad2_X_title = "E_{T} [MeV]";
    TString pad2_Y_title = "MC15b/AF2";
    double pad2_Y_max = 1.05;
    double pad2_Y_min = 0.95;

    // MC
    // Set titles and axes scales for top pad (pad3)
    TString pad3_X_title = "E_{T} [MeV]";
    TString pad3_Y_title = "MC Efficiency";
    double pad3_Y_max = 1.10;
    double pad3_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad4)
    TString pad4_X_title = "E_{T} [MeV]";
    TString pad4_Y_title = "MC15b/AF2";
    double pad4_Y_max = 1.05;
    double pad4_Y_min = 0.95;

    // SF
    // Set titles and axes scales for top pad (pad5)
    TString pad5_X_title = "E_{T} [MeV]";
    TString pad5_Y_title = "Scale Factor";
    double pad5_Y_max = 1.10;
    double pad5_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad6)
    TString pad6_X_title = "E_{T} [MeV]";
    TString pad6_Y_title = "MC15b/AF2";
    double pad6_Y_max = 1.05;
    double pad6_Y_min = 0.95;

    SetAtlasStyle();

    TString folder;
    if (iso != "")
        folder = menu + "_" + iso;
    else
        folder = menu;

    TString fileName1 = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/TagAndProbe/MyTagAndProbe_test29/20160208_v8/MC15bd0z0_ScaleFactors.root";

    TH2F *effdata1      = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffData_CentralValue");
    TH2F *effdata1_tot  = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffData_TotalError");
    TH2F *effdata1_stat = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffData_StatError");

    TH2F *effmc1      = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffMC_CentralValue");
    TH2F *effmc1_tot  = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffMC_TotalError");
    TH2F *effmc1_stat = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "EffMC_StatError");

    TH2F *sf1      = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "SF_CentralValue");
    TH2F *sf1_tot  = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "SF_TotalError");
    TH2F *sf1_stat = get13TeV2DHistogram(fileName1, menu + "_d0z0_v8", iso, "SF_StatError");

    // Remider:
    // x: pt
    // y: eta
    
    TH1F* pt1[3][30]; // keeps total uncertainties
    TH1F* pt1_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot1_err[3][30];
    TH1F* sys1_err[3][30];
    TH1F* stat1_err[3][30];
    
    // Fill the uncertainties to the histograms
    for (int eta = 0; eta < effdata1->GetYaxis()->GetNbins() + 1; eta++) {
        if (eta == 0) continue; // underflow bin
        // Data
        pt1[0][eta]       = (TH1F *)effdata1->ProjectionX("", eta, eta)->Clone();
        pt1_tmp[0][eta]   = (TH1F *)effdata1->ProjectionX("", eta, eta)->Clone();
        tot1_err[0][eta]  = (TH1F *)effdata1_tot->ProjectionX("", eta, eta)->Clone();
        stat1_err[0][eta] = (TH1F *)effdata1_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt1[0][eta],     tot1_err[0][eta]);
        fixHistogramError(pt1_tmp[0][eta], stat1_err[0][eta]);

        // MC
        pt1[1][eta]       = (TH1F *)effmc1->ProjectionX("", eta, eta)->Clone();
        pt1_tmp[1][eta]   = (TH1F *)effmc1->ProjectionX("", eta, eta)->Clone();
        tot1_err[1][eta]  = (TH1F *)effmc1_tot->ProjectionX("", eta, eta)->Clone();
        stat1_err[1][eta] = (TH1F *)effmc1_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt1[1][eta],     tot1_err[1][eta]);
        fixHistogramError(pt1_tmp[1][eta], stat1_err[1][eta]);

        // SF
        pt1[2][eta]       = (TH1F *)sf1->ProjectionX("", eta, eta)->Clone();
        pt1_tmp[2][eta]   = (TH1F *)sf1->ProjectionX("", eta, eta)->Clone();
        tot1_err[2][eta]  = (TH1F *)sf1_tot->ProjectionX("", eta, eta)->Clone();
        stat1_err[2][eta] = (TH1F *)sf1_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt1[2][eta],     tot1_err[2][eta]);
        fixHistogramError(pt1_tmp[2][eta], stat1_err[2][eta]);
    }

//--------------------

    TString fileName2 = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/TagAndProbe/MyTagAndProbe_test29/20151218/AF2d0z0_ScaleFactors.root";

    TH2F *effdata2      = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffData_CentralValue");
    TH2F *effdata2_tot  = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffData_TotalError");
    TH2F *effdata2_stat = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffData_StatError");

    TH2F *effmc2      = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffMC_CentralValue");
    TH2F *effmc2_tot  = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffMC_TotalError");
    TH2F *effmc2_stat = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffMC_StatError");

    TH2F *sf2      = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "SF_CentralValue");
    TH2F *sf2_tot  = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "SF_TotalError");
    TH2F *sf2_stat = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "SF_StatError");

    TH1F* pt2[3][30]; // keeps total uncertainties
    TH1F* pt2_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot2_err[3][30];
    TH1F* sys2_err[3][30];
    TH1F* stat2_err[3][30];

    // Fill the uncertainties to the histograms
    for (int eta = 0; eta < effdata2->GetYaxis()->GetNbins() + 1; eta++) {
        if (eta == 0) continue; // underflow bin
        // Data
        pt2[0][eta]       = (TH1F *)effdata2->ProjectionX("", eta, eta)->Clone();
        pt2_tmp[0][eta]   = (TH1F *)effdata2->ProjectionX("", eta, eta)->Clone();
        tot2_err[0][eta]  = (TH1F *)effdata2_tot->ProjectionX("", eta, eta)->Clone();
        stat2_err[0][eta] = (TH1F *)effdata2_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt2[0][eta],     tot2_err[0][eta]);
        fixHistogramError(pt2_tmp[0][eta], stat2_err[0][eta]);

        // MC
        pt2[1][eta]       = (TH1F *)effmc2->ProjectionX("", eta, eta)->Clone();
        pt2_tmp[1][eta]   = (TH1F *)effmc2->ProjectionX("", eta, eta)->Clone();
        tot2_err[1][eta]  = (TH1F *)effmc2_tot->ProjectionX("", eta, eta)->Clone();
        stat2_err[1][eta] = (TH1F *)effmc2_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt2[1][eta],     tot2_err[1][eta]);
        fixHistogramError(pt2_tmp[1][eta], stat2_err[1][eta]);

        // SF
        pt2[2][eta]       = (TH1F *)sf2->ProjectionX("", eta, eta)->Clone();
        pt2_tmp[2][eta]   = (TH1F *)sf2->ProjectionX("", eta, eta)->Clone();
        tot2_err[2][eta]  = (TH1F *)sf2_tot->ProjectionX("", eta, eta)->Clone();
        stat2_err[2][eta] = (TH1F *)sf2_stat->ProjectionX("", eta, eta)->Clone();
        fixHistogramError(pt2[2][eta],     tot2_err[2][eta]);	
        fixHistogramError(pt2_tmp[2][eta], stat2_err[2][eta]);	
    }

//--------------------

    // Big Canvas
    TCanvas* c1 = new TCanvas("Data Efficiency", folder, 600, 600);

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    pad1->SetRightMargin(0.08);
    //pad1->SetGridy(); // grid lines
    //pad1->SetLogx();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetRightMargin(0.08);
    pad2->SetGridy(); // grid lines
    //pad2->SetLogx();
    pad2->Draw();

    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here

    float high, low;
    FindOptimalRange(high, low, pt1[0][eta], pt2[0][eta]);
    pad1_Y_max = high;
    if (low < 0.)
        pad1_Y_min = 0.;
    else
        pad1_Y_min = low;

    // Set titles, maximum and minimum of axes
    pt1[0][eta]->GetXaxis()->SetTitle(pad1_X_title);
   	pt1[0][eta]->GetYaxis()->SetTitle(pad1_Y_title);
    pt1[0][eta]->SetMaximum(pad1_Y_max);
   	pt1[0][eta]->SetMinimum(pad1_Y_min);

    // file1 data efficiency
    pt1[0][eta]->SetLineColor(kBlue);
    pt1[0][eta]->SetLineWidth(1);
    pt1[0][eta]->SetMarkerColor(kBlue);
    pt1[0][eta]->SetMarkerSize(1);
    pt1[0][eta]->SetMarkerStyle(kFullCircle);
    pt1[0][eta]->GetXaxis()->SetRangeUser(7000, 150000);
   	pt1[0][eta]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.

    // file2 data efficiency
    pt2[0][eta]->SetLineColor(kRed);
    pt2[0][eta]->SetLineWidth(1);
    pt2[0][eta]->SetMarkerColor(kRed);
    pt2[0][eta]->SetMarkerSize(1);
    pt2[0][eta]->SetMarkerStyle(kOpenCircle);
    pt2[0][eta]->GetXaxis()->SetRangeUser(7000, 150000);
   	pt2[0][eta]->Draw("E0,SAME");

    TLine *line1 = new TLine(7000, 1., 150000, 1.);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(2);
    line1->SetLineWidth(1);
    line1->Draw("SAME");

    //myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");

    char name1[100];
    sprintf(&name1[0], "%.2f < #eta < %.2f",
            effdata1->GetYaxis()->GetBinLowEdge(eta),
            effdata1->GetYaxis()->GetBinUpEdge(eta));
    myText(0.2,0.70, kBlack, name1);

    // Add legend
    TLegend *leg1 = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg1->AddEntry(pt1[0][eta], "MC15bd0z0 (20160208_v8)", "lp");
    leg1->AddEntry(pt2[0][eta], "AF2d0z0 (20151218)", "lp");
    leg1->SetBorderSize(0);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.05);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->Draw();

    pad2->cd(); // pad2 becomes the current pad

    // Calculate the data efficiency ratio between two files
    TH1F *ratio2 = (TH1F *)pt1[0][eta]->Clone();
    ratio2->Divide(pt2[0][eta]);

    FindOptimalRange(high, low, ratio2);
    pad2_Y_max = high;
    if (low < 0.)
        pad2_Y_min = 0.;
    else
        pad2_Y_min = low;

    TH1F *frame2 = pad2->DrawFrame(7000, pad2_Y_min, 150000, pad2_Y_max);
    frame2->GetXaxis()->SetNdivisions(510);
    frame2->GetYaxis()->SetNdivisions(405);
    frame2->SetLineWidth(1);
    frame2->SetXTitle(pad2_X_title);
    frame2->GetXaxis()->SetTitleSize(20);
    frame2->GetXaxis()->SetTitleFont(47);
    frame2->GetXaxis()->SetTitleOffset(3.0);
    frame2->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2->GetXaxis()->SetLabelSize(16);
    frame2->SetYTitle(pad2_Y_title);
    frame2->GetYaxis()->SetTitleSize(17);
    frame2->GetYaxis()->SetTitleFont(43);
    frame2->GetYaxis()->SetTitleOffset(2.0);
    frame2->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame2->GetYaxis()->SetLabelSize(16);
    frame2->Draw();

    ratio2->SetLineColor(kBlack);
    ratio2->SetLineWidth(1);
    ratio2->SetMarkerColor(kBlack);
    ratio2->SetMarkerSize(1);
    ratio2->SetMarkerStyle(20);
    ratio2->Draw("E1,SAME");
    
    TString etaLowEdge2 = TString::Format("%.f", effdata1->GetYaxis()->GetBinLowEdge(eta)*100.);
    TString etaUpEdge2  = TString::Format("%.f", effdata1->GetYaxis()->GetBinUpEdge(eta)*100.);
    
    c1->SaveAs("plots/compare_detaEff_eta" + etaLowEdge2 + "-" + etaUpEdge2 + "_" + folder + ".pdf", "pdf");

//--------------------

    // Big Canvas
    TCanvas* c3 = new TCanvas("MC Efficiency", folder, 600, 600);

    //Upper plot will be in pad3
    TPad *pad3 = new TPad("pad3", "pad3", 0, 0.35, 1, 1.0);
    pad3->SetBottomMargin(0); // Upper and lower plot are joined
    pad3->SetRightMargin(0.08);
    //pad3->SetGridy(); // grid lines
    //pad3->SetLogx();
    pad3->Draw();
    
    // lower plot will be in pad4
    TPad *pad4 = new TPad("pad4", "pad4", 0, 0.05, 1, 0.35);
    pad4->SetTopMargin(0);
    pad4->SetBottomMargin(0.3);
    pad4->SetRightMargin(0.08);
    pad4->SetGridy(); // grid lines
    //pad4->SetLogx();
    pad4->Draw();
    
    pad3->cd(); // pad3 becomes the current pad
    //pad3->SetFrameLineWidth(2);
    
    // Draw curve here
    
    //float high, low;
    FindOptimalRange(high, low, pt1[1][eta], pt2[1][eta]);
    pad3_Y_max = high;
    if (low < 0.)
        pad3_Y_min = 0.;
    else
        pad3_Y_min = low;
    
    // Set titles, maximum and minimum of axes
    pt1[1][eta]->GetXaxis()->SetTitle(pad3_X_title);
   	pt1[1][eta]->GetYaxis()->SetTitle(pad3_Y_title);
    pt1[1][eta]->SetMaximum(pad3_Y_max);
   	pt1[1][eta]->SetMinimum(pad3_Y_min);
    
    // file1 MC efficiency
    pt1[1][eta]->SetLineColor(kBlue);
    pt1[1][eta]->SetLineWidth(1);
    pt1[1][eta]->SetMarkerColor(kBlue);
    pt1[1][eta]->SetMarkerSize(1);
    pt1[1][eta]->SetMarkerStyle(kFullCircle);
    pt1[1][eta]->GetXaxis()->SetRangeUser(7000, 150000);
   	pt1[1][eta]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.
    
    // file2 MC efficiency
    pt2[1][eta]->SetLineColor(kRed);
    pt2[1][eta]->SetLineWidth(1);
    pt2[1][eta]->SetMarkerColor(kRed);
    pt2[1][eta]->SetMarkerSize(1);
    pt2[1][eta]->SetMarkerStyle(kOpenCircle);
    pt2[1][eta]->GetXaxis()->SetRangeUser(7000, 150000);
   	pt2[1][eta]->Draw("E0,SAME");
    
    TLine *line3 = new TLine(7000, 1., 150000, 1.);
    line3->SetLineColor(kBlack);
    line3->SetLineStyle(2);
    line3->SetLineWidth(1);
    line3->Draw("SAME");
    
    //myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    
    char name3[100];
    sprintf(&name3[0], "%.2f < #eta < %.2f",
            effdata1->GetYaxis()->GetBinLowEdge(eta),
            effdata1->GetYaxis()->GetBinUpEdge(eta));
    myText(0.2,0.70, kBlack, name3);
    
    // Add legend
    TLegend *leg3 = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg3->AddEntry(pt1[1][eta], "MC15bd0z0 (20160208_v8)", "lp");
    leg3->AddEntry(pt2[1][eta], "AF2d0z0 (20151218)", "lp");
    leg3->SetBorderSize(0);
    leg3->SetTextFont(42);
    leg3->SetTextSize(0.05);
    leg3->SetFillColor(0);
    leg3->SetFillStyle(0);
    leg3->Draw();
    
    pad4->cd(); // pad4 becomes the current pad
    
    // Calculate the data efficiency ratio between two files
    TH1F *ratio4 = (TH1F *)pt1[1][eta]->Clone();
    ratio4->Divide(pt2[1][eta]);
    
    FindOptimalRange(high, low, ratio4);
    pad4_Y_max = high;
    if (low < 0.)
        pad4_Y_min = 0.;
    else
        pad4_Y_min = low;
    
    TH1F *frame4 = pad4->DrawFrame(7000, pad4_Y_min, 150000, pad4_Y_max);
    frame4->GetXaxis()->SetNdivisions(510);
    frame4->GetYaxis()->SetNdivisions(405);
    frame4->SetLineWidth(1);
    frame4->SetXTitle(pad2_X_title);
    frame4->GetXaxis()->SetTitleSize(20);
    frame4->GetXaxis()->SetTitleFont(47);
    frame4->GetXaxis()->SetTitleOffset(3.0);
    frame4->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame4->GetXaxis()->SetLabelSize(16);
    frame4->SetYTitle(pad2_Y_title);
    frame4->GetYaxis()->SetTitleSize(17);
    frame4->GetYaxis()->SetTitleFont(43);
    frame4->GetYaxis()->SetTitleOffset(2.0);
    frame4->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame4->GetYaxis()->SetLabelSize(16);
    frame4->Draw();
    
    ratio4->SetLineColor(kBlack);
    ratio4->SetLineWidth(1);
    ratio4->SetMarkerColor(kBlack);
    ratio4->SetMarkerSize(1);
    ratio4->SetMarkerStyle(20);
    ratio4->Draw("E1,SAME");
    
    TString etaLowEdge4 = TString::Format("%.f", effdata1->GetYaxis()->GetBinLowEdge(eta)*100.);
    TString etaUpEdge4  = TString::Format("%.f", effdata1->GetYaxis()->GetBinUpEdge(eta)*100.);
    
    c3->SaveAs("plots/compare_MCEff_eta" + etaLowEdge4 + "-" + etaUpEdge4 + "_" + folder + ".pdf", "pdf");

//--------------------

    // Big Canvas
    TCanvas* c5 = new TCanvas("Scale Factors", folder, 600, 600);
    
    //Upper plot will be in pad5
    TPad *pad5 = new TPad("pad5", "pad5", 0, 0.35, 1, 1.0);
    pad5->SetBottomMargin(0); // Upper and lower plot are joined
    pad5->SetRightMargin(0.08);
    //pad5->SetGridy(); // grid lines
    //pad5->SetLogx();
    pad5->Draw();
    
    // lower plot will be in pad6
    TPad *pad6 = new TPad("pad6", "pad6", 0, 0.05, 1, 0.35);
    pad6->SetTopMargin(0);
    pad6->SetBottomMargin(0.3);
    pad6->SetRightMargin(0.08);
    pad6->SetGridy(); // grid lines
    //pad6->SetLogx();
    pad6->Draw();
    
    pad5->cd(); // pad5 becomes the current pad
    //pad6->SetFrameLineWidth(2);
    
    // Draw curve here
    
    //float high, low;
    FindOptimalRange(high, low, pt1[2][eta], pt2[2][eta]);
    pad5_Y_max = high;
    if (low < 0.)
        pad5_Y_min = 0.;
    else
        pad5_Y_min = low;
    
    // Set titles, maximum and minimum of axes
    pt1[2][eta]->GetXaxis()->SetTitle(pad5_X_title);
   	pt1[2][eta]->GetYaxis()->SetTitle(pad5_Y_title);
    pt1[2][eta]->SetMaximum(pad5_Y_max);
   	pt1[2][eta]->SetMinimum(pad5_Y_min);
    
    // file1 SF
    pt1[2][eta]->SetLineColor(kBlue);
    pt1[2][eta]->SetLineWidth(1);
    pt1[2][eta]->SetMarkerColor(kBlue);
    pt1[2][eta]->SetMarkerSize(1);
    pt1[2][eta]->SetMarkerStyle(kFullCircle);
    pt1[2][eta]->GetXaxis()->SetRangeUser(7000, 150000);
   	pt1[2][eta]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.
    
    // file2 SF
    pt2[2][eta]->SetLineColor(kRed);
    pt2[2][eta]->SetLineWidth(1);
    pt2[2][eta]->SetMarkerColor(kRed);
    pt2[2][eta]->SetMarkerSize(1);
    pt2[2][eta]->SetMarkerStyle(kOpenCircle);
    pt2[2][eta]->GetXaxis()->SetRangeUser(7000, 150000);
   	pt2[2][eta]->Draw("E0,SAME");
    
    TLine *line5 = new TLine(7000, 1., 150000, 1.);
    line5->SetLineColor(kBlack);
    line5->SetLineStyle(2);
    line5->SetLineWidth(1);
    line5->Draw("SAME");
    
    //myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    
    char name5[100];
    sprintf(&name5[0], "%.2f < #eta < %.2f",
            effdata1->GetYaxis()->GetBinLowEdge(eta),
            effdata1->GetYaxis()->GetBinUpEdge(eta));
    myText(0.2,0.70, kBlack, name5);
    
    // Add legend
    TLegend *leg5 = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg5->AddEntry(pt1[1][eta], "MC15bd0z0 (20160208_v8)", "lp");
    leg5->AddEntry(pt2[1][eta], "AF2d0z0 (20151218)", "lp");
    leg5->SetBorderSize(0);
    leg5->SetTextFont(42);
    leg5->SetTextSize(0.05);
    leg5->SetFillColor(0);
    leg5->SetFillStyle(0);
    leg5->Draw();
    
    pad6->cd(); // pad4 becomes the current pad
    
    // Calculate the data efficiency ratio between two files
    TH1F *ratio6 = (TH1F *)pt1[2][eta]->Clone();
    ratio6->Divide(pt2[2][eta]);
    
    FindOptimalRange(high, low, ratio4);
    pad6_Y_max = high;
    if (low < 0.)
        pad6_Y_min = 0.;
    else
        pad6_Y_min = low;
    
    TH1F *frame6 = pad6->DrawFrame(7000, pad6_Y_min, 150000, pad6_Y_max);
    frame6->GetXaxis()->SetNdivisions(510);
    frame6->GetYaxis()->SetNdivisions(405);
    frame6->SetLineWidth(1);
    frame6->SetXTitle(pad2_X_title);
    frame6->GetXaxis()->SetTitleSize(20);
    frame6->GetXaxis()->SetTitleFont(47);
    frame6->GetXaxis()->SetTitleOffset(3.0);
    frame6->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame6->GetXaxis()->SetLabelSize(16);
    frame6->SetYTitle(pad2_Y_title);
    frame6->GetYaxis()->SetTitleSize(17);
    frame6->GetYaxis()->SetTitleFont(43);
    frame6->GetYaxis()->SetTitleOffset(2.0);
    frame6->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame6->GetYaxis()->SetLabelSize(16);
    frame6->Draw();
    
    ratio6->SetLineColor(kBlack);
    ratio6->SetLineWidth(1);
    ratio6->SetMarkerColor(kBlack);
    ratio6->SetMarkerSize(1);
    ratio6->SetMarkerStyle(20);
    ratio6->Draw("E1,SAME");
    
    TString etaLowEdge6 = TString::Format("%.f", effdata1->GetYaxis()->GetBinLowEdge(eta)*100.);
    TString etaUpEdge6  = TString::Format("%.f", effdata1->GetYaxis()->GetBinUpEdge(eta)*100.);
    
    c5->SaveAs("plots/compare_SF_eta" + etaLowEdge6 + "-" + etaUpEdge6 + "_" + folder + ".pdf", "pdf");
}
