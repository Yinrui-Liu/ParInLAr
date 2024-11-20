#include "MyHit.hh"

MyHit::MyHit() : G4VHit() {
  fPosition = G4ThreeVector(); // Default: (0, 0, 0)
  fEnergyDep = 0.0;
  fTime = 0.0;
}

MyHit::~MyHit() {}
