#include "UserActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include <G4MTRunManager.hh>

UserActionInitialization::UserActionInitialization(DetectorConstruction* descr, EventAction* action) : 
	description(descr),
	eventAction(action)
{
}

UserActionInitialization::~UserActionInitialization()
{
}

void UserActionInitialization::BuildForMaster() const
{
}

void UserActionInitialization::Build() const
{
  auto primary = new PrimaryGeneratorAction(description);
  SetUserAction(primary);

  auto stepping = new SteppingAction(description, eventAction);
  SetUserAction(stepping);
}
