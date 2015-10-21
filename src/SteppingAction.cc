//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: SteppingAction.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4SteppingManager.hh"

#include "G4Step.hh"

#include <math.h>

////#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det,
                                         EventAction* evt)
:detector(det), eventaction(evt)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    G4Track* theTrack = aStep->GetTrack();

    if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Detector"){
         eventaction->AddEnergy( aStep->GetTotalEnergyDeposit()/keV);
         //G4cout << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << " " <<   aStep->GetTotalEnergyDeposit()/keV << G4endl;
    }
    if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Teflon"){
    	eventaction->AddEnergyDead(aStep->GetTotalEnergyDeposit()/keV);
    }

    G4StepPoint* thePrePoint = aStep->GetPreStepPoint();
    G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

    G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
    G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

    G4OpBoundaryProcessStatus boundaryStatus=Undefined;
    static G4OpBoundaryProcess* boundary=NULL;

    if(!boundary){
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
    if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
    //Optical photon only

    //Was the photon absorbed by the absorption process
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName()
       =="OpAbsorption"){
      ;//G4cout << "Absorption" << G4endl;
      //eventInformation->IncAbsorption();
      //trackInformation->AddTrackStatusFlag(absorbed);
    }

    boundaryStatus=boundary->GetStatus();

    //Check to see if the partcile was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check
    if(thePostPoint->GetStepStatus()==fGeomBoundary){
      switch(boundaryStatus){
      case Absorption:
	;//G4cout << "AbsorptionBoundary" << G4endl;//trackInformation->AddTrackStatusFlag(boundaryAbsorbed);
	//eventInformation->IncBoundaryAbsorption();
	break;
      case Detection: //Note, this assumes that the volume causing detection
                      //is the photocathode because it is the only one with
	              //non-zero efficiency
	{
	  //Triger sensitive detector manually since photon is
	  //absorbed but status was Detection
	  /*G4SDManager* SDman = G4SDManager::GetSDMpointer();
	  G4String sdName="/LXeDet/pmtSD";
	  LXePMTSD* pmtSD = (LXePMTSD*)SDman
	    ->FindSensitiveDetector(sdName);
	  if(pmtSD)
	    pmtSD->ProcessHits_constStep(theStep,NULL);
	  trackInformation->AddTrackStatusFlag(hitPMT);*/
	  ;//G4cout << "Detection ********************************************************************************************************************" << G4endl;
	  eventaction->AddDetection();
	  eventaction->PassWaveRun(2,1240/(theTrack->GetDynamicParticle()->GetKineticEnergy()/eV));
	  eventaction->AddTime(theTrack->GetGlobalTime()/ns);
	  eventaction->AddFiberDetected((int)round(theTrack->GetPosition().getY()/10));
	  break;
	}
      case FresnelReflection:
      case TotalInternalReflection:
      case SpikeReflection:
	;//G4cout << "Reflection " << G4endl;//trackInformation->IncReflections();
	break;
      default:
	break;
      }
      if(thePostPV->GetName()=="sphere")
	;//trackInformation->AddTrackStatusFlag(hitSphere);
    }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
