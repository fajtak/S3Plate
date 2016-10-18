#pragma once

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : 
  public G4UserSteppingAction
{
public:
  SteppingAction(DetectorConstruction*, EventAction*);
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step*);
    
private:
  DetectorConstruction* detector;
  EventAction*          eventaction;  
};
