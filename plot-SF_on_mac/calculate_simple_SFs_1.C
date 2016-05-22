// This is used to calculate the simplified isolation scale factors.
// Do not apply background subtraction.
//

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>

#include <iostream>
#include <vector>
using namespace std;

TH2F* Make2DHistogram(TString key, bool dR);
unsigned int GetMllBin(double mll);
double getSumw2ForSlice(TH3F* hist3D, unsigned int etbin, unsigned int etabin, int mll_WindowLowEdge, int mll_WindowHighEdge);
TH1F* getMllSlice(TH3F* hist3D,
				  unsigned int etbinLow, unsigned int etbinHigh,
				  unsigned int etabinLow,unsigned int etabinHigh,
				  int mll_WindowLowEdge, int mll_WindowHighEdge);

const double m_et_bins[20] =
{4000.,   7000.,   10000.,  15000.,  20000.,  25000., 30000.,
 35000.,  40000.,  45000.,  50000.,  60000.,  80000., 125000.,
 200000., 250000., 300000., 350000., 400000., 500000.};

const double m_eta_bins[21] =
{-2.47, -2.37, -2.01, -1.81, -1.52, -1.37, -1.15, -0.80, -0.60, -0.10, 0.00,
 0.10,  0.60,  0.80,  1.15,  1.37,  1.52,  1.81,  2.01,  2.37,  2.47};

const double m_deltaR_bins[8] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 2.0, 10.0};

const double m_mll_bins[82] =
{ 60.,  61.,  62.,  63.,  64.,  65.,  66.,  67.,  68.,  69.,
  70.,  71.,  72.,  73.,  74.,  75.,  76.,  77.,  78.,  79.,
  80.,  81.,  82.,  83.,  84.,  85.,  86.,  87.,  88.,  89.,
  90.,  91.,  92.,  93.,  94.,  95.,  96.,  97.,  98.,  99.,
 100., 101., 102., 103., 104., 105., 106., 107., 108., 109.,
 110., 111., 112., 113., 114., 115., 116., 117., 118., 119.,
 120., 125., 130., 135., 140., 145., 150., 155., 160., 165.,
 170., 175., 180., 185., 190., 195., 200., 210., 220., 230.,
 240., 250.};


