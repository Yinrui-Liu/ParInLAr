#ifndef MYSENSITIVEDETECTOR_HH
#define MYSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"
#include "G4Step.hh"
#include "MyHit.hh"

class MySensitiveDetector : public G4VSensitiveDetector {
public:
  MySensitiveDetector(const G4String& name);
  virtual ~MySensitiveDetector();
  
  virtual void Initialize(G4HCofThisEvent* hce) override;
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
  
private:
  G4THitsCollection<MyHit>* fHitsCollection;
};

#endif
