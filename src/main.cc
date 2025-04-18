#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "neutronGlobals.hh"

#ifndef NEUTRONGLOBALS_HH
#error "neutronGlobals.hh is not included!"
#endif

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1)
        ui = new G4UIExecutive(argc, argv);

    auto runManager = G4RunManagerFactory::CreateRunManager();

    runManager->SetUserInitialization(new DetectorConstruction());
    G4PhysListFactory factory;
    runManager->SetUserInitialization(factory.GetReferencePhysList("FTFP_BERT"));
    runManager->SetUserInitialization(new ActionInitialization());

    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    runManager->Initialize();

    auto UImanager = G4UImanager::GetUIpointer();

    if (argc > 1) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    if (ui) {
        ui->SessionStart();
        delete ui;
    }
    G4cout << ">>> Total number of neutrons produced: " << neutronCountTotal.load() << G4endl;
    G4cout << ">>> Total number of neutrons that was able to excape from the target: " << neutronCount.load() << G4endl;


    delete visManager;
    delete runManager;
    return 0;
}
