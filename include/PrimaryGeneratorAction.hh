#pragma once

#include <CLHEP/Units/PhysicalConstants.h>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

using namespace CLHEP;

class G4ParticleGun;
class G4Event;
class DetectorConstruction;
class PrimaryGeneratorMessenger;

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
