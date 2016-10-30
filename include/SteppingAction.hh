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
#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : 
	public G4UserSteppingAction
{
public:
  SteppingAction(DetectorConstruction*, EventAction*);
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step*);
    
private:
  DetectorConstruction* detector;
  EventAction* eventaction;  
};
