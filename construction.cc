#include "construction.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4EllipticalTube.hh"
#include <algorithm>
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

MyDetectorConstruction::MyDetectorConstruction()
{

    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
    fMessenger->DeclareProperty("inCuvMat", inCuvMat, "Material in cuvette");
    inCuvMat = "G4_WATER"; // "G4_AIR" ;

   // DefineMaterials();

}

void MyDetectorConstruction::DefineMaterials()
{

    G4cout << "DefineMaterials() called" << G4endl;
    G4cout << "inCuvMat = [" << inCuvMat << "]" << G4endl;
    
    G4NistManager *nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    water = nist->FindOrBuildMaterial(inCuvMat);
    quartz = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    spectralonMaterial = nist->FindOrBuildMaterial("G4_TEFLON");
    G4cout << "water->GetName() = " << water->GetName() << G4endl;

        // Refractive index info
    G4double factor = 1.239841939;
    G4double wavelength[24] = {260., 266., 274.87, 280., 300., 308., 320., 325., 337., 340., 360., 365.48, 380., 400., 404.65, 435.83, 441.6, 447.1, 486.13, 488., 514.5, 532.00, 546.07, 587.56};
    G4double rIndexQuartz[24] = {1.5024, 1.4997, 1.4961, 1.4942, 1.4878, 1.4856, 1.4827, 1.4816, 1.4792, 1.4787, 1.4753, 1.4745, 1.4725, 1.4701, 1.4696, 1.4667, 1.4662, 1.4658, 1.4631, 1.463, 1.4616, 1.4607, 1.4601, 1.4585};
    
   //G4double rIndexQuartz[24] = {1.5024, 1.4997, 1.4961, 1.4942, 1.4878, 1.4856, 7.0,8.05,9.0,9.50,10.0,10.5,11.0,11.5,12.0,12.5,13.0,13.5,14.0,14.5,15.0,15.5,16.0,16.5};
   
   //G4double rIndexQuartz[24] = {10., 10., 10., 10., 10., 10.,10., 10., 10., 10., 10., 10.,10., 10., 10., 10., 10., 10.,10., 10., 10., 10., 10., 10.};
    
  //  G4double rIndexQuartz[24] = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
    
   
    G4double rIndexWater[24] = {
    1.3588,
    1.3569,
    1.354,
    1.353,
    1.349,
    1.348,
    1.3466,
    1.346,
    1.3446,
    1.3442,
    1.3422,
    1.3418,
    1.3406,
    1.339,
    1.3388,
    1.3376,
    1.3373,
    1.3371,
    1.3356,
    1.3355,
    1.3344,
    1.3337,
    1.332,
    1.3325
};


//    G4double rIndexWater[24];
  //  std::fill_n(rIndexWater,24, 1.3325);
    // for Tyvek
    
    G4double reflectivity[24];
    std::fill_n(reflectivity, 24, 1.0);
    
    // For absorber 
   // /*
    //G4double reflectivity[24];
    //std::fill_n(reflectivity,24,0.0);
    
    G4double transmission[24];
    std::fill_n(transmission,24,0.0);
   // */
    
    G4double rIndexAir[24];
    std::fill_n(rIndexAir,24, 1.);
  
 //   G4double rIndexWater[24];
 //   std::fill_n(rIndexWater,24,1.33);
 
    G4double absLengthQuartz[24];
    std::fill_n(absLengthQuartz, 24, 1.*m);
    
    G4double absLengthWater[24];
    std::fill_n(absLengthWater, 24, 100.*m);
    
    G4double absLengthAbsorber[24];
    std::fill_n(absLengthAbsorber, 24, 0.0*m);
    
    G4double energy[24];
  //  getEnergy(wavelength, factor, 24, energy, );
  //  std::cout<< "index 1 check: " << energy[0] << std::endl;
    G4double sortedRIndexQuartz[24];
    G4double sortedRIndexWater[24];
    
    
    getEnergy(wavelength, factor,24, energy, rIndexQuartz,rIndexWater,sortedRIndexQuartz,sortedRIndexWater);
    
    G4double specularlobe[24];
    std::fill_n(specularlobe, 24, 0.0);
    
    G4double specularspike[24];
    std::fill_n(specularspike, 24, 0.0);
    
    G4double backscatter[24];
    std::fill_n(backscatter,24, 0.0);
    
   // G4double lambertian[24];
   // std::fill_n(lambertian, 24, 0.92);
    



    G4MaterialPropertiesTable *mptAir = new G4MaterialPropertiesTable();
    mptAir->AddProperty("RINDEX", energy, rIndexAir,24);
    worldMat->SetMaterialPropertiesTable(mptAir);
    
    G4MaterialPropertiesTable *mptQuartz = new G4MaterialPropertiesTable();
   // mptQuartz->AddProperty("RINDEX", energy, rIndexQuartz, 24);
    mptQuartz->AddProperty("RINDEX", energy, sortedRIndexQuartz, 24);
    mptQuartz->AddProperty("ABSLENGTH", energy, absLengthQuartz ,24);
    quartz->SetMaterialPropertiesTable(mptQuartz);
    
    G4cout << "\n--- QUARTZ RINDEX CHECK ---" << G4endl;

    for (G4int i = 0; i < 24; i++)
    {
        G4cout << "Energy: " << energy[i]/eV << " eV"
               << "  RINDEX: " << sortedRIndexQuartz[i]
               << G4endl;
    }
    
    
    G4MaterialPropertiesTable *mptWater = new G4MaterialPropertiesTable();
   // mptWater->AddProperty("RINDEX", energy, rIndexWater, 24);
    mptWater->AddProperty("RINDEX", energy, sortedRIndexWater, 24);
    mptWater->AddProperty("ABSLENGTH", energy, absLengthWater, 24);
    water->SetMaterialPropertiesTable(mptWater);
    
    G4cout << "\nChecking  refractive index:" << G4endl;

for (G4int i = 0; i < 24; i++)
{
    G4cout << "Energy: " << energy[i]/eV
           << " eV, Quartz RINDEX: "
           << sortedRIndexQuartz[i]
           << ", Water RINDEX: "
           << sortedRIndexWater[i]
           << G4endl;
}
    
   /* 
    absorberSurface = 
    new G4OpticalSurface("Absorber");
    absorberSurface->SetModel(unified);
    absorberSurface->SetType(dielectric_dielectric);
    absorberSurface->SetFinish(ground);
    G4MaterialPropertiesTable *mptAbs = new G4MaterialPropertiesTable();
    mptAbs->AddProperty("REFLECTIVITY", energy, reflectivity,24);
    mptAbs->AddProperty("ABSLENGTH", energy, absLengthAbsorber,24);
 //   mptAbs->AddProperty("
    */
    
    spectralonSurface = new G4OpticalSurface("Spectralon");
    
    spectralonSurface->SetType(dielectric_metal);
    spectralonSurface->SetModel(unified);
    spectralonSurface->SetFinish(ground);
    G4MaterialPropertiesTable *mptSpec = new G4MaterialPropertiesTable();
    mptSpec->AddProperty("REFLECTIVITY", energy, reflectivity,24);
    mptSpec->AddProperty("SPECULARLOBECONSTANT", energy, specularlobe, 24);
    mptSpec->AddProperty("SPECULARSPIKECONSTANT", energy, specularspike, 24);
    mptSpec->AddProperty("BACKSCATTERCONSTANT", energy, backscatter, 24);
    spectralonSurface->SetMaterialPropertiesTable(mptSpec);
    
    
    
    
    /* 
    spectralonSurface =
    new G4OpticalSurface("Spectralon");
    spectralonSurface->SetType(dielectric_dielectric);
    spectralonSurface->SetModel(unified);
    spectralonSurface->SetFinish(groundbackpainted);
    spectralonSurface->SetSigmaAlpha(0.1);
    G4MaterialPropertiesTable *mptSpec = new G4MaterialPropertiesTable();
    mptSpec->AddProperty("REFLECTIVITY", energy, reflectivity,24);
    mptSpec->AddProperty("SPECULARLOBECONSTANT", energy, specularlobe, 24);
    mptSpec->AddProperty("SPECULARSPIKECONSTANT", energy, specularspike, 24);
    mptSpec->AddProperty("BACKSCATTERCONSTANT", energy, backscatter, 24);
    spectralonSurface->SetMaterialPropertiesTable(mptSpec);
    */


}

