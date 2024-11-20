#include "MyPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() {
  // Create a particle gun with n_particle
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);
  
  // Define particle type (pion) and set its properties
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton"; // e+, pi+, mu+, proton, pi0, gamma, neutron, kaon+
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.)); // Along the z-axis
  fParticleGun->SetParticleMomentum(1.0 * GeV); // momentum
  
  // Set initial position of the particle within the center of the detector
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -0.5 * m)); // Starting near one edge of the box
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction() {
  delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
  std::cout<<"$$$ GeneratePrimaries"<<std::endl;
  fParticleGun->GeneratePrimaryVertex(event);
}
