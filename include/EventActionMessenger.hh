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

#pragma once
#include <globals.hh>
#include <G4UImessenger.hh>

class EventAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

class EventActionMessenger :
	public G4UImessenger
{
public:
  EventActionMessenger(EventAction*);
  virtual ~EventActionMessenger();
    
  virtual void SetNewValue(G4UIcommand*, G4String);
    
private:
  EventAction* eventAction;
  G4UIdirectory* eventDir;   
  G4UIcmdWithAnInteger* printCmd;    
};