void calculate_simple_SFs_1()
{
	bool debug = true;

	TString probeID[3]  = {"TightLLH_d0z0_v8", "MediumLLH_d0z0_v8", "LooseAndBLayerLLH_d0z0_v8"};
	TString isol[5]     = {"Tight", "Loose", "LooseTrackOnly", "Gradient", "GradientLoose"};
	TString temp[2]     = {"Run2Variation2AndPassTrackQuality", "Run2Variation1AndPassTrackQuality"};
	TString tagID[3]    = {"TightLLHMC15_v8", "TightLLHMC15_v8_Iso", "MediumLLHMC15_v8_Iso"};
	TString SFLevel[6]  = {"Den", "Num", "DenTempl", "NumTempl", "Den_SS", "Num_SS"};
	TString SFHist3D[7] = {"Mll_3d", "Mll_3d_deltaR", "Mll_3d_minDeltaR", 
						   "Mll_3d_deltaR_nocrack", "Mll_3d_minDeltaR_nocrack", 
						   "deltaR_3d", "minDeltaR_3d"};
	int mllWindow[3][2] = {{80, 100}, {75, 105}, {70, 110}};

    //int N_probeID = sizeof(probeID) / sizeof(probeID[0]);
    int N_probeID = 1; // We only use TightLLH_d0z0_v8
    int N_isol = sizeof(isol) / sizeof(isol[0]);
    int N_temp = sizeof(temp) / sizeof(temp[0]);
    int N_tagID = sizeof(tagID) / sizeof(tagID[0]);
    int N_SFLevel = sizeof(SFLevel) / sizeof(SFLevel[0]);
    int N_SFHist3D = sizeof(SFHist3D) / sizeof(SFHist3D[0]); 
	int N_mllWindow_x = sizeof(mllWindow) / sizeof(mllWindow[0]);

	if (debug) {
		cout << "N_probeID=" << N_probeID << endl;
		cout << "N_isol=" << N_isol << endl;
		cout << "N_temp=" << N_temp << endl;
		cout << "N_tagID=" << N_tagID << endl;
		cout << "N_SFLevel=" << N_SFLevel << endl;
		cout << "N_SFHist3D=" << N_SFHist3D << endl;
		cout << "N_mllWindow_x=" << N_mllWindow_x << endl;
	}

	TFile *data_file = TFile::Open("rebinned-hist-data.root","read");
	TFile *mc_file = TFile::Open("rebinned-hist-mc.root","read");
	
    TObjArray Hist(0);

	for (int i_probeID = 0; i_probeID < N_probeID; i_probeID++) {
		for (int i_isol = 0; i_isol < N_isol; i_isol++) {
			for (int i_temp = 0; i_temp < N_temp; i_temp++) {
				for (int i_tagID = 0; i_tagID < N_tagID; i_tagID++) {
					for (int i_mllWindow_x = 0; i_mllWindow_x < N_mllWindow_x; i_mllWindow_x++) {
						TString dir_name = "rebin_dR_" + probeID[i_probeID] + "_isol" + isol[i_isol] + "_Templ" + temp[i_temp] + "_Tag" + tagID[i_tagID];
						if (debug) cout << dir_name << endl;

						// Data
						shared_ptr<TH3F> Data_Den_Mll_3d           ((TH3F*)data_file->Get(dir_name + "_Data_Den_Mll_3d"));
						shared_ptr<TH3F> Data_Num_Mll_3d           ((TH3F*)data_file->Get(dir_name + "_Data_Num_Mll_3d"));
						shared_ptr<TH3F> Data_Den_Mll_3d_minDeltaR ((TH3F*)data_file->Get(dir_name + "_Data_Den_Mll_3d_minDeltaR"));
						shared_ptr<TH3F> Data_Num_Mll_3d_minDeltaR ((TH3F*)data_file->Get(dir_name + "_Data_Num_Mll_3d_minDeltaR"));
						// MC
						shared_ptr<TH3F> MC_Den_Mll_3d           ((TH3F*)mc_file->Get(dir_name + "_MCZee_NoFilter_Den_Mll_3d"));
						shared_ptr<TH3F> MC_Num_Mll_3d           ((TH3F*)mc_file->Get(dir_name + "_MCZee_NoFilter_Num_Mll_3d"));
						shared_ptr<TH3F> MC_Den_Mll_3d_minDeltaR ((TH3F*)mc_file->Get(dir_name + "_MCZee_NoFilter_Den_Mll_3d_minDeltaR"));
						shared_ptr<TH3F> MC_Num_Mll_3d_minDeltaR ((TH3F*)mc_file->Get(dir_name + "_MCZee_NoFilter_Num_Mll_3d_minDeltaR"));

						if (debug) {
							cout << Data_Den_Mll_3d << endl;
							cout << Data_Num_Mll_3d << endl;
							cout << Data_Den_Mll_3d_minDeltaR << endl;
							cout << Data_Num_Mll_3d_minDeltaR << endl;

							cout << MC_Den_Mll_3d << endl;
							cout << MC_Num_Mll_3d << endl;
							cout << MC_Den_Mll_3d_minDeltaR << endl;
							cout << MC_Num_Mll_3d_minDeltaR << endl;
						}

						TString mllWindow_low_edge = TString::Format("%d", mllWindow[i_mllWindow_x][0]);
						TString mllWindow_up_edge  = TString::Format("%d", mllWindow[i_mllWindow_x][1]);
						TString ProbeIDAndVariationName = probeID[i_probeID] + "_isol" + isol[i_isol] + 
														  "_Templ" + temp[i_temp] + "_Tag" + tagID[i_tagID] + 
														  "_mll" + mllWindow_low_edge + mllWindow_up_edge;
						if (debug) cout << ProbeIDAndVariationName << endl;

    					TH2F *h_EffData_CentralValue = Make2DHistogram("EffData_CentralValue_"+ProbeIDAndVariationName,false);
						TH2F *h_EffData_StatError    = Make2DHistogram("EffData_StatError_"   +ProbeIDAndVariationName,false);
						TH2F *h_EffMC_CentralValue   = Make2DHistogram("EffMC_CentralValue_"  +ProbeIDAndVariationName,false);
						TH2F *h_EffMC_StatError      = Make2DHistogram("EffMC_StatError_"     +ProbeIDAndVariationName,false);
						TH2F *h_SF_CentralValue      = Make2DHistogram("SF_CentralValue_"     +ProbeIDAndVariationName,false);
						TH2F *h_SF_StatError         = Make2DHistogram("SF_StatError_"        +ProbeIDAndVariationName,false);

    					TH2F *h_EffData_CentralValue_minDeltaR = Make2DHistogram("EffData_CentralValue_minDeltaR_"+ProbeIDAndVariationName,true);
						TH2F *h_EffData_StatError_minDeltaR    = Make2DHistogram("EffData_StatError_minDeltaR_"   +ProbeIDAndVariationName,true);
						TH2F *h_EffMC_CentralValue_minDeltaR   = Make2DHistogram("EffMC_CentralValue_minDeltaR_"  +ProbeIDAndVariationName,true);
						TH2F *h_EffMC_StatError_minDeltaR      = Make2DHistogram("EffMC_StatError_minDeltaR_"     +ProbeIDAndVariationName,true);
						TH2F *h_SF_CentralValue_minDeltaR      = Make2DHistogram("SF_CentralValue_minDeltaR_"     +ProbeIDAndVariationName,true);
						TH2F *h_SF_StatError_minDeltaR         = Make2DHistogram("SF_StatError_minDeltaR_"        +ProbeIDAndVariationName,true);

						// mll bins
						int mll_WindowLowEdge  = GetMllBin(mllWindow[i_mllWindow_x][0]);
						int mll_WindowHighEdge = GetMllBin(mllWindow[i_mllWindow_x][1]);

						if (debug) cout << "mll_WindowLowEdge="  << mll_WindowLowEdge << endl;
						if (debug) cout << "mll_WindowHighEdge=" << mll_WindowHighEdge << endl;

						int N_et_bins  = sizeof(m_et_bins) / sizeof(m_et_bins[0]) - 1;
						int N_dR_bins  = sizeof(m_deltaR_bins) / sizeof(m_deltaR_bins[0]) - 1;
                        int N_eta_bins = sizeof(m_eta_bins) / sizeof(m_eta_bins[0]) - 1;

						if (debug) {
							cout << "N_et_bins=" << N_et_bins << endl;
							cout << "N_dR_bins=" << N_dR_bins << endl;
							cout << "N_eta_bins=" << N_eta_bins << endl;
						}

                        // Loop over et bins
						for(int etbin = 1; etbin <= N_et_bins ; ++etbin) {
/*
                            // loop over delta R bins
							for(int minDeltaRbin = 1; minDeltaRbin <= N_dR_bins; ++minDeltaRbin) {
								if (debug) {
									cout << "etbin=" << etbin << ", minDeltaRbin=" << minDeltaRbin;
									cout << ", et is " << Data_Den_Mll_3d_minDeltaR->GetXaxis()->GetBinLowEdge(etbin) 
										 << " to "     << Data_Den_Mll_3d_minDeltaR->GetXaxis()->GetBinUpEdge(etbin);
									cout << ", minDeltaR is " << Data_Den_Mll_3d_minDeltaR->GetYaxis()->GetBinLowEdge(minDeltaRbin) 
										 << " to "            << Data_Den_Mll_3d_minDeltaR->GetYaxis()->GetBinUpEdge(minDeltaRbin);
									cout << ", mll window is " << Data_Den_Mll_3d_minDeltaR->GetZaxis()->GetBinLowEdge(mll_WindowLowEdge) 
										 << " to "             << Data_Den_Mll_3d_minDeltaR->GetZaxis()->GetBinUpEdge(mll_WindowHighEdge-1) 
										 << endl;
								}

								double den_base_zp = Data_Den_Mll_3d_minDeltaR->Integral(etbin, etbin, minDeltaRbin, minDeltaRbin, mll_WindowLowEdge, mll_WindowHighEdge-1);
								double num_base_zp = Data_Num_Mll_3d_minDeltaR->Integral(etbin, etbin, minDeltaRbin, minDeltaRbin, mll_WindowLowEdge, mll_WindowHighEdge-1);
								double den_mc_base_zp = MC_Den_Mll_3d_minDeltaR->Integral(etbin, etbin, minDeltaRbin, minDeltaRbin, mll_WindowLowEdge, mll_WindowHighEdge-1);
								double num_mc_base_zp = MC_Num_Mll_3d_minDeltaR->Integral(etbin, etbin, minDeltaRbin, minDeltaRbin, mll_WindowLowEdge, mll_WindowHighEdge-1);
								if (debug) {
									cout << "den_base_zp=" << den_base_zp << endl;
									cout << "num_base_zp=" << num_base_zp << endl;
									cout << "den_mc_base_zp=" << den_mc_base_zp << endl;
									cout << "num_mc_base_zp=" << num_mc_base_zp << endl;
								}

								// Only used if sumw2 was filled; otherwise we'll calculate the errors ourselves
								double num_mc_base_zp_sumw2 = -999;
								double den_mc_base_zp_sumw2 = -999;
								if (debug) cout << "MC_Num_Mll_3d_minDeltaR->GetSumw2N()=" << MC_Num_Mll_3d_minDeltaR->GetSumw2N() << endl;
								bool sumw2_filled = (MC_Num_Mll_3d_minDeltaR->GetSumw2N() > 0);
								if(sumw2_filled){
									num_mc_base_zp_sumw2 = getSumw2ForSlice(MC_Num_Mll_3d.get(), etbin, minDeltaRbin, mll_WindowLowEdge, mll_WindowHighEdge);
									den_mc_base_zp_sumw2 = getSumw2ForSlice(MC_Den_Mll_3d.get(), etbin, minDeltaRbin, mll_WindowLowEdge, mll_WindowHighEdge);
								}
								if (debug) cout << "num_mc_base_zp_sumw2=" << num_mc_base_zp_sumw2 << ", den_mc_base_zp_sumw2=" << den_mc_base_zp_sumw2 << endl;

								// Handle edge cases for low statistics
								if(den_base_zp < 1e-30)      den_base_zp      = 1e-30;
								if(den_mc_base_zp < 1e-30)   den_mc_base_zp   = 1e-30;
								if(num_mc_base_zp < 1e-30)   num_mc_base_zp   = 1e-30;
								if (debug) {
									cout << "After edge handled:" << endl;
									cout << "den_base_zp=" << den_base_zp << endl;
									cout << "num_base_zp=" << num_base_zp << endl;
									cout << "den_mc_base_zp=" << den_mc_base_zp << endl;
									cout << "num_mc_base_zp=" << num_mc_base_zp << endl;
								}

								// Data signal efficiency
								double sig_eff = num_base_zp / den_base_zp;
								if (debug) cout << "sig_eff=" << sig_eff << endl;
								if(sig_eff < 0.01 || sig_eff > 1) sig_eff = 1;
								if (debug) cout << "sig_eff=" << sig_eff << endl;
								// MC signal efficiency:
								double mc_eff = num_mc_base_zp / den_mc_base_zp;
								if (debug) cout << "mc_eff=" << mc_eff << endl;
								if(mc_eff < 0.01 || mc_eff > 1) mc_eff = 0.01;
								if (debug) cout << "mc_eff=" << mc_eff << endl;

								double scale_factor = sig_eff / mc_eff;
								if (debug) cout << "scale_factor=" << scale_factor << endl;

								// Binomial error with no background for both data and mc
								// Data error
								double sig_eff_error;
								// Assuming no sumw2:
								sig_eff_error = (1/den_base_zp)*sqrt( (1-2*sig_eff)*num_base_zp + sig_eff*sig_eff*den_base_zp );
                                if (debug) cout << "sig_eff_error=" << sig_eff_error << endl;
								// MC error
								double mc_eff_error;
								if(num_mc_base_zp_sumw2 > 0 && den_mc_base_zp_sumw2 > 0) {
									// This is for when sumw2 filled for the weighted samples
									mc_eff_error = (1/den_mc_base_zp)*sqrt( (1-2*mc_eff)*num_mc_base_zp_sumw2 + mc_eff*mc_eff*den_mc_base_zp_sumw2 );
								}
								else {
									// This is for the unfiltered samples, i.e. no sumw2
									mc_eff_error = (1/den_mc_base_zp)*sqrt( (1-2*mc_eff)*num_mc_base_zp + mc_eff*mc_eff*den_mc_base_zp );
								}
								if (debug) cout << "mc_eff_error=" << mc_eff_error << endl;
								double sig_error_over_eff = sig_eff_error / sig_eff;
								double mc_error_over_eff = mc_eff_error / mc_eff;
								double scale_factor_error = scale_factor * sqrt( sig_error_over_eff*sig_error_over_eff + mc_error_over_eff*mc_error_over_eff );
								if (debug) {
									cout << "sig_error_over_eff=" << sig_error_over_eff << endl;
									cout << "mc_error_over_eff="  << mc_error_over_eff << endl;
									cout << "scale_factor_error=" << scale_factor_error << endl;
								}

								// Fill histograms with efficiencies, SFs, and errors for each systematic variation
								h_EffData_CentralValue_minDeltaR->SetBinContent(etbin, minDeltaRbin, sig_eff);
								h_EffData_StatError_minDeltaR->   SetBinContent(etbin, minDeltaRbin, sig_eff_error);
								h_EffMC_CentralValue_minDeltaR->  SetBinContent(etbin, minDeltaRbin, mc_eff);
								h_EffMC_StatError_minDeltaR->     SetBinContent(etbin, minDeltaRbin, mc_eff_error);
								h_SF_CentralValue_minDeltaR->     SetBinContent(etbin, minDeltaRbin, scale_factor);
								h_SF_StatError_minDeltaR->        SetBinContent(etbin, minDeltaRbin, scale_factor_error);
							}
*/
                            // loop over eta bins
                            for(int etabin = 1; etabin <= N_eta_bins; ++etabin) {
                                if (debug) {
                                    cout << "etbin=" << etbin << ", etabin=" << etabin;
                                    cout << ", et is " << Data_Den_Mll_3d->GetXaxis()->GetBinLowEdge(etbin)
                                         << " to "     << Data_Den_Mll_3d->GetXaxis()->GetBinUpEdge(etbin);
                                    cout << ", eta is " << Data_Den_Mll_3d->GetYaxis()->GetBinLowEdge(etabin)
                                         << " to "      << Data_Den_Mll_3d->GetYaxis()->GetBinUpEdge(etabin);
                                    cout << ", mll window is " << Data_Den_Mll_3d->GetZaxis()->GetBinLowEdge(mll_WindowLowEdge)
                                         << " to "             << Data_Den_Mll_3d->GetZaxis()->GetBinUpEdge(mll_WindowHighEdge-1)
                                         << endl;
                                }
/*                               
                                double den_base_zp = Data_Den_Mll_3d->Integral(etbin, etbin, etabin, etabin, mll_WindowLowEdge, mll_WindowHighEdge-1);
                                double num_base_zp = Data_Num_Mll_3d->Integral(etbin, etbin, etabin, etabin, mll_WindowLowEdge, mll_WindowHighEdge-1);
                                double den_mc_base_zp = MC_Den_Mll_3d->Integral(etbin, etbin, etabin, etabin, mll_WindowLowEdge, mll_WindowHighEdge-1);
                                double num_mc_base_zp = MC_Num_Mll_3d->Integral(etbin, etbin, etabin, etabin, mll_WindowLowEdge, mll_WindowHighEdge-1);
                                if (debug) {
                                    cout << "den_base_zp=" << den_base_zp << endl;
                                    cout << "num_base_zp=" << num_base_zp << endl;
                                    cout << "den_mc_base_zp=" << den_mc_base_zp << endl;
                                    cout << "num_mc_base_zp=" << num_mc_base_zp << endl;
                                }
                                
                                // Only used if sumw2 was filled; otherwise we'll calculate the errors ourselves
                                double num_mc_base_zp_sumw2 = -999;
                                double den_mc_base_zp_sumw2 = -999;
                                if (debug) cout << "MC_Num_Mll_3d->GetSumw2N()=" << MC_Num_Mll_3d->GetSumw2N() << endl;
                                bool sumw2_filled = (MC_Num_Mll_3d->GetSumw2N() > 0);
                                if(sumw2_filled){
                                    num_mc_base_zp_sumw2 = getSumw2ForSlice(MC_Num_Mll_3d.get(), etbin, etabin, mll_WindowLowEdge, mll_WindowHighEdge);
                                    den_mc_base_zp_sumw2 = getSumw2ForSlice(MC_Den_Mll_3d.get(), etbin, etabin, mll_WindowLowEdge, mll_WindowHighEdge);
                                }
                                if (debug) cout << "num_mc_base_zp_sumw2=" << num_mc_base_zp_sumw2 << ", den_mc_base_zp_sumw2=" << den_mc_base_zp_sumw2 << endl;
                                
                                // Handle edge cases for low statistics
                                if(den_base_zp < 1e-30)      den_base_zp      = 1e-30;
                                if(den_mc_base_zp < 1e-30)   den_mc_base_zp   = 1e-30;
                                if(num_mc_base_zp < 1e-30)   num_mc_base_zp   = 1e-30;
                                if (debug) {
                                    cout << "After edge handled:" << endl;
                                    cout << "den_base_zp=" << den_base_zp << endl;
                                    cout << "num_base_zp=" << num_base_zp << endl;
                                    cout << "den_mc_base_zp=" << den_mc_base_zp << endl;
                                    cout << "num_mc_base_zp=" << num_mc_base_zp << endl;
                                }
                                
                                // Data signal efficiency
                                double sig_eff = num_base_zp / den_base_zp;
                                if (debug) cout << "sig_eff=" << sig_eff << endl;
                                if(sig_eff < 0.01 || sig_eff > 1) sig_eff = 1;
                                if (debug) cout << "sig_eff=" << sig_eff << endl;
                                // MC signal efficiency:
                                double mc_eff = num_mc_base_zp / den_mc_base_zp;
                                if (debug) cout << "mc_eff=" << mc_eff << endl;
                                if(mc_eff < 0.01 || mc_eff > 1) mc_eff = 0.01;
                                if (debug) cout << "mc_eff=" << mc_eff << endl;
                                
                                double scale_factor = sig_eff / mc_eff;
                                if (debug) cout << "scale_factor=" << scale_factor << endl;
                                
                                // Binomial error with no background for both data and mc
                                // Data error
                                double sig_eff_error;
                                // Assuming no sumw2:
                                sig_eff_error = (1/den_base_zp)*sqrt( (1-2*sig_eff)*num_base_zp + sig_eff*sig_eff*den_base_zp );
                                if (debug) cout << "sig_eff_error=" << sig_eff_error << endl;
                                // MC error
                                double mc_eff_error;
                                if(num_mc_base_zp_sumw2 > 0 && den_mc_base_zp_sumw2 > 0) {
                                    // This is for when sumw2 filled for the weighted samples
                                    mc_eff_error = (1/den_mc_base_zp)*sqrt( (1-2*mc_eff)*num_mc_base_zp_sumw2 + mc_eff*mc_eff*den_mc_base_zp_sumw2 );
                                }
                                else {
                                    // This is for the unfiltered samples, i.e. no sumw2
                                    mc_eff_error = (1/den_mc_base_zp)*sqrt( (1-2*mc_eff)*num_mc_base_zp + mc_eff*mc_eff*den_mc_base_zp );
                                }
                                if (debug) cout << "mc_eff_error=" << mc_eff_error << endl;
                                double sig_error_over_eff = sig_eff_error / sig_eff;
                                double mc_error_over_eff = mc_eff_error / mc_eff;
                                double scale_factor_error = scale_factor * sqrt( sig_error_over_eff*sig_error_over_eff + mc_error_over_eff*mc_error_over_eff );
                                if (debug) {
                                    cout << "sig_error_over_eff=" << sig_error_over_eff << endl;
                                    cout << "mc_error_over_eff="  << mc_error_over_eff << endl;
                                    cout << "scale_factor_error=" << scale_factor_error << endl;
                                }
                                
                                // Fill histograms with efficiencies, SFs, and errors for each systematic variation
                                h_EffData_CentralValue->SetBinContent(etbin, etabin, sig_eff);
                                h_EffData_StatError->   SetBinContent(etbin, etabin, sig_eff_error);
                                h_EffMC_CentralValue->  SetBinContent(etbin, etabin, mc_eff);
                                h_EffMC_StatError->     SetBinContent(etbin, etabin, mc_eff_error);
                                h_SF_CentralValue->     SetBinContent(etbin, etabin, scale_factor);
                                h_SF_StatError->        SetBinContent(etbin, etabin, scale_factor_error);
*/
                            }
						}
						Hist.Add(h_EffData_CentralValue_minDeltaR);
						Hist.Add(h_EffData_StatError_minDeltaR);
						Hist.Add(h_EffMC_CentralValue_minDeltaR);
						Hist.Add(h_EffMC_StatError_minDeltaR);
						Hist.Add(h_SF_CentralValue_minDeltaR);
						Hist.Add(h_SF_StatError_minDeltaR);
                        
                        Hist.Add(h_EffData_CentralValue);
                        Hist.Add(h_EffData_StatError);
                        Hist.Add(h_EffMC_CentralValue);
                        Hist.Add(h_EffMC_StatError);
                        Hist.Add(h_SF_CentralValue);
                        Hist.Add(h_SF_StatError);
					}
				}
			}
		}
	}
	TFile *output_file = TFile::Open("variations_rebin_deltaR.root","recreate");
	Hist.Write();
	output_file->Close();	
}

