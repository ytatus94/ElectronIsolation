// This script is used to compare data efficiency, MC efficiency, and scale factors between two files.
// The selected pT bin will be projected on the eta axis.
// Three ratio plots will be generated: data efficiency ratio plot, MC efficiency ratio plot, scale factors ratio plot.
//
//
//int pt = 2; // pT = 7-10 GeV
//int pt = 3; // pT = 10-15 GeV
//int pt = 4; // pT = 15-20 GeV
//int pt = 8; // pT = 35-40 GeV
//int pt = 13; // pT = 80-150 GeV
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"
#include "FindOptimalRange.C"

void myCompTwoFilesEffAndSFEta(TString menu = "TightLLH",
                               TString iso  = "isolTight",
                               int pt = 2)
{
    // Data
    // Set titles and axes scales for top pad (pad1)
    TString pad1_X_title = "#eta";
    TString pad1_Y_title = "Data Efficiency";
    double pad1_Y_max = 1.10;
    double pad1_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad2)
    TString pad2_X_title = "#eta";
    TString pad2_Y_title = "file1/file2";
    double pad2_Y_max = 1.05;
    double pad2_Y_min = 0.95;

    // MC
    // Set titles and axes scales for top pad (pad3)
    TString pad3_X_title = "#eta";
    TString pad3_Y_title = "MC Efficiency";
    double pad3_Y_max = 1.10;
    double pad3_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad4)
    TString pad4_X_title = "#eta";
    TString pad4_Y_title = "file1/file2";
    double pad4_Y_max = 1.05;
    double pad4_Y_min = 0.95;

    // SF
    // Set titles and axes scales for top pad (pad5)
    TString pad5_X_title = "#eta";
    TString pad5_Y_title = "Scale Factor";
    double pad5_Y_max = 1.10;
    double pad5_Y_min = 0.91;

    // Set titles and axes scales for bottom pad (pad6)
    TString pad6_X_title = "#eta";
    TString pad6_Y_title = "file1/file2";
    double pad6_Y_max = 1.05;
    double pad6_Y_min = 0.95;

    SetAtlasStyle();

    TString folder;
    if (iso != "")
		folder = menu + "_" + iso;
    else
		folder = menu;

	TString fileName1 = "ScaleFactors.root";

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

    TH1F* eta1[3][30]; // keeps total uncertainties
    TH1F* eta1_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot1_err[3][30];
    TH1F* sys1_err[3][30];
    TH1F* stat1_err[3][30];

    // Fill the uncertainties to the histograms
    for (int pt = 0; pt < effdata1->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
		// Data
		eta1[0][pt]      = (TH1F *)effdata1->ProjectionY("", pt, pt)->Clone();
		eta1_tmp[0][pt]  = (TH1F *)effdata1->ProjectionY("", pt, pt)->Clone();
		tot1_err[0][pt]  = (TH1F *)effdata1_tot->ProjectionY("", pt, pt)->Clone();
		stat1_err[0][pt] = (TH1F *)effdata1_stat->ProjectionY("", pt, pt)->Clone();
		fixHistogramError(eta1[0][pt],     tot1_err[0][pt]);	
		fixHistogramError(eta1_tmp[0][pt], stat1_err[0][pt]);	

	   	// MC
	   	eta1[1][pt]      = (TH1F *)effmc1->ProjectionY("", pt, pt)->Clone();
	   	eta1_tmp[1][pt]  = (TH1F *)effmc1->ProjectionY("", pt, pt)->Clone();
	   	tot1_err[1][pt]  = (TH1F *)effmc1_tot->ProjectionY("", pt, pt)->Clone();
	   	stat1_err[1][pt] = (TH1F *)effmc1_stat->ProjectionY("", pt, pt)->Clone();
	   	fixHistogramError(eta1[1][pt],     tot1_err[1][pt]);
	   	fixHistogramError(eta1_tmp[1][pt], stat1_err[1][pt]);

        // SF
        eta1[2][pt]      = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
        eta1_tmp[2][pt]  = (TH1F *)sf1->ProjectionY("", pt, pt)->Clone();
        tot1_err[2][pt]  = (TH1F *)sf1_tot->ProjectionY("", pt, pt)->Clone();
        stat1_err[2][pt] = (TH1F *)sf1_stat->ProjectionY("", pt, pt)->Clone();
        fixHistogramError(eta1[2][pt],     tot1_err[2][pt]);
        fixHistogramError(eta1_tmp[2][pt], stat1_err[2][pt]);
	}

