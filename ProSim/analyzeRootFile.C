#include <TFile.h>
#include <TTree.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TH1F.h>

void analyzeRootFile() {
    // Open the ROOT file
    TFile *file = TFile::Open("output.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Cannot open ROOT file!" << std::endl;
        return;
    }

    // Access the tree
    TTree *tree = (TTree*)file->Get("SimulationTree");
    if (!tree) {
        std::cerr << "Error: Cannot find TTree 'SimulationTree'!" << std::endl;
        file->Close();
        return;
    }

    // Variables to hold data from branches
    std::vector<double> *positionX = nullptr;
    std::vector<double> *dEdx = nullptr;

    // Set branch addresses
    tree->SetBranchAddress("PositionX", &positionX);
    tree->SetBranchAddress("dEdx", &dEdx);

    // Create histograms and canvas
    TCanvas *canvas1 = new TCanvas("canvas1", "dEdx vs PositionX", 800, 600);
    TH2F *scatterPlot = new TH2F("scatterPlot", "dEdx vs PositionX;PositionX;dEdx",
                                 100, -1.0, 1.0, 100, 0, 1.0);

    TCanvas *canvas2 = new TCanvas("canvas2", "Projection of PositionX", 800, 600);
    TH1F *histPositionX = new TH1F("histPositionX", "Projection of PositionX;PositionX;Count",
                                   100, -1.0, 1.0);

    // Fill histograms
    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);

        // Fill scatter plot and histogram
        for (size_t j = 0; j < positionX->size(); ++j) {
            scatterPlot->Fill((*positionX)[j], (*dEdx)[j]);
            histPositionX->Fill((*positionX)[j]);
        }
    }

    // Draw scatter plot
    canvas1->cd();
    scatterPlot->Draw("COLZ");
    canvas1->SaveAs("scatter_dEdx_vs_PositionX.png");

    // Draw projection histogram
    canvas2->cd();
    histPositionX->Draw();
    canvas2->SaveAs("hist_PositionX.png");

    // Cleanup
    delete canvas1;
    delete canvas2;
    delete scatterPlot;
    delete histPositionX;
    file->Close();
}
