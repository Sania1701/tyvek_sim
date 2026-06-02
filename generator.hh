#ifndef GENERATOR_HH
#define GENERATOR_HH 

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh" 
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4OpticalPhoton.hh"
#include "RunAction.hh"
#define G4UniformRand() CLHEP::HepRandom::getTheEngine()->flat()

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public: 
    MyPrimaryGenerator(RunAction* runAction);
    ~MyPrimaryGenerator();
    
    virtual void GeneratePrimaries(G4Event*);
    
private: 
    G4ParticleGun *fParticleGun;
    RunAction* fRunAction;
 
};

#endif 
