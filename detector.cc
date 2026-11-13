#include "detector.hh" 
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
#include "event.hh" 

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}



G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4int PhotonHitCount = 0;
   
    G4Track *track= aStep->GetTrack();
    G4ThreeVector dir = track->GetMomentumDirection();

    if(track->GetDefinition() != G4OpticalPhoton::Definition())
       return false;
    
    
    bool isPhoton = (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() || 
                     track->GetDefinition() == G4Gamma::GammaDefinition());
    if (!isPhoton) return false;   
    
    if(dir.y() > 0)
    { 
        G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
        if(preStepPoint->GetStepStatus() == fGeomBoundary)
        {       
            G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
            G4ThreeVector posPhoton = preStepPoint->GetPosition();
            //G4cout << "Photon position: " << posPhoton << G4endl;
            track->SetTrackStatus(fStopAndKill);
            
            const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
            
            G4int copyNo = touchable->GetCopyNumber();
            //G4cout << " Copy number: " << copyNo << G4endl;
            
            G4VPhysicalVolume * physVol = touchable->GetVolume();
            G4ThreeVector posDetector = physVol->GetTranslation();
            
            //G4cout <<"Detector position: " << posDetector <<G4endl;
          //  G4int copyNo  = touchable->GetVolume(0);
            
            G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
            
           // G4cout << "Events: " << evt << G4endl;
            
           // Get number of hits that detector sees 
           
           auto * runManager = G4RunManager::GetRunManager();
           auto* userEventAction = runManager->GetUserEventAction();
//           auto * eventAction =  //static_cast<const MyEventAction*>(runManager->GetUserEventAction());
            
            
            
           if (userEventAction) {
              
               auto* myEventAction = const_cast<MyEventAction*>(static_cast<const MyEventAction*>(userEventAction));
            myEventAction->AddPhotonHit();
            PhotonHitCount++ ;
          //  std::cout << "[EVENT TIME PHOTON HIT]: " << PhotonHitCount++ <<G4endl;
               //const_cast<MyEventAction*>(eventAction)->AddPhotonHit();
           }
            
            G4AnalysisManager *man = G4AnalysisManager::Instance();
            man->FillNtupleIColumn(0,evt);
            man->FillNtupleDColumn(1,posDetector[0]);
            man->FillNtupleDColumn(2,posDetector[1]);
            man->FillNtupleDColumn(3,posDetector[2]);
            man->FillNtupleIColumn(0, PhotonHitCount);
            man->AddNtupleRow(0);
            
        } 
    
    }
    return true;

}

/*if(preStepPoint->GetStepStatus() == fGeomBoundary)
        {       
            G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
            G4ThreeVector posPhoton = preStepPoint->GetPosition();
            G4cout << "Photon position: " << posPhoton << G4endl;
            track->SetTrackStatus(fStopAndKill);
        } */
        
/*
        G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
        G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
        G4ThreeVector posPhoton = preStepPoint->GetPosition();
        G4cout << "Photon position: " << posPhoton << G4endl;
        track->SetTrackStatus(fStopAndKill);        
  */      
