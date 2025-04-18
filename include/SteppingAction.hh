// SteppingAction.hh
#ifndef STEPPING_ACTION_HH
#define STEPPING_ACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction(G4LogicalVolume* scoringVolume);
    ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
private:
    G4LogicalVolume* fScoringVolume = nullptr;

};



#endif


