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
#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4PVPlacement;
class G4Material;
class DetectorMessenger;

class DetectorConstruction : 
	public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

public:
	virtual G4VPhysicalVolume* Construct();
	
	G4double GetWorldSizeXY() { return worldSizeXY; };
	G4double GetWorldSizeZ() { return worldSizeZ; };
	G4double GetDetX(){ return detX; };
	G4double GetDetY(){ return detY; };
	G4double GetDetZ(){ return detZ; };

private:
	G4double worldSizeXY;
	G4double worldSizeZ;
	double detX;
	double detY;
	double detZ;

	DetectorMessenger* detectorMessenger;

	G4Box* solidWorld;
	G4LogicalVolume* logicWorld;
	G4VPhysicalVolume* physiWorld;

	G4Material* aluminiumMaterial;
	G4Material* airMaterial;
	G4Material* scintilator;
	G4Material* pstyrene;
	G4Material* pMMA;
	G4Material* fPethylene;
	G4Material* mylar;
	G4Material* borGlass;
	G4Material* teflon;
	G4Material* teflonMat;

private:
	void MaterialPropertiesFiber();
	void MaterialPropertiesScintillator();
	void MaterialPropertiesPMT(G4LogicalVolume*, G4PVPlacement*, G4PVPlacement*);
	void MaterialPropertiesTeflon(G4LogicalVolume*, G4PVPlacement*, G4PVPlacement*);
	void DefineMaterials();
	void PrintErrorMessage(G4String message);
};

