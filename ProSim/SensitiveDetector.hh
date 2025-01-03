#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include <vector>

class SensitiveDetector : public G4VSensitiveDetector {
public:
    SensitiveDetector(const G4String& name);
    virtual ~SensitiveDetector();

    virtual void Initialize(G4HCofThisEvent* hce) override;
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    virtual void EndOfEvent(G4HCofThisEvent* hce) override;

    // Getters for recorded data
    std::vector<std::string> GetParticleType() const { return particleType; }
    std::vector<double> GetMomentumMag() const { return momentumMag; }
    std::vector<double> GetTheta() const { return theta; }
    std::vector<double> GetPhi() const { return phi; }
    std::vector<double> GetBeta() const { return beta; }
    std::vector<double> GetGamma() const { return gamma; }
    std::vector<double> GetTotalEnergy() const { return totalEnergy; }
    std::vector<double> GetPositionX() const { return positionX; }
    std::vector<double> GetPositionY() const { return positionY; }
    std::vector<double> GetPositionZ() const { return positionZ; }
    std::vector<double> GetEnergyDeposited() const { return energyDeposited; }
    std::vector<double> GetdEdx() const { return dEdx; }
    std::vector<double> GetTrackLength() const { return trackLength; }
    std::vector<double> GetTOF() const { return tof; }

private:
    std::vector<std::string> particleType;
    std::vector<double> momentumMag, theta, phi, beta, gamma, totalEnergy;
    std::vector<double> positionX, positionY, positionZ;
    std::vector<double> energyDeposited, dEdx, trackLength, tof;
};

#endif
