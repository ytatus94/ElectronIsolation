#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH1F.h>
#include <TH2F.h>

#include <iostream>

void makeInputSF(TString outputDir = "../output-simpleSF")
{
    std::string runRangeValidity = "0_99999999999";
  
    const unsigned int Nfiles = 1;
    const unsigned int nID = 2;
    const unsigned int nIsol = 5;
  
    TString mID[nID] = {"TightLLHMC15_v6", "MediumLLHMC15_v6"};
    TString mIsol[nIsol] = {"_isolTight", "_isolLoose", "_isolLooseTrackOnly", "_isolGradient", "_isolGradientLoose"};
    TString mFiles[Nfiles] = {"ScaleFactors.root"};
    TString mFilesVar[Nfiles] = {"variations_reference.root"};
    TString mIDlab[nID] = {"TightLH", "MediumLH"};
    TString mIsollab[nIsol] = {"Tight", "Loose", "LooseTrackOnly", "Gradient", "GradientLoose"};

    TFile *f[Nfiles];
    TFile *fvar[Nfiles];
  
    for (unsigned i = 0; i < Nfiles; i++) {
        f[i] = new TFile(outputDir + "/" + mFiles[i]);
		//f[i]->ls();
        fvar[i] = new TFile(outputDir + "/" + mFilesVar[i]);
		//fvar[i]->ls();
    }
    
    TH2F* SF[nID][nIsol][Nfiles];
    TH2F* SFstat[nID][nIsol][Nfiles];
    TH2F* SFsyst[nID][nIsol][Nfiles];
    TH2F* SFnpv[nID][nIsol][Nfiles];
    TH1F* sysnpv[nID][nIsol];
  
    for (unsigned int i = 0; i < nID; i++) {
        for(unsigned int j = 0; j < nIsol; j++) {
            TString dirName =  mID[i];
            dirName += mIsol[j];
			//cout << dirName << endl;

            for (unsigned int ifile = 0; ifile < Nfiles; ifile++) {
                TString SFname = dirName + "/SF_CentralValue_" + dirName;
                TString SFstatName = dirName + "/SF_StatError_" + dirName;
                TString SFsystName = dirName + "/SF_SystError_" + dirName;
                TString SFnpvName = "SF_CentralValue_Nvtx" + dirName + "_TemplVariation1AndPassTrackQuality_TagTightPlusPlus_mll80100";
/*
				cout << SFname << endl;
				cout << SFstatName << endl;
				cout << SFsystName << endl;
				cout << SFnpvName << endl;
*/
                SF[i][j][ifile] = (TH2F*)f[ifile]->Get(SFname);
                SFstat[i][j][ifile] = (TH2F*)f[ifile]->Get(SFstatName);
                SFsyst[i][j][ifile] = (TH2F*)f[ifile]->Get(SFsystName);
                SFnpv[i][j][ifile] = (TH2F*)fvar[ifile]->Get(SFnpvName);
/*
				cout << SF[i][j][ifile] << endl;
				cout << SFstat[i][j][ifile] << endl;
				cout << SFsyst[i][j][ifile] << endl;
				cout << SFnpv[i][j][ifile] << endl;	
*/
				// If the Get() method cannot find the object, then return 0.
                if(!SF[i][j][ifile] || !SFstat[i][j][ifile] || !SFsyst[i][j][ifile] || !SFnpv[i][j][ifile]) {
                    cout << "SF[" << i << "][" << j << "][" << ifile << "]=" << SF[i][j][ifile] << ", "
                         << "SFstat[" << i << "][" << j << "][" << ifile << "]=" << SFstat[i][j][ifile] << ", "
                         << "SFsyst[" << i << "][" << j << "][" << ifile << "]=" << SFsyst[i][j][ifile] << ", "
                         << "SFnpv[" << i << "][" << j << "][" << ifile << "]=" << SFnpv[i][j][ifile]
                         << endl;
                }
            }

            TH2F* SFFinal = (TH2F*)SF[i][j][0]->Clone("FullSim_sf");
			//SFFinal->Draw("colz");
/*
            TString hname = "sysnpv" + dirName;
			//cout << hname << endl;
            sysnpv[i][j] = (TH1F*)SFnpv[i][j][0]->ProjectionX()->Clone(hname);

            // derive some npv syst
            int minx = SFnpv[i][j][0]->ProjectionX()->FindBin(15000.);
            for (int ibinx = 1; ibinx <= SFnpv[i][j][0]->GetNbinsX(); ibinx++) {
                float mean = 0;
                float rms = 0;
                int nbins = 0;
                int min = SFnpv[i][j][0]->ProjectionY()->FindBin(3);
                int max = SFnpv[i][j][0]->ProjectionY()->FindBin(18);
                if (ibinx >= minx){
                    for (int ibiny = min; ibiny <= max; ibiny++) {
                        mean += SFnpv[i][j][0]->GetBinContent(ibinx, ibiny);
                        //cout << "ibinx = " << ibinx
                        //     << ", ibiny = " << ibiny
                        //     << ", valy = " << SFnpv[i][j][0]->GetBinContent(ibinx,ibiny)
                        //     << ", mean = " << mean
                        //     << endl;
                        nbins += 1;
                    }
                    if(nbins > 0) mean /= static_cast<float>(nbins);
                    //cout << "mean final = " << mean << endl;
                    //float rms = 0;
                    for (int ibiny = min; ibiny < max; ibiny++){
                        rms += pow((SFnpv[i][j][0]->GetBinContent(ibinx, ibiny) - mean), 2);
                        //cout << "ibinx = " << ibinx
                        //     << ", ibiny = " << ibiny
                        //     << ", rms valy = " << pow((SFnpv[i][j][0]->GetBinContent(ibinx, ibiny) - mean), 2)
                        //     << ", rms = " << rms
                        //     << endl;
                    }
                    if(nbins > 0) rms /= static_cast<float>(nbins);
                    cout << "rms final = " << sqrt(rms) << endl;
                }
                //else{
                //    rms=0;
                //}
                sysnpv[i][j]->SetBinContent(ibinx,sqrt(rms));
            }
*/
/*
            // sum errors in quadrature
            for(int ibin = 1; ibin < SF[i][j][0]->GetSize(); ibin++) {
                // take central values and stat,syst from 8 TeV:
                float val  = SF[i][j][0]->GetBinContent(ibin);
                float stat = SFstat[i][j][0]->GetBinContent(ibin);
                float syst = SFsyst[i][j][0]->GetBinContent(ibin);
                // take central value from 13 TeV:
                float val13 = SF[i][j][1]->GetBinContent(ibin);
                float diff = fabs(val13 - val);
                //cout << "val = " << val
                //     << ", stat = " << stat
                //     << ", syst = " << syst
                //     << ", diff = " << diff
                //     << endl;
                float tot = sqrt(stat * stat + syst * syst + diff * diff);
	
                SFFinal->SetBinContent(ibin, val);
                SFFinal->SetBinError(ibin, tot);
            }
*/
            //TString outputname = "recommendations/efficiencySF.Isolation." + mIsollab[j] + "." + mIDlab[i] + ".2015.13TeV.rel20p0.v01.root";
            TString outputname = "recommendations/efficiencySF.Isolation." + mIsollab[j] + "." + mIDlab[i] + ".2015.13TeV50ns.rel20p0.v01.root";
            TFile *foutput = new TFile(outputname, "RECREATE");
            foutput->mkdir(runRangeValidity.c_str());
            foutput->cd(runRangeValidity.c_str());
            SFFinal->Write();
            //sysnpv[i][j]->Write();
            SFFinal->Delete();
            foutput->Close();
        }
    }
}