TH2F* Make2DHistogram(TString key, bool dR = true)
{
	vector<double> vec1, vec2;
	vec1 = vector<double>(m_et_bins, m_et_bins + sizeof(m_et_bins) / sizeof(double));
	if (dR)
		vec2 = vector<double>(m_deltaR_bins, m_deltaR_bins + sizeof(m_deltaR_bins) / sizeof(double));
	else
		vec2 = vector<double>(m_eta_bins, m_eta_bins + sizeof(m_eta_bins) / sizeof(double));
	int lvar1 = -1. + vec1.size();
	int lvar2 = -1. + vec2.size();
	TH2F *hist = new TH2F(key, key, lvar1, &vec1[0], lvar2, &vec2[0]);
	hist->SetXTitle("p_{T} [MeV]");
	if (dR)
		hist->SetYTitle("#Delta R");
	else
		hist->SetYTitle("#eta");
	return hist;
}

unsigned int GetMllBin(double mll)
{
	vector<double> mll_vec;
	mll_vec = vector<double>(m_mll_bins, m_mll_bins + sizeof(m_mll_bins) / sizeof(double));

	// If mll < lowest bin, return lowest bin for the TAxis
	if (mll < mll_vec[0]) return 1;

	// Find the bin this mll value falls into
	for (unsigned int index = 0; index < mll_vec.size() - 1; ++index) {
		if (mll_vec[index] <= mll && mll < mll_vec[index + 1]) {
			return index+1; // because this is the TAxis binning
		}
	}

	// If mll value did not fall into any bins, return the highest bin
	return mll_vec.size();
}


