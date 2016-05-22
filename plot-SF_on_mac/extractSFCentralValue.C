// This script extracts the SF_CentralValue from the variations_reference.root
// There are 18 SF_CentralValue histograms for a working point.
// 2
// 3
// 3

#include <TROOT.h>
#include <TObjArray.h>
#include <TFile.h>
//#include <TIter.h>
#include <TKey.h>
#include <TString.h>

#include <iostream>
using namespace std;

void extractSFCentralValue()
{
    TObjArray Hist(0);
    
    TFile *f1 = TFile::Open("/Users/ytshen/Desktop/MC15b_variations_reference.root");
    TIter next1(f1->GetListOfKeys());
    TKey *key1;
    while ((key1 = (TKey*)next1())) {
        TString keyName1 = key1->GetName();
        if (keyName1.Contains("SF_CentralValue") &&
            (!keyName1.Contains("LooseLLH_d0z0_v8")) &&
            (!keyName1.Contains("LooseLLHMC15_v8"))) {
            cout << keyName1 << endl;
            Hist.Add(f1->Get(keyName1));
        }
    }
    cout << Hist.GetEntries() << endl;
    
    TFile fout("SFCentralValue_variations.root","recreate");
    Hist.Write();
    fout.Close();
}
/*
void addHistograms()
{
    TFile *f1 = TFile::Open("SFCentralValue_variations.root");
    TH2F *h = 0;
    TIter next1(f1->GetListOfKeys());
    TKey *key1;
    while ((key1 = (TKey*)next1())) {
        TString keyName1 = key1->GetName();
    }
}
*/