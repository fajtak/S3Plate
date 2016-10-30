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

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DetectorMessenger : 
	public G4UImessenger
{
public:
	DetectorMessenger(DetectorConstruction* );
	virtual ~DetectorMessenger();
	
	virtual void SetNewValue(G4UIcommand*, G4String);
	
private:
	DetectorConstruction* detector;	
	G4UIdirectory* n03Dir;
	G4UIdirectory* detDir;
	G4UIcmdWithAString* absMaterCmd;
	G4UIcmdWithAString* gapMaterCmd;
	G4UIcmdWithADoubleAndUnit* absThickCmd;
	G4UIcmdWithADoubleAndUnit* gapThickCmd;
	G4UIcmdWithADoubleAndUnit* sizeYZCmd;
	G4UIcmdWithAnInteger* nbLayersCmd;    
	G4UIcmdWithADoubleAndUnit* magFieldCmd;
	G4UIcmdWithoutParameter* updateCmd;
};

