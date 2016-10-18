#pragma once
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4PVPlacement;
class G4Material;
class G4UniformMagField;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

   DetectorConstruction();
   virtual ~DetectorConstruction();

public:

     virtual G4VPhysicalVolume* Construct();

     void MaterialPropertiesFiber();
     void MaterialPropertiesScintillator();
     void MaterialPropertiesPMT(G4LogicalVolume* photocath_log, G4PVPlacement* photocath_phys, G4PVPlacement* vacuumGap_phys);
     void MaterialPropertiesTeflon(G4LogicalVolume*, G4PVPlacement*, G4PVPlacement*);

     G4double GetWorldSizeXY()           {return WorldSizeXY;};
     G4double GetWorldSizeZ()          {return WorldSizeZ;};

     G4double GetDetX(){return detX;};
     G4double GetDetY(){return detY;};
     G4double GetDetZ(){return detZ;};

private:

     G4double           WorldSizeXY;
     G4double           WorldSizeZ;

    double detX;
    double detY;
    double detZ;

//     DetectorMessenger* detectorMessenger;  //pointer to the Messenger

     G4Box*             solidWorld;    //pointer to the solid World
     G4LogicalVolume*   logicWorld;    //pointer to the logical World
     G4VPhysicalVolume* physiWorld;    //pointer to the physical World

     G4Material*        aluminiumMaterial;
     G4Material*        airMaterial;
     G4Material*        scintilator;
     G4Material*        Pstyrene;
     G4Material*        PMMA;
     G4Material*        fPethylene;
     G4Material*        mylar;
     G4Material*        borGlass;
     G4Material*        teflon;
     G4Material*        teflonMat;

  private:

     void DefineMaterials();
};
