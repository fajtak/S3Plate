//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: DetectorConstruction.hh,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4PVPlacement;
class G4Material;
class G4UniformMagField;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
   ~DetectorConstruction();

  public:

     G4VPhysicalVolume* Construct();

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

     DetectorMessenger* detectorMessenger;  //pointer to the Messenger

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

  private:

     void DefineMaterials();
};

#endif

