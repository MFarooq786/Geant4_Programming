#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include <cmath>

SensitiveDetector::SensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name) {}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent* /*hce*/) {
    particleType.clear();
    momentumMag.clear();
    theta.clear();
    phi.clear();
    beta.clear();
    gamma.clear();
    totalEnergy.clear();
    positionX.clear();
    positionY.clear();
    positionZ.clear();
    energyDeposited.clear();
    dEdx.clear();
    trackLength.clear();
    tof.clear();
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* /*history*/) {
    G4Track* track = step->GetTrack();
    const G4ThreeVector& momentum = track->GetMomentum();
    const G4ThreeVector& position = step->GetPostStepPoint()->GetPosition();
    double kineticE = track->GetKineticEnergy();
    double edep = step->GetTotalEnergyDeposit();
    double time = step->GetPostStepPoint()->GetGlobalTime();
    double length = step->GetStepLength();
    double mass = track->GetDefinition()->GetPDGMass();

    // Derived quantities
    double momentumMagnitude = momentum.mag();
    double totalE = std::sqrt(momentumMagnitude * momentumMagnitude + mass * mass);
    double particleBeta = momentumMagnitude / totalE;
    double particleGamma = 1.0 / std::sqrt(1.0 - particleBeta * particleBeta);
    double polarTheta = momentum.theta();
    double azimuthalPhi = momentum.phi();
    double dedx = (length > 0) ? edep / length : 0.0;

    // Store data
    particleType.push_back(track->GetDefinition()->GetParticleName());
    momentumMag.push_back(momentumMagnitude);
    theta.push_back(polarTheta);
    phi.push_back(azimuthalPhi);
    beta.push_back(particleBeta);
    gamma.push_back(particleGamma);
    totalEnergy.push_back(totalE);
    positionX.push_back(position.x());
    positionY.push_back(position.y());
    positionZ.push_back(position.z());
    energyDeposited.push_back(edep);
    dEdx.push_back(dedx);
    trackLength.push_back(length);
    tof.push_back(time);

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*hce*/) {
    // Do nothing; data is handled in EventAction
}
