#include "RunAction.hh"
#include "G4Run.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
: G4UserRunAction()
{
    fWL = 500.*nm; // default wavelength
}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*)
{
    G4cout << "\n--- Run starting ---\n";
    G4cout << "Wavelength = " << fWL/nm << " nm\n";
}

void RunAction::EndOfRunAction(const G4Run*)
{
    G4cout << "--- Run finished ---\n";
}
