#include "MyDetectorConstruction.hh"
#include "MySensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

MyDetectorConstruction::MyDetectorConstruction() : G4VUserDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* liquidArgon = nist->FindOrBuildMaterial("G4_lAr");
  
  // World volume
  G4double worldSize = 1.0 * m;
  G4Box* worldBox = new G4Box("World", worldSize, worldSize, worldSize); // name and size (half-length)
  G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_Galactic"); // extreme vacuum
  G4LogicalVolume* worldLogical = new G4LogicalVolume(worldBox, worldMaterial, "World");
  G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0, G4ThreeVector(), worldLogical, "World", 0, false, 0);
  
  // Liquid Argon detector volume
  G4double argonSize = 0.6 * m;
  G4Box* argonBox = new G4Box("LiquidArgonBox", argonSize, argonSize, argonSize);
  G4LogicalVolume* argonLogical = new G4LogicalVolume(argonBox, liquidArgon, "LiquidArgonBox");
  new G4PVPlacement(0, G4ThreeVector(), argonLogical, "LiquidArgonBox", worldLogical, false, 0);
  
  // Visualization
  worldLogical->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VisAttributes* argonVisAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.2));
  argonLogical->SetVisAttributes(argonVisAttributes);
  
  // Assign sensitive detector to the argon volume
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  MySensitiveDetector* argonDetector = new MySensitiveDetector("ArgonSD");
  sdManager->AddNewDetector(argonDetector);
  argonLogical->SetSensitiveDetector(argonDetector);
  
  return worldPhysical;
}
