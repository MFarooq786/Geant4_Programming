#include "construction.hh"
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"

MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    // World volume
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* solidWorld = new G4Box("solidWorld", 1.0 * m, 1.0 * m, 1.0 * m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);

    // Detector volume
    G4Material* detectorMat = nist->FindOrBuildMaterial("G4_Si");
    G4Box* solidDetector = new G4Box("solidDetector", 0.5 * m, 0.5 * m, 0.1 * m);
    G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, detectorMat, "logicDetector");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.5 * m), logicDetector, "physDetector", logicWorld, false, 0, true);

    // Attach sensitive detector
    SensitiveDetector* sd = new SensitiveDetector("SensitiveDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    logicDetector->SetSensitiveDetector(sd);

    return physWorld;
}
