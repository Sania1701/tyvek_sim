#include "event.hh"
#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"
#include "run.hh"

MyEventAction::MyEventAction(MyRunAction* runAction)    
      : G4UserEventAction(),
      fRunAction(runAction),
      fPhotonCount(0)
{
    //fWavelength = 2 ;
   
}

MyEventAction::~MyEventAction()
{}

//G4double MyEventAction::ScanWavelength()
//{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{

    fPhotonCount = 0;

}

void MyEventAction::EndOfEventAction(const G4Event* event)
{
    //G4cout <<" Wavelength: "<< fWavelength << G4endl;
 
  //  G4cout << "Total det hits : " << fPhotonCount << G4endl;
  
  //  std::cout << ">>> [EVENT END] Hits: " << fPhotonCount << " <<<" << std::endl;
    
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    //man->FillNtup...
    //man->AddNtupleRow(2)
    if (fRunAction) {
        fRunAction->AccumulatePhotons(fPhotonCount);
    }
    
}
