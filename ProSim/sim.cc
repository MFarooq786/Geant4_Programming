#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "construction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "action.hh"
#include "physics.hh"

int main(int argc, char** argv) {
    // Create the run manager
    G4RunManager* runManager = new G4RunManager();

    // Initialize user-defined classes
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    // Initialize the G4 kernel
    runManager->Initialize();

    // Visualization manager
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // User interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Open a visualization session
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    // Visualization commands
    UImanager->ApplyCommand("/run/initialize");                 // Ensure geometry is initialized
    UImanager->ApplyCommand("/vis/open OGL");                   // Open OpenGL viewer
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");                 // Draw the volume
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");

    // Start interactive session
    ui->SessionStart();

    // Cleanup
    delete ui;
    delete visManager;
    delete runManager;

    return 0;
}
