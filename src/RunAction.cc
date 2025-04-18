// RunAction.cc
#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction() {}
RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysis = G4AnalysisManager::Instance();
    analysis->OpenFile("neutron_output.root");
    // Histogram 0: energy in MeV
    analysis->CreateH1("NeutronEnergy", "Energy of escaping neutrons", 100, 0., 100.); 

    // Histogram 1: angle in degrees
    analysis->CreateH1("NeutronAngle", "Angle of escaping neutrons", 180, 0., 180.);


}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysis = G4AnalysisManager::Instance();
    analysis->Write();
    analysis->CloseFile();
}
