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
#include <CLHEP/Units/PhysicalConstants.h>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <globals.hh>

using namespace CLHEP;

class G4ParticleGun;
class G4Event;
class DetectorConstruction;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : 
	public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction*);
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);
  void SetRndmFlag(G4String val) { rndmFlag = val;}
  double GetX(void){return x;};
  double GetY(void){return y;};
  double GetZ(void){return z;};

  void SetX(double newX){x = newX*cm;};
  void SetY(double newY){y = newY*cm;};
  void SetZ(double newZ){z = newZ*cm;};

  void SetPoint(void);
  void SetWholeDet(void);
  void SetKalabashky(void);

private:
  G4ParticleGun* particleGun;
  DetectorConstruction* detector;

  PrimaryGeneratorMessenger* gunMessenger;
  G4String rndmFlag;

  G4double x;
  G4double y;
  G4double z;

  G4bool point;
  G4bool wholeDet;
  G4bool kalabashky;
};


