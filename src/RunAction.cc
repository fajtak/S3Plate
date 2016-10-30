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

#include <RunAction.hh>
#include <G4Run.hh>
#include <G4RunManager.hh>
#include <G4UnitsTable.hh>
#include <macros.hh>

using namespace CLHEP;

RunAction::RunAction()
{
	analysisManager = G4AnalysisManager::Instance();	
}

RunAction::~RunAction()
{
	SAFE_DELETE( analysisManager );
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
		SetupAnalysisManager();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
	if (analysisManager != nullptr)
	{
		analysisManager->Write();
		analysisManager->CloseFile();
	}	
}

void RunAction::SetupAnalysisManager()
{	
	if (analysisManager != nullptr)
	{  
		analysisManager->OpenFile("temp.root");
		
		analysisManager->SetFirstHistoId(1);
		analysisManager->CreateH1("Energy", "Energy deposited in the scintillator", 1000, 0, 5000);
		analysisManager->CreateH1("EnergyDead", "Energy deposited in the dead layer", 1000, 0, 5000);
		analysisManager->CreateH1("Produced", "Number of photons generated in one event", 20000, 0, 20000);
		analysisManager->CreateH1("Detected", "Number of photons detected in one event", 3000, 0, 3000);
		analysisManager->CreateH1("waveProduced", "Wavelength spectra of produced photons", 1000, 0, 1000);
		analysisManager->CreateH1("waveDetected", "Wavelength spectra of detected photons", 1000, 0, 1000);
		analysisManager->CreateH1("time", "Time distribution of detected p.e.", 1000, 0, 1000);
		analysisManager->CreateH1("fiber", "Distribution of hitted fibers", 30, -15, 15);		
	}	
}

 
