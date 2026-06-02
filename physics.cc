#include "physics.hh" 
#include "G4OpticalPhysics.hh"
#include "RunAction.hh"

MyPhysicsList::MyPhysicsList()
{

    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());

}

MyPhysicsList::~MyPhysicsList()
{}