MyDetectorConstruction::~MyDetectorConstruction()
{}
/*
void MyDetectorConstruction::getEnergy(const G4double input[], const G4double factor, const int N, G4double output[]){
    for (G4int i = 0; i<N; i++)
    {    
        
        G4double corr_wavelength = input[i]*0.001;	
        output[i] = factor/corr_wavelength;
 
    }
    std::sort(output, output+N);

}
*/

void MyDetectorConstruction::getEnergy(const G4double input[], const G4double factor, const int N, G4double output[], const G4double originalRIndex1[], const G4double originalRIndex2[], G4double sortedRIndex1[], G4double sortedRIndex2[])
{

    for (G4int i = 0; i < N; i++)
    {    
        G4int reverseIndex = (N - 1) - i;
        
      //  std::cout << "Wavelength is: " << input[reverseIndex] << std::endl;
        G4double corr_wavelength = input[reverseIndex] * 0.001;	
        output[i] = (factor / corr_wavelength)* eV;
      //  std::cout << "Energy is: " << output[i] << std::endl;
        
       
        sortedRIndex1[i] = originalRIndex1[reverseIndex];
        sortedRIndex2[i] = originalRIndex2[reverseIndex];
        //std::cout << "Corresponding Rindex is: " << sortedRIndex1[i] << std::endl;
        //std::cout << "Corresponding Rindex is: " << sortedRIndex2[i] << std::endl;
    }
    /*
    for (G4int i = 0; i < N; i++)
    {
     //   std::cout << "Quartz Refractive Index: " << sortedRIndex1[i] << std::endl;
        std::cout << "Water Refractive Index: " << sortedRIndex2[i] << std::endl;
    }
    */
    
    std::cout << "Index\tEnergy\t\tQuartz RIndex\tWater RIndex" << std::endl;

    for (G4int i = 0; i < N; i++)
    {
        std::cout << i << "\t"
                  << output[i]/eV<< "\t"
                  << sortedRIndex1[i] << "\t"
                  << sortedRIndex2[i] << std::endl;
    }
    
    
    
}




