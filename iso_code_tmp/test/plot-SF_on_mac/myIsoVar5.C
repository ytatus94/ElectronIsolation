// This script compare topoetcone40 with and without applying data driven shift
// We want to see the distributions of isolation variables so we cannot apply isolation requirement on the probe electrons.
// i.e. Only see the histograms under PlotVars_<menu>
// Make plots of topoetcone40 and topoetcone40_DDCorrection project on z axis. Scan ET-eta bins.
// MC is normalized to data.
//
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

void myIsoVar5(TString menu = "TightLLHMC15_v8")
{
    SetAtlasStyle();

    TString folder = "PlotVars_" + menu;

    TString path1 = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/TagAndProbe/MyTagAndProbe_test33/topoetcone40/";
    TFile *fdata1 = TFile::Open(path1 + "merged-hist-data.root");
    TFile *fmc1   = TFile::Open(path1 + "merged-hist-mc.root");

    // Loading the isolation variables from the data and MC root files.
    TString h_3D_el_topoetcone40 = "PlotVars_" + menu + "_h_3D_el_topoetcone40";

    TH3F *data_3D_el_topoetcone40 = (TH3F *)fdata1->Get(folder + "/" + h_3D_el_topoetcone40);
    data_3D_el_topoetcone40->Sumw2();

    TH3F *mc_3D_el_topoetcone40 = (TH3F *)fmc1->Get(folder + "/" + h_3D_el_topoetcone40);
    mc_3D_el_topoetcone40->Sumw2();

    // Apply DD shift
    TString path2 = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/TagAndProbe/MyTagAndProbe_test33/DD_shift/";
    TFile *fdata2 = TFile::Open(path2 + "merged-hist-data.root");
    TFile *fmc2   = TFile::Open(path2 + "merged-hist-mc.root");

    // Loading the isolation variables from the data and MC root files.
    TString h_3D_el_topoetcone40_DDCorrection = "PlotVars_" + menu + "_h_3D_el_topoetcone40_DDCorrection";

    TH3F *data_3D_el_topoetcone40_DDCorrection = (TH3F *)fdata2->Get(folder + "/" + h_3D_el_topoetcone40_DDCorrection);
    data_3D_el_topoetcone40_DDCorrection->Sumw2();

    TH3F *mc_3D_el_topoetcone40_DDCorrection = (TH3F *)fmc2->Get(folder + "/" + h_3D_el_topoetcone40_DDCorrection);
    mc_3D_el_topoetcone40_DDCorrection->Sumw2();

    //------------------------------------------------------//

    int firstxbin = 0;
    int lastxbin  = -1;
    int firstybin = 0;
    int lastybin  = -1;
    int firstzbin = 0;
    int lastzbin  = -1;

    // Binning
    int pt_binning_array[26] = {8, 10, 11, 15, 16, 20, 21, 25, 26, 30, 31, 35, 36, 40, 41, 45, 46, 50, 51, 55, 56, 60, 61, 80, 81, 150};
    int eta_binning_array[20] = {1, 10, 11, 60, 61, 80, 81, 115, 116, 137, 138, 152, 153, 181, 182, 201, 202, 237, 238, 247};
    // Full range.
    //int pt_binning_array[2] = {8, 150};
    //int eta_binning_array[2] = {1, 247};

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

            TH1F *h_data_3D_el_topoetcone40_project_on_z_axis = (TH1F *)data_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
            double xmin1 = h_data_3D_el_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
            double xmax1 = h_data_3D_el_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
            h_data_3D_el_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin1/1000, xmax1/1000);

            TH1F *h_mc_3D_el_topoetcone40_project_on_z_axis = (TH1F *)mc_3D_el_topoetcone40->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
            double xmin2 = h_mc_3D_el_topoetcone40_project_on_z_axis->GetXaxis()->GetXmin();
            double xmax2 = h_mc_3D_el_topoetcone40_project_on_z_axis->GetXaxis()->GetXmax();
            h_mc_3D_el_topoetcone40_project_on_z_axis->GetXaxis()->SetLimits(xmin2/1000, xmax2/1000);

            double data_area1 = h_data_3D_el_topoetcone40_project_on_z_axis->Integral();
            double mc_area1   = h_mc_3D_el_topoetcone40_project_on_z_axis->Integral();

            h_mc_3D_el_topoetcone40_project_on_z_axis->Scale(data_area1 / mc_area1);

            // Apply DD shift
            TH1F *h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis = (TH1F *)data_3D_el_topoetcone40_DDCorrection->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
            double xmin3 = h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->GetXaxis()->GetXmin();
            double xmax3 = h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->GetXaxis()->GetXmax();
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->GetXaxis()->SetLimits(xmin3/1000, xmax3/1000);

            TH1F *h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis = (TH1F *)mc_3D_el_topoetcone40_DDCorrection->ProjectionZ("", firstxbin, lastxbin, firstybin, lastybin)->Clone();
            double xmin4 = h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->GetXaxis()->GetXmin();
            double xmax4 = h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->GetXaxis()->GetXmax();
            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->GetXaxis()->SetLimits(xmin4/1000, xmax4/1000);

            double data_area2 = h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Integral();
            double mc_area2   = h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Integral();

            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Scale(data_area2 / mc_area2);

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
            //pad1->SetLogy();

            h_data_3D_el_topoetcone40_project_on_z_axis->SetXTitle("E_{T}^{topocone40} [GeV]");
            h_data_3D_el_topoetcone40_project_on_z_axis->SetYTitle("Events");
            h_data_3D_el_topoetcone40_project_on_z_axis->SetMarkerColor(kBlack);
            h_data_3D_el_topoetcone40_project_on_z_axis->SetMarkerStyle(kOpenCircle);
            h_data_3D_el_topoetcone40_project_on_z_axis->SetMarkerSize(0.7);
            h_data_3D_el_topoetcone40_project_on_z_axis->SetLineColor(kBlack);
            h_data_3D_el_topoetcone40_project_on_z_axis->Rebin(2);
            h_data_3D_el_topoetcone40_project_on_z_axis->GetXaxis()->SetRangeUser(-5, 15);
            h_data_3D_el_topoetcone40_project_on_z_axis->Draw("E0");

            h_mc_3D_el_topoetcone40_project_on_z_axis->SetMarkerColor(kRed);
            h_mc_3D_el_topoetcone40_project_on_z_axis->SetMarkerStyle(kOpenTriangleUp);
            h_mc_3D_el_topoetcone40_project_on_z_axis->SetMarkerSize(0.7);
            h_mc_3D_el_topoetcone40_project_on_z_axis->SetLineColor(kRed);
            h_mc_3D_el_topoetcone40_project_on_z_axis->Rebin(2);
            h_mc_3D_el_topoetcone40_project_on_z_axis->Draw("E0,SAME");

            // Apply DD shift
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetXTitle("E_{T}^{topocone40} [GeV]");
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetYTitle("Events");
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerColor(kBlue);
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerStyle(kFullCircle);
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerSize(0.7);
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetLineColor(kBlue);
            h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Rebin(2);
            //h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Draw("E0,SAME");

            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerColor(kBlue);
            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerStyle(kFullTriangleDown);
            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerSize(0.7);
            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->SetLineColor(kBlue);
            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Rebin(2);
            h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Draw("E0,SAME");

            myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
            myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
            TString pt_low_edge = TString::Format("%.d", static_cast<int>(data_3D_el_topoetcone40->GetXaxis()->GetBinLowEdge(firstxbin)/1000.));
            TString pt_up_edge  = TString::Format("%.d", static_cast<int>(data_3D_el_topoetcone40->GetXaxis()->GetBinUpEdge(lastxbin)/1000.));
            myText(0.55, 0.69, kBlack, pt_low_edge + " GeV < E_{T} < " + pt_up_edge + " GeV");
            TString eta_low_edge = TString::Format("%.2f", data_3D_el_topoetcone40->GetYaxis()->GetBinLowEdge(firstybin));
            TString eta_up_edge  = TString::Format("%.2f", data_3D_el_topoetcone40->GetYaxis()->GetBinUpEdge(lastybin));
            myText(0.55, 0.61, kBlack, eta_low_edge + " < |#eta| <" + eta_up_edge);

            TLegend *leg1 = new TLegend(0.55, 0.35, 0.80, 0.58);
            leg1->AddEntry(h_data_3D_el_topoetcone40_project_on_z_axis, "Data", "lp");
            leg1->AddEntry(h_mc_3D_el_topoetcone40_project_on_z_axis, "Z #rightarrow ee MC (w/o DD shift)", "lp");
            //leg1->AddEntry(h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis, "Data (w/ DD shift)", "lp");
            leg1->AddEntry(h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis, "Z #rightarrow ee MC (w/ DD shift)", "lp");
            leg1->SetBorderSize(0);
            leg1->SetTextFont(42);
            leg1->SetTextSize(0.05);
            leg1->SetFillColor(0);
            leg1->SetFillStyle(0);
            leg1->Draw();

            pad2->cd(); // pad2 becomes the current pad
            double pad2_X_max = 15;
            double pad2_X_min = -5;
            double pad2_Y_max = 3.;
            double pad2_Y_min = 0.;
            TH1F *frame1 = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
            frame1->GetXaxis()->SetNdivisions(505);
            frame1->GetYaxis()->SetNdivisions(403);
            frame1->SetLineWidth(1);
            frame1->SetXTitle("E_{T}^{topocone40} [GeV]");
            frame1->GetXaxis()->SetTitleSize(20);
            frame1->GetXaxis()->SetTitleFont(47);
            frame1->GetXaxis()->SetTitleOffset(3.0);
            frame1->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            frame1->GetXaxis()->SetLabelSize(18);
            frame1->SetYTitle("Data/MC");
            frame1->GetYaxis()->SetTitleSize(16);
            frame1->GetYaxis()->SetTitleFont(43);
            frame1->GetYaxis()->SetTitleOffset(2.5);
            frame1->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
            frame1->GetYaxis()->SetLabelSize(18);
            frame1->Draw();

            TH1F *data_over_mc_topoetcone40_project_on_z_axis = (TH1F *)h_data_3D_el_topoetcone40_project_on_z_axis->Clone();
            data_over_mc_topoetcone40_project_on_z_axis->Divide(h_mc_3D_el_topoetcone40_project_on_z_axis);
            data_over_mc_topoetcone40_project_on_z_axis->SetMarkerColor(kRed);
            data_over_mc_topoetcone40_project_on_z_axis->SetMarkerStyle(kOpenCircle);
            data_over_mc_topoetcone40_project_on_z_axis->SetMarkerSize(0.7);
            data_over_mc_topoetcone40_project_on_z_axis->SetLineColor(kRed);
            data_over_mc_topoetcone40_project_on_z_axis->Draw("E0,SAME");

            // Apply DD shift
            //TH1F *data_over_mc_topoetcone40_DDCorrection_project_on_z_axis = (TH1F *)h_data_3D_el_topoetcone40_DDCorrection_project_on_z_axis->Clone();
            TH1F *data_over_mc_topoetcone40_DDCorrection_project_on_z_axis = (TH1F *)h_data_3D_el_topoetcone40_project_on_z_axis->Clone();
            data_over_mc_topoetcone40_DDCorrection_project_on_z_axis->Divide(h_mc_3D_el_topoetcone40_DDCorrection_project_on_z_axis);
            data_over_mc_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerColor(kBlue);
            data_over_mc_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerStyle(kFullCircle);
            data_over_mc_topoetcone40_DDCorrection_project_on_z_axis->SetMarkerSize(0.7);
            data_over_mc_topoetcone40_DDCorrection_project_on_z_axis->SetLineColor(kBlue);
            data_over_mc_topoetcone40_DDCorrection_project_on_z_axis->Draw("E0,SAME");

            TLegend *leg2 = new TLegend(0.3, 0.85, 0.80, 0.95);
            leg2->AddEntry(data_over_mc_topoetcone40_project_on_z_axis, "w/o DD shift", "lp");
            leg2->AddEntry(data_over_mc_topoetcone40_DDCorrection_project_on_z_axis, "w/ DD shift", "lp");
            leg2->SetNColumns(2);
            leg2->SetBorderSize(0);
            leg2->SetTextFont(42);
            leg2->SetTextSize(0.1);
            leg2->SetFillColor(0);
            leg2->SetFillStyle(0);
            leg2->Draw();

            c1->SaveAs("plots/iso_var_Compare_DDshift_topoetcone40_pT" + pt_low_edge + "-" + pt_up_edge + "_eta" + eta_low_edge + "-" + eta_up_edge + "_" + menu + ".pdf", "pdf");
        }
    }
}
