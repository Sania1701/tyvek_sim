#include <iostream>
#include <fstream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "run.hh"


void print_thing(std::ofstream& output_stream, G4double var)
{
    output_stream << (char) (var) << " "; 
    
}


int main(int argc, char** argv)
{   
    /*
    G4RunManager *runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    
    runManager->Initialize();
    G4UIExecutive *ui = 0;
    */
    
    

    // not batch
    G4RunManager *runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    
    runManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
   

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    UImanager->ApplyCommand("/vis/open OGL");

    UImanager->ApplyCommand("/vis/drawVolume");

    UImanager->ApplyCommand("/vis/viewer/set/style wireframe");
    
    UImanager->ApplyCommand("/vis/viewer/set/upVector 0 0 1");

    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0 0");

    UImanager->ApplyCommand("/tracking/storeTrajectory 1");
    
    UImanager->ApplyCommand("/vis/scene/add/axes 1 1 1 10 cm");

    UImanager->ApplyCommand("/vis/scene/add/trajectories");
    
    UImanager->ApplyCommand("/tracking/storeTrajectory 1");
    
   // UImanager->ApplyCommand("/tracking/verbose 2");

    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");

    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    
   // UImanager->ApplyCommand("/process/optical/boundary/verbose 2");
    
    UImanager->ApplyCommand("/run/beamOn 100");
    
    
    /*
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/upVector 1 0 0");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0 0");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/tracking/storeTrajectory 1");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    */
  
  
  
   // UImanager->ApplyCommand("/control/execute vis.mac");

   
    ui->SessionStart();
   
    
    
    
    return 0;
}