G4VPhysicalVolume *MyDetectorConstruction::Construct()
{ 
    DefineMaterials();
    
    G4cout << "2water->GetName() = " << water->GetName() << G4endl;
    

    
    /*
    G4NistManager *nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    water = nist->FindOrBuildMaterial(inCuvMat);
    quartz = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    spectralonMaterial = nist->FindOrBuildMaterial("G4_TEFLON");
    */
     /*
     G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *water = nist->FindOrBuildMaterial(inCuvMat);
    G4Material *quartz = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    G4Material *steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material* spectralonMaterial = nist->FindOrBuildMaterial("G4_TEFLON");
     
     
     
     






    // Refractive index info
    G4double factor = 1.239841939;
    G4double wavelength[24] = {260., 266., 274.87, 280., 300., 308., 320., 325., 337., 340., 360., 365.48, 380., 400., 404.65, 435.83, 441.6, 447.1, 486.13, 488., 514.5, 532.00, 546.07, 587.56};
    G4double rIndexQuartz[24] = {1.5024, 1.4997, 1.4961, 1.4942, 1.4878, 1.4856, 1.4827, 1.4816, 1.4792, 1.4787, 1.4753, 1.4745, 1.4725, 1.4701, 1.4696, 1.4667, 1.4662, 1.4658, 1.4631, 1.463, 1.4616, 1.4607, 1.4601, 1.4585};
    G4double reflectivity[24];
    std::fill_n(reflectivity, 24, 1.0);
    
    G4double rIndexAir[24];
    std::fill_n(rIndexAir,24, 1.);
  
    G4double rIndexWater[24];
    std::fill_n(rIndexWater,24,1.33);
 
    G4double absLengthQuartz[24];
    std::fill_n(absLengthQuartz, 24, 100.*m);
    
    G4double absLengthWater[24];
    std::fill_n(absLengthWater, 24, 100.*m);
    
    G4double energy[24];
    getEnergy(wavelength, factor, 24, energy);
  //  std::cout<< "index 1 check: " << energy[0] << std::endl;
    
    G4double specularlobe[24];
    std::fill_n(specularlobe, 24, 0.0);
    
    G4double specularspike[24];
    std::fill_n(specularspike, 24, 0.0);
    
    G4double backscatter[24];
    std::fill_n(backscatter,24, 0.0);
    */
    
    /*
    G4MaterialPropertiesTable *mptAir = new G4MaterialPropertiesTable();
    mptAir->AddProperty("RINDEX", energy, rIndexAir,24);
    worldMat->SetMaterialPropertiesTable(mptAir);
    
    G4MaterialPropertiesTable *mptQuartz = new G4MaterialPropertiesTable();
    mptQuartz->AddProperty("RINDEX", energy, rIndexQuartz, 24);
    mptQuartz->AddProperty("ABSLENGTH", energy, absLengthQuartz ,24);
    quartz->SetMaterialPropertiesTable(mptQuartz);
    
    G4MaterialPropertiesTable *mptWater = new G4MaterialPropertiesTable();
    mptWater->AddProperty("RINDEX", energy, rIndexWater, 24);
    mptWater->AddProperty("ABSLENGTH", energy, absLengthWater, 24);
    water->SetMaterialPropertiesTable(mptWater);
    
    // Sample surface 
    
    spectralonSurface =
    new G4OpticalSurface("Spectralon");

    spectralonSurface->SetType(dielectric_metal);
    spectralonSurface->SetModel(unified);
    spectralonSurface->SetFinish(ground);
    G4MaterialPropertiesTable *mptSpec = new G4MaterialPropertiesTable();
    mptSpec->AddProperty("REFLECTIVITY", energy, reflectivity,24);
    mptSpec->AddProperty("SPECULARLOBECONSTANT", energy, specularlobe, 24);
    mptSpec->AddProperty("SPECULARSPIKECONSTANT", energy, specularspike, 24);
    mptSpec->AddProperty("BACKSCATTERCONSTANT", energy, backscatter, 24);
    spectralonSurface->SetMaterialPropertiesTable(mptSpec);
    */
    
    
   
    
    // Mother volume info -----------------------------------------------------------------------
    solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m,0.5*m); // takes in arguments of half length, default unit mm, so nee *m to make it in metres instead 
    
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    
    physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld",0, false, 0, true);
    
    // ------------------------------------------------------------------------------------------
    
    // Cuvette volume info -----------------------------------------------------------------
    
    G4double wall = 1.25*mm;
    G4double eps = 0.001*mm;
    G4double safety =  0.05*mm;// 5.*um;  
    
    // Cuv outer dims
    
    G4double outerCuvX = 12.50*mm; 
    G4double outerCuvY = 12.50*mm;
    G4double outerCuvZ = 45.0*mm;
    
    // Cuv inner dims 
    /*
    G4double innerCuvX = outerCuvX - 2.0*wall;//10.00*mm; 
    G4double innerCuvY = outerCuvY - 2.0*wall;//10.00*mm; 
    G4double innerCuvZ = 45.00*mm; 
    */
    // water dims w/ tolerance
    G4double waterX = outerCuvX -2.*wall - 2.*safety;
    G4double waterY = outerCuvY -2.*wall - 2.*safety;
    G4double waterZ = outerCuvZ -2.*wall - 2.*safety;
    
    // Water geometry 
    
    solidWater = new G4Box("solidWater", waterX/2.0, waterY/2.0, waterZ/2.0);
    
    logicWater = new G4LogicalVolume(solidWater,water, "logicWater"); 
    
    // Quartz outer 
    
    solidOuterCuv = new G4Box("solidOuterCuv", outerCuvX/2.0, outerCuvY/2.0, outerCuvZ/2.0);
    
    logicOuterCuv = new G4LogicalVolume(solidOuterCuv, quartz, "logicOuterCuv");
    
    // Quartz inner 
    
  // G4Box *solidInnerCuv = new G4Box("solidInnerCuv", waterX/2.0, waterY/2.0, waterZ/2.0);
     
  //  G4SubtractionSolid* solidInnerCuvShell = new G4SubtractionSolid("solidInnerCuvShell", solidOuterCuv, solidInnerCuv, nullptr, G4ThreeVector(0,0,0));
    
  //  G4LogicalVolume* logicCuv = new G4LogicalVolume(solidInnerCuvShell, quartz,"logicCuv");
    
    // Placement 
    
    physCuv = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,0.), logicOuterCuv, "physCuv",logicWorld, false, 0, true);
    
    physWater = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,0.), logicWater, "physWater", logicOuterCuv,false, 0, true);
    
    
    // Visualisation 
    
    auto cuvVis = new G4VisAttributes(G4Colour(0.8,0.8,0.8,0.15));
    
    cuvVis->SetForceSolid(true);
    
    logicOuterCuv->SetVisAttributes(cuvVis);
    
    auto waterVis = new G4VisAttributes(G4Colour(0.0,0.0,1,0.3));
    
    waterVis->SetForceSolid(true);
    
    logicWater->SetVisAttributes(waterVis);
    
    
    //Aperture
    G4double plateX = 30.0*mm; 
    G4double plateY = 1.0*mm -eps;
    G4double plateZ = 45.0*mm;
    
    G4double opX = 12.5*mm;
    G4double opY = 20.0*mm;
    G4double opZ = 1.0*mm;
    
    G4double sampleX = waterX - 2.*safety;
    G4double sampleY = 1.0 *mm;
    G4double sampleZ = waterZ - 2.*safety;
    
        
    solidPlate = new G4Box("solidPlate", plateX/2.0, plateY/2.0, plateZ/2.0);
    
    // Rotation matrix to rotate the ellipse to extrude in the right direction. 
    
    rot = new G4RotationMatrix();
    rot->rotateX(90*deg);
    
    solidOp = new G4Box("solidOp", opX/2.0, opY/2.0, opZ/2.0);
    
    solidAperture = new G4SubtractionSolid("solidAperture", solidPlate, solidOp, rot, G4ThreeVector(0.,0.,0.));
    
    logicAperture = new G4LogicalVolume(solidAperture, steel, "logicAperture");
    
    physAperture = new G4PVPlacement(nullptr, G4ThreeVector(0.,6.75,0.), logicAperture, "physAperture", logicWorld, false, 0, true);
    
    //G4LogicalVolume* logicPlate = new G4LogicalVolume(solidPlate, steel, "logicPlate");
    
    //Tyvek sample 
    
    solidSample = new G4Box("solidSample", sampleX/2.0, sampleY/2.0, sampleZ/2.0);
    
    logicSample = new G4LogicalVolume(solidSample, spectralonMaterial, "logicSample");
    
    physSample = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,0.), logicSample, "physSample", logicWater,false,0,true);
    
    sampleSkinSurface = new G4LogicalSkinSurface("sampleSkinSurface", logicSample, spectralonSurface);
       
    
    
    
        
    // Detector 
  
//    G4Box *solidDetector = new G4Box("solidDetector", 0.5*mm, 0.5*mm, 0.5*mm);
  
  
    solidDetector = new G4Box("solidDetector", 12.5/2.0*mm, 0.5*mm, 20./2.0*mm);
    
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    
    physDetector = new G4PVPlacement(nullptr,
                G4ThreeVector(0.0, 7.75, 0.0),
                logicDetector,
                "physDetector",
                logicWorld,
                false,
                0,
                true
            );
    /*
    
    
    for (G4int i = 0; i < 12; i++) 
    {
        for (G4int j = 0; j < 20; j++)
        {
            G4double x = (-5.5 + i) * mm;
            G4double y = 7.75 * mm;   
            G4double z = (-9.5 + j) * mm;
            
            new G4PVPlacement(
                nullptr,
                G4ThreeVector(x, y, z),
                logicDetector,
                "physDetector",
                logicWorld,
                false,
                i + j * 12,
                true
            );
        }
    }
   */ 
  
   
    
    
    
    //--------------------------------------------------------------------------------------
    
    return physWorld; //Always return highest mother volume
    
}


void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
   
    logicDetector->SetSensitiveDetector(sensDet); 
    
    
}







