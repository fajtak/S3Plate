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
#include <G4VUserPhysicsList.hh>
#include <globals.hh>

class PhysicsList : 
	public G4VUserPhysicsList
{
public:
  PhysicsList();
  virtual ~PhysicsList();
  
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  virtual void SetCuts();

private:
  void ConstructDecay();
  void ConstructEM();
  void ConstructOp();
};
