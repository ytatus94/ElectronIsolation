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

	TCanvas *c1 = new TCanvas();
	c1->SetLogy();
	hdata->SetTitle(menu);
	hdata->SetXTitle("p_{T}^{varcone20} [GeV]");
	double xmin = hdata->GetXaxis()->GetXmin();
	double xmax = hdata->GetXaxis()->GetXmax();
	hdata->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
	hdata->SetLineColor(kBlack);
	hdata->SetLineWidth(2);
	hdata->SetMarkerColor(kBlack);
	hdata->SetMarkerStyle(kFullCircle);
	hdata->SetStats(kFALSE);
	hdata->Draw("E1");
	xmin = hmc->GetXaxis()->GetXmin();
	xmax = hmc->GetXaxis()->GetXmax();
	hmc->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
	hmc->Scale(hdata->Integral() / hmc->Integral());
	hmc->SetLineColor(kRed);
	hmc->SetLineWidth(2)
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

	TCanvas *c1 = new TCanvas();
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

void topoetcone20(TString path, TString menu = "TightLLH")
{
	TFile *fdata = TFile::Open(path + "merged-hist-data.root");
	TFile *fmc = TFile::Open(path + "merged-hist-mc.root");

	// Get topoetcone20/pt histograms
	TH1F *hdata = (TH1F *)fdata->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20");
	TH1F *hmc = (TH1F *)fmc->Get("PlotVars_" + menu + "_d0z0_Smooth_v11/PlotVars_" + menu + "_d0z0_Smooth_v11_h_el_topoetcone20");

	TCanvas *c1 = new TCanvas();
	c1->SetLogy();
	hdata->SetTitle(menu);
	hdata->SetXTitle("E_{T}^{topocone20} [GeV]");
	double xmin = hdata->GetXaxis()->GetXmin();
	double xmax = hdata->GetXaxis()->GetXmax();
	hdata->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
	hdata->SetLineColor(kBlue);
	hdata->SetLineWidth(2);
	hdata->SetMarkerColor(kBlack);
	hdata->SetMarkerStyle(kFullCircle);
	hdata->SetStats(kFALSE);
	hdata->Draw("hist");
	xmin = hmc->GetXaxis()->GetXmin();
	xmax = hmc->GetXaxis()->GetXmax();
	hmc->GetXaxis()->SetLimits(xmin / 1000, xmax / 1000);
	hmc->Scale(hdata->Integral() / hmc->Integral());
	hdata->SetMarkerColor(kRed);
	hdata->SetMarkerStyle(kFullCircle);
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

	TCanvas *c1 = new TCanvas();
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