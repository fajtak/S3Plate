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
#include <G4SteppingVerbose.hh>

class SteppingVerbose : 
	public G4SteppingVerbose
{
public:
	SteppingVerbose();
	virtual ~SteppingVerbose();

	void StepInfo();
	void TrackingStarted();
};
