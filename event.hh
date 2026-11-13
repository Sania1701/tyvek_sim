#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"

#include "run.hh"

class MyEventAction:  public G4UserEventAction
{

public: 
    MyEventAction(MyRunAction* runAction);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    
    void AddPhotonHit() {fPhotonCount++;}
   // G4double ScanWavelength(G4double wlength); //change later to actually scan

private: 
    MyRunAction* fRunAction = nullptr; 
    G4double fWavelength;
    G4int fPhotonCount = 0;


};

#endif
