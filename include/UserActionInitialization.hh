#pragma once
#include <G4VUserActionInitialization.hh>
#include "DetectorConstruction.hh"
#include "EventAction.hh"

class DetectorConstruction;
class EventAction;

class UserActionInitialization : 
	public G4VUserActionInitialization
{
public:
  UserActionInitialization(DetectorConstruction* description, EventAction* action);
  virtual ~UserActionInitialization();

  virtual void Build() const;
  virtual void BuildForMaster() const;

private:
  DetectorConstruction* description;
  EventAction* eventAction;
};
