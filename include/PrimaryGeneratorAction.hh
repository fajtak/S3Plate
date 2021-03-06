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
// $Id: PrimaryGeneratorAction.hh,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include <CLHEP/Units/PhysicalConstants.h>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

using namespace CLHEP;

class G4ParticleGun;
class G4Event;
class DetectorConstruction;
class PrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction*);
  virtual ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*);
  void SetRndmFlag(G4String val) { rndmFlag = val;}
  double GetX(void){return x;};
  double GetY(void){return y;};
  double GetZ(void){return z;};

  void SetX(double newX){x = newX*cm;};
  void SetY(double newY){y = newY*cm;};
  void SetZ(double newZ){z = newZ*cm;};

  void SetPoint(void);
  void SetWholeDet(void);
  void SetKalabashky(void);

private:
  G4ParticleGun*           particleGun;	 //pointer a to G4  class
  DetectorConstruction*    Detector;     //pointer to the geometry

  PrimaryGeneratorMessenger* gunMessenger;   //messenger of this class
  G4String                   rndmFlag;	     //flag for a rndm impact point

  G4double x;
  G4double y;
  G4double z;

  G4bool point;
  G4bool wholeDet;
  G4bool kalabashky;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


