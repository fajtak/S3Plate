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
#include <G4UserEventAction.hh>
#include <globals.hh>

class EventAction : 
	public G4UserEventAction
{
public:
	EventAction();
	virtual ~EventAction();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

	void PassWaveRun(int whichHist, double wavelength);
	void AddTime(double time);
	void AddFiberDetected(int fiberID);

public:	
	void Interact() { interaction = 1; };
	void Pass() { passage = 1; };
	void AddEnergy(G4double energy) { energyDep += energy; };
	void AddEnergyDead(G4double energy) { energyDepDead += energy; };

	void AddDetection() { nDetection++; };
	void SetProducedPhotons(int newValue) { nProduced = newValue; };
	
private:
	G4int interaction;
	G4int passage;
	G4double energyDep;
	G4double energyDepDead;
	G4int nDetection;
	G4int nProduced;
};