//--------------------

	TString fileName2 = "MC15bd0z0_ScaleFactors.root";

	TH2F *effdata2      = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffData_CentralValue");
	TH2F *effdata2_tot  = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffData_TotalError");
	TH2F *effdata2_stat = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffData_StatError");

	TH2F *effmc2      = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffMC_CentralValue");
	TH2F *effmc2_tot  = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffMC_TotalError");
	TH2F *effmc2_stat = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "EffMC_StatError");

    TH2F *sf2      = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "SF_CentralValue");
    TH2F *sf2_tot  = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "SF_TotalError");
    TH2F *sf2_stat = get13TeV2DHistogram(fileName2, menu + "_d0z0_v8", iso, "SF_StatError");

    TH1F* eta2[3][30]; // keeps total uncertainties
    TH1F* eta2_tmp[3][30]; // keeps statistical uncertainties
    TH1F* tot2_err[3][30];
    TH1F* sys2_err[3][30];
    TH1F* stat2_err[3][30];

    for (int pt = 0; pt < effdata2->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		if (pt < 2) continue; // The plots are empty when pt=1
		// Data
		eta2[0][pt]      = (TH1F *)effdata2->ProjectionY("", pt, pt)->Clone();
		eta2_tmp[0][pt]  = (TH1F *)effdata2->ProjectionY("", pt, pt)->Clone();
		tot2_err[0][pt]  = (TH1F *)effdata2_tot->ProjectionY("", pt, pt)->Clone();
		stat2_err[0][pt] = (TH1F *)effdata2_stat->ProjectionY("", pt, pt)->Clone();
		fixHistogramError(eta2[0][pt],     tot2_err[0][pt]);	
		fixHistogramError(eta2_tmp[0][pt], stat2_err[0][pt]);	

	   	// MC
	   	eta2[1][pt]      = (TH1F *)effmc2->ProjectionY("", pt, pt)->Clone();
	   	eta2_tmp[1][pt]  = (TH1F *)effmc2->ProjectionY("", pt, pt)->Clone();
	   	tot2_err[1][pt]  = (TH1F *)effmc2_tot->ProjectionY("", pt, pt)->Clone();
	   	stat2_err[1][pt] = (TH1F *)effmc2_stat->ProjectionY("", pt, pt)->Clone();
	   	fixHistogramError(eta2[1][pt],     tot2_err[1][pt]);
	   	fixHistogramError(eta2_tmp[1][pt], stat2_err[1][pt]);

        // SF
        eta2[2][pt]      = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
        eta2_tmp[2][pt]  = (TH1F *)sf2->ProjectionY("", pt, pt)->Clone();
        tot2_err[2][pt]  = (TH1F *)sf2_tot->ProjectionY("", pt, pt)->Clone();
        stat2_err[2][pt] = (TH1F *)sf2_stat->ProjectionY("", pt, pt)->Clone();
        fixHistogramError(eta2[2][pt],     tot2_err[2][pt]);
        fixHistogramError(eta2_tmp[2][pt], stat2_err[2][pt]);
	}

