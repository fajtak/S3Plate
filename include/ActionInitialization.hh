/*
 * SCube simulation
 * 
 * Author(s): Vladimir Fekete, vladko.fekete@gmail.com
 * 
 * Copyright GNU General Public License v2.0.
 * 
 * You should have received a copy of the GNU General Public License
 * along with SCube.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <G4VUserActionInitialization.hh>
#include <DetectorConstruction.hh>

class ActionInitialization : 
	public G4VUserActionInitialization
{
public:
	ActionInitialization(DetectorConstruction* detectorConstruction);
	virtual ~ActionInitialization();
	
	virtual void BuildForMaster() const;
	virtual void Build() const;
		
private:
	DetectorConstruction* detConstruction;
};
