#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <string>

class MyRunAction : public G4UserRunAction {
public:
    MyRunAction();
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run* run) override;
    virtual void EndOfRunAction(const G4Run* run) override;

    TTree* GetTree() const { return tree; }
    std::ofstream& GetCsvFile() { return csvFile; }

    void FillStepData(int eventID, const std::vector<std::string>& particleType,
                      const std::vector<double>& momentumMag, const std::vector<double>& theta,
                      const std::vector<double>& phi, const std::vector<double>& beta,
                      const std::vector<double>& gamma, const std::vector<double>& totalEnergy,
                      const std::vector<double>& posX, const std::vector<double>& posY,
                      const std::vector<double>& posZ, const std::vector<double>& edep,
                      const std::vector<double>& dedx, const std::vector<double>& trackLength,
                      const std::vector<double>& tof);

private:
    TFile* rootFile;
    TTree* tree;
    std::ofstream csvFile;

    // Variables for ROOT branches
    int eventID;
    std::vector<std::string> particleType;
    std::vector<double> momentumMag, theta, phi, beta, gamma, totalEnergy;
    std::vector<double> positionX, positionY, positionZ;
    std::vector<double> energyDeposited, dEdx, trackLength, tof;
};

#endif
