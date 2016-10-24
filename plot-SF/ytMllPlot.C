// This is used to make Mll plots for each pT bins.
// normalizing those bins by their bin width: contents = contenst/bin_width (then the y-axis is "Events/GeV")
// Usage: root -l ytMllPlot_v2.C"(\"TightLLH\",\"isolTight\")"
//
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include "AtlasStyle/AtlasStyle.C"
#include "AtlasStyle/AtlasLabels.C"
#include "AtlasStyle/AtlasUtils.C"

#include <iostream>
using namespace std;

void ytMllPlot(TString menu = "TightLLH", TString iso  = "isolTight")
{
    gStyle->SetOptStat(0);
	//SetAtlasStyle();

    //bool debug = true;
    bool debug = false;

    TString folder_name;
    if (iso.Contains("isolPhFixedCut"))
        folder_name = menu + "_Smooth_v11_" + iso;
    else
        folder_name = menu + "_d0z0_Smooth_v11_" + iso;
    if (debug) cout << folder_name << endl;

    TFile *data_file = TFile::Open("../merged-hist-data.root");
    TFile *mc_file   = TFile::Open("../merged-hist-mc.root");

    TString bkg_template[2] = {"TemplRun2Variation1AndPassTrackQuality", "TemplRun2Variation2AndPassTrackQuality"};
    TString tag[3] = {"TagTightLLH_v11", "TagTightLLH_v11_Iso", "TagMediumLLH_v11_Iso"};

    int N_bkg_template = sizeof(bkg_template) / sizeof(bkg_template[0]);
    int N_tag = sizeof(tag) / sizeof(tag[0]);
    if (debug) cout << "Nbkg_template=" << N_bkg_template << ", N_tag" << N_tag << endl;

    TString folder;
    for (int i = 0; i < N_bkg_template; i++) {
        for (int j = 0; j < N_tag; j++) {
            folder = folder_name + "_" + bkg_template[i] + "_" + tag[j];
            if (debug) cout << folder << endl;

            TString data_den_hist_name = folder + "_Data_Den_Mll_3d";
            TString data_num_hist_name = folder + "_Data_Num_Mll_3d";
            TString mc_den_hist_name = folder + "_MCZee_NoFilter_Den_Mll_3d";
            TString mc_num_hist_name = folder + "_MCZee_NoFilter_Num_Mll_3d";
            if (debug) {
                cout << data_den_hist_name << endl;
                cout << data_num_hist_name << endl;
                cout << mc_den_hist_name << endl;
                cout << mc_num_hist_name << endl;
            }

            TH3F *data_den_hist = (TH3F *)data_file->Get(folder + "/" + data_den_hist_name);
            TH3F *data_num_hist = (TH3F *)data_file->Get(folder + "/" + data_num_hist_name);
            TH3F *mc_den_hist = (TH3F *)mc_file->Get(folder + "/" + mc_den_hist_name);
            TH3F *mc_num_hist = (TH3F *)mc_file->Get(folder + "/" + mc_num_hist_name);
            if (debug) {
                cout << data_den_hist << endl;
                cout << data_num_hist << endl;
                cout << mc_den_hist << endl;
                cout << mc_num_hist << endl;
            }

            // Remider:
            // x: pt
            // y: eta
            // z: mll
            cout << folder << endl;
            cout << "Number of bins in pt: "  << data_den_hist->GetXaxis()->GetNbins() << endl;
            cout << "Number of bins in eta: " << data_den_hist->GetYaxis()->GetNbins() << endl;

            // Canvas
            //
            // for data:
            //
            TCanvas *c1 = new TCanvas(data_den_hist_name + "_1", data_den_hist_name + "_1", 1600, 800);
            c1->Divide(3, 2);
            // make mll plots for 7-10, 10-15, 15-20, 20-25, 25-30, 30-35
            for (int pt = 2; pt < 2 + 6; pt++) {
                data_den_hist->GetXaxis()->SetRange(pt, pt);
                data_num_hist->GetXaxis()->SetRange(pt, pt);
                TH1F *den = (TH1F *)data_den_hist->Project3D("z")->Clone();
                TH1F *num = (TH1F *)data_num_hist->Project3D("z")->Clone();
                // Get the same TH1F structure
                TH1F *normalized_den = (TH1F *)den->Clone();
                TH1F *normalized_num = (TH1F *)num->Clone();
                normalized_den->Reset();
                normalized_num->Reset();
                //Normalize bins by their bin width
                for (int i = 0; i < den->GetXaxis()->GetNbins() + 1; i++) {
                    normalized_den->SetBinContent(i, den->GetBinContent(i)/den->GetXaxis()->GetBinWidth(i));
                    normalized_num->SetBinContent(i, num->GetBinContent(i)/num->GetXaxis()->GetBinWidth(i));
                }
                c1->cd(pt - 1);
                normalized_den->Draw("hist");
                normalized_num->Draw("hist,same");
                if (debug) {
                    cout << "pt=(" << data_den_hist->GetXaxis()->GetBinLowEdge(pt) << ", " << data_den_hist->GetXaxis()->GetBinUpEdge(pt) << ")"
                    << "Num=" << normalized_num->GetEntries() << ", Den=" << normalized_den->GetEntries() << endl;
                }
                // Some cosmetics
                normalized_den->GetXaxis()->SetRangeUser(60, 140);
                normalized_den->SetMarkerSize(1);
                normalized_den->GetXaxis()->SetTitle("m_{ll} [GeV]");
                //normalized_den->GetYaxis()->SetTitle("Events/#Delta(m_{ll}) [GeV]");
                normalized_den->GetYaxis()->SetTitle("Events");
                normalized_den->SetMarkerColor(kRed);
                normalized_den->SetLineColor(kRed);
                normalized_den->SetLineWidth(1);
                normalized_num->SetLineStyle(1);
                normalized_num->SetLineWidth(1);
                normalized_num->SetMarkerSize(1);
                normalized_num->SetMarkerColor(kBlue);
                normalized_num->SetLineColor(kBlue);
                char name[100];
                sprintf(&name[0], "%d GeV < p_{T} < %d GeV",
                        static_cast<int>(data_den_hist->GetXaxis()->GetBinLowEdge(pt) / 1000.),
                        static_cast<int>(data_den_hist->GetXaxis()->GetBinUpEdge(pt) / 1000.));
                myText(0.45, 0.85, kBlack, name);
                myText(0.45, 0.79, kBlack, const_cast<char *>(folder_name.Data()) );
                myText(0.45, 0.73, kBlack, const_cast<char *>(tag[j].Data()) );
                myText(0.20, 0.85, kBlack, "Data");
                // Dump some integrals 80<mll<100
                sprintf(&name[0], "Num (80-100 GeV): %3.0f",
                        normalized_num->Integral(normalized_num->GetXaxis()->FindBin(80), normalized_num->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.67, kBlue, name);
                sprintf(&name[0], "Den (80-100 GeV): %3.0f",
                        normalized_den->Integral(normalized_den->GetXaxis()->FindBin(80), normalized_den->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.61, kRed, name);
            }
            c1->Print("plots/Mll_data_" + data_den_hist_name + "_1.pdf");

            TCanvas *c2 = new TCanvas(data_den_hist_name + "_2", data_den_hist_name + "_2", 1600, 800);
            c2->Divide(3, 2);
            // make mll plots for 35-40, 40-45, 45-50, 50-60, 60-80, 80-125
            for (int pt = 8; pt < 8 + 6; pt++) {
                data_den_hist->GetXaxis()->SetRange(pt, pt);
                data_num_hist->GetXaxis()->SetRange(pt, pt);
                TH1F *den = (TH1F *)data_den_hist->Project3D("z")->Clone();
                TH1F *num = (TH1F *)data_num_hist->Project3D("z")->Clone();
                // Get the same TH1F structure
                TH1F *normalized_den = (TH1F *)den->Clone();
                TH1F *normalized_num = (TH1F *)num->Clone();
                normalized_den->Reset();
                normalized_num->Reset();
                //Normalize bins by their bin width
                for (int i = 0; i < den->GetXaxis()->GetNbins() + 1; i++) {
                    normalized_den->SetBinContent(i, den->GetBinContent(i)/den->GetXaxis()->GetBinWidth(i));
                    normalized_num->SetBinContent(i, num->GetBinContent(i)/num->GetXaxis()->GetBinWidth(i));
                }
                c2->cd(pt - 7);
                normalized_den->Draw("hist");
                normalized_num->Draw("hist,same");
                if (debug) {
                    cout << "pt=(" << data_den_hist->GetXaxis()->GetBinLowEdge(pt) << ", " << data_den_hist->GetXaxis()->GetBinUpEdge(pt) << ")"
                    << "Num=" << normalized_num->GetEntries() << ", Den=" << normalized_den->GetEntries() << endl;
                }
                // Some cosmetics
                normalized_den->GetXaxis()->SetRangeUser(60, 140);
                normalized_den->SetMarkerSize(1);
                normalized_den->GetXaxis()->SetTitle("m_{ll} [GeV]");
                //normalized_den->GetYaxis()->SetTitle("Events/#Delta(m_{ll}) [GeV]");
                normalized_den->GetYaxis()->SetTitle("Events");
                normalized_den->SetMarkerColor(kRed);
                normalized_den->SetLineColor(kRed);
                normalized_den->SetLineWidth(1);
                normalized_num->SetLineStyle(1);
                normalized_num->SetLineWidth(1);
                normalized_num->SetMarkerSize(1);
                normalized_num->SetMarkerColor(kBlue);
                normalized_num->SetLineColor(kBlue);
                char name[100];
                sprintf(&name[0], "%d GeV < p_{T} < %d GeV",
                        static_cast<int>(data_den_hist->GetXaxis()->GetBinLowEdge(pt) / 1000.),
                        static_cast<int>(data_den_hist->GetXaxis()->GetBinUpEdge(pt) / 1000.));
                myText(0.45, 0.85, kBlack, name);
                myText(0.45, 0.79, kBlack, const_cast<char *>(folder_name.Data()) );
                myText(0.45, 0.73, kBlack, const_cast<char *>(tag[j].Data()) );
                myText(0.20, 0.85, kBlack, "Data");
                // Dump some integrals 80<mll<100
                sprintf(&name[0], "Num (80-100 GeV): %3.0f",
                        normalized_num->Integral(normalized_num->GetXaxis()->FindBin(80), normalized_num->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.67, kBlue, name);
                sprintf(&name[0], "Den (80-100 GeV): %3.0f",
                        normalized_den->Integral(normalized_den->GetXaxis()->FindBin(80), normalized_den->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.61, kRed, name);
            }
            c2->Print("plots/Mll_data_" + data_den_hist_name + "_2.pdf");

            TCanvas *c3 = new TCanvas(data_den_hist_name + "_3", data_den_hist_name + "_3", 1600, 800);
            c3->Divide(3, 2);
            // make mll plots for 125-200, 200-250, 250-300, 300-350, 350-400, 400-500
            for (int pt = 14; pt < 14 + 6; pt++) {
                data_den_hist->GetXaxis()->SetRange(pt, pt);
                data_num_hist->GetXaxis()->SetRange(pt, pt);
                TH1F *den = (TH1F *)data_den_hist->Project3D("z")->Clone();
                TH1F *num = (TH1F *)data_num_hist->Project3D("z")->Clone();
                // Get the same TH1F structure
                TH1F *normalized_den = (TH1F *)den->Clone();
                TH1F *normalized_num = (TH1F *)num->Clone();
                normalized_den->Reset();
                normalized_num->Reset();
                //Normalize bins by their bin width
                for (int i = 0; i < den->GetXaxis()->GetNbins() + 1; i++) {
                    normalized_den->SetBinContent(i, den->GetBinContent(i)/den->GetXaxis()->GetBinWidth(i));
                    normalized_num->SetBinContent(i, num->GetBinContent(i)/num->GetXaxis()->GetBinWidth(i));
                }
                c3->cd(pt - 13);
                normalized_den->Draw("hist");
                normalized_num->Draw("hist,same");
                if (debug) {
                    cout << "pt=(" << data_den_hist->GetXaxis()->GetBinLowEdge(pt) << ", " << data_den_hist->GetXaxis()->GetBinUpEdge(pt) << ")"
                    << "Num=" << normalized_num->GetEntries() << ", Den=" << normalized_den->GetEntries() << endl;
                }
                // Some cosmetics
                normalized_den->GetXaxis()->SetRangeUser(60, 140);
                normalized_den->SetMarkerSize(1);
                normalized_den->GetXaxis()->SetTitle("m_{ll} [GeV]");
                //normalized_den->GetYaxis()->SetTitle("Events/#Delta(m_{ll}) [GeV]");
                normalized_den->GetYaxis()->SetTitle("Events");
                normalized_den->SetMarkerColor(kRed);
                normalized_den->SetLineColor(kRed);
                normalized_den->SetLineWidth(1);
                normalized_num->SetLineStyle(1);
                normalized_num->SetLineWidth(1);
                normalized_num->SetMarkerSize(1);
                normalized_num->SetMarkerColor(kBlue);
                normalized_num->SetLineColor(kBlue);
                char name[100];
                sprintf(&name[0], "%d GeV < p_{T} < %d GeV",
                        static_cast<int>(data_den_hist->GetXaxis()->GetBinLowEdge(pt) / 1000.),
                        static_cast<int>(data_den_hist->GetXaxis()->GetBinUpEdge(pt) / 1000.));
                myText(0.45, 0.85, kBlack, name);
                myText(0.45, 0.79, kBlack, const_cast<char *>(folder_name.Data()) );
                myText(0.45, 0.73, kBlack, const_cast<char *>(tag[j].Data()) );
                myText(0.20, 0.85, kBlack, "Data");
                // Dump some integrals 80<mll<100
                sprintf(&name[0], "Num (80-100 GeV): %3.0f",
                        normalized_num->Integral(normalized_num->GetXaxis()->FindBin(80), normalized_num->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.67, kBlue, name);
                sprintf(&name[0], "Den (80-100 GeV): %3.0f",
                        normalized_den->Integral(normalized_den->GetXaxis()->FindBin(80), normalized_den->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.61, kRed, name);
            }
            c3->Print("plots/Mll_data_" + data_den_hist_name + "_3.pdf");

            //
            // for MC:
            //
            TCanvas *c4 = new TCanvas(mc_den_hist_name + "_1", mc_den_hist_name + "_1", 1600, 800);
            c4->Divide(3, 2);
            // make mll plots for 7-10, 10-15, 15-20, 20-25, 25-30, 30-35
            for (int pt = 2; pt < 2 + 6; pt++) {
                mc_den_hist->GetXaxis()->SetRange(pt, pt);
                mc_num_hist->GetXaxis()->SetRange(pt, pt);
                TH1F *den = (TH1F *)mc_den_hist->Project3D("z")->Clone();
                TH1F *num = (TH1F *)mc_num_hist->Project3D("z")->Clone();
                // Get the same TH1F structure
                TH1F *normalized_den = (TH1F *)den->Clone();
                TH1F *normalized_num = (TH1F *)num->Clone();
                normalized_den->Reset();
                normalized_num->Reset();
                //Normalize bins by their bin width
                for (int i = 0; i < den->GetXaxis()->GetNbins() + 1; i++) {
                    normalized_den->SetBinContent(i, den->GetBinContent(i)/den->GetXaxis()->GetBinWidth(i));
                    normalized_num->SetBinContent(i, num->GetBinContent(i)/num->GetXaxis()->GetBinWidth(i));
                }
                c4->cd(pt - 1);
                normalized_den->Draw("hist");
                normalized_num->Draw("hist,same");
                if (debug) {
                    cout << "pt=(" << mc_den_hist->GetXaxis()->GetBinLowEdge(pt) << ", " << mc_den_hist->GetXaxis()->GetBinUpEdge(pt) << ")"
                    << "Num=" << normalized_num->GetEntries() << ", Den=" << normalized_den->GetEntries() << endl;
                }
                // Some cosmetics
                normalized_den->GetXaxis()->SetRangeUser(60, 140);
                normalized_den->SetMarkerSize(1);
                normalized_den->GetXaxis()->SetTitle("m_{ll} [GeV]");
                //normalized_den->GetYaxis()->SetTitle("Events/#Delta(m_{ll}) [GeV]");
                normalized_den->GetYaxis()->SetTitle("Events");
                normalized_den->SetMarkerColor(kRed);
                normalized_den->SetLineColor(kRed);
                normalized_den->SetLineWidth(1);
                normalized_num->SetLineStyle(1);
                normalized_num->SetLineWidth(1);
                normalized_num->SetMarkerSize(1);
                normalized_num->SetMarkerColor(kBlue);
                normalized_num->SetLineColor(kBlue);
                char name[100];
                sprintf(&name[0], "%d GeV < p_{T} < %d GeV",
                        static_cast<int>(mc_den_hist->GetXaxis()->GetBinLowEdge(pt) / 1000.),
                        static_cast<int>(mc_den_hist->GetXaxis()->GetBinUpEdge(pt) / 1000.));
                myText(0.45, 0.85, kBlack, name);
                myText(0.45, 0.79, kBlack, const_cast<char *>(folder_name.Data()) );
                myText(0.45, 0.73, kBlack, const_cast<char *>(tag[j].Data()) );
                myText(0.20, 0.85, kBlack, "Z#rightarrow ee MC");
                // Dump some integrals 80<mll<100
                sprintf(&name[0], "Num (80-100 GeV): %3.0f",
                        normalized_num->Integral(normalized_num->GetXaxis()->FindBin(80), normalized_num->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.67, kBlue, name);
                sprintf(&name[0], "Den (80-100 GeV): %3.0f",
                        normalized_den->Integral(normalized_den->GetXaxis()->FindBin(80), normalized_den->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.61, kRed, name);
            }
            c4->Print("plots/Mll_mc_" + mc_den_hist_name + "_1.pdf");

            TCanvas *c5 = new TCanvas(mc_den_hist_name + "_2", mc_den_hist_name + "_2", 1600, 800);
            c5->Divide(3, 2);
            // make mll plots for 35-40, 40-45, 45-50, 50-60, 60-80, 80-125
            for (int pt = 8; pt < 8 + 6; pt++) {
                mc_den_hist->GetXaxis()->SetRange(pt, pt);
                mc_num_hist->GetXaxis()->SetRange(pt, pt);
                TH1F *den = (TH1F *)mc_den_hist->Project3D("z")->Clone();
                TH1F *num = (TH1F *)mc_num_hist->Project3D("z")->Clone();
                // Get the same TH1F structure
                TH1F *normalized_den = (TH1F *)den->Clone();
                TH1F *normalized_num = (TH1F *)num->Clone();
                normalized_den->Reset();
                normalized_num->Reset();
                //Normalize bins by their bin width
                for (int i = 0; i < den->GetXaxis()->GetNbins() + 1; i++) {
                    normalized_den->SetBinContent(i, den->GetBinContent(i)/den->GetXaxis()->GetBinWidth(i));
                    normalized_num->SetBinContent(i, num->GetBinContent(i)/num->GetXaxis()->GetBinWidth(i));
                }
                c5->cd(pt - 7);
                normalized_den->Draw("hist");
                normalized_num->Draw("hist,same");
                if (debug) {
                    cout << "pt=(" << mc_den_hist->GetXaxis()->GetBinLowEdge(pt) << ", " << mc_den_hist->GetXaxis()->GetBinUpEdge(pt) << ")"
                    << "Num=" << normalized_num->GetEntries() << ", Den=" << normalized_den->GetEntries() << endl;
                }
                // Some cosmetics
                normalized_den->GetXaxis()->SetRangeUser(60, 140);
                normalized_den->SetMarkerSize(1);
                normalized_den->GetXaxis()->SetTitle("m_{ll} [GeV]");
                //normalized_den->GetYaxis()->SetTitle("Events/#Delta(m_{ll}) [GeV]");
                normalized_den->GetYaxis()->SetTitle("Events");
                normalized_den->SetMarkerColor(kRed);
                normalized_den->SetLineColor(kRed);
                normalized_den->SetLineWidth(1);
                normalized_num->SetLineStyle(1);
                normalized_num->SetLineWidth(1);
                normalized_num->SetMarkerSize(1);
                normalized_num->SetMarkerColor(kBlue);
                normalized_num->SetLineColor(kBlue);
                char name[100];
                sprintf(&name[0], "%d GeV < p_{T} < %d GeV",
                        static_cast<int>(mc_den_hist->GetXaxis()->GetBinLowEdge(pt) / 1000.),
                        static_cast<int>(mc_den_hist->GetXaxis()->GetBinUpEdge(pt) / 1000.));
                myText(0.45, 0.85, kBlack, name);
                myText(0.45, 0.79, kBlack, const_cast<char *>(folder_name.Data()) );
                myText(0.45, 0.73, kBlack, const_cast<char *>(tag[j].Data()) );
                myText(0.20, 0.85, kBlack, "Z#rightarrow ee MC");
                // Dump some integrals 80<mll<100
                sprintf(&name[0], "Num (80-100 GeV): %3.0f",
                        normalized_num->Integral(normalized_num->GetXaxis()->FindBin(80), normalized_num->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.67, kBlue, name);
                sprintf(&name[0], "Den (80-100 GeV): %3.0f",
                        normalized_den->Integral(normalized_den->GetXaxis()->FindBin(80), normalized_den->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.61, kRed, name);
            }
            c5->Print("plots/Mll_mc_" + mc_den_hist_name + "_2.pdf");

            TCanvas *c6 = new TCanvas(mc_den_hist_name + "_3", mc_den_hist_name + "_3", 1600, 800);
            c6->Divide(3, 2);
            // make mll plots for 125-200, 200-250, 250-300, 300-350, 350-400, 400-500
            for (int pt = 14; pt < 14 + 6; pt++) {
                mc_den_hist->GetXaxis()->SetRange(pt, pt);
                mc_num_hist->GetXaxis()->SetRange(pt, pt);
                TH1F *den = (TH1F *)mc_den_hist->Project3D("z")->Clone();
                TH1F *num = (TH1F *)mc_num_hist->Project3D("z")->Clone();
                // Get the same TH1F structure
                TH1F *normalized_den = (TH1F *)den->Clone();
                TH1F *normalized_num = (TH1F *)num->Clone();
                normalized_den->Reset();
                normalized_num->Reset();
                //Normalize bins by their bin width
                for (int i = 0; i < den->GetXaxis()->GetNbins() + 1; i++) {
                    normalized_den->SetBinContent(i, den->GetBinContent(i)/den->GetXaxis()->GetBinWidth(i));
                    normalized_num->SetBinContent(i, num->GetBinContent(i)/num->GetXaxis()->GetBinWidth(i));
                }
                c6->cd(pt - 13);
                normalized_den->Draw("hist");
                normalized_num->Draw("hist,same");
                if (debug) {
                    cout << "pt=(" << mc_den_hist->GetXaxis()->GetBinLowEdge(pt) << ", " << mc_den_hist->GetXaxis()->GetBinUpEdge(pt) << ")"
                    << "Num=" << normalized_num->GetEntries() << ", Den=" << normalized_den->GetEntries() << endl;
                }
                // Some cosmetics
                normalized_den->GetXaxis()->SetRangeUser(60, 140);
                normalized_den->SetMarkerSize(1);
                normalized_den->GetXaxis()->SetTitle("m_{ll} [GeV]");
                //normalized_den->GetYaxis()->SetTitle("Events/#Delta(m_{ll}) [GeV]");
                normalized_den->GetYaxis()->SetTitle("Events");
                normalized_den->SetMarkerColor(kRed);
                normalized_den->SetLineColor(kRed);
                normalized_den->SetLineWidth(1);
                normalized_num->SetLineStyle(1);
                normalized_num->SetLineWidth(1);
                normalized_num->SetMarkerSize(1);
                normalized_num->SetMarkerColor(kBlue);
                normalized_num->SetLineColor(kBlue);
                char name[100];
                sprintf(&name[0], "%d GeV < p_{T} < %d GeV",
                        static_cast<int>(mc_den_hist->GetXaxis()->GetBinLowEdge(pt) / 1000.),
                        static_cast<int>(mc_den_hist->GetXaxis()->GetBinUpEdge(pt) / 1000.));
                myText(0.45, 0.85, kBlack, name);
                myText(0.45, 0.79, kBlack, const_cast<char *>(folder_name.Data()) );
                myText(0.45, 0.73, kBlack, const_cast<char *>(tag[j].Data()) );
                myText(0.20, 0.85, kBlack, "Z#rightarrow ee MC");
                // Dump some integrals 80<mll<100
                sprintf(&name[0], "Num (80-100 GeV): %3.0f",
                        normalized_num->Integral(normalized_num->GetXaxis()->FindBin(80), normalized_num->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.67, kBlue, name);
                sprintf(&name[0], "Den (80-100 GeV): %3.0f",
                        normalized_den->Integral(normalized_den->GetXaxis()->FindBin(80), normalized_den->GetXaxis()->FindBin(100)) );
                myText(0.45, 0.61, kRed, name);
            }
            c6->Print("plots/Mll_mc_" + mc_den_hist_name + "_3.pdf");
        }
    }
}
