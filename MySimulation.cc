#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "MyDetectorConstruction.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "QGSP_BERT.hh"
#include "MyEventAction.hh"
#include "Randomize.hh"
#include <ctime>

int main() {
  G4Random::setTheEngine(new CLHEP::RanecuEngine); // Use the Ranecu random number engine
  G4Random::setTheSeed(static_cast<long>(time(nullptr)));
  
  G4RunManager* runManager = new G4RunManager; // the default run manager
  runManager->SetUserInitialization(new MyDetectorConstruction()); // Detector construction
  runManager->SetUserInitialization(new QGSP_BERT); // Physics list
  runManager->SetUserAction(new MyPrimaryGeneratorAction()); // Primary generator action
  runManager->SetUserAction(new MyEventAction()); // event action, what about run/step action
  runManager->Initialize();
  
  G4UImanager* UI = G4UImanager::GetUIpointer(); // Get the pointer to the User Interface manager
  UI->ApplyCommand("/run/initialize");
  UI->ApplyCommand("/run/beamOn 1");
  
  delete runManager;
  return 0;
}
