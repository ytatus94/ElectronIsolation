#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

using namespace std;

void rebin_deltaR(bool isMC=false)
{
    //bool debug = true;
    bool debug = false;

    double pt_bins[20] = {
    4000., 7000., 10000., 15000., 20000., 25000., 30000., 35000., 40000.,
    45000., 50000., 60000., 80000., 125000.,
    200000., 250000., 300000., 350000., 400000., 500000.}; // x bins do not change

    double new_deltaR_bins[8] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 2.0, 10.0}; // y bins use the new bins

    double mll_bins[82] = {
     60., 61., 62., 63., 64., 65., 66., 67., 68., 69.,
     70., 71., 72., 73., 74., 75., 76., 77., 78., 79.,
     80., 81., 82., 83., 84., 85., 86., 87., 88., 89.,
     90., 91., 92., 93., 94., 95., 96., 97., 98., 99.,
    100.,101.,102.,103.,104.,105.,106.,107.,108.,109.,
    110.,111.,112.,113.,114.,115.,116.,117.,118.,119.,
    120.,125.,130.,135.,140.,145.,150.,155.,160.,165.,
    170.,175.,180.,185.,190.,195.,200.,210.,220.,230.,
    240.,250.};

    int nx = sizeof(pt_bins) / sizeof(pt_bins[0]) - 1;
    int ny = sizeof(new_deltaR_bins) / sizeof(new_deltaR_bins[0]) - 1;
    int nz = sizeof(mll_bins) / sizeof(mll_bins[0]) - 1;
    if (debug) cout << "nx=" << nx << ", ny=" << ny << ", nz=" << nz << endl;

    TFile *original_file = 0;
    if (isMC)
        original_file = TFile::Open("../merged-hist-mc.root");
    else
        original_file = TFile::Open("../merged-hist-data.root");

    TString probeID[3] = {"TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"};
    TString isol[5] = {"Tight", "Loose", "LooseTrackOnly", "Gradient", "GradientLoose"};
    TString temp[2] = {"Run2Variation2AndPassTrackQuality", "Run2Variation1AndPassTrackQuality"};
    TString tagID[3] = {"TightLLHMC15_v8", "TightLLHMC15_v8_Iso", "MediumLLHMC15_v8_Iso"};
    TString SFLevel[6] = {"Den", "Num", "DenTempl", "NumTempl", "Den_SS", "Num_SS"};
    TString SFHist3D[7] = {"Mll_3d", "Mll_3d_deltaR", "Mll_3d_minDeltaR", "Mll_3d_deltaR_nocrack", "Mll_3d_minDeltaR_nocrack", "deltaR_3d", "minDeltaR_3d"};

    //int N_probeID = sizeof(probeID) / sizeof(probeID[0]);
    int N_probeID = 1; // We only use TightLLH_d0z0_v8
    int N_isol = sizeof(isol) / sizeof(isol[0]);
    int N_temp = sizeof(temp) / sizeof(temp[0]);
    int N_tagID = sizeof(tagID) / sizeof(tagID[0]);
    int N_SFLevel = sizeof(SFLevel) / sizeof(SFLevel[0]);
    int N_SFHist3D = sizeof(SFHist3D) / sizeof(SFHist3D[0]); 

    TObjArray Hist(0);

    int count_hist = 0;
    for(int i_probeID = 0; i_probeID < N_probeID; i_probeID++) {
        for (int i_isol = 0; i_isol < N_isol; i_isol++) {
            for (int i_temp = 0; i_temp < N_temp; i_temp++) {
                for (int i_tagID = 0; i_tagID < N_tagID; i_tagID++) {
                    TString dir_name = probeID[i_probeID] + "_isol" + isol[i_isol] + "_Templ" + temp[i_temp] + "_Tag" + tagID[i_tagID];
                    if (debug) cout << dir_name << endl;
                    if (debug) cout << original_file->Get(dir_name) << endl;
                    for (int i_SFLevel = 0; i_SFLevel < N_SFLevel; i_SFLevel++) {
                        for (int i_SFHist3D = 0; i_SFHist3D < N_SFHist3D; i_SFHist3D++) {
                            TString hist_name;
                            if (isMC)
                                hist_name = dir_name + "_MCZee_NoFilter_" + SFLevel[i_SFLevel] + "_" + SFHist3D[i_SFHist3D];
                            else
                                hist_name = dir_name + "_Data_" + SFLevel[i_SFLevel] + "_" + SFHist3D[i_SFHist3D];
                            if (debug) cout << hist_name << endl;
                            if (debug) cout << original_file->Get(dir_name + "/" + hist_name) << endl;
                            TH3F *old_hist = (TH3F*)original_file->Get(dir_name + "/" + hist_name);
                            if (old_hist != 0) {
                                if (debug) cout << old_hist->GetName() << endl;
                                TString new_hist_name = "rebin_dR_" + hist_name;
                                TH3F *new_hist = new TH3F(new_hist_name, old_hist->GetTitle(), nx, pt_bins, ny, new_deltaR_bins, nz, mll_bins);
                                new_hist->Sumw2();
                                TAxis *xaxis = old_hist->GetXaxis();
                                TAxis *yaxis = old_hist->GetYaxis();
                                TAxis *zaxis = old_hist->GetZaxis();
                                TAxis *xaxisN = new_hist->GetXaxis();
                                TAxis *yaxisN = new_hist->GetYaxis();
                                TAxis *zaxisN = new_hist->GetZaxis();
                                if (debug) cout << "Start to fill the histogram." << endl;
                                for (int k = 1; k <= zaxis->GetNbins(); k++) {
                                    for (int j = 1; j <= yaxis->GetNbins(); j++) {
                                        for (int i = 1; i <= xaxis->GetNbins(); i++) {
                                            int binx = i;//xaxis->GetBinCenter(i);
                                            int biny = j;//yaxis->GetBinCenter(j);
                                            int binz = k;//zaxis->GetBinCenter(k);
                                            float content = old_hist->GetBinContent(binx, biny, binz);
                                            float error   = old_hist->GetBinError(binx, biny, binz);
                                            int binxN = xaxisN->FindBind(xaxis->GetBinCenter(i));
                                            int binyN = yaxisN->FindBind(xaxis->GetBinCenter(j));
                                            int binzN = zaxisN->FindBind(xaxis->GetBinCenter(k));
                                            float contentN = new_hist->GetBinContent(binx, biny, binz);
                                            float errorN   = new_hist->GetBinError(binx, biny, binz);
                                            new_hist->SetBinContent(binxN, binyN, binzN, contentN+content);
                                            new_hist->SetBinError(binxN, binyN, binzN, sqrt( errorN*errorN + error*error ));
                                            
                                            
                                        }
                                    }
                                }
                                Hist.Add(new_hist);
                                if (debug) cout << "Done." << endl;
                                count_hist++;
                            }
                        }
                    } 
                }
            }
        }
    }
    if (debug) cout << "number of historams=" << count_hist << endl; 
    if (debug) cout << "Hist.GetEntries()=" << Hist.GetEntries() << endl;

    TFile *fout;
    if (isMC)
	    fout = TFile::Open("rebinned-hist-mc.root","recreate");
    else
	    fout = TFile::Open("rebinned-hist-data.root","recreate");
	//TFile fout("rebinned-hist-data.root","recreate");
    cout << "Write into file." << endl;
	Hist.Write();
    cout << "Finish writing." << endl;
	fout->Close();	
}

