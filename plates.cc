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
 
#include <G4MTRunManager.hh>
#include <G4UImanager.hh>
#include <Randomize.hh>
#include <DetectorConstruction.hh>
#include <PhysicsList.hh>
#include <SteppingVerbose.hh>
#include <ActionInitialization.hh>
#include <ctime>
#include <macros.hh>

void ParseInputParameters(int argc, char** argv, G4int &numOfThreads, G4int& numOfEvents);

int main(int argc, char** argv)
{
	G4int numberOfEvents = 10;
	G4int numberOfThreads = 10;
	
	ParseInputParameters(argc, argv, numberOfThreads, numberOfEvents);
	
	auto systime = std::time(NULL);
	auto seed = (long) systime;
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
	CLHEP::HepRandom::setTheSeed(seed);	
	
	G4VSteppingVerbose::SetInstance(new SteppingVerbose);
	
	auto runManager = new G4MTRunManager();
	
	if (runManager == nullptr)
	{
		G4cout << "Main\t E: Cannot create multi-thread run manager" << std::endl;
		return -1;
	}
	
	auto detectorConstruction = new DetectorConstruction();
	
	runManager->SetNumberOfThreads(10);
	runManager->SetUserInitialization(detectorConstruction);	
	runManager->SetUserInitialization(new PhysicsList());
	runManager->SetUserInitialization(new ActionInitialization(detectorConstruction));
	
	runManager->Initialize();
	
	runManager->BeamOn(numberOfEvents);
	
	SAFE_DELETE(runManager);
	
	return 0;
}

void ParseInputParameters(int argc, char** argv, G4int &numOfThreads, G4int& numOfEvents)
{
	if (argc != 3)
	{
		G4cout << "USAGE: plates <numberOfThreads> <numberOfEvents>" << G4endl;
		G4cout << "Use -1 to ignore the variable" << G4endl;
		G4cout << "Run without argument is equal to plates 10 10" << G4endl;
		G4cout << G4endl;
		return;
	}
		
	auto threads = atoi(argv[1]);
	if (threads != -1)
	{
		numOfThreads = threads;
	}
	
	auto events = atoi(argv[2]);
	if (events > -1)
	{
		numOfEvents = events;
	}
}
