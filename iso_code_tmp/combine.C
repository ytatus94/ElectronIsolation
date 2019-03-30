// This is used to combine two variations_reference.root files.
// Select TightLLH_d0z0, MediumLLH_d0z0, and LooseAndBLayerLLH_d0z0 from variations_reference_d0z0.root.
// Select TightLLHMC15, MediumLLHMC15, and LooseAndBLayerLLHMC15 from variations_reference.root
//
#include <TROOT.h>
#include <TObjArray.h>
#include <TFile.h>
//#include <TIter.h>
#include <TKey.h>
#include <TString.h>

#include <iostream>
using namespace std;

void combine(){

	TObjArray Hist(0);

	TFile *f1 = TFile::Open("AF2d0z0_variations_reference.root");
	TIter next1(f1->GetListOfKeys());
	TKey *key1;
	int i = 0;
	while ((key1 = (TKey*)next1())) {
		TString keyName1 = key1->GetName();
		//cout << keyName1 << endl;
		//i++;

		//if (keyName1.Contains("isolPhFixed")) {
		//	cout << keyName1 << endl;
		//	i++;
		//}

		// find the isolation WPs and put in the the array
		if (!keyName1.Contains("isolPhFixedCut"))
			Hist.Add(f1->Get(keyName1));
	}
	//cout << Hist.GetEntries() << endl;
	//cout << i << endl;

	TFile *f2 = TFile::Open("AF2_variations_reference.root");
	TIter next2(f2->GetListOfKeys());
	TKey *key2;
	int j = 0;
	while ((key2 = (TKey*)next2())) {
		TString keyName2 = key2->GetName();
		//cout << keyName2 << endl;
		//j++;

		// find the photon isolation WPs and put in the array
		if (keyName2.Contains("isolPhFixedCut")) {
			//cout << keyName2 << endl;
			//j++;
			Hist.Add(f2->Get(keyName2));
		}

		//if (!keyName2.Contains("isolPhFixed"))
			//Hist.Add(f1->Get(keyName));
	}
	cout << Hist.GetEntries() << endl;
	//cout << j << endl;

	TFile fout("AF2_variations_reference_combined.root","recreate");
	Hist.Write();
	fout.Close();	
}
