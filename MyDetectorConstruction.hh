#ifndef MYDETECTORCONSTRUCTION_HH
#define MYDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
  MyDetectorConstruction();
  virtual ~MyDetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
};

#endif
