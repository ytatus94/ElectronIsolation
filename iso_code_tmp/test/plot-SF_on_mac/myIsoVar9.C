// This script is used to make isolation variables plots.
// We want to see the distributions of isolation variables so we cannot apply isolation requirement on the probe electrons.
// i.e. Only see the histograms under PlotVars_<menu>
// Make plots of isolation variables for each pt and eta bins.
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

void myIsoVar9(TString menu = "TightLLH_Smooth_v11_isolPhFixedCutLoose")
{
    SetAtlasStyle();
    bool debug = true;

    TString folder = "PlotVars_" + menu;

    TString path = "~/Desktop/";
    TFile *fdata = TFile::Open(path + "merged-hist-data.root");
    TFile *fmc   = TFile::Open(path + "merged-hist-mc.root");

    if (debug) {
        cout << fdata << endl;
        cout << fmc << endl;
    }

	TString isolation_variable[7] = {
        "ptcone20",
        "ptvarcone20",
        "topoetcone20",
        "topoetcone40",
        "topoetcone40_DDCorrection",
        "ptvarcone20_over_pt",
        "topoetcone20_over_pt"
    };
    // Choose the isolation variables
    int i = 0;
    if (debug) {
        cout << isolation_variable[i] << endl;
    }

    // Loading the isolation variables from the data and MC root files.
    // Get data
    TH2F *data_2D_isolation_variable_vs_pt  = (TH2F *)fdata->Get(folder + "/PlotVars_" + menu + "_h_2D_el_" + isolation_variable[i] + "_vs_pt");
    TH2F *data_2D_isolation_variable_vs_eta = (TH2F *)fdata->Get(folder + "/PlotVars_" + menu + "_h_2D_el_" + isolation_variable[i] + "_vs_eta");
    data_2D_isolation_variable_vs_pt->Sumw2();
    data_2D_isolation_variable_vs_eta->Sumw2();
    // Get MC
    TH2F *mc_2D_isolation_variable_vs_pt  = (TH2F *)fmc->Get(folder + "/PlotVars_" + menu + "_h_2D_el_" + isolation_variable[i] + "_vs_pt");
    TH2F *mc_2D_isolation_variable_vs_eta = (TH2F *)fmc->Get(folder + "/PlotVars_" + menu + "_h_2D_el_" + isolation_variable[i] + "_vs_eta");
    mc_2D_isolation_variable_vs_pt->Sumw2();
    mc_2D_isolation_variable_vs_eta->Sumw2();
    if (debug) {
        // Data
        cout << data_2D_isolation_variable_vs_pt->GetName() << " : " << data_2D_isolation_variable_vs_pt << endl;
        cout << data_2D_isolation_variable_vs_eta->GetName() << " : " << data_2D_isolation_variable_vs_eta << endl;
        // MC
        cout << mc_2D_isolation_variable_vs_pt->GetName() << " : " << mc_2D_isolation_variable_vs_pt << endl;
        cout << mc_2D_isolation_variable_vs_eta->GetName() << " : " << mc_2D_isolation_variable_vs_eta << endl;
    }

    // 2D plots
    if (debug) {
        // Data
        TCanvas *c1 = new TCanvas("c1", isolation_variable[i], 1000, 500);
        c1->Divide(2, 1);
        c1->cd(1);
        double xmin1 = data_2D_isolation_variable_vs_pt->GetYaxis()->GetXmin();
        double xmax1 = data_2D_isolation_variable_vs_pt->GetYaxis()->GetXmax();
        data_2D_isolation_variable_vs_pt->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);
        data_2D_isolation_variable_vs_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
        data_2D_isolation_variable_vs_pt->GetYaxis()->SetTitle(isolation_variable[i]);
        data_2D_isolation_variable_vs_pt->SetMarkerSize(1);
        data_2D_isolation_variable_vs_pt->Draw();
        c1->cd(2);
        data_2D_isolation_variable_vs_eta->GetXaxis()->SetTitle("|#eta|");
        data_2D_isolation_variable_vs_eta->GetYaxis()->SetTitle(isolation_variable[i]);
        data_2D_isolation_variable_vs_eta->SetMarkerSize(1);
        data_2D_isolation_variable_vs_eta->Draw();
        // MC
        TCanvas *c2 = new TCanvas("c2", isolation_variable[i], 1000, 500);
        c2->Divide(2, 1);
        c2->cd(1);
        double xmin3 = mc_2D_isolation_variable_vs_pt->GetYaxis()->GetXmin();
        double xmax4 = mc_2D_isolation_variable_vs_pt->GetYaxis()->GetXmax();
        mc_2D_isolation_variable_vs_pt->GetXaxis()->SetLimits(xmin3/1000, xmax4/1000);
        mc_2D_isolation_variable_vs_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
        mc_2D_isolation_variable_vs_pt->GetYaxis()->SetTitle(isolation_variable[i]);
        mc_2D_isolation_variable_vs_pt->SetMarkerSize(1);
        mc_2D_isolation_variable_vs_pt->Draw();
        c2->cd(2);
        mc_2D_isolation_variable_vs_eta->GetXaxis()->SetTitle("|#eta|");
        mc_2D_isolation_variable_vs_eta->GetYaxis()->SetTitle(isolation_variable[i]);
        mc_2D_isolation_variable_vs_eta->SetMarkerSize(1);
        mc_2D_isolation_variable_vs_eta->Draw();
    }

    int NbinsX_data_2D_isolation_variable_vs_pt  = data_2D_isolation_variable_vs_pt->GetXaxis()->GetNbins();
    int NbinsY_data_2D_isolation_variable_vs_pt  = data_2D_isolation_variable_vs_pt->GetYaxis()->GetNbins();
    int NbinsX_data_2D_isolation_variable_vs_eta = data_2D_isolation_variable_vs_eta->GetXaxis()->GetNbins();
    int NbinsY_data_2D_isolation_variable_vs_eta = data_2D_isolation_variable_vs_eta->GetYaxis()->GetNbins();
    int NbinsX_mc_2D_isolation_variable_vs_pt    = mc_2D_isolation_variable_vs_pt->GetXaxis()->GetNbins();
    int NbinsY_mc_2D_isolation_variable_vs_pt    = mc_2D_isolation_variable_vs_pt->GetYaxis()->GetNbins();
    int NbinsX_mc_2D_isolation_variable_vs_eta   = mc_2D_isolation_variable_vs_eta->GetXaxis()->GetNbins();
    int NbinsY_mc_2D_isolation_variable_vs_eta   = mc_2D_isolation_variable_vs_eta->GetYaxis()->GetNbins();
    if (debug) {
        cout << NbinsX_data_2D_isolation_variable_vs_pt << endl;
        cout << NbinsY_data_2D_isolation_variable_vs_pt << endl;
        cout << NbinsX_data_2D_isolation_variable_vs_eta << endl;
        cout << NbinsY_data_2D_isolation_variable_vs_eta << endl;
        cout << NbinsX_mc_2D_isolation_variable_vs_pt << endl;
        cout << NbinsY_mc_2D_isolation_variable_vs_pt << endl;
        cout << NbinsX_mc_2D_isolation_variable_vs_eta << endl;
        cout << NbinsY_mc_2D_isolation_variable_vs_eta << endl;
    }

    // Projection to 1-dim isolation variable axis
    TH1F *hdata_pt  = (TH1F *)data_2D_isolation_variable_vs_pt->ProjectionY()->Clone();
    TH1F *hmc_pt    = (TH1F *)mc_2D_isolation_variable_vs_pt->ProjectionY()->Clone();
    TH1F *hdata_eta = (TH1F *)data_2D_isolation_variable_vs_eta->ProjectionY()->Clone();
    TH1F *hmc_eta   = (TH1F *)mc_2D_isolation_variable_vs_eta->ProjectionY()->Clone();
    if (debug) {
        cout << hdata_pt << endl;
        cout << hmc_pt << endl;
        cout << hdata_eta << endl;
        cout << hmc_eta << endl;
    }
    // Change MeV to GeV
    double xmin1 = data_2D_isolation_variable_vs_pt->GetYaxis()->GetXmin();
    double xmax1 = data_2D_isolation_variable_vs_pt->GetYaxis()->GetXmax();
    hdata_pt->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);
    double xmin2 = data_2D_isolation_variable_vs_eta->GetYaxis()->GetXmin();
    double xmax2 = data_2D_isolation_variable_vs_eta->GetYaxis()->GetXmax();
    hdata_eta->GetXaxis()->SetLimits(xmin2/1000, xmax2/1000);
    double xmin3 = mc_2D_isolation_variable_vs_pt->GetYaxis()->GetXmin();
    double xmax3 = mc_2D_isolation_variable_vs_pt->GetYaxis()->GetXmax();
    hmc_pt->GetXaxis()->SetLimits(xmin3/1000, xmax3/1000);
    double xmin4 = mc_2D_isolation_variable_vs_eta->GetYaxis()->GetXmin();
    double xmax4 = mc_2D_isolation_variable_vs_eta->GetYaxis()->GetXmax();
    hmc_eta->GetXaxis()->SetLimits(xmin4/1000, xmax4/1000);
    // Normalize MC to data
    double data_area_pt = hdata_pt->Integral();
    double mc_area_pt   = hmc_pt->Integral();
    hmc_pt->Scale(data_area_pt / mc_area_pt);
    double data_area_eta = hdata_eta->Integral();
    double mc_area_eta   = hmc_eta->Integral();
    hmc_eta->Scale(data_area_eta / mc_area_eta);
    // 1-dim plots
    TCanvas *c1 = new TCanvas("c1",isolation_variable[i], 1000, 500);
    c1->Divide(2, 1);
    c1->cd(1);
    hdata_pt->GetXaxis()->SetTitle(isolation_variable[i] + " [GeV]");
    hdata_pt->GetYaxis()->SetTitle("Events");
    hdata_pt->SetTitle(isolation_variable[i]);
    hdata_pt->SetMarkerSize(1);
    hdata_pt->SetMarkerStyle(kCircle);
    hdata_pt->SetMarkerColor(kBlack);
    hdata_pt->SetLineColor(kBlack);
    hdata_pt->Draw();
    hmc_pt->SetMarkerSize(1);
    hmc_pt->SetMarkerStyle(kOpenTriangleUp);
    hmc_pt->SetMarkerColor(kRed);
    hmc_pt->SetLineColor(kRed);
    hmc_pt->Draw("same");
    c1->cd(2);
    hdata_eta->GetXaxis()->SetTitle(isolation_variable[i] + " [GeV]");
    hdata_eta->GetYaxis()->SetTitle("Events");
    hdata_eta->SetMarkerSize(1);
    hdata_eta->SetMarkerStyle(kCircle);
    hdata_eta->SetMarkerColor(kBlack);
    hdata_eta->SetLineColor(kBlack);
    hdata_eta->Draw();
    hmc_eta->SetMarkerSize(1);
    hmc_eta->SetMarkerStyle(kOpenTriangleUp);
    hmc_eta->SetMarkerColor(kRed);
    hmc_eta->SetLineColor(kRed);
    hmc_eta->Draw("same");

    /*
    // Choose histograms to make plot
    TH2F *hdata_2D = NULL, *hmc_2D = NULL;
    TString xtitle = "", output = "";

    hdata_2D = data_2D_el_ptcone20_vs_pt;
    hmc_2D = mc_2D_el_ptcone20_vs_pt;
    xtitle = "p_{T}^{cone20}";
    output = "ptcone20";
    double pad2_X_min = 0;
    double pad2_X_max = 5;

    hdata_2D = data_2D_el_ptvarcone20_vs_pt;
    hmc_2D = mc_2D_el_ptvarcone20_vs_pt;
    xtitle = "p_{T}^{varcone20}";
    output = "ptvarcone20";
    double pad2_X_min = 0;
    double pad2_X_max = 5;

    hdata_2D = data_2D_el_topoetcone20_vs_pt;
    hmc_2D = mc_2D_el_topoetcone20_vs_pt;
    xtitle = "E_{T}^{topocone20}";
    output = "topoetcone20";
    double pad2_X_min = -5;
    double pad2_X_max = 10;

    hdata_2D = data_2D_el_topoetcone40_vs_pt;
    hmc_2D = mc_2D_el_topoetcone40_vs_pt;
    xtitle = "E_{T}^{topocone40}";
    output = "topoetcone40";
    double pad2_X_min = -5.;
    double pad2_X_max = 15.;

    hdata_2D = data_2D_el_ptvarcone20_over_pt_vs_pt;
    hmc_2D = mc_2D_el_ptvarcone20_over_pt_vs_pt;
    xtitle = "p_{T}^{varcone20}/p_{T}";
    output = "ptvarcone20_over_pt";
    double pad2_X_min = -5.;
    double pad2_X_max = 15.;

    hdata_2D = data_2D_el_topoetcone20_over_pt_vs_pt;
    hmc_2D = mc_2D_el_topoetcone20_over_pt_vs_pt;
    xtitle = "E_{T}^{topocone20}/p_{T}";
    output = "topoetcone20_over_pt";
    double pad2_X_min = -5.;
    double pad2_X_max = 15.;

    if (debug) {
        cout << hdata_2D << endl;
        cout << hmc_2D << endl;
    }

    TH1F *hdata = (TH1F *)hdata_2D->ProjectionY()->Clone();
    double xmin1 = hdata_2D->GetYaxis()->GetXmin();
    double xmax1 = hdata_2D->GetYaxis()->GetXmax();
    //hdata->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);

    TH1F *hmc = (TH1F *)hmc_2D->ProjectionY()->Clone();
    double xmin2 = hmc_2D->GetYaxis()->GetXmin();
    double xmax2 = hmc_2D->GetYaxis()->GetXmax();
    //hmc->GetXaxis()->SetLimits(xmin2/1000, xmax2/1000);

    double data_area = hdata->Integral();
    double mc_area   = hmc->Integral();

    hmc->Scale(data_area / mc_area);

    //------------------------------------------------------//

    TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);

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

    hdata->SetXTitle(xtitle);
    hdata->SetYTitle("Events");
    hdata->SetMarkerColor(kBlack);
    hdata->SetMarkerStyle(kFullCircle);
    hdata->SetMarkerSize(0.7);
    hdata->SetLineColor(kBlack);
    //hdata->Rebin(2);
    hdata->GetXaxis()->SetRangeUser(pad2_X_min, pad2_X_max);
    hdata->Draw("E0");

    hmc->SetMarkerColor(kRed);
    hmc->SetMarkerStyle(kOpenTriangleUp);
    hmc->SetMarkerSize(0.7);
    hmc->SetLineColor(kRed);
    //hmc->Rebin(2);
    hmc->Draw("E0,SAME");

    //myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.85, kBlack, const_cast<char*>("TightLLH_Smooth_v11"));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    //TString pt_low_edge = TString::Format("%.d", static_cast<int>(hdata_2D->GetXaxis()->GetBinLowEdge(firstxbin)/1000.));
    //TString pt_up_edge  = TString::Format("%.d", static_cast<int>(hdata_2D->GetXaxis()->GetBinUpEdge(lastxbin)/1000.));
    //myText(0.55, 0.69, kBlack, pt_low_edge + " GeV < E_{T} < " + pt_up_edge + " GeV");
    //TString eta_low_edge = TString::Format("%.2f", hdata_2D->GetYaxis()->GetBinLowEdge(firstybin));
    //TString eta_up_edge  = TString::Format("%.2f", hdata_2D->GetYaxis()->GetBinUpEdge(lastybin));
    //myText(0.55, 0.61, kBlack, eta_low_edge + " < |#eta| <" + eta_up_edge);

    //TLegend *leg1 = new TLegend(0.55, 0.45, 0.80, 0.58);
    TLegend *leg1 = new TLegend(0.55, 0.62, 0.80, 0.73);
    leg1->AddEntry(hdata, "Data", "lp");
    leg1->AddEntry(hmc, "Z #rightarrow ee MC", "lp");
    leg1->SetBorderSize(0);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.05);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->Draw();

    pad2->cd(); // pad2 becomes the current pad
    //double pad2_X_max = 10;
    //double pad2_X_min = 0;
    double pad2_Y_max = 2.1;
    double pad2_Y_min = 0;
    TH1F *frame1 = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame1->GetXaxis()->SetNdivisions(510);
    frame1->GetYaxis()->SetNdivisions(403);
    frame1->SetLineWidth(1);
    frame1->SetXTitle(xtitle);
    frame1->GetXaxis()->SetTitleSize(20);
    frame1->GetXaxis()->SetTitleFont(47);
    frame1->GetXaxis()->SetTitleOffset(3.0);
    frame1->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1->GetXaxis()->SetLabelSize(16);
    frame1->SetYTitle("Data/MC");
    frame1->GetYaxis()->SetTitleSize(15);
    frame1->GetYaxis()->SetTitleFont(43);
    frame1->GetYaxis()->SetTitleOffset(2.0);
    frame1->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame1->GetYaxis()->SetLabelSize(16);
    frame1->Draw();
    
    TH1F *data_over_mc = (TH1F *)hdata->Clone();
    data_over_mc->Divide(hmc);
    data_over_mc->SetMarkerColor(kBlack);
    data_over_mc->SetMarkerStyle(kFullCircle);
    data_over_mc->SetMarkerSize(0.7);
    data_over_mc->SetLineColor(kBlack);
    data_over_mc->Draw("E0,SAME");

    c1->Print("iso_var_" + output + ".pdf");
 */
 
 
