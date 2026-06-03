#include "construction.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4EllipticalTube.hh"
#include <algorithm>

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::getEnergy(const G4double input[], const G4double factor, const int N, G4double output[]){
    for (G4int i = 0; i<N; i++)
    {    
        
        G4double corr_wavelength = input[i]*0.001;	
        output[i] = factor/corr_wavelength;
 
    }
    std::sort(output, output+N);

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *water = nist->FindOrBuildMaterial("G4_WATER");
    G4Material *quartz = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    G4Material *steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    
    
    // Refractive index info
    G4double factor = 1.239841939;
    G4double wavelength[24] = {260., 266., 274.87, 280., 300., 308., 320., 325., 337., 340., 360., 365.48, 380., 400., 404.65, 435.83, 441.6, 447.1, 486.13, 488., 514.5, 532.00, 546.07, 587.56};
    G4double rIndexQuartz[24] = {1.5024, 1.4997, 1.4961, 1.4942, 1.4878, 1.4856, 1.4827, 1.4816, 1.4792, 1.4787, 1.4753, 1.4745, 1.4725, 1.4701, 1.4696, 1.4667, 1.4662, 1.4658, 1.4631, 1.463, 1.4616, 1.4607, 1.4601, 1.4585};
    
    G4double rIndexAir[24];
    std::fill_n(rIndexAir,24, 1.);
    std::cout<< "air ri: " << rIndexAir[4] <<std::endl;
    G4double rIndexWater[24];
    std::fill_n(rIndexWater,24,1.33);
 
    G4double absLengthQuartz[24];
    std::fill_n(absLengthQuartz, 24, 100.*m);
    
    G4double absLengthWater[24];
    std::fill_n(absLengthWater, 24, 100.*m);
    
    G4double energy[24];
    getEnergy(wavelength, factor, 24, energy);
  //  std::cout<< "index 1 check: " << energy[0] << std::endl;
     
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
    // Mother volume info -----------------------------------------------------------------------
    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m,0.5*m); // takes in arguments of half length, default unit mm, so nee *m to make it in metres instead 
    
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld",0, false, 0, true);
    
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
    
    G4Box* solidWater = new G4Box("solidWater", waterX/2.0, waterY/2.0, waterZ/2.0);
    
    G4LogicalVolume* logicWater = new G4LogicalVolume(solidWater,water, "logicWater"); 
    
    // Quartz outer 
    
    G4Box *solidOuterCuv = new G4Box("solidOuterCuv", outerCuvX/2.0, outerCuvY/2.0, outerCuvZ/2.0);
    
    G4LogicalVolume* logicOuterCuv = new G4LogicalVolume(solidOuterCuv, quartz, "logicOuterCuv");
    
    // Quartz inner 
    
  // G4Box *solidInnerCuv = new G4Box("solidInnerCuv", waterX/2.0, waterY/2.0, waterZ/2.0);
     
  //  G4SubtractionSolid* solidInnerCuvShell = new G4SubtractionSolid("solidInnerCuvShell", solidOuterCuv, solidInnerCuv, nullptr, G4ThreeVector(0,0,0));
    
  //  G4LogicalVolume* logicCuv = new G4LogicalVolume(solidInnerCuvShell, quartz,"logicCuv");
    
    // Placement 
    
    G4VPhysicalVolume *physCuv = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,0.), logicOuterCuv, "physCuv",logicWorld, false, 0, true);
    
    G4VPhysicalVolume *physWater = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,0.), logicWater, "physWater", logicOuterCuv,false, 0, true);
    
    
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
    
        
    G4Box* solidPlate = new G4Box("solidPlate", plateX/2.0, plateY/2.0, plateZ/2.0);
    
    // Rotation matrix to rotate the ellipse to extrude in the right direction. 
    
    auto rot = new G4RotationMatrix();
    rot->rotateX(90*deg);
    
    auto solidOp = new G4Box("solidOp", opX/2.0, opY/2.0, opZ/2.0);
    
    G4SubtractionSolid* solidAperture = new G4SubtractionSolid("solidAperture", solidPlate, solidOp, rot, G4ThreeVector(0.,0.,0.));
    
    G4LogicalVolume *logicAperture = new G4LogicalVolume(solidAperture, steel, "logicAperture");
    
    G4VPhysicalVolume* physAperture = new G4PVPlacement(nullptr, G4ThreeVector(0.,6.75,0.), logicAperture, "physAperture", logicWorld, false, 0, true);
    
    //G4LogicalVolume* logicPlate = new G4LogicalVolume(solidPlate, steel, "logicPlate");
    
        
    // Detector 
  
    G4Box *solidDetector = new G4Box("solidDetector", 0.5*mm, 0.5*mm, 0.5*mm);
    
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    
    
    
    
    
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
    
  
   
    
    
    
    //--------------------------------------------------------------------------------------
    
    return physWorld; //Always return highest mother volume
    
}


void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
   
    logicDetector->SetSensitiveDetector(sensDet); 
    
    
}







