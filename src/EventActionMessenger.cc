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

#include <EventActionMessenger.hh>
#include <EventAction.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <globals.hh>
#include <macros.hh>

EventActionMessenger::EventActionMessenger(EventAction* evAct) :
	eventAction(evAct)
{
  eventDir = new G4UIdirectory("/N03/event/");
  eventDir->SetGuidance("event control");
   
  printCmd = new G4UIcmdWithAnInteger("/N03/event/printModulo",this);
  printCmd->SetGuidance("Print events modulo n");
  printCmd->SetParameterName("EventNb",false);
  printCmd->SetRange("EventNb>0");
}

EventActionMessenger::~EventActionMessenger()
{
  SAFE_DELETE( printCmd );
  SAFE_DELETE( eventDir );   
}

void EventActionMessenger::SetNewValue(G4UIcommand* ,G4String)
{
}
