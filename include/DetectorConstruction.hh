// DetectorConstruction.hh
#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction() = default;
    virtual ~DetectorConstruction() = default;

    virtual G4VPhysicalVolume* Construct() override;
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

private:
    G4LogicalVolume* fScoringVolume = nullptr;
};

#endif


