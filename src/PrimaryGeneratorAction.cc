// PrimaryGeneratorAction.cc
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1);

    auto particle = G4ParticleTable::GetParticleTable()->FindParticle("proton");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(1.0 * GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -50.*cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    fParticleGun->GeneratePrimaryVertex(event);
}
