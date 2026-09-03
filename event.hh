#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"

#include "run.hh"

class MyEventAction:  public G4UserEventAction
{

public: 
    MyEventAction(MyRunAction*);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
   // G4double ScanWavelength(G4double wlength); //change later to actually scan

private: 
    G4double fWavelength;


};

#endif