#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fWavelength = 2 ;
    
}

MyEventAction::~MyEventAction()
{}

//G4double MyEventAction::ScanWavelength()
//{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{

}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4cout <<" Wavelength: "<< fWavelength << G4endl;

    G4AnalysisManager* man = G4AnalysisManager::Instance();
    //man->FillNtup...
    //man->AddNtupleRow(2)
}