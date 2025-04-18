// DetectorConstruction.cc
#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {
    auto nist = G4NistManager::Instance();

    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");

    G4double worldSize = 2.0 * m;
    auto solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
    auto logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    auto physWorld = new G4PVPlacement(nullptr, {}, logicWorld, "World", nullptr, false, 0);

    auto solidTarget = new G4Tubs("Target", 0., 15.*cm, 30.*cm, 0., 360.*deg);
    auto logicTarget = new G4LogicalVolume(solidTarget, tungsten, "Target");
    new G4PVPlacement(nullptr, {}, logicTarget, "Target", logicWorld, false, 0);

    fScoringVolume = logicTarget;

    return physWorld;
}
