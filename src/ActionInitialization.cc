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

#include <ActionInitialization.hh>
#include <SteppingAction.hh>
#include <ExN06StackingAction.hh>
#include <PrimaryGeneratorAction.hh>
#include <EventAction.hh>
#include <RunAction.hh>

ActionInitialization::ActionInitialization(DetectorConstruction* detectorConstruction) :
	detConstruction(detectorConstruction)
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{   
	SetUserAction(new RunAction);
}

void ActionInitialization::Build() const
{
	SetUserAction(new PrimaryGeneratorAction(detConstruction));	
	
	auto eventAction = new EventAction();
	
	SetUserAction(eventAction);
	SetUserAction(new SteppingAction(detConstruction, eventAction));
	SetUserAction(new RunAction());	
	SetUserAction(new ExN06StackingAction(eventAction));
}
