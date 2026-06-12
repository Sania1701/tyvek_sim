#include "run.hh" 
#include "G4AnalysisManager.hh"

MyRunAction::MyRunAction()
{    

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->CreateNtuple("Hits", "Hits");
    
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    
    man->FinishNtuple(0);}


MyRunAction::~MyRunAction()
{}



void MyRunAction::BeginOfRunAction(const G4Run* run)
{

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    G4int runID =  run->GetRunID();
    
    std::stringstream strRunID;
    
    strRunID << runID;
    
    const G4String& fileName = "output"+strRunID.str()+".root" ;
    
    man->OpenFile(fileName);

    

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetVerboseLevel(1);
    man->Write(); // write before close or root files will be sad
    
    man->CloseFile();


}

