#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
using namespace std;

void ptvarcone20(TString path, TString menu = "TightLLH")
{
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc = TFile::Open(path + "merged-hist-mc.root");

    // Get ptvarcone20 histograms
    TH1F *hdata = (TH1F *)fdata->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20");
    TH1F *hmc = (TH1F *)fmc->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    c1->SetLogy();
    hdata->SetTitle(menu);
    hdata->SetXTitle("p_{T}^{varcone20} [GeV]");
    double xmin = hdata->GetXaxis()->GetXmin();
    double xmax = hdata->GetXaxis()->GetXmax();
    hdata->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
    hdata->SetLineColor(kBlack);
    hdata->SetMarkerColor(kBlack);
    hdata->SetMarkerStyle(kFullCircle);
    hdata->SetStats(kFALSE);
    hdata->Draw("E1");
    xmin = hmc->GetXaxis()->GetXmin();
    xmax = hmc->GetXaxis()->GetXmax();
    hmc->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
    hmc->Scale(hdata->Integral() / hmc->Integral());
    hmc->SetLineColor(kRed);
    hmc->SetMarkerColor(kRed);
    hmc->SetMarkerStyle(kFullCircle);
    hmc->Draw("E1,same");

    TLegend *leg = new TLegend(0.6, 0.65, 0.9, 0.8);
    leg->AddEntry(hdata, "Data 25.469 fb^{-1}", "lp");
    leg->AddEntry(hmc, "MC", "lp");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    c1->SaveAs("ptvarcone20_" + menu + ".pdf", "pdf");
}

void ptvarcone20_over_pt(TString path, TString menu = "TightLLH")
{
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc = TFile::Open(path + "merged-hist-mc.root");

    // Get ptvarcone20/pt histograms
    TH1F *hdata = (TH1F *)fdata->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");
    TH1F *hmc = (TH1F *)fmc->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    c1->SetLogy();
    hdata->SetTitle(menu);
    hdata->SetXTitle("p_{T}^{varcone20}/p_{T}");
    hdata->SetLineColor(kBlue);
    hdata->SetLineWidth(2);
    hdata->SetStats(kFALSE);
    hdata->Draw("hist");
    hmc->Scale(hdata->Integral() / hmc->Integral());
    hmc->SetLineColor(kRed);
    hmc->SetLineWidth(2);
    hmc->Draw("hist,same");

    TLegend *leg = new TLegend(0.6, 0.65, 0.9, 0.8);
    leg->AddEntry(hdata, "Data 25.469 fb^{-1}");
    leg->AddEntry(hmc, "MC");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    c1->SaveAs("ptvarcone20_over_pt_" + menu + ".pdf", "pdf");
}

void ptvarcone20_over_pt_ratio_plot(TString path, TString menu = "TightLLH")
{
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc = TFile::Open(path + "merged-hist-mc.root");

    // Get ptvarcone20/pt histograms
    TH1F *hdata = (TH1F *)fdata->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");
    TH1F *hmc = (TH1F *)fmc->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");

    // Big Canvas
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    //pad1->SetGridy(); // grid lines
    pad1->SetLogy();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetGridy(); // grid lines
    pad2->Draw();

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here
    hdata->SetTitle(menu);
    hdata->SetXTitle("p_{T}^{varcone20}/p_{T}");
    hdata->GetXaxis()->SetRangeUser(0., 1.5);
    hdata->SetMinimum(1.1);
    hdata->SetLineColor(kBlue);
    hdata->SetLineWidth(2);
    hdata->SetStats(kFALSE);
    hdata->Draw("hist");
    hmc->Scale(hdata->Integral() / hmc->Integral());
    hmc->SetLineColor(kRed);
    hmc->SetLineWidth(2);
    hmc->Draw("hist,same");

    TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.8);
    leg->AddEntry(hdata, "Data 25.469 fb^{-1}");
    leg->AddEntry(hmc, "MC");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    TH1F *frame = pad2->DrawFrame(0., 0.5, 1.5, 3.9);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle("p_{T}^{varcone20}/p_{T}");
    frame->GetXaxis()->SetTitleSize(20);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(3.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(16);
    frame->SetYTitle("Data / MC");
    frame->GetYaxis()->SetTitleSize(17);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(2.0);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(16);
    frame->Draw();

    TH1F *ratio = (TH1F *)hdata->Clone();
    ratio->Divide(hmc);

    ratio->SetLineColor(kBlack);
    ratio->SetLineWidth(2);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerSize(1);
    ratio->SetMarkerStyle(20);
    ratio->Draw("E1,same");

    c1->SaveAs("ptvarcone_over_pt_ratio_plot_" + menu + ".pdf", "pdf");
}

