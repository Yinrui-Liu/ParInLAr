#ifndef MYPRIMARYGENERATORACTION_HH
#define MYPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  MyPrimaryGeneratorAction();
  virtual ~MyPrimaryGeneratorAction();
  
  virtual void GeneratePrimaries(G4Event* event) override;
  
private:
  G4ParticleGun* fParticleGun;
};

#endif
