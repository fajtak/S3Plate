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

#include <ExN06StackingAction.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTypes.hh>
#include <G4Track.hh>
#include <G4ios.hh>
#include <EventAction.hh>
#include <CLHEP/Units/PhysicalConstants.h>

using namespace CLHEP;


ExN06StackingAction::ExN06StackingAction(EventAction* evt) : 
	gammaCounter(0), 
	eventAction(evt)
{   
}

ExN06StackingAction::~ExN06StackingAction()
{
}

G4ClassificationOfNewTrack ExN06StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && 
		 aTrack->GetParentID() > 0)
  { 
		gammaCounter++;
		eventAction->PassWaveRun(1,1240/(aTrack->GetDynamicParticle()->GetKineticEnergy()/eV));
  }
  
  return fUrgent;
}

void ExN06StackingAction::NewStage()
{
	eventAction->SetProducedPhotons(gammaCounter);
}

void ExN06StackingAction::PrepareNewEvent()
{ 
	gammaCounter = 0; 
}
