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
#include <G4UserRunAction.hh>
#include <g4root.hh>

class RunAction : 
	public G4UserRunAction
{
public:
	RunAction();
	virtual ~RunAction();

	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
	
private:
	void SetupAnalysisManager();

private:
	G4AnalysisManager* analysisManager;
};

