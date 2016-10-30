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
#include <G4UImessenger.hh>
#include <globals.hh>

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWith3Vector;
class G4UIcmdWithABool;

class PrimaryGeneratorMessenger :
	public G4UImessenger
{
public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
  virtual ~PrimaryGeneratorMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

private:
  PrimaryGeneratorAction* action;
  G4UIdirectory* gunDir;
  G4UIcmdWithAString* rndmCmd;
  G4UIcmdWith3Vector* positionCmd;
  G4UIcmdWithABool* pointCmd;
  G4UIcmdWithABool* wholeDetCmd;
  G4UIcmdWithABool* kalabashkyCmd;
};
