#pragma once
#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
class EventActionMessenger;

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction*);
  virtual ~EventAction();

  void  BeginOfEventAction(const G4Event*);
  void    EndOfEventAction(const G4Event*);

  void Interact(void) {interaction = 1;};
  void Pass(void) {passage = 1;};
  void AddEnergy(G4double energy){energyDep += energy;};
  void AddEnergyDead(G4double energy){energyDepDead += energy;};
  void AddDetection(void){nDetection++;};
  void SetProducedPhotons(int newValue){nProduced = newValue;};
  void PassWaveRun(int whichHist, double wavelength);
  void AddTime(double time);
  void AddFiberDetected(int fiberID);

  void SetPrintModulo(G4int    val)  {printModulo = val;};

private:
   RunAction*  runAct;

   G4int     printModulo;

   G4int     interaction;
   G4int     passage;

   G4double  energyDep;
   G4double  energyDepDead;

   G4int nDetection;
   G4int nProduced;

   EventActionMessenger*  eventMessenger;
};
