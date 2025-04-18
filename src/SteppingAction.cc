// SteppingAction.cc
#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "neutronGlobals.hh"

#include "G4LogicalVolume.hh"
#include "globals.hh"

SteppingAction::SteppingAction(G4LogicalVolume* scoringVolume)
: fScoringVolume(scoringVolume) {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    // Guard: return early if scoring volume is not set
    if (!fScoringVolume) return;

    auto track = step->GetTrack();
    auto particle = track->GetDefinition();

    // Fill histogram for all neutrons that leave the geometry (i.e., killed)
    if (particle->GetParticleName() == "neutron" && track->GetNextVolume() == nullptr) {
        G4double energy = track->GetKineticEnergy();
        G4AnalysisManager::Instance()->FillH1(0, energy);
    }

    // Count all neutrons created (step 1 = creation step)
    if (particle->GetParticleName() == "neutron" &&
        track->GetCurrentStepNumber() == 1) {
        neutronCountTotal++;
    }

    // Get pre and post step volumes
    auto prePoint = step->GetPreStepPoint();
    auto postPoint = step->GetPostStepPoint();

    auto preVolume = prePoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // SAFELY check postVolume (may be nullptr at world boundary)
    G4LogicalVolume* postVolume = nullptr;
    if (postPoint->GetTouchableHandle()->GetVolume()) {
        postVolume = postPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    }

    // Count only neutrons that exit the tungsten target
    if (particle->GetParticleName() == "neutron") {
        if (preVolume == fScoringVolume && postVolume != fScoringVolume) {
            neutronCount++;

            // Record energy (MeV)
            G4double energy = track->GetKineticEnergy() / MeV;

            // Record angle (w.r.t. beamline Z axis)
            G4ThreeVector momentum = track->GetMomentumDirection();
            G4double theta = momentum.theta(); // radians
            G4double theta_deg = theta * 180.0 / CLHEP::pi;

            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillH1(0, energy);     // Energy histogram
            analysisManager->FillH1(1, theta_deg);  // Angle histogram
        }
    }
}