void Compare_ptvarcone20_over_pt_ratio_plot(TString path, TString menu = "TightLLH")
{
    TFile *fdata1 = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc1 = TFile::Open(path + "merged-hist-mc.root");

    TFile *fdata2 = TFile::Open(path + "../testGrid_newT/merged-hist-data.root");
    TFile *fmc2 = TFile::Open(path + "../testGrid_newT/merged-hist-mc.root");

    // Get ptvarcone20/pt histograms
    TH1F *hdata1 = (TH1F *)fdata1->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");
    TH1F *hmc1 = (TH1F *)fmc1->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");

    TH1F *hdata2 = (TH1F *)fdata2->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");
    TH1F *hmc2 = (TH1F *)fmc2->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_ptvarcone20_over_pt");

    // Big Canvas
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    //pad1->SetGridy(); // grid lines
    pad1->SetLogy();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetGridy(); // grid lines
    pad2->Draw();

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here
    hdata1->SetTitle(menu);
    hdata1->SetXTitle("p_{T}^{varcone20}/p_{T}");
    hdata1->GetXaxis()->SetRangeUser(0., 0.5);
    hdata1->SetMinimum(1.1);
    hdata1->SetLineColor(kBlue);
    hdata1->SetLineWidth(2);
    hdata1->SetStats(kFALSE);
    hdata1->Draw("hist");
    hmc1->Scale(hdata1->Integral() / hmc1->Integral());
    hmc1->SetLineColor(kRed);
    hmc1->SetLineWidth(2);
    hmc1->Draw("hist,same");

    hdata2->SetLineColor(kOrange);
    hdata2->SetLineWidth(2);
    hdata2->SetStats(kFALSE);
    hdata2->Draw("hist,same");
    hmc2->Scale(hdata2->Integral() / hmc2->Integral());
    hmc2->SetLineColor(kMagenta);
    hmc2->SetLineWidth(2);
    hmc2->Draw("hist,same");

    TLegend *leg = new TLegend(0.5, 0.5, 0.9, 0.8);
    leg->AddEntry(hdata1, "Data 25.469 fb^{-1} (modified p_{T}^{varcone20})");
    leg->AddEntry(hmc1, "MC (modified p_{T}^{varcone20})");
    leg->AddEntry(hdata2, "Data 25.469 fb^{-1}");
    leg->AddEntry(hmc2, "MC");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    TH1F *frame = pad2->DrawFrame(0., 0.5, 0.5, 1.9);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle("p_{T}^{varcone20}/p_{T}");
    frame->GetXaxis()->SetTitleSize(20);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(3.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(16);
    frame->SetYTitle("Data / MC");
    frame->GetYaxis()->SetTitleSize(17);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(2.0);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(16);
    frame->Draw();

    TH1F *ratio1 = (TH1F *)hdata1->Clone();
    ratio1->Divide(hmc1);

    ratio1->SetLineColor(kBlack);
    ratio1->SetLineWidth(2);
    ratio1->SetMarkerColor(kBlack);
    ratio1->SetMarkerSize(1);
    ratio1->SetMarkerStyle(20);
    ratio1->Draw("E1,same");

    TH1F *ratio2 = (TH1F *)hdata2->Clone();
    ratio2->Divide(hmc2);

    ratio2->SetLineColor(kGreen);
    ratio2->SetLineWidth(2);
    ratio2->SetMarkerColor(kGreen);
    ratio2->SetMarkerSize(1);
    ratio2->SetMarkerStyle(20);
    ratio2->Draw("E1,same");

    c1->SaveAs("compare_ptvarcone_over_pt_ratio_plot_" + menu + ".pdf", "pdf");
}


//
// calo isolation variable
//
void topoetcone20(TString path, TString menu = "TightLLH")
{
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc = TFile::Open(path + "merged-hist-mc.root");

    // Get topoetcone20/pt histograms
    TH1F *hdata = (TH1F *)fdata->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20");
    TH1F *hmc = (TH1F *)fmc->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20");

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    c1->SetLogy();
    hdata->SetTitle(menu);
    hdata->SetXTitle("E_{T}^{topocone20} [GeV]");
    double xmin = hdata->GetXaxis()->GetXmin();
    double xmax = hdata->GetXaxis()->GetXmax();
    hdata->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
    hdata->SetLineColor(kBlue);
    hdata->SetLineWidth(2);
    hdata->SetStats(kFALSE);
    hdata->Draw("hist");
    xmin = hmc->GetXaxis()->GetXmin();
    xmax = hmc->GetXaxis()->GetXmax();
    hmc->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
    hmc->Scale(hdata->Integral() / hmc->Integral());
    hmc->SetLineColor(kRed);
    hmc->SetLineWidth(2);
    hmc->Draw("hist,same");

    TLegend *leg = new TLegend(0.6, 0.65, 0.9, 0.8);
    leg->AddEntry(hdata, "Data 25.469 fb^{-1}");
    leg->AddEntry(hmc, "MC");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    c1->SaveAs("topoetcone20_" + menu + ".pdf", "pdf");
}

void topoetcone20_over_pt(TString path, TString menu = "TightLLH")
{
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc = TFile::Open(path + "merged-hist-mc.root");

    // Get topoetcone20/pt histograms
    TH1F *hdata = (TH1F *)fdata->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20_over_pt");
    TH1F *hmc = (TH1F *)fmc->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20_over_pt");
    cout << hdata << endl;
    cout << hmc << endl;

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    c1->SetLogy();
    hdata->SetTitle(menu);
    hdata->SetXTitle("E_{T}^{topocone20}/p_{T}");
    hdata->SetLineColor(kBlue);
    hdata->SetLineWidth(2);
    hdata->SetStats(kFALSE);
    hdata->Draw("hist");
    hmc->Scale(hdata->Integral() / hmc->Integral());
    hmc->SetLineColor(kRed);
    hmc->SetLineWidth(2);
    hmc->Draw("hist,same");

    TLegend *leg = new TLegend(0.6, 0.65, 0.9, 0.8);
    leg->AddEntry(hdata, "Data 25.469 fb^{-1}");
    leg->AddEntry(hmc, "MC");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    c1->SaveAs("topoetcone20_over_pt_" + menu + ".pdf", "pdf");
}

void topoetcone20_over_pt_ratio_plot(TString path, TString menu = "TightLLH")
{
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc = TFile::Open(path + "merged-hist-mc.root");

    // Get ptvarcone20/pt histograms
    TH1F *hdata = (TH1F *)fdata->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20_over_pt");
    TH1F *hmc = (TH1F *)fmc->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20_over_pt");

    // Big Canvas
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    //pad1->SetGridy(); // grid lines
    pad1->SetLogy();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetGridy(); // grid lines
    pad2->Draw();

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here
    hdata->SetTitle(menu);
    hdata->SetXTitle("E_{T}^{topocone20}/p_{T}");
    hdata->GetXaxis()->SetRangeUser(-0.5, 1.5);
    hdata->SetMinimum(1.1);
    hdata->SetLineColor(kBlue);
    hdata->SetLineWidth(2);
    hdata->SetStats(kFALSE);
    hdata->Draw("hist");
    hmc->Scale(hdata->Integral() / hmc->Integral());
    hmc->SetLineColor(kRed);
    hmc->SetLineWidth(2);
    hmc->Draw("hist,same");

    TLegend *leg = new TLegend(0.6, 0.6, 0.9, 0.8);
    leg->AddEntry(hdata, "Data 25.469 fb^{-1}");
    leg->AddEntry(hmc, "MC");
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->Draw();

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    TH1F *frame = pad2->DrawFrame(-0.5, 0.5, 1.5, 3.9);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle("E_{T}^{topocone20}/p_{T}");
    frame->GetXaxis()->SetTitleSize(20);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(3.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(16);
    frame->SetYTitle("Data / MC");
    frame->GetYaxis()->SetTitleSize(17);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(2.0);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(16);
    frame->Draw();

    TH1F *ratio = (TH1F *)hdata->Clone();
    ratio->Divide(hmc);

    ratio->SetLineColor(kBlack);
    ratio->SetLineWidth(2);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerSize(1);
    ratio->SetMarkerStyle(20);
    ratio->Draw("E1,same");

    c1->SaveAs("topoetcone20_over_pt_ratio_plot_" + menu + ".pdf", "pdf");
}
