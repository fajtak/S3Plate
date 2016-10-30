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
#include <G4UserStackingAction.hh>

class EventAction;

class ExN06StackingAction : 
	public G4UserStackingAction
{
public:
	ExN06StackingAction(EventAction*);
	virtual ~ExN06StackingAction();

	virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
	virtual void NewStage();
	virtual void PrepareNewEvent();

private:
	G4int gammaCounter;
	EventAction* eventAction;
};

