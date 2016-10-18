#include <G4MTRunManager.hh>
#include <G4UImanager.hh>

#include <Randomize.hh>

#include <DetectorConstruction.hh>
#include <PhysicsList.hh>
#include <PrimaryGeneratorAction.hh>
#include <RunAction.hh>
#include <EventAction.hh>
#include <SteppingAction.hh>
#include <SteppingVerbose.hh>
#include <StackingAction.hh>
#include <UserActionInitialization.hh>

#include <ctime>

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) if ((x) != nullptr) { delete(x); (x) = nullptr; }
#endif

int main(int, char**)
{
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);       
  CLHEP::HepRandom::setTheSeed((long) time(nullptr));
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);

  auto runManager = new G4MTRunManager;

  if (runManager == nullptr)
  {
    return -1;
  }

  runManager->SetNumberOfThreads(4);


  auto detector = new DetectorConstruction();
  runManager->SetUserInitialization(detector);
  auto physics = new PhysicsList();  
  runManager->SetUserInitialization(physics);

   
  auto gen_action = new PrimaryGeneratorAction(detector);
  auto run_action = new RunAction(gen_action);
  auto event_action = new EventAction(run_action);

/*
  auto stepping_action = new SteppingAction(detector, event_action);
  auto stacking_action = new StackingAction(event_action);
  
  runManager->SetUserAction(gen_action);
  runManager->SetUserAction(run_action);
  runManager->SetUserAction(event_action);
  runManager->SetUserAction(stepping_action);
  runManager->SetUserAction(stacking_action);
*/

  auto actions = new UserActionInitialization(detector, event_action);
  runManager->SetUserInitialization(actions);


  runManager->Initialize();

  G4int numberOfEvent = 10;
  runManager->BeamOn(numberOfEvent);

  SAFE_DELETE(runManager);

  return 0;
}
