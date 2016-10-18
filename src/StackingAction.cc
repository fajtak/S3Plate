#include "globals.hh"
#include "StackingAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

#include "EventAction.hh"

#include <CLHEP/Units/PhysicalConstants.h>

using namespace CLHEP;

StackingAction::StackingAction(EventAction* evt) : gammaCounter(0), eventaction(evt)
{
}

StackingAction::~StackingAction()
{
}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      gammaCounter++;
      eventaction->PassWaveRun(1,1240/(aTrack->GetDynamicParticle()->GetKineticEnergy()/eV));
      //G4cout << aTrack->GetDynamicParticle()->GetKineticEnergy()/eV << G4endl;
    }
  }
  return fUrgent;
}

void StackingAction::NewStage()
{
  eventaction->SetProducedPhotons(gammaCounter);
}

void StackingAction::PrepareNewEvent()
{ 
  gammaCounter = 0; 
}


