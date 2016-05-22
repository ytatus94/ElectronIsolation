// This script is used to compare the difference of the results between two config files:
// testLxplus2 uses ZmassSystematicsIsolation25ns
// testLxplus3 uses ZmassSystematicsIsolation25nsAlternative
// print out the value and see the difference
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TH2.h>
#include <TAxis.h>

#include <iostream>
using namespace std;

void compareScaleFactors1()
{
	TString dir1 = "/afs/cern.ch/work/y/yushen/private/TagAndProbe/MyTagAndProbe_test14/TagAndProbeFrame/util/testLxplus2/output/";
	TString dir2 = "/afs/cern.ch/work/y/yushen/private/TagAndProbe/MyTagAndProbe_test14/TagAndProbeFrame/util/testLxplus3/output/";

	TFile *file1 = new TFile(dir1 + "ScaleFactors.root");
	TFile *file2 = new TFile(dir2 + "ScaleFactors.root");

	TString menu[4] = {"TightLLHMC15_v9", "MediumLLHMC15_v9", "LooseLLHMC15_v9", "LooseAndBLayerLLHMC15_v9"};
	TString iso[11] = {"isolTight",
                           "isolLoose", "isolLooseTrackOnly", 
                           "isolGradient", "isolGradientLoose", 
                           "isolFixedCutTightTrackOnly", "isolFixedCutTight", "isolFixedCutLoose",
                           "isolPhFixedCutTightCaloOnly", "isolPhFixedCutTight", "isolPhFixedCutLoose"};

	TString hName[3] = {"EffData_CentralValue_", "EffMC_CentralValue_", "SF_CentralValue_"};

	for(int i = 0; i < 4; i++) {
		for (int j = 0; j < 11; j++) {
			for (int k = 0; k < 3; k++) {
				TH2F *h1 = (TH2F *)file1->Get(menu[i] + "_" + iso[j] + "/" + hName[k] + menu[i] + "_" + iso[j]);
				TH2F *h2 = (TH2F *)file2->Get(menu[i] + "_" + iso[j] + "/" + hName[k] + menu[i] + "_" + iso[j]);
				if (h1->GetXaxis()->GetNbins() != h2->GetXaxis()->GetNbins()) {
					cout << "h1->GetXaxis()->GetNbins()=" << h1->GetXaxis()->GetNbins() << endl;
					cout << "h2->GetXaxis()->GetNbins()=" << h2->GetXaxis()->GetNbins() << endl;
				}
				else if (h1->GetYaxis()->GetNbins() != h2->GetYaxis()->GetNbins()) {
					cout << "h1->GetYaxis()->GetNbins()=" << h1->GetYaxis()->GetNbins() << endl;
					cout << "h2->GetYaxis()->GetNbins()=" << h2->GetYaxis()->GetNbins() << endl;
				}
				for (int m = 0; m < h1->GetXaxis()->GetNbins(); m++) {
					for (int n = 0; n < h1->GetYaxis()->GetNbins(); n++) {
						if(h1->GetBinContent(m, n) != h2->GetBinContent(m, n)) {
							cout << "Compare " << h1->GetName() << " and " << h2->GetName() << endl;
							cout << "h1->GetBinContent(m, n)=" << h1->GetBinContent(m, n) << endl;
							cout << "h2->GetBinContent(m, n)=" << h2->GetBinContent(m, n) << endl;
						}
					}
				}
			}
		}
	}
}
