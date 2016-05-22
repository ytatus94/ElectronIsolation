#include <TH1.h>
#include <TH2.h>

void fixHistogramError(TH1F *h1, TH1F *herr)
{
	for (Int_t ik = 1; ik <= h1->GetXaxis()->GetNbins(); ik++) {
		float err = herr->GetBinContent(ik);
		h1->SetBinError(ik, err);
	}
}
/*
void fix1DHistogramError(TH1F *h1,TH1F *herr)
{
	for (int ik = 1; ik < h1->GetSize(); ik++) {
		float err = herr->GetBinContent(ik);
		h1->SetBinError(ik, err);
	}
}

void fix2DHistogramError(TH2F *h1,TH2F *herr)
{
	for (int ik = 1; ik < h1->GetSize(); ik++) {
		float err = herr->GetBinContent(ik);
		h1->SetBinError(ik, err);
	}
}
*/
