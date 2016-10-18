#include "EventAction.hh"

#include "RunAction.hh"
#include "EventActionMessenger.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <fstream>
#include <iostream>
#include <iomanip>

EventAction::EventAction(RunAction* run) : runAct(run),printModulo(1),eventMessenger(0)
{
  eventMessenger = new EventActionMessenger(this);
}

EventAction::~EventAction()
{
  delete eventMessenger;
}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  if (evtNb%10 == 0) {
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;
  }

  interaction = 0;
  passage = 0;
  energyDep = 0;
  energyDepDead = 0;
  nDetection = 0;
  nProduced = 0;
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  //accumulates statistic  
  runAct->fillPerEvent(nProduced, nDetection,energyDep,energyDepDead);
}

void EventAction::PassWaveRun(int whichHist, double wavelength)
{
    if (whichHist == 1)
        runAct->fillPhotoWaveProduced(wavelength);
    if (whichHist == 2)
        runAct->fillPhotoWaveDetected(wavelength);
}

void EventAction::AddTime(double time)
{
    runAct->fillTime(time);
}

void EventAction::AddFiberDetected(int fiberID)
{
    runAct->fillFiber(fiberID);
}
