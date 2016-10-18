#pragma once
#include "G4UserStackingAction.hh"

class EventAction;

class StackingAction : public G4UserStackingAction
{
  public:
   StackingAction(EventAction*);
   virtual ~StackingAction();

  public:

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    void NewStage();
    void PrepareNewEvent();

  private:
    G4int gammaCounter;

    EventAction*          eventaction;
};
