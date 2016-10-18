#pragma once
#include "G4String.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

#include "ProcessingConfigurator.hh"

class DetectorConstructionGDML : public G4VUserDetectorConstruction
{
public:
  DetectorConstructionGDML();
  virtual ~DetectorConstructionGDML();

  virtual G4VPhysicalVolume* Construct();
  virtual void SetCuts();

protected:
  virtual void ConstructParticle();
  virtual void ConstructProcess();

};
