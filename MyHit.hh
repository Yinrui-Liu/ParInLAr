#ifndef MYHIT_HH
#define MYHIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"

class MyHit : public G4VHit {
public:
  MyHit();
  virtual ~MyHit();
  
  void SetPosition(const G4ThreeVector& pos) { fPosition = pos; }
  void SetEnergyDep(G4double edep) { fEnergyDep = edep; }
  void SetTime(G4double time) { fTime = time; }
  
  const G4ThreeVector& GetPosition() const { return fPosition; }
  G4double GetEnergyDep() const { return fEnergyDep; }
  G4double GetTime() const { return fTime; }
  
private:
  G4ThreeVector fPosition;
  G4double fEnergyDep;
  G4double fTime;
};

#endif
