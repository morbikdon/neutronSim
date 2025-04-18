// SteppingAction.cc
#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "globals.hh"

SteppingAction::SteppingAction() {}
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
	    neutronCount++;
    }
}