void rebin_deltaR_test()
{
    bool debug = true;

    double pt_bins[20] = {
    4000., 7000., 10000., 15000., 20000., 25000., 30000., 35000., 40000.,
    45000., 50000., 60000., 80000., 125000.,
    200000., 250000., 300000., 350000., 400000., 500000.}; // x bins do not change

    double new_deltaR_bins[8] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 2.0, 10.0}; // y bins use the new bins

    double mll_bins[82] = {
     60., 61., 62., 63., 64., 65., 66., 67., 68., 69.,
     70., 71., 72., 73., 74., 75., 76., 77., 78., 79.,
     80., 81., 82., 83., 84., 85., 86., 87., 88., 89.,
     90., 91., 92., 93., 94., 95., 96., 97., 98., 99.,
    100.,101.,102.,103.,104.,105.,106.,107.,108.,109.,
    110.,111.,112.,113.,114.,115.,116.,117.,118.,119.,
    120.,125.,130.,135.,140.,145.,150.,155.,160.,165.,
    170.,175.,180.,185.,190.,195.,200.,210.,220.,230.,
    240.,250.};

    int nx = sizeof(pt_bins) / sizeof(pt_bins[0]) - 1;
    int ny = sizeof(new_deltaR_bins) / sizeof(new_deltaR_bins[0]) - 1;
    int nz = sizeof(mll_bins) / sizeof(mll_bins[0]) - 1;
    if (debug) cout << "nx=" << nx << ", ny=" << ny << ", nz=" << nz << endl;

    TFile *original_file = TFile::Open("../merged-hist-data.root");
	TString dir_name = "TightLLH_d0z0_v8_isolTight_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8";
	TString hist_name = "TightLLH_d0z0_v8_isolTight_TemplRun2Variation1AndPassTrackQuality_TagTightLLHMC15_v8_Data_Den_Mll_3d_minDeltaR";
    TH3F *old_hist = (TH3F*)original_file->Get(dir_name + "/" + hist_name);
    cout << old_hist << endl;
    TAxis *xaxis = old_hist->GetXaxis();
    TAxis *yaxis = old_hist->GetYaxis();
    TAxis *zaxis = old_hist->GetZaxis();
    cout << "Start to fill the histogram." << endl;
    TH3F *new_hist = new TH3F("new", old_hist->GetTitle(), nx, pt_bins, ny, new_deltaR_bins, nz, mll_bins);
    for (int k = 1; k <= zaxis->GetNbins(); k++) {
    	for (int j = 1; j <= yaxis->GetNbins(); j++) {
    		for (int i = 1; i <= xaxis->GetNbins(); i++) {
    			new_hist->Fill(xaxis->GetBinCenter(i), yaxis->GetBinCenter(j), zaxis->GetBinCenter(k),
    			old_hist->GetBinContent(i, j, k));
    		}
    	}
    }
    new_hist->Project3D("yx")->Draw("colz,text");
}

