#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TLegend.h>
#include <TLine.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include "fixHistogramError.C"
#include "get13TeV2DHistogram.C"
#include "FindOptimalRange.C"

#include <iostream>
using namespace std;

void project_Mll_on_deltaR(TString menu, TString iso, bool isMC,
                           int pt_bin_lower, int pt_bin_upper,
                           int deltaR_bin_lower, int deltaR_bin_upper)
{
    SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    // load the denominator and numerator histograms in both data and mc.
    TFile *data_file = TFile::Open("../merged-hist-data.root");
    TFile *mc_file = TFile::Open("../merged-hist-mc.root");

	TString background_template[2] ={"TemplRun2Variation1AndPassTrackQuality", "TemplRun2Variation2AndPassTrackQuality"};
    TString tag[3] = {"TagTightLLHMC15_v8", "TagTightLLHMC15_v8_Iso", "TagMediumLLHMC15_v8_Iso"};

    TString data_folder, data_den, data_num, mc_folder, mc_den, mc_num;
    // use TemplRun2Variation1AndPassTrackQuality and TagTightLLHMC15_v8 by default
    if (iso.Contains("isolPhFixedCut")) {
        data_folder = menu + "MC15_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        data_den    = data_folder + "/" + data_folder + "_Data_Den_Mll_3d_minDeltaR";
        data_num    = data_folder + "/" + data_folder + "_Data_Num_Mll_3d_minDeltaR";

        mc_folder = menu + "MC15_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        mc_den    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Den_Mll_3d_minDeltaR";
        mc_num    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Num_Mll_3d_minDeltaR";
    }
    else {
        data_folder = menu + "_d0z0_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        data_den    = data_folder + "/" + data_folder + "_Data_Den_Mll_3d_minDeltaR";
        data_num    = data_folder + "/" + data_folder + "_Data_Num_Mll_3d_minDeltaR";

        mc_folder = menu + "_d0z0_v8_" + iso + "_" + background_template[0] + "_" + tag[0];
        mc_den    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Den_Mll_3d_minDeltaR";
        mc_num    = mc_folder + "/" + mc_folder + "_MCZee_NoFilter_Num_Mll_3d_minDeltaR";
    }

    if (debug) {
        cout << data_den << endl;
        cout << data_num << endl;
        cout << mc_den << endl;
        cout << mc_num << endl;
    }

    TH3F *h_data_den, *h_data_num, *h_mc_den, *h_mc_num;
    h_data_den = (TH3F*)data_file->Get(data_den);
    h_data_num = (TH3F*)data_file->Get(data_num);
    h_mc_den   = (TH3F*)mc_file->Get(mc_den);
    h_mc_num   = (TH3F*)mc_file->Get(mc_num); 

    if (debug) {
        cout << h_data_den << endl;
        cout << h_data_num << endl;
        cout << h_mc_den << endl;
        cout << h_mc_num << endl;
    }

    // project on the mll axis. The pt and deltaR ranges are specified.
    TH1D *h_mll_data_den = (TH1D*)h_data_den->ProjectionZ("", pt_bin_lower, pt_bin_upper-1, deltaR_bin_lower, deltaR_bin_upper-1)->Clone();
    TH1D *h_mll_data_num = (TH1D*)h_data_num->ProjectionZ("", pt_bin_lower, pt_bin_upper-1, deltaR_bin_lower, deltaR_bin_upper-1)->Clone();
    TH1D *h_mll_mc_den   = (TH1D*)h_mc_den->ProjectionZ("", pt_bin_lower, pt_bin_upper-1, deltaR_bin_lower, deltaR_bin_upper-1)->Clone();
    TH1D *h_mll_mc_num   = (TH1D*)h_mc_num->ProjectionZ("", pt_bin_lower, pt_bin_upper-1, deltaR_bin_lower, deltaR_bin_upper-1)->Clone();

    TString folder;
    TH1D *h_mll_den, *h_mll_num;
    TH3F *h_den, *h_num;
    if (isMC) {
        folder = mc_folder;
        h_mll_den = (TH1D*)h_mll_mc_den->Clone();
        h_mll_num = (TH1D*)h_mll_mc_num->Clone();
        // normalize bins by their bin width
        h_mll_den->Reset();
        h_mll_num->Reset();
        for (int i = 0; i < h_mll_mc_den->GetXaxis()->GetNbins() + 1; i++) {
            h_mll_den->SetBinContent(i, h_mll_mc_den->GetBinContent(i) / h_mll_mc_den->GetXaxis()->GetBinWidth(i));
        }
        for (int i = 0; i < h_mll_mc_num->GetXaxis()->GetNbins() + 1; i++) {
            h_mll_num->SetBinContent(i, h_mll_mc_num->GetBinContent(i) / h_mll_mc_num->GetXaxis()->GetBinWidth(i));
        }
        h_den = h_mc_den;
        h_num = h_mc_num;
    }
    else {
        folder = data_folder;
        h_mll_den = (TH1D*)h_mll_data_den->Clone();
        h_mll_num = (TH1D*)h_mll_data_num->Clone();
        // normalize bins by their bin width
        h_mll_den->Reset();
        h_mll_num->Reset();
        for (int i = 0; i < h_mll_data_den->GetXaxis()->GetNbins() + 1; i++) {
            h_mll_den->SetBinContent(i, h_mll_data_den->GetBinContent(i) / h_mll_data_den->GetXaxis()->GetBinWidth(i));
        }
        for (int i = 0; i < h_mll_data_num->GetXaxis()->GetNbins() + 1; i++) {
            h_mll_num->SetBinContent(i, h_mll_data_num->GetBinContent(i) / h_mll_data_num->GetXaxis()->GetBinWidth(i));
        }
        h_den = h_data_den;
        h_num = h_data_num;
    }

    TCanvas *c1 = new TCanvas(folder, folder, 600, 600);

    h_mll_den->GetXaxis()->SetRangeUser(60, 140);
    h_mll_den->SetXTitle("m_{ll} [GeV]");
    h_mll_den->SetYTitle("Events");
    h_mll_den->SetLineColor(kBlue);
    h_mll_den->SetLineWidth(2);
    h_mll_den->Draw("hist");

    h_mll_num->SetLineColor(kRed);
    h_mll_num->SetLineWidth(2);
    h_mll_num->Draw("hist,same");

    char pt_range[100];
    sprintf(&pt_range[0], "%d GeV < p_{T} < %d GeV",
            static_cast<int>(h_den->GetXaxis()->GetBinLowEdge(pt_bin_lower) / 1000.),
            static_cast<int>(h_den->GetXaxis()->GetBinLowEdge(pt_bin_upper) / 1000.));
    myText(0.45, 0.88, kBlack, pt_range);

    char deltaR_range[100];
    sprintf(&deltaR_range[0], "%.2f < #Delta R < %.2f",
            h_den->GetYaxis()->GetBinLowEdge(deltaR_bin_lower),
            h_den->GetYaxis()->GetBinLowEdge(deltaR_bin_upper));
    myText(0.45, 0.80, kBlack, deltaR_range);
    if (iso.Contains("isolPhFixedCut"))
        myText(0.45, 0.72, kBlack, const_cast<char *>((menu + "MC15_v8").Data()));
    else
        myText(0.45, 0.72, kBlack, const_cast<char *>((menu + "_d0z0_v8").Data()));
    myText(0.45, 0.64, kBlack, const_cast<char *>(iso.Data()));
    //myText(0.45, 0.56, kBlack, const_cast<char *>(tag[1].Data()));

    if (isMC) myText(0.45, 0.56, kBlack, "Z#rightarrow ee MC");
    else      myText(0.45, 0.56, kBlack, "Data");

    // integrals 80 < mll < 100
    char nevents[100];
    sprintf(&nevents[0], "Num (80-100 GeV): %3.0f",
            h_mll_num->Integral(h_mll_num->GetXaxis()->FindBin(80), h_mll_num->GetXaxis()->FindBin(100)));
    myText(0.45, 0.48, kRed, nevents);
    sprintf(&nevents[0], "Den (80-100 GeV) %3.0f",
            h_mll_den->Integral(h_mll_den->GetXaxis()->FindBin(80), h_mll_den->GetXaxis()->FindBin(100)));
    myText(0.45, 0.40, kBlue, nevents );

    // save canvas
    TString pt_low_edge = TString::Format("%.f", h_den->GetXaxis()->GetBinLowEdge(pt_bin_lower) / 1000.);
    TString pt_up_edge  = TString::Format("%.f", h_den->GetXaxis()->GetBinLowEdge(pt_bin_upper) / 1000.); 
    TString deltaR_low_edge = TString::Format("%.2f", h_den->GetYaxis()->GetBinLowEdge(deltaR_bin_lower));
    TString deltaR_up_edge  = TString::Format("%.2f", h_den->GetYaxis()->GetBinLowEdge(deltaR_bin_upper));
    TString plot_name;
    if (isMC)
        plot_name = "plots/Mll_mc_" + folder + "_pT" + pt_low_edge + "-" + pt_up_edge + "_dR" + deltaR_low_edge + "-" + deltaR_up_edge + ".pdf";
    else
        plot_name = "plots/Mll_data_" + folder + "_pT" + pt_low_edge + "-" + pt_up_edge + "_dR" + deltaR_low_edge + "-" + deltaR_up_edge + ".pdf";
    if (debug)
        cout << plot_name << endl;
    c1->SaveAs(plot_name, "pdf");
}
