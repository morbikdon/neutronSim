// SteppingAction.cc
#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "neutronGlobals.hh"


#include "G4LogicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"




SteppingAction::SteppingAction(G4LogicalVolume* scoringVolume): fScoringVolume(scoringVolume){}
SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    auto track = step->GetTrack();
    auto particle = track->GetDefinition();

    if (particle->GetParticleName() == "neutron" && track->GetNextVolume() == nullptr) {
        G4double energy = track->GetKineticEnergy();
        G4AnalysisManager::Instance()->FillH1(0, energy);
    }

    if (track->GetDefinition()->GetParticleName() == "neutron" &&
    	track->GetCurrentStepNumber() == 1) {
	    neutronCountTotal++;
    }

    auto prePoint = step->GetPreStepPoint();
    auto postPoint = step->GetPostStepPoint();

    auto preVolume = prePoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    auto postVolume = postPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // Check if particle is a neutron and it's exiting the target
    if (track->GetDefinition()->GetParticleName() == "neutron") {
        if (preVolume == fScoringVolume && postVolume != fScoringVolume) {
            neutronCount++;

            // Record energy (kinetic energy in MeV)
            G4double energy = track->GetKineticEnergy() / MeV;

            // Record angle (w.r.t. Z axis)
            G4ThreeVector momentum = track->GetMomentumDirection();
            G4double theta = momentum.theta(); // in radians
            G4double theta_deg = theta * 180.0 / CLHEP::pi;

            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillH1(0, energy);
            analysisManager->FillH1(1, theta_deg);
        }
     }

}



