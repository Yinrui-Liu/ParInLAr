#include "MySensitiveDetector.hh"
#include "MyHit.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include <iostream>

MySensitiveDetector::MySensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {
  collectionName.insert("MyHitCollection");
}

MySensitiveDetector::~MySensitiveDetector() {}

void MySensitiveDetector::Initialize(G4HCofThisEvent* hce) {
  fHitsCollection = new G4THitsCollection<MyHit>(SensitiveDetectorName, "MyHitCollection");
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID("MyHitCollection");
  hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
  if (!step) return false;
  
  G4double energyDep = step->GetTotalEnergyDeposit();
  if (energyDep <= 0.) return false;
  
  G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
  G4double time = step->GetPreStepPoint()->GetGlobalTime(); // time (ns) since the event starts
  MyHit* hit = new MyHit();
  hit->SetPosition(position);
  hit->SetEnergyDep(energyDep);
  hit->SetTime(time);
  fHitsCollection->insert(hit);
  //G4cout<<"## "<<energyDep<<"\t"<<time<<G4endl;
  return true;
}
