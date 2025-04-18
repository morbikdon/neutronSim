// RunAction.cc
#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction() {}
RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysis = G4AnalysisManager::Instance();
    analysis->OpenFile("neutron_output");
    analysis->CreateH1("neutron_energy", "Escaping Neutron Energy", 100, 0., 100*MeV);
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysis = G4AnalysisManager::Instance();
    analysis->Write();
    analysis->CloseFile();
}
