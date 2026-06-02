#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "RunAction.hh"

int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    
    runManager->Initialize();

    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
   

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    
    UImanager->ApplyCommand("/vis/open OGL");

    UImanager->ApplyCommand("/vis/drawVolume");

    UImanager->ApplyCommand("/vis/viewer/set/style wireframe");
    
    UImanager->ApplyCommand("/vis/viewer/set/upVector 0 0 1");

    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0 0");

    UImanager->ApplyCommand("/tracking/storeTrajectory 1");
    
    UImanager->ApplyCommand("/vis/scene/add/axes 1 1 1 10 cm");

    UImanager->ApplyCommand("/vis/scene/add/trajectories");
    
    UImanager->ApplyCommand("/tracking/storeTrajectory 1");
    
    UImanager->ApplyCommand("/tracking/verbose 2");
    
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/default/setLineWidth 10");

    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");

    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    
    UImanager->ApplyCommand("/process/optical/boundary/verbose 2");
    
    for (double wl = 260; wl <= 600; wl += 1)
{
    fRunAction->SetScanWavelength(wl);

    UImanager->ApplyCommand("/run/beamOn 100");
}
    


    UImanager->ApplyCommand("/vis/viewer/flush");
    
    
    
    
    /*
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/upVector 0 0 1");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0 0");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 10 cm");
    UImanager->ApplyCommand("/vis/enable true");
    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
   
    UImanager->ApplyCommand("/tracking/verbose 1");
    UImanager->ApplyCommand("/vis/viewer/set/style wireframe");
    UImanager->ApplyCommand("/run/beamOn 1");
    UImanager->ApplyCommand("/vis/viewer/flush");
   // UImanager->ApplyCommand("/vis/scene/endOfEventAction refresh");
   // UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
   */
   
   
    ui->SessionStart();
   
    return 0;
}