void rebin_deltaR_variations_reference()
{
    //bool debug = true;
    bool debug = false;

    TObjArray Hist(0);

    TFile *original_file = TFile::Open("../output/variations_reference.root");

    TIter next(original_file->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
        TH2F *old_histogram = (TH2F*)key->ReadObj();

        double pt_bins[20] = {4000., 7000., 10000., 15000., 20000., 25000., 30000., 35000., 40000.,
                              45000., 50000., 60000., 80000., 125000.,
                              200000., 250000., 300000., 350000., 400000., 500000.}; // x bins do not change
        double new_deltaR_bins[8] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 2.0, 10.0}; // y bins use the new bins
        //int nx = old_histogram->GetXaxis()->GetNbins() - 1;
        int nx = sizeof(pt_bins) / sizeof(pt_bins[0]) - 1;
        int ny = sizeof(new_deltaR_bins) / sizeof(new_deltaR_bins[0]) - 1;
        if (debug) cout << "nx=" << nx << ", ny=" << ny << endl;

        TString histogram_name = "rebin_dR_" + TString(old_histogram->GetName());
        if (debug) cout << histogram_name << endl;
        if (debug) cout << old_histogram->GetTitle() << endl;
        TH2F *new_histogram = new TH2F(histogram_name, old_histogram->GetTitle(), nx, pt_bins, ny, new_deltaR_bins);

        TAxis *xaxis = old_histogram->GetXaxis();
        TAxis *yaxis = old_histogram->GetYaxis();
        for (int j = 1; j <= yaxis->GetNbins(); j++) {
            for (int i = 1; i <= xaxis->GetNbins(); i++) {
                new_histogram->Fill(xaxis->GetBinCenter(i), yaxis->GetBinCenter(j), old_histogram->GetBinContent(i,j));
            }
        }
        Hist.Add(new_histogram);
    }

	TFile fout("variations_rebin_deltaR.root","recreate");
	Hist.Write();
	fout.Close();	
}
