#ifndef RUNACTION_HH
#define RUNACTION_HH


#include "G4UserRunAction.hh"
#include "globals.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    void SetScanWavelength(G4double wl) { fWL = wl; }
    G4double GetScanWavelength() const { return fWL; }

private:
    G4double fWL = 500.*nm;   // important: initialise it
};

#endif
