// ActionInitialization.cc
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "neutronGlobals.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization() {}
ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new RunAction());

    // Get the scoring volume (tungsten target) from DetectorConstruction
    auto detector = static_cast<const DetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction()
    );
    auto scoringVolume = detector->GetScoringVolume();

    // Pass it to SteppingAction
    SetUserAction(new SteppingAction(scoringVolume));

    // Optional: set verbosity for analysis output
    G4AnalysisManager::Instance()->SetVerboseLevel(1);
}
