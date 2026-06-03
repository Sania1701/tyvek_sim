#include "run.hh" 
#include "G4AnalysisManager.hh"

MyRunAction::MyRunAction()
{}


MyRunAction::~MyRunAction()
{}



void MyRunAction::BeginOfRunAction(const G4Run*)
{

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    const G4String& fileName = "output.root" ;
    
    man->OpenFile(fileName);
    
    man->CreateNtuple("Hits", "Hits");
    
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    
    man->FinishNtuple(0);
    

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetVerboseLevel(1);
    man->Write(); // write before close or root files will be sad
    
    man->CloseFile();


}

