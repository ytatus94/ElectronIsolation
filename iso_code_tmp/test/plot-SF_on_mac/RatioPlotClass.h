// This is the class declaration and implementation of ratio plot class
// NOT FINISH YET!!!
//
//
#include <TROOT.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TPad.h>
#include <TLegend.h>
#include <TLine.h>

class plot {
public:
    plot() {}
    ~plot() {}

    // Set functions
    void set_histogram_1(TH1 &h) {h1 = h;}
    void set_histogram_2(TH1 &h) {h2 = h;}
    void set_X_title(TString title) {x_title = title;}
    void set_Y_title(TString title) {y_title = title;}
    void set_X_maximum(float max) {x_max = max;}
    void set_X_minimum(float min) {x_min = min;}
    void set_Y_maximum(float max) {y_max = max;}
    void set_Y_minimum(float min) {y_min = min;}
    // Get functions
};
class RatioPlot {
public:
    RatioPlot() {};
    //RatioPlot(int, int);
    ~RatioPlot() {};

    // Set functions
    
    
    
    
    void set_canvas_width(int value) {canvas_width = value;}
    void set_canvas_height(int value) {canvas_height = value;}

    // Get functions
    int     get_canvas_width()  {return canvas_width;}
    int     get_canvas_height() {return canvas_height;}
    TString get_X_title() {return x_title;}
    TString get_Y_title() {return y_title;}

    void make_ratio_plot();
private:
    TH1 h1 = 0;
    TH1 h2 = 0;
    TString x_title;
    TString y_title;
    int canvas_width = 0;
    int canvas_height = 0;
    double pad1_X_max = 0;
    double pad1_X_min = 0;
    double pad1_Y_max = 0;
    double pad1_Y_min = 0;
    double pad2_X_max = 0;
    double pad2_X_min = 0;
    double pad2_Y_max = 0;
    double pad2_Y_min = 0;
    
};


void RatioPlot::make_ratio_plot()
{
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

    h1->SetXTitle(get_X_title());
    h1->SetYTitle(get_Y_title());
    h1->SetMaximum(pad1_Y_max);
    h1->SetMinimum(pad1_Y_min);

    h1->SetMarkerColor(kBlack);
    h1->SetMarkerStyle(kFullCircle);
    h1->SetMarkerSize(0.7);
    h1->SetLineColor(kBlack);
    h1->Rebin(2);
    h1->Draw("E0");
    h1->GetXaxis()->SetRangeUser(-2, 10);

    h2->SetMarkerColor(kRed);
    h2->SetMarkerStyle(kOpenTriangleUp);
    h2->SetMarkerSize(0.7);
    h2->SetLineColor(kRed);
    h2->Rebin(2);
    h2->Draw("E0,SAME");

    myText(0.55, 0.85, kBlack, const_cast<char*>(menu.Data()));
    myText(0.55, 0.77, kBlack, "#sqrt{s} = 13 TeV, 3.2 fb^{-1}");
    myText(0.55, 0.69, kBlack, "90 GeV < E_{T} < 100 GeV");
    myText(0.55, 0.61, kBlack, "2.25 < |#eta| < 2.5");

    TLegend *leg1 = new TLegend(0.55, 0.45, 0.80, 0.58);
    leg1->AddEntry(h1, "Data", "lp");
    leg1->AddEntry(h2, "Z #rightarrow ee MC", "lp");
    leg1->SetBorderSize(0);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.05);
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->Draw();

    pad2->cd(); // pad2 becomes the current pad

    TH1F *frame1 = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame1->GetXaxis()->SetNdivisions(505);
    frame1->GetYaxis()->SetNdivisions(403);
    frame1->SetLineWidth(1);
    frame1->SetXTitle("E_{T}^{topocone40} [GeV]");
    //frame1->SetXTitle("E_{T}^{topocone40}/p_{T} [GeV]");
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
    
    TH1F *data_over_mc_topoetcone40_project_on_z_axis = (TH1F *)h_data_topoetcone40_project_on_z_axis->Clone();
    data_over_mc_topoetcone40_project_on_z_axis->Divide(h_mc_topoetcone40_project_on_z_axis);
    data_over_mc_topoetcone40_project_on_z_axis->SetMarkerColor(kBlack);
    data_over_mc_topoetcone40_project_on_z_axis->SetMarkerStyle(kFullCircle);
    data_over_mc_topoetcone40_project_on_z_axis->SetMarkerSize(0.7);
    data_over_mc_topoetcone40_project_on_z_axis->SetLineColor(kBlack);
    data_over_mc_topoetcone40_project_on_z_axis->Draw("E0,SAME");
    
    c1->SaveAs("plots/iso_var_topoetcone40_pt90-100_eta225-250_" + menu + ".pdf", "pdf");
}
