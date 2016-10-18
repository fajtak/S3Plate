#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4SteppingManager.hh"

#include "G4Step.hh"

#include <math.h>

using namespace CLHEP;

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt) : detector(det), eventaction(evt)
{ 
}

SteppingAction::~SteppingAction()
{ 
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    G4Track* theTrack = aStep->GetTrack();

    if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Detector"){
         eventaction->AddEnergy( aStep->GetTotalEnergyDeposit()/keV);
    }
    if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Teflon"){
    	eventaction->AddEnergyDead(aStep->GetTotalEnergyDeposit()/keV);
    }

    G4StepPoint* thePostPoint = aStep->GetPostStepPoint();

    G4OpBoundaryProcessStatus boundaryStatus = Undefined;

    //vfe: preco do pice staticka premenna v metode? wtf?
    static G4OpBoundaryProcess* boundary=NULL;

    if(!boundary)
    {
        G4ProcessManager* pm
            = aStep->GetTrack()->GetDefinition()->GetProcessManager();
        G4int nprocesses = pm->GetProcessListLength();
        G4ProcessVector* pv = pm->GetProcessList();
        G4int i;
        for( i=0;i<nprocesses;i++){
            if((*pv)[i]->GetProcessName()=="OpBoundary"){
                boundary = (G4OpBoundaryProcess*)(*pv)[i];
                break;
            }
        }
    }

    G4ParticleDefinition* particleType = theTrack->GetDefinition();

    if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
    {
    //Optical photon only

    boundaryStatus=boundary->GetStatus();

    if(thePostPoint->GetStepStatus()==fGeomBoundary)
    {
      switch(boundaryStatus)
      {
      case Detection: //Note, this assumes that the volume causing detection
                      //is the photocathode because it is the only one with
	              //non-zero efficiency
	{
	  eventaction->AddDetection();
	  eventaction->PassWaveRun(2,1240/(theTrack->GetDynamicParticle()->GetKineticEnergy()/eV));
	  eventaction->AddTime(theTrack->GetGlobalTime()/ns);
	  eventaction->AddFiberDetected((int)round(theTrack->GetPosition().getY()/10));
	  break;
	}
      case Absorption:
      case FresnelReflection:
      case TotalInternalReflection:
      case SpikeReflection:
	break;
      default:
	break;
      }
    }
  }
}
