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

#include <PrimaryGeneratorMessenger.hh>
#include <PrimaryGeneratorAction.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWith3Vector.hh>
#include <G4UIcmdWithABool.hh>
#include <macros.hh>

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* gun) :
	action(gun)
{
  gunDir = new G4UIdirectory("/myPG/");
  gunDir->SetGuidance("PrimaryGenerator control");

  rndmCmd = new G4UIcmdWithAString("/myPG/rndm",this);
  rndmCmd->SetGuidance("Shoot randomly the incident particle.");
  rndmCmd->SetGuidance("  Choice : on(default), off");
  rndmCmd->SetParameterName("choice",true);
  rndmCmd->SetDefaultValue("on");
  rndmCmd->SetCandidates("on off");
  rndmCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  positionCmd = new G4UIcmdWith3Vector("/myPG/position", this);
  positionCmd->SetGuidance("Set the position of the primary particle.");

  pointCmd = new G4UIcmdWithABool("/myPG/point",this);
  wholeDetCmd = new G4UIcmdWithABool("/myPG/wholeDet",this);
  kalabashkyCmd = new G4UIcmdWithABool("/myPG/kalabashky",this);
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  SAFE_DELETE( rndmCmd );
  SAFE_DELETE( gunDir );
  SAFE_DELETE( positionCmd );
  SAFE_DELETE( pointCmd );
  SAFE_DELETE( wholeDetCmd );
  SAFE_DELETE( kalabashkyCmd );
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if( command == rndmCmd )
    {
        action->SetRndmFlag(newValue);
    }
    else if (command == positionCmd )
    {
        action->SetX( positionCmd->GetNew3VectorValue(newValue).getX() );
        action->SetY( positionCmd->GetNew3VectorValue(newValue).getY() );
        action->SetZ( positionCmd->GetNew3VectorValue(newValue).getZ() );
    }
    else if (command == pointCmd )
    {
        action->SetPoint();
    }
    else if (command == wholeDetCmd )
    {
        action->SetWholeDet();
    }
    else if (command == kalabashkyCmd )
    {
        action->SetKalabashky();
    }
}
