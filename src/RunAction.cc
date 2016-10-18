#include "RunAction.hh"

#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include <string>
#include <time.h>

using namespace CLHEP;

RunAction::RunAction(PrimaryGeneratorAction* PG) : partGen(PG)
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    nInteracting = 0;
    nPassing = 0;

    hist = new TH1F("Energy","Energy deposited in the scintillator",1000,0,5000);
    histDead = new TH1F("EnergyDead","Energy deposited in the dead layer",1000,0,5000);
    histProduced = new TH1F("Produced","Number of photons generated in one event",20000,0,20000);
    histDetected = new TH1F("Detected","Number of photons detected in one event",3000,0,3000);
    photoWaveProduced = new TH1F("waveProduced","Wavelength spectra of produced photons",1000,0,1000);
    photoWaveDetected = new TH1F("waveDetected","Wavelength spectra of detected photons",1000,0,1000);
    timeH = new TH1F("time", "Time distribution of detected p.e.",1000,0,1000);
    fiber = new TH1F("fiber", "Distribution of hited fibers",30,-15,15);

    std::string fileName = "time";
    std::string fileName2 = "fiber";

    char print[50];
    sprintf(print, "%.2fx%.2fx%.2f", partGen->GetX()/cm , partGen->GetY()/cm, partGen->GetZ()/cm);
    fileName += print;
    fileName += ".txt";
    fileName2 += print;
    fileName2 += ".txt";
    timeFile.open(fileName.c_str());
    fiberFile.open(fileName2.c_str());
    time(&myTime);
}

void RunAction::fillPerEvent(int interact, int pass, G4double energy, G4double energyDead)
{
  //accumulate statistic
  //
  nInteracting += interact;
  nPassing += pass;
  energyDeposited = energy;
  energyDepositedDead = energyDead;
  if (energy != 0 ) hist->Fill(energy);
  histDead->Fill(energyDead);
  if (interact != 0 ) histProduced->Fill(interact);
  if (pass != 0 )histDetected->Fill(pass);
  timeFile << -1 << G4endl;
  fiberFile << -9999 << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;

  //print
  //
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << "\n Number of passing         : " << nPassing << " = " << (double)nPassing/NbOfEvents*100 << " %"
     << "\n Number of intercting      : " << nInteracting << " = " << (double)nInteracting/NbOfEvents*100 << " %"
     << "\n Ratio interacting/passing : " << (double)nInteracting/nPassing*100 << " %"
     << "\n Number of events          : " << NbOfEvents
     << G4endl;

  f=new TFile("temp.root","update");

  TObjString*  dimensions = new TObjString();

  struct tm * timeinfo;

  timeinfo = localtime(&myTime);

  char buffer[80];
  strftime(buffer,80,"%F--%H-%M-%S",timeinfo);

  char print[100];
  sprintf(print, "%.2f %.2f %.2f cm %s ", partGen->GetX()/cm , partGen->GetY()/cm, partGen->GetZ()/cm,buffer);
  dimensions->SetString(print);

  f->mkdir(print);
  f->cd(print);
  hist->Write();
  histDead->Write();
  histProduced->Write();
  histDetected->Write();
  photoWaveProduced->Write();
  photoWaveDetected->Write();
  timeH->Write();
  fiber->Write();
  timeFile.close();
  fiberFile.close();

    delete hist;
    delete histDead;
    delete histProduced;
    delete histDetected;
    delete photoWaveProduced;
    delete photoWaveDetected;
    delete timeH;
    delete fiber;

  G4cout<<"Closing file..."<<G4endl;
  f->cd();
  f->Close();
}

 void RunAction::fillPhotoWaveProduced(double wavelength)
 {
    photoWaveProduced->Fill(wavelength);
 }

 void RunAction::fillPhotoWaveDetected(double wavelength)
 {
    photoWaveDetected->Fill(wavelength);
 }

 void RunAction::fillTime(double newTime)
 {
    timeH->Fill(newTime);
    timeFile << newTime << " ";
 }

 void RunAction::fillFiber(int fiberID)
 {
    fiber->Fill(fiberID);
    fiberFile << fiberID << " ";
 }