//--------------------

    // Big Canvas
    TCanvas* c1 = new TCanvas("Data Efficiency", folder, 600, 600);

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    //pad1->SetGridy(); // grid lines
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetGridy(); // grid lines
    pad2->Draw();

    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here

    float high, low;
    FindOptimalRange(high, low, eta1[0][pt], eta2[0][pt]);
    pad1_Y_max = high;
    if (low < 0.)
        pad1_Y_min = 0.;
    else
        pad1_Y_min = low;
    
    // Set titles, maximum and minimum of axes
    eta1[0][pt]->GetXaxis()->SetTitle(pad1_X_title);
   	eta1[0][pt]->GetYaxis()->SetTitle(pad1_Y_title);
    eta1[0][pt]->SetMaximum(pad1_Y_max);
   	eta1[0][pt]->SetMinimum(pad1_Y_min);
    
    // file1 data efficiency
    eta1[0][pt]->SetLineColor(kBlue);
    eta1[0][pt]->SetLineWidth(1);
    eta1[0][pt]->SetMarkerColor(kBlue);
    eta1[0][pt]->SetMarkerSize(1);
    eta1[0][pt]->SetMarkerStyle(kFullCircle);
   	eta1[0][pt]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.
    
    // file2 data efficiency
   	eta2[0][pt]->SetLineColor(kRed);
   	eta2[0][pt]->SetLineWidth(2);
   	eta2[0][pt]->SetMarkerColor(kRed);
   	eta2[0][pt]->SetMarkerSize(1);
   	eta2[0][pt]->SetMarkerStyle(kOpenCircle);
   	eta2[0][pt]->Draw("E0,SAME");
   	
    TLine *line1 = new TLine(eta1[0][pt]->GetXaxis()->GetXmin(), 1.,
                             eta1[0][pt]->GetXaxis()->GetXmax(), 1.);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(2);
    line1->SetLineWidth(1);
    line1->Draw("SAME");
    
    //myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    
    char name1[100];
    sprintf(&name1[0], "%d GeV < E_{T} < %d GeV",
            static_cast<int>(effdata1->GetXaxis()->GetBinLowEdge(pt) / 1000.),
            static_cast<int>(effdata1->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
    myText(0.2,0.70, kBlack, name1);
    
    // Add legend
    TLegend *leg1 = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg1->AddEntry(eta1[0][pt], "file1", "lp");
    leg1->AddEntry(eta2[0][pt], "file2", "lp");
    leg1->SetBorderSize(0);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.05);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->Draw();
    
    pad2->cd(); // pad2 becomes the current pad

    // Calculate the data efficiency ratio between two files
    TH1F *ratio2 = (TH1F *)eta1[0][pt]->Clone();
    ratio2->Divide(eta2[0][pt]);

    FindOptimalRange(high, low, ratio2);
    pad2_Y_max = high;
    if (low < 0.)
        pad2_Y_min = 0.;
    else
        pad2_Y_min = low;

    TH1F *frame2;
    frame2 = pad2->DrawFrame(eta1[0][pt]->GetXaxis()->GetXmin(), pad2_Y_min,
                             eta1[0][pt]->GetXaxis()->GetXmax(), pad2_Y_max);
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
    ratio2->Draw("E1,same");

    TString ptLowEdge2 = TString::Format("%.f", effdata1->GetXaxis()->GetBinLowEdge(pt) / 1000.);
    TString ptUpEdge2  = TString::Format("%.f", effdata1->GetXaxis()->GetBinUpEdge(pt) / 1000.);
    
    c1->SaveAs("plots/compare_dataEff_pT" + ptLowEdge2 + "-" + ptUpEdge2 + "GeV_" + folder + ".pdf", "pdf");

//--------------------

    // Big Canvas
    TCanvas* c3 = new TCanvas("MC efficiency", folder, 600, 600);
    
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
    
    //float high, low;
    FindOptimalRange(high, low, eta1[1][pt], eta2[1][pt]);
    pad3_Y_max = high;
    if (low < 0.)
        pad3_Y_min = 0.;
    else
        pad3_Y_min = low;
    
    // Set titles, maximum and minimum of axes
    eta1[1][pt]->GetXaxis()->SetTitle(pad3_X_title);
   	eta1[1][pt]->GetYaxis()->SetTitle(pad3_Y_title);
    eta1[1][pt]->SetMaximum(pad3_Y_max);
   	eta1[1][pt]->SetMinimum(pad3_Y_min);
    
    // file1 MC efficiency
    eta1[1][pt]->SetLineColor(kBlue);
    eta1[1][pt]->SetLineWidth(1);
    eta1[1][pt]->SetMarkerColor(kBlue);
    eta1[1][pt]->SetMarkerSize(1);
    eta1[1][pt]->SetMarkerStyle(kFullCircle);
   	eta1[1][pt]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.
    
    // file2 MC efficiency
   	eta2[1][pt]->SetLineColor(kRed);
   	eta2[1][pt]->SetLineWidth(2);
   	eta2[1][pt]->SetMarkerColor(kRed);
   	eta2[1][pt]->SetMarkerSize(1);
   	eta2[1][pt]->SetMarkerStyle(kOpenCircle);
   	eta2[1][pt]->Draw("E0,SAME");
   	
    TLine *line3 = new TLine(eta1[1][pt]->GetXaxis()->GetXmin(), 1.,
                             eta1[1][pt]->GetXaxis()->GetXmax(), 1.);
    line3->SetLineColor(kBlack);
    line3->SetLineStyle(2);
    line3->SetLineWidth(1);
    line3->Draw("SAME");
    
    //myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    
    char name3[100];
    sprintf(&name3[0], "%d GeV < E_{T} < %d GeV",
            static_cast<int>(effmc1->GetXaxis()->GetBinLowEdge(pt) / 1000.),
            static_cast<int>(effmc1->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
    myText(0.2,0.70, kBlack, name3);
    
    // Add legend
    TLegend *leg3 = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg3->AddEntry(eta1[0][pt], "file1", "lp");
    leg3->AddEntry(eta2[0][pt], "file2", "lp");
    leg3->SetBorderSize(0);
    leg3->SetTextFont(42);
    leg3->SetTextSize(0.05);
    leg3->SetFillColor(0);
    leg3->SetFillStyle(0);
    leg3->Draw();
    
    pad4->cd(); // pad4 becomes the current pad
    
    // Calculate the MC efficiency ratio between two files
    TH1F *ratio4 = (TH1F *)eta1[1][pt]->Clone();
    ratio4->Divide(eta2[1][pt]);
    
    FindOptimalRange(high, low, ratio4);
    pad4_Y_max = high;
    if (low < 0.)
        pad4_Y_min = 0.;
    else
        pad4_Y_min = low;
    
    TH1F *frame4;
    frame4 = pad4->DrawFrame(eta1[1][pt]->GetXaxis()->GetXmin(), pad2_Y_min,
                             eta1[1][pt]->GetXaxis()->GetXmax(), pad2_Y_max);
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
    ratio4->Draw("E1,same");
    
    TString ptLowEdge4 = TString::Format("%.f", effdata1->GetXaxis()->GetBinLowEdge(pt) / 1000.);
    TString ptUpEdge4  = TString::Format("%.f", effdata1->GetXaxis()->GetBinUpEdge(pt) / 1000.);
    
    c3->SaveAs("plots/compare_MCEff_pT" + ptLowEdge4 + "-" + ptUpEdge4 + "GeV_" + folder + ".pdf", "pdf");

//--------------------

    // Big Canvas
    TCanvas* c5 = new TCanvas("Scale Factors", folder, 600, 600);
    
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
    
    //float high, low;
    FindOptimalRange(high, low, eta1[2][pt], eta2[2][pt]);
    pad5_Y_max = high;
    if (low < 0.)
        pad5_Y_min = 0.;
    else
        pad5_Y_min = low;

    // Set titles, maximum and minimum of axes
    eta1[2][pt]->GetXaxis()->SetTitle(pad5_X_title);
   	eta1[2][pt]->GetYaxis()->SetTitle(pad5_Y_title);
    eta1[2][pt]->SetMaximum(pad5_Y_max);
   	eta1[2][pt]->SetMinimum(pad5_Y_min);

    // file1 SF
    eta1[2][pt]->SetLineColor(kBlue);
    eta1[2][pt]->SetLineWidth(1);
    eta1[2][pt]->SetMarkerColor(kBlue);
    eta1[2][pt]->SetMarkerSize(1);
    eta1[2][pt]->SetMarkerStyle(kFullCircle);
   	eta1[2][pt]->Draw("E0"); // E0: Draw error bars. Markers are drawn for bins with 0 contents.

    // file2 SF
   	eta2[2][pt]->SetLineColor(kRed);
   	eta2[2][pt]->SetLineWidth(2);
   	eta2[2][pt]->SetMarkerColor(kRed);
   	eta2[2][pt]->SetMarkerSize(1);
   	eta2[2][pt]->SetMarkerStyle(kOpenCircle);
   	eta2[2][pt]->Draw("E0,SAME");

    TLine *line5 = new TLine(eta1[2][pt]->GetXaxis()->GetXmin(), 1.,
                             eta1[2][pt]->GetXaxis()->GetXmax(), 1.);
    line5->SetLineColor(kBlack);
    line5->SetLineStyle(2);
    line5->SetLineWidth(1);
    line5->Draw("SAME");

    //myText(0.2,0.85,  kBlack, const_cast<char *>(folder.Data()));
    ATLASLabel(0.2, 0.85,"Internal");
    myText(0.2, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    
    char name5[100];
    sprintf(&name5[0], "%d GeV < E_{T} < %d GeV",
            static_cast<int>(sf1->GetXaxis()->GetBinLowEdge(pt) / 1000.),
            static_cast<int>(sf1->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
    myText(0.2,0.70, kBlack, name5);

    // Add legend
    TLegend *leg5 = new TLegend(0.6, 0.68, 0.9, 0.81);
    leg5->AddEntry(eta1[2][pt], "file1", "lp");
    leg5->AddEntry(eta2[2][pt], "file2", "lp");
    leg5->SetBorderSize(0);
    leg5->SetTextFont(42);
    leg5->SetTextSize(0.05);
    leg5->SetFillColor(0);
    leg5->SetFillStyle(0);
    leg5->Draw();

    pad6->cd(); // pad6 becomes the current pad
    
    // Calculate the ratio between with and without d0sig+z0 cuts
    TH1F *ratio6 = (TH1F *)eta1[2][pt]->Clone();
    ratio6->Divide(eta2[2][pt]);

    FindOptimalRange(high, low, ratio6);
    pad6_Y_max = high;
    if (low < 0.)
        pad6_Y_min = 0.;
    else
        pad6_Y_min = low;

    TH1F *frame6;
    frame6 = pad6->DrawFrame(eta1[2][pt]->GetXaxis()->GetXmin(), pad6_Y_min,
                             eta1[2][pt]->GetXaxis()->GetXmax(), pad6_Y_max);
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
    ratio6->Draw("E1,same");

    TString ptLowEdge6 = TString::Format("%.f", sf1->GetXaxis()->GetBinLowEdge(pt) / 1000.);
    TString ptUpEdge6  = TString::Format("%.f", sf1->GetXaxis()->GetBinUpEdge(pt) / 1000.);
    
    c5->SaveAs("plots/compare_SF_pT" + ptLowEdge6 + "-" + ptUpEdge6 + "GeV_" + folder + ".pdf", "pdf");
}