/*
    // Loading the isolation variables from the data and MC root files.
    TString h_3D_el_ptcone20 = "PlotVars_" + menu + "_h_3D_el_ptcone20";

    TH3F *data_ptcone20_3D = (TH3F *)fdata->Get(folder + "/" + h_3D_el_ptcone20);
    data_ptcone20_3D->Sumw2();

    TH3F *mc_ptcone20_3D = (TH3F *)fmc->Get(folder + "/" + h_3D_el_ptcone20);
    mc_ptcone20_3D->Sumw2();

    //------------------------------------------------------//
//
    int NbinsX_data_ptcone20_3D = data_ptcone20_3D->GetXaxis()->GetNbins(); // 200
    int NbinsY_data_ptcone20_3D = data_ptcone20_3D->GetYaxis()->GetNbins(); // 250
    int NbinsZ_data_ptcone20_3D = data_ptcone20_3D->GetZaxis()->GetNbins(); // 100

    cout << NbinsX_data_ptcone20_3D << endl;
    cout << NbinsY_data_ptcone20_3D << endl;
    cout << NbinsZ_data_ptcone20_3D << endl;

    int NbinsX_mc_ptcone20_3D = mc_ptcone20_3D->GetXaxis()->GetNbins(); // 200
    int NbinsY_mc_ptcone20_3D = mc_ptcone20_3D->GetYaxis()->GetNbins(); // 250
    int NbinsZ_mc_ptcone20_3D = mc_ptcone20_3D->GetZaxis()->GetNbins(); // 100

    cout << NbinsX_mc_ptcone20_3D << endl;
    cout << NbinsY_mc_ptcone20_3D << endl;
    cout << NbinsZ_mc_ptcone20_3D << endl;
//
    // For 3-dim histograms:
    // x axis: pT (0 to 200000 MeV, 200 bins, i.e. 1000 MeV/bin = 1 GeV/bin)
    // y axis: fabs(eta) (0 to 2.5, 250 bins, i.e. 0.01/bin)
    // z axis: isolation variables (0 to 10000, 100 bins, i.e. 100 MeV/bin)
    
    int firstxbin = 0;
    int lastxbin  = -1;
    int firstybin = 0;
    int lastybin  = -1;
    int firstzbin = 0;
    int lastzbin  = -1;

    // Binning
    //int pt_binning_array[26] = {8, 10, 11, 15, 16, 20, 21, 25, 26, 30, 31, 35, 36, 40, 41, 45, 46, 50, 51, 55, 56, 60, 61, 80, 81, 150};
    //int eta_binning_array[20] = {1, 10, 11, 60, 61, 80, 81, 115, 116, 137, 138, 152, 153, 181, 182, 201, 202, 237, 238, 247};
    // Full range.
    int pt_binning_array[2] = {8, 150};
    int eta_binning_array[2] = {1, 247};
    
    for (int i = 0; i < sizeof(pt_binning_array)/sizeof(pt_binning_array[0]); i=i+2) {
        firstxbin = pt_binning_array[i];
        lastxbin  = pt_binning_array[i+1];
        //cout << data_ptcone20_3D->GetXaxis()->GetBinLowEdge(firstxbin) /1000. << "<ET<"
        //     << data_ptcone20_3D->GetXaxis()->GetBinUpEdge(lastxbin) /1000.<< endl;
        for (int j = 0; j < sizeof(eta_binning_array)/sizeof(eta_binning_array[0]); j=j+2) {
            firstybin = eta_binning_array[j];
            lastybin  = eta_binning_array[j+1];
            //cout << data_ptcone20_3D->GetYaxis()->GetBinLowEdge(firstybin) << "<eta<"
            //     << data_ptcone20_3D->GetYaxis()->GetBinUpEdge(lastybin) << endl;

            TH1F *h_data_ptcone20_3D_project_on_z_axis = (TH1F *)data_ptcone20_3D->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
            double xmin1 = h_data_ptcone20_3D_project_on_z_axis->GetXaxis()->GetXmin();
            double xmax1 = h_data_ptcone20_3D_project_on_z_axis->GetXaxis()->GetXmax();
            h_data_ptcone20_3D_project_on_z_axis->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);

            TH1F *h_mc_ptcone20_3D_project_on_z_axis = (TH1F *)mc_ptcone20_3D->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
            double xmin2 = h_mc_ptcone20_3D_project_on_z_axis->GetXaxis()->GetXmin();
            double xmax2 = h_mc_ptcone20_3D_project_on_z_axis->GetXaxis()->GetXmax();
            h_mc_ptcone20_3D_project_on_z_axis->GetXaxis()->SetLimits(xmin2/1000, xmax2/1000);

            double data_area = h_data_ptcone20_3D_project_on_z_axis->Integral();
            double mc_area   = h_mc_ptcone20_3D_project_on_z_axis->Integral();

            h_mc_ptcone20_3D_project_on_z_axis->Scale(data_area / mc_area);

            //------------------------------------------------------//

            TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);

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

            h_data_ptcone20_3D_project_on_z_axis->SetXTitle("p_{T}^{cone20} [GeV]");
            h_data_ptcone20_3D_project_on_z_axis->SetYTitle("Events");
            h_data_ptcone20_3D_project_on_z_axis->SetMarkerColor(kBlack);
            h_data_ptcone20_3D_project_on_z_axis->SetMarkerStyle(kFullCircle);
            h_data_ptcone20_3D_project_on_z_axis->SetMarkerSize(0.7);
            h_data_ptcone20_3D_project_on_z_axis->SetLineColor(kBlack);
            h_data_ptcone20_3D_project_on_z_axis->Rebin(2);
            h_data_ptcone20_3D_project_on_z_axis->Draw("E0");

            h_mc_ptcone20_3D_project_on_z_axis->SetMarkerColor(kRed);
            h_mc_ptcone20_3D_project_on_z_axis->SetMarkerStyle(kOpenTriangleUp);
            h_mc_ptcone20_3D_project_on_z_axis->SetMarkerSize(0.7);
            h_mc_ptcone20_3D_project_on_z_axis->SetLineColor(kRed);
            h_mc_ptcone20_3D_project_on_z_axis->Rebin(2);
            h_mc_ptcone20_3D_project_on_z_axis->Draw("E0,SAME");

            myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
            myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
            TString pt_low_edge = TString::Format("%.d", static_cast<int>(data_ptcone20_3D->GetXaxis()->GetBinLowEdge(firstxbin)/1000.));
            TString pt_up_edge  = TString::Format("%.d", static_cast<int>(data_ptcone20_3D->GetXaxis()->GetBinUpEdge(lastxbin)/1000.));
            myText(0.55, 0.69, kBlack, pt_low_edge + " GeV < E_{T} < " + pt_up_edge + " GeV");
            TString eta_low_edge = TString::Format("%.2f", data_ptcone20_3D->GetYaxis()->GetBinLowEdge(firstybin));
            TString eta_up_edge  = TString::Format("%.2f", data_ptcone20_3D->GetYaxis()->GetBinUpEdge(lastybin));
            myText(0.55, 0.61, kBlack, eta_low_edge + " < |#eta| <" + eta_up_edge);

            TLegend *leg1 = new TLegend(0.55, 0.45, 0.80, 0.58);
            leg1->AddEntry(h_data_ptcone20_3D_project_on_z_axis, "Data", "lp");
            leg1->AddEntry(h_mc_ptcone20_3D_project_on_z_axis, "Z #rightarrow ee MC", "lp");
            leg1->SetBorderSize(0);
            leg1->SetTextFont(42);
            leg1->SetTextSize(0.05);
            leg1->SetFillColor(0);
            leg1->SetFillStyle(0);
            leg1->Draw();

            pad2->cd(); // pad2 becomes the current pad
            double pad2_X_max = 10;
            double pad2_X_min = 0;
            double pad2_Y_max = 2.1;
            double pad2_Y_min = 0;
            TH1F *frame1 = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
            frame1->GetXaxis()->SetNdivisions(505);
            frame1->GetYaxis()->SetNdivisions(403);
            frame1->SetLineWidth(1);
            frame1->SetXTitle("p_{T}^{cone20} [GeV]");
            frame1->GetXaxis()->SetTitleSize(20);
            frame1->GetXaxis()->SetTitleFont(47);
            frame1->GetXaxis()->SetTitleOffset(3.0);
            frame1->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            frame1->GetXaxis()->SetLabelSize(16);
            frame1->SetYTitle("Data/MC");
            frame1->GetYaxis()->SetTitleSize(15);
            frame1->GetYaxis()->SetTitleFont(43);
            frame1->GetYaxis()->SetTitleOffset(2.0);
            frame1->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            frame1->GetYaxis()->SetLabelSize(16);
            frame1->Draw();

            TH1F *data_over_mc_ptcone20_project_on_z_axis = (TH1F *)h_data_ptcone20_3D_project_on_z_axis->Clone();
            data_over_mc_ptcone20_project_on_z_axis->Divide(h_mc_ptcone20_3D_project_on_z_axis);
            data_over_mc_ptcone20_project_on_z_axis->SetMarkerColor(kBlack);
            data_over_mc_ptcone20_project_on_z_axis->SetMarkerStyle(kFullCircle);
            data_over_mc_ptcone20_project_on_z_axis->SetMarkerSize(0.7);
            data_over_mc_ptcone20_project_on_z_axis->SetLineColor(kBlack);
            data_over_mc_ptcone20_project_on_z_axis->Draw("E0,SAME");

            c1->SaveAs("plots/iso_var_ptcone20_pT" + pt_low_edge + "-" + pt_up_edge + "_eta" + eta_low_edge + "-" + eta_up_edge + "_" + menu + ".pdf", "pdf");
        }
    }
*/
}
