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

#include <EventAction.hh>
#include <g4root.hh>

EventAction::EventAction()
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event*)
{
	interaction = 0;
	passage = 0;
	energyDep = 0;
	energyDepDead = 0;
	nDetection = 0;
	nProduced = 0;
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
	auto analysisManager = G4AnalysisManager::Instance();
	
	if (analysisManager != nullptr)
	{
		auto interactHistoId = analysisManager->GetH1Id("Produced");
		auto passHistoId = analysisManager->GetH1Id("Detected");
		auto energyDepHistId = analysisManager->GetH1Id("Energy");
		auto energyDepDeadHistId = analysisManager->GetH1Id("EnergyDead");
		
		analysisManager->FillH1(interactHistoId, nProduced);
		analysisManager->FillH1(passHistoId, nDetection);
		analysisManager->FillH1(energyDepHistId, energyDep);
		analysisManager->FillH1(energyDepDeadHistId, energyDepDead);
	}
}

void EventAction::PassWaveRun(int whichHist, double wavelength)
{
	auto analysisManager = G4AnalysisManager::Instance();
	
	if (analysisManager == nullptr)
	{
		return;
	}	
	
	switch(whichHist)
	{
		case 1:
		{
			auto waveProducedHistoId =  analysisManager->GetH1Id("waveProduced");
			analysisManager->FillH1(waveProducedHistoId, wavelength);
		}
		break;
		case 2:
		{
			auto waveDetectedHistoId =  analysisManager->GetH1Id("waveDetected");
			analysisManager->FillH1(waveDetectedHistoId, wavelength);
		}
		break;
		default:
			G4cout << "EventAction::PassWaveRun\tError: Invalid histogram id" << std::endl;
	}
}

void EventAction::AddTime(double time)
{
	auto analysisManager = G4AnalysisManager::Instance();
	
	if (analysisManager == nullptr)
	{
		return;
	}
	
	auto timeHistoId = analysisManager->GetH1Id("time");
	analysisManager->FillH1(timeHistoId, time);
}

void EventAction::AddFiberDetected(int fiberID)
{	
	auto analysisManager = G4AnalysisManager::Instance();
	
	if (analysisManager == nullptr)
	{
		return;
	}
	
	auto timeHistoId = analysisManager->GetH1Id("fiber");
	analysisManager->FillH1(timeHistoId, fiberID);
}
