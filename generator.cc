#include "generator.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh" 
#include "RunAction.hh"


MyPrimaryGenerator::MyPrimaryGenerator(RunAction* runAction)
: fRunAction(runAction)
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(1); //one primary vertex per event is created
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "opticalphoton");
    fParticleGun->SetParticleDefinition(particle);

    
    
     
    
}
/*
G4double MyPrimaryGenerator::G4GaussianRand()
{
    static const G4double twopi = 2.0 * CLHEP::pi;

    G4double u1 = G4UniformRand();
    G4double u2 = G4UniformRand();

    return std::sqrt(-2.0 * std::log(u1)) * std::cos(twopi * u2);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePhotonForScan(G4double lambda0_nm)
{
    // slit bandwidth (instrument resolution)
    G4double FWHM = 1.0*nm;
    G4double sigma = FWHM / 2.355;

    // Gaussian sampling
    G4double lambda =
        lambda0_nm + sigma * G4GaussianRand();

    // safety clamp (important in UV-Vis edges)
    if (lambda < 180*nm) lambda = 180*nm;
    if (lambda > 900*nm) lambda = 900*nm;

    // convert to energy
    const G4double hc = 1239.841984; // eV·nm
    G4double E = (hc / (lambda/nm)) * eV;

    particleGun->SetParticleEnergy(E);
}
*/
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) 
{ 
    
    G4double wl = fRunAction->GetScanWavelength();


    G4double energy = (1240.0 / (wl/nm)) * eV;

    fParticleGun->SetParticleEnergy(energy);
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 87.5*mm, 0));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, -1, 0));

    fParticleGun->GeneratePrimaryVertex(anEvent);
    
   
            
 
    
    // setting random polarization angle 
    G4double angle = G4UniformRand() * CLHEP::twopi;
    
    G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
    
    G4ThreeVector normal = kphoton.orthogonal();
    
    G4ThreeVector perp = kphoton.cross(normal);
    
    G4ThreeVector polarization =
    std::cos(angle) * normal +
    std::sin(angle) * perp;
    
    fParticleGun->SetParticlePolarization(polarization);
    
    
    
    
    
    
    
    
    
    
    /*
    RegisterPhysics(new G4OpticalPhysics());
    
    fParticleGun->SetParticleDefinition(G4OpticalPhoton::Definition());
    
    fParticleGun->SetParticleEnergy(3.0*eV); // single energy for now but will make a range later 
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,1.,0.));
    
    fParticleGun->SetParticlePosition(G4ThreeVector(0.,-8.75*cm,0.));
    */

    G4double width = 12.0*mm;
    G4double height = 20.00*mm;
    
    G4double x = (G4UniformRand() - 0.5)*width;
    G4double z = (G4UniformRand() - 0.5)*height;
   
   // fParticleGun->SetParticlePosition(G4ThreeVector(0.,8.75*cm,0.));
    
    fParticleGun->SetParticlePosition(G4ThreeVector(x,8.75*cm,z));
    fParticleGun->GeneratePrimaryVertex(anEvent); 


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
