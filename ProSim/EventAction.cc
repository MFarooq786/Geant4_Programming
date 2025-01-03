#include "EventAction.hh"
#include "RunAction.hh"
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4Event.hh"

// Constructor and Destructor
MyEventAction::MyEventAction(MyRunAction* runAction)
    : G4UserEventAction(), fRunAction(runAction) {}

MyEventAction::~MyEventAction() {}

// Empty implementation for BeginOfEventAction
void MyEventAction::BeginOfEventAction(const G4Event* /*event*/) {
    // No specific action for now
}

// Implementation for EndOfEventAction
void MyEventAction::EndOfEventAction(const G4Event* event) {
    // Get the sensitive detector
    SensitiveDetector* sd = static_cast<SensitiveDetector*>(
        G4SDManager::GetSDMpointer()->FindSensitiveDetector("SensitiveDetector"));
    
    // If the sensitive detector exists, pass its data to RunAction
    if (sd) {
        fRunAction->FillStepData(
            event->GetEventID(),
            sd->GetParticleType(),             // Particle type
            sd->GetMomentumMag(),              // Momentum magnitude
            sd->GetTheta(),                    // Polar angle
            sd->GetPhi(),                      // Azimuthal angle
            sd->GetBeta(),                     // Beta
            sd->GetGamma(),                    // Gamma
            sd->GetTotalEnergy(),              // Total energy
            sd->GetPositionX(),                // X position
            sd->GetPositionY(),                // Y position
            sd->GetPositionZ(),                // Z position
            sd->GetEnergyDeposited(),          // Energy deposited
            sd->GetdEdx(),                     // Stopping power
            sd->GetTrackLength(),              // Track length
            sd->GetTOF()                       // Time of flight
        );
    }
}
