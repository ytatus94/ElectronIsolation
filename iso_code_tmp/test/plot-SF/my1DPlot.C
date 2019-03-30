// This is used to make 1-dim efficiency plots and SF plots with uncertainty
// Usage: root my1DPlot.C"(\"TightLLHMC15_v6\",\"isolTight\",\"Eff\")"
//
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

#define YMAX 1.2
#define YMIN 0.8

#include <iostream>

void my1DPlot(TString menu = "TightLLHMC15_v9",
              TString iso  = "isolTight",
			  TString plot = "Eff")
{
    SetAtlasStyle();

    TString folder;
    if (iso != "")
		folder = menu + "_" + iso;
    else
		folder = menu;

	TString fileName = "../output-SF/ScaleFactors.root";

	TH2F *effdata      = get13TeV2DHistogram(fileName, menu, iso, "EffData_CentralValue");
	TH2F *effdata_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffData_TotalError");
	TH2F *effdata_stat = get13TeV2DHistogram(fileName, menu, iso, "EffData_StatError");

	TH2F *effmc      = get13TeV2DHistogram(fileName, menu, iso, "EffMC_CentralValue");
	TH2F *effmc_tot  = get13TeV2DHistogram(fileName, menu, iso, "EffMC_TotalError");
	TH2F *effmc_stat = get13TeV2DHistogram(fileName, menu, iso, "EffMC_StatError");

	TH2F *sf      = get13TeV2DHistogram(fileName, menu, iso, "SF_CentralValue");
	TH2F *sf_tot  = get13TeV2DHistogram(fileName, menu, iso, "SF_TotalError");
	TH2F *sf_stat = get13TeV2DHistogram(fileName, menu, iso, "SF_StatError");

    // Remider:
    // x: pt
    // y: eta

    cout << "For Data:" << endl;
    cout << "Number of bins in pt: "  << effdata->GetXaxis()->GetNbins() << endl;
    cout << "Number of bins in eta: " << effdata->GetYaxis()->GetNbins() << endl;

    if (plot == "Eff") {
		cout << "For MC:" << endl;
		cout << "Number of bins in pt: "  << effmc->GetXaxis()->GetNbins() << endl;
		cout << "Number of bins in eta: " << effmc->GetYaxis()->GetNbins() << endl;
    }

    // Big Canvas
    TCanvas* c1 = new TCanvas(folder, folder, 1600, 800);
    c1->Divide(6, 3);

    TH1F* eta[2][30]; 
    TH1F* eta_tmp[2][30];
    TH1F* tot_err[2][30];
    TH1F* sys_err[2][30];
    TH1F* stat_err[2][30];

    for (int pt = 0; pt < effdata->GetXaxis()->GetNbins() + 1; pt++) {
		if (pt == 0) continue; // underflow bin
		//if (pt < 4) continue; // The plots are empty when pt=1, 2, 3
		//c1->cd(pt - 3);
		if (pt < 2) continue; // The plots are empty when pt=1
		c1->cd(pt - 1);
 
	    // MC (only efficiency has MC)
		if (plot == "Eff") {
	    	eta[1][pt]      = (TH1F *)effmc->ProjectionY("", pt, pt)->Clone();
	    	eta_tmp[1][pt]  = (TH1F *)effmc->ProjectionY("", pt, pt)->Clone();
	    	tot_err[1][pt]  = (TH1F *)effmc_tot->ProjectionY("", pt, pt)->Clone();
	    	stat_err[1][pt] = (TH1F *)effmc_stat->ProjectionY("", pt, pt)->Clone();
	    	fixHistogramError(eta[1][pt],     tot_err[1][pt]);
	    	fixHistogramError(eta_tmp[1][pt], stat_err[1][pt]);

	    	eta[1][pt]->GetXaxis()->SetTitle("#eta");
	    	eta[1][pt]->GetYaxis()->SetTitle("Efficiency");
	    	//eta[1][pt]->SetMaximum(YMAX);
	    	//eta[1][pt]->SetMinimum(YMIN);
	    	eta[1][pt]->SetLineColor(kOrange-3);
	    	eta[1][pt]->SetLineWidth(2);
	    	eta[1][pt]->SetMarkerColor(kOrange-3);
	    	eta[1][pt]->SetMarkerSize(0.7);
	    	eta[1][pt]->SetMarkerStyle(20);
	    	eta[1][pt]->Draw();
	    	//eta[1][pt]->Draw("e1");

	    	eta_tmp[1][pt]->SetLineColor(kOrange-3);
	    	eta_tmp[1][pt]->SetLineWidth(1);
	    	eta_tmp[1][pt]->SetMarkerColor(kOrange-3);
	    	eta_tmp[1][pt]->SetMarkerSize(0.7);
	    	eta_tmp[1][pt]->SetMarkerStyle(20);
	    	eta_tmp[1][pt]->Draw("same");
	    	//eta_tmp[1][pt]->Draw("E1,same");
		}

		// Data
		if (plot == "Eff") {
			eta[0][pt]     = (TH1F *)effdata->ProjectionY("", pt, pt)->Clone();
			eta_tmp[0][pt] = (TH1F *)effdata->ProjectionY("", pt, pt)->Clone();
			tot_err[0][pt] = (TH1F *)effdata_tot->ProjectionY("", pt, pt)->Clone();
			stat_err[0][pt] = (TH1F *)effdata_stat->ProjectionY("", pt, pt)->Clone();
		}
		else if (plot == "SF") {
			eta[0][pt]     = (TH1F *)sf->ProjectionY("", pt, pt)->Clone();
			eta_tmp[0][pt] = (TH1F *)sf->ProjectionY("", pt, pt)->Clone();
			tot_err[0][pt] = (TH1F *)sf_tot->ProjectionY("", pt, pt)->Clone();
			stat_err[0][pt] = (TH1F *)sf_stat->ProjectionY("", pt, pt)->Clone();	
		}
		fixHistogramError(eta[0][pt],     tot_err[0][pt]);	
		fixHistogramError(eta_tmp[0][pt], stat_err[0][pt]);	

		eta[0][pt]->GetXaxis()->SetTitle("#eta");
		if (plot == "Eff") {
	    	eta[0][pt]->GetYaxis()->SetTitle("Efficiency");
	    	//eta[0][pt]->SetMaximum(YMAX);
	    	//eta[0][pt]->SetMinimum(YMIN);
		}
		else if (plot == "SF") {
	    	eta[0][pt]->GetYaxis()->SetTitle("Scale Factors");
	    	//eta[0][pt]->SetMaximum(YMAX);
	    	//eta[0][pt]->SetMinimum(YMIN);
		}
		eta[0][pt]->SetLineColor(kBlue);
		eta[0][pt]->SetLineWidth(2);
		eta[0][pt]->SetMarkerColor(kBlue);
		eta[0][pt]->SetMarkerSize(0.7);
		eta[0][pt]->SetMarkerStyle(20);

		//eta[0][pt]->Print("all");

		eta_tmp[0][pt]->SetLineColor(kGreen-2);
		eta_tmp[0][pt]->SetLineWidth(1);
		eta_tmp[0][pt]->SetMarkerColor(kGreen-2);
		eta_tmp[0][pt]->SetMarkerSize(0.7);
		eta_tmp[0][pt]->SetMarkerStyle(20);

		if (plot == "Eff") {
	    	eta[0][pt]->Draw("same");
	    	eta_tmp[0][pt]->Draw("same");
	    	//eta[0][pt]->Draw("e1,same");
	    	//eta_tmp[0][pt]->Draw("E1,same");
		}
		else if (plot == "SF") {
	    	eta[0][pt]->Draw("E0");
	    	eta_tmp[0][pt]->Draw("E0,same");
	    	//eta[0][pt]->Draw("e1");
	    	//eta_tmp[0][pt]->Draw("E1,same");
		}

		TLine *line = new TLine(eta[0][pt]->GetXaxis()->GetXmin(), 1., eta[0][pt]->GetXaxis()->GetXmax(),1.);
		line->SetLineColor(kBlack);
		line->SetLineStyle(2);
		line->SetLineWidth(1);
		line->Draw("same");

		char name[100];
		sprintf(&name[0], "p_{T} bin: %d - %d GeV", 
				static_cast<int>(effdata->GetXaxis()->GetBinLowEdge(pt) / 1000.),
				static_cast<int>(effdata->GetXaxis()->GetBinUpEdge(pt) / 1000.) );
		myText(0.55,0.88, kBlack, name);

		myText(0.55,0.8,  kBlack, const_cast<char *>(menu.Data()) );
		myText(0.55,0.72, kBlack, const_cast<char *>(iso.Data()) );
    }
/*
    if (plot == "Eff") {
		// Add legend
		c1->cd(11);
		TLegend *leg = new TLegend(0.2, 0.2, 0.8, 0.8);
		TH1* h_mc = new TH1F("", "", 1, 0, 1);
		TH1* h_tot_data  = new TH1F("", "", 1, 0, 1);
		TH1* h_stat_data = new TH1F("", "", 1, 0, 1);
		h_mc->SetLineColor(kOrange-3);
		h_tot_data->SetLineColor(kBlue);
		h_stat_data->SetLineColor(kGreen-2);
		leg->AddEntry(h_mc, "Z #rightarrow ee MC", "l");
		leg->AddEntry(h_stat_data, "Data (stat. uncert.)", "l");
		leg->AddEntry(h_tot_data,  "Data (total uncert.)", "l");
		leg->Draw();
    }
    else if (plot == "SF") {
		// Add legend
		c1->cd(11);
		TLegend *leg = new TLegend(0.2, 0.2, 0.8, 0.8);
		TH1* h_tot_data  = new TH1F("", "", 1, 0, 1);
		TH1* h_stat_data = new TH1F("", "", 1, 0, 1);
		h_tot_data->SetLineColor(kBlue);
		h_stat_data->SetLineColor(kGreen-2);
		leg->AddEntry(h_stat_data, "SF (stat. uncert.)", "l");
		leg->AddEntry(h_tot_data,  "SF (total uncert.)", "l");
		leg->Draw();
    }
*/
    if (plot == "Eff") {
		//c1->SaveAs("plots/Eff_" + folder + ".png", "png");
		c1->SaveAs("plots/Eff_" + folder + ".pdf", "pdf");
    }
    else if (plot == "SF") {
		//c1->SaveAs("plots/SF_" + folder + ".png", "png");
		c1->SaveAs("plots/SF_" + folder + ".pdf", "pdf");
    }
}