double getSumw2ForSlice(TH3F *hist3D, unsigned int etbin, unsigned int etabin, int mll_WindowLowEdge, int mll_WindowHighEdge)
{
	shared_ptr<TH1F> projectedHist (getMllSlice(hist3D, etbin, etbin, etabin, etabin ,mll_WindowLowEdge, mll_WindowHighEdge));

	TArrayD *sumw2_obj = projectedHist->GetSumw2();
	int   sumw2_length = projectedHist->GetSumw2N();
	double totalSumw2 = 0;

	for (int i = 0; i < sumw2_length; ++i) {
		totalSumw2 += sumw2_obj->At(i);
	}

	return totalSumw2;
}

TH1F* getMllSlice(TH3F *hist3D,
				  unsigned int etbinLow, unsigned int etbinHigh,
				  unsigned int etabinLow,unsigned int etabinHigh,
				  int mll_WindowLowEdge, int mll_WindowHighEdge)
{
	shared_ptr<TH3F> tmp_hist3D ((TH3F*) hist3D->Clone());
	tmp_hist3D->GetXaxis()->SetRange(etbinLow, etbinHigh);
	tmp_hist3D->GetYaxis()->SetRange(etabinLow,etabinHigh);
	if(mll_WindowLowEdge != -1 && mll_WindowHighEdge != -1){
		tmp_hist3D->GetZaxis()->SetRange(mll_WindowLowEdge, mll_WindowHighEdge - 1);
	}

	TH1F* projectedHist = (TH1F*) tmp_hist3D->Project3D("z");

	if(projectedHist->GetSumw2N() == 0){
		projectedHist->Sumw2(); // so errors scale properly
	}

	return projectedHist;
}
