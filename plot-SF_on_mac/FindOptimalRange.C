#include <TH1.h>

void FindOptimalRange(Float_t& high, Float_t& low, TH1F* h1, TH1F* h2 = NULL)
{
	high = -99;
	low  = 99;

	float content;
	float error;

	// h1
	for (int b = 1; b < h1->GetXaxis()->GetNbins(); b++){
		content = h1->GetBinContent(b);
		error   = h1->GetBinError(b);
		// exclude the very large unreasonable vlaue
		if (error > 10000.) continue;
		if (content + error > high)
			high = content + error;
		if (content - error < low)
			low = content - error;
	}

	// h2
	if (h2 != NULL) {
		for (int b = 1; b < h2->GetXaxis()->GetNbins(); b++) {
			content = h2->GetBinContent(b);
			error   = h2->GetBinError(b);
			// exclude the very large unreasonable vlaue
			if (error > 10000.) continue;
			if(content + error > high)
				high = content + error;
			if(content - error < low)
				low = content - error;
		}
	}

	// Keep the (high - low) = 50% of the figure.
	// Keep 40% space at the top of plots and 10% space at the bottom of the plots.
	float plot_y_size = (high - low) / 0.5;
	high += plot_y_size * 0.4;
	low  -= plot_y_size * 0.1;
}
