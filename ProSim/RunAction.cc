#include "RunAction.hh"
#include "G4SystemOfUnits.hh"

MyRunAction::MyRunAction()
    : rootFile(nullptr), tree(nullptr), eventID(0) {}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run* /*run*/) {
    // Initialize ROOT file and tree
    rootFile = new TFile("output.root", "RECREATE");
    tree = new TTree("SimulationTree", "Kinematics Data");

    tree->Branch("EventID", &eventID, "EventID/I");
    tree->Branch("ParticleType", &particleType);
    tree->Branch("MomentumMag", &momentumMag);
    tree->Branch("Theta", &theta);
    tree->Branch("Phi", &phi);
    tree->Branch("Beta", &beta);
    tree->Branch("Gamma", &gamma);
    tree->Branch("TotalEnergy", &totalEnergy);
    tree->Branch("PositionX", &positionX);
    tree->Branch("PositionY", &positionY);
    tree->Branch("PositionZ", &positionZ);
    tree->Branch("EnergyDeposited", &energyDeposited);
    tree->Branch("dEdx", &dEdx);
    tree->Branch("TrackLength", &trackLength);
    tree->Branch("TOF", &tof);

    // Initialize CSV file
    csvFile.open("output.csv");
    csvFile << "EventID,ParticleType,MomentumMag,Theta,Phi,Beta,Gamma,TotalEnergy,"
               "PositionX,PositionY,PositionZ,EnergyDeposited,dEdx,TrackLength,TOF\n";
}

void MyRunAction::EndOfRunAction(const G4Run* /*run*/) {
    // Write ROOT file and close CSV file
    rootFile->Write();
    rootFile->Close();
    csvFile.close();
}

void MyRunAction::FillStepData(int id, const std::vector<std::string>& pType,
                               const std::vector<double>& pMag, const std::vector<double>& th,
                               const std::vector<double>& ph, const std::vector<double>& b,
                               const std::vector<double>& g, const std::vector<double>& tEnergy,
                               const std::vector<double>& posX, const std::vector<double>& posY,
                               const std::vector<double>& posZ, const std::vector<double>& eDep,
                               const std::vector<double>& dedX, const std::vector<double>& tLength,
                               const std::vector<double>& tOF) {
    // Assign data to member variables
    this->eventID = id;
    this->particleType = pType;
    this->momentumMag = pMag;
    this->theta = th;
    this->phi = ph;
    this->beta = b;
    this->gamma = g;
    this->totalEnergy = tEnergy;
    this->positionX = posX;
    this->positionY = posY;
    this->positionZ = posZ;
    this->energyDeposited = eDep;
    this->dEdx = dedX;
    this->trackLength = tLength;
    this->tof = tOF;

    // Fill ROOT tree
    tree->Fill();

    // Write data to CSV file
    for (size_t i = 0; i < pType.size(); ++i) {
        csvFile << id << "," << pType[i] << "," << pMag[i] << "," << th[i] << "," << ph[i] << ","
                << b[i] << "," << g[i] << "," << tEnergy[i] << "," << posX[i] << ","
                << posY[i] << "," << posZ[i] << "," << eDep[i] << "," << dedX[i] << ","
                << tLength[i] << "," << tOF[i] << "\n";
    }
}
