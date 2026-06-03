#include "generator.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh" 
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
//#include "runaction.hh"
#include <iostream>
#include <fstream>

//MyPrimaryGenerator::MyPrimaryGenerator(MyRunAction* runAction): fRunAction(runAction)
MyPrimaryGenerator::MyPrimaryGenerator()
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(1); //one primary vertex per event is created
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
}


void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) 
{ 
   // std::ofstream file_stream;
   // file_stream.open ("output.txt");
    
    // Current working settings 
     
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "opticalphoton");
    
    fParticleGun->SetParticleDefinition(particle);
    
    
    
        // setting random polarization angle 
    G4double angle = G4UniformRand() * CLHEP::twopi;
    
    G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
    
    G4ThreeVector normal = kphoton.orthogonal();
    
    G4ThreeVector perp = kphoton.cross(normal);
    
    G4ThreeVector polarization =
    std::cos(angle) * normal +
    std::sin(angle) * perp;
    
    fParticleGun->SetParticlePolarization(polarization);
 //   G4double wavelength = fRunAction->GetScanWavelength();

    //G4double energy = (h_Planck*c_light)/wavelength;
    
   // G4double energy = 1239.84/wavelength;

   // fParticleGun->SetParticleEnergy(energy*eV);
    //std::ostringstream stream; 
   // stream << energy; 
  //  file_stream << stream.str() << "\n";

   // file_stream.close();

   // G4cout << "Wavelength : "<< wavelength / nm << " nm" << G4endl;
    fParticleGun->SetParticleEnergy(3.0*eV); // single energy for now but will make a range later 
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.));
    
    G4double width = 12.0*mm;
    G4double height = 20.00*mm;
    
    G4double x = (G4UniformRand() - 0.5)*width;
    G4double z = (G4UniformRand() - 0.5)*height;
    
    
    fParticleGun->SetParticlePosition(G4ThreeVector(x,8.75*cm,z));
    fParticleGun->GeneratePrimaryVertex(anEvent); 


    
    
    
    //RegisterPhysics(new G4OpticalPhysics());
    
    

/*  Beam of protons at 100MeV from tutorial but not what I want rn
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="proton";
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");
    
    G4ThreeVector pos(0.,10.,0.);
    G4ThreeVector mom(0.,-1.,0.);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100.*GeV);
    fParticleGun->SetParticleDefinition(particle);
    
    
    fParticleGun->GeneratePrimaryVertex(anEvent); 
*/
} 
