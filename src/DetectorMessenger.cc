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

#include <DetectorMessenger.hh>
#include <DetectorConstruction.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <macros.hh>

DetectorMessenger::DetectorMessenger(DetectorConstruction* det) : 
	detector(det)
{
  n03Dir = new G4UIdirectory("/n03/");
  n03Dir->SetGuidance("UI commands of this example");

  detDir = new G4UIdirectory("/n03/det/");
  detDir->SetGuidance("detector control");

  absMaterCmd = new G4UIcmdWithAString("/n03/det/setabsMat",this);
  absMaterCmd->SetGuidance("Select Material of the absorber.");
  absMaterCmd->SetParameterName("choice",false);
  absMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  gapMaterCmd = new G4UIcmdWithAString("/n03/det/setgapMat",this);
  gapMaterCmd->SetGuidance("Select Material of the gap.");
  gapMaterCmd->SetParameterName("choice",false);
  gapMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  absThickCmd = new G4UIcmdWithADoubleAndUnit("/n03/det/setabsThick",this);
  absThickCmd->SetGuidance("Set Thickness of the absorber");
  absThickCmd->SetParameterName("size",false);
  absThickCmd->SetRange("size>=0.");
  absThickCmd->SetUnitCategory("Length");
  absThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  gapThickCmd = new G4UIcmdWithADoubleAndUnit("/n03/det/setgapThick",this);
  gapThickCmd->SetGuidance("Set Thickness of the gap");
  gapThickCmd->SetParameterName("size",false);
  gapThickCmd->SetRange("size>=0.");
  gapThickCmd->SetUnitCategory("Length");
  gapThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  sizeYZCmd = new G4UIcmdWithADoubleAndUnit("/n03/det/setsizeYZ",this);
  sizeYZCmd->SetGuidance("Set tranverse size of the calorimeter");
  sizeYZCmd->SetParameterName("size",false);
  sizeYZCmd->SetRange("size>0.");
  sizeYZCmd->SetUnitCategory("Length");
  sizeYZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  nbLayersCmd = new G4UIcmdWithAnInteger("/n03/det/setNbOfLayers",this);
  nbLayersCmd->SetGuidance("Set number of layers.");
  nbLayersCmd->SetParameterName("nbLayers",false);
  nbLayersCmd->SetRange("nbLayers>0 && nbLayers<500");
  nbLayersCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  updateCmd = new G4UIcmdWithoutParameter("/n03/det/update",this);
  updateCmd->SetGuidance("Update calorimeter geometry.");
  updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  updateCmd->SetGuidance("if you changed geometrical value(s).");
  updateCmd->AvailableForStates(G4State_Idle);

  magFieldCmd = new G4UIcmdWithADoubleAndUnit("/n03/det/setField",this);
  magFieldCmd->SetGuidance("Define magnetic field.");
  magFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
  magFieldCmd->SetParameterName("Bz",false);
  magFieldCmd->SetUnitCategory("Magnetic flux density");
  magFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
  SAFE_DELETE( nbLayersCmd );
  SAFE_DELETE( absMaterCmd ); 
	SAFE_DELETE( gapMaterCmd );
  SAFE_DELETE( absThickCmd ); 
	SAFE_DELETE( gapThickCmd );
  SAFE_DELETE( sizeYZCmd );   
	SAFE_DELETE( updateCmd );
  SAFE_DELETE( magFieldCmd );
  SAFE_DELETE( detDir );
  SAFE_DELETE( n03Dir );
}

void DetectorMessenger::SetNewValue(G4UIcommand*, G4String)
{
/*	
  if( command == absMaterCmd )
   { Detector->SetabsorberMaterial(newValue);}

  if( command == gapMaterCmd )
   { Detector->SetgapMaterial(newValue);}

  if( command == absThickCmd )
   { Detector->SetabsorberThickness(absThickCmd->GetNewDoubleValue(newValue));}

  if( command == gapThickCmd )
   { Detector->SetgapThickness(gapThickCmd->GetNewDoubleValue(newValue));}

  if( command == sizeYZCmd )
   { Detector->SetCalorsizeYZ(sizeYZCmd->GetNewDoubleValue(newValue));}

  if( command == nbLayersCmd )
   { Detector->SetNbOfLayers(nbLayersCmd->GetNewIntValue(newValue));}

  if( command == updateCmd )
   { Detector->UpdateGeometry(); }

  if( command == magFieldCmd )
   { Detector->SetmagField(magFieldCmd->GetNewDoubleValue(newValue));}
*/   
}
