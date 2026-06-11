#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh" 
#include "G4SubtractionSolid.hh"
#include "action.hh" 
#include "generator.hh"
//#include "runaction.hh"
#include "detector.hh"
#include "G4GenericMessenger.hh" 



class MyDetectorConstruction : public G4VUserDetectorConstruction
{ 
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    
    void getEnergy(const G4double input[], const G4double factor,const int N, G4double output[]);
    
    
    virtual G4VPhysicalVolume *Construct();
    
private: 
    G4LogicalVolume *logicDetector;
    virtual void ConstructSDandField(); 

    G4String inCuvMat; 

    G4GenericMessenger* fMessenger;   
    
    G4Box *solidWorld, *solidWater, *solidOuterCuv, *solidPlate, *solidSample, *solidOp, *solidDetector;
    
    G4LogicalVolume *logicWorld, *logicWater, *logicOuterCuv,  *logicAperture, *logicSample ;


};



#endif
