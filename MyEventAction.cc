#include "MyEventAction.hh"
#include "MyHit.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsCollection.hh"

MyEventAction::MyEventAction() {
  fOutputFile.open("output.txt", std::ios::out);
}

MyEventAction::~MyEventAction() {
  fOutputFile.close();
}

void MyEventAction::BeginOfEventAction(const G4Event* event) {
  G4int eventNb = event->GetEventID();
  G4cout << "$$$ Begin of event " << eventNb << G4endl;
  fOutputFile << "### X Y Z Energy Time\n";
}

void MyEventAction::EndOfEventAction(const G4Event* event) {
  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if (!hce) return;
  
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID("ArgonSD/MyHitCollection");
  auto hitsCollection = static_cast<G4THitsCollection<MyHit>*>(hce->GetHC(hcID));
  
  if (!hitsCollection) return;
  
  bool primaryInteracted = false; // Flag telling if the primary particle interacts
  
  // Store hits in a vector for sorting
  std::vector<MyHit*> hitVector;
  for (std::size_t i = 0; i < hitsCollection->entries(); ++i) {
    MyHit* hit = (*hitsCollection)[i];
    
    /*// Check if the primary particle has interacted
     const G4Track* track = hit->GetTrack(); // Assuming you store track reference in MyHit
     if (track->GetParentID() == 0) {  // Check if it’s the primary particle
     auto status = track->GetTrackStatus();
     if (status == fStopAndKill || status == fPostponeToNextEvent ||
     track->GetStep()->GetSecondaryInCurrentStep()->size() > 0) {
     primaryInteracted = true;
     }
     }*/
    if (primaryInteracted) break; // Stop saving after interaction
    
    hitVector.push_back(hit);
  }
  
  // Sort hits by time
  //std::sort(hitVector.begin(), hitVector.end(), [](MyHit* a, MyHit* b) {
  //  return a->GetTime() < b->GetTime();
  //});
  
  // Write sorted hits to the output file
  for (const auto& hit : hitVector) {
    G4ThreeVector pos = hit->GetPosition();
    fOutputFile << pos.x() << " " << pos.y() << " " << pos.z() << " "
    << hit->GetEnergyDep() << " " << hit->GetTime() << "\n";
  }
}
