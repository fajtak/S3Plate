/*
 * SCube simulation
 * 
 * Author(s): Lukas Fajtl
 *            Vladimir Fekete, vladko.fekete@gmail.com
 * 
 * Copyright GNU General Public License v2.0.
 * 
 * You should have received a copy of the GNU General Public License
 * along with SCube.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SteppingAction.hh>
#include <DetectorConstruction.hh>
#include <EventAction.hh>
#include <G4ParticleDefinition.hh>
#include <G4OpBoundaryProcess.hh>
#include <G4SteppingManager.hh>
#include <G4Step.hh>
#include <math.h>

using namespace CLHEP;

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt) :
	detector(det), 
	eventaction(evt)
{   
}

SteppingAction::~SteppingAction()
{ 	
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4Track* theTrack = aStep->GetTrack();

	if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Detector")
	{
				eventaction->AddEnergy( aStep->GetTotalEnergyDeposit()/keV);
	}

	if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Teflon")
	{
		eventaction->AddEnergyDead(aStep->GetTotalEnergyDeposit()/keV);
	}

	G4StepPoint* thePrePoint = aStep->GetPreStepPoint();
	G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

	G4StepPoint* thePostPoint = aStep->GetPostStepPoint();
	G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

	G4OpBoundaryProcessStatus boundaryStatus=Undefined;
	static G4OpBoundaryProcess* boundary=NULL;

	if(!boundary)
	{
		G4ProcessManager* pm = aStep->GetTrack()->GetDefinition()->GetProcessManager();
		G4int nprocesses = pm->GetProcessListLength();
		G4ProcessVector* pv = pm->GetProcessList();
		
		for(G4int i=0;i<nprocesses;i++)
		{
			if( (*pv)[i]->GetProcessName() == "OpBoundary" )
			{
				boundary = (G4OpBoundaryProcess*)(*pv)[i];
				break;
			}
		}
	}

	G4ParticleDefinition* particleType = theTrack->GetDefinition();
	if(particleType==G4OpticalPhoton::OpticalPhotonDefinition())
	{
		if(thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption")
		{
				;//G4cout << "Absorption" << G4endl;
				//eventInformation->IncAbsorption();
				//trackInformation->AddTrackStatusFlag(absorbed);
		}

		boundaryStatus=boundary->GetStatus();

		//Check to see if the partcile was actually at a boundary
		//Otherwise the boundary status may not be valid
		//Prior to Geant4.6.0-p1 this would not have been enough to check
		if( thePostPoint->GetStepStatus() == fGeomBoundary)
		{
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
			
			//if(thePostPV->GetName()=="sphere") trackInformation->AddTrackStatusFlag(hitSphere);
		}
	}
}
