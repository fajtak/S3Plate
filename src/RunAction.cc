//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: RunAction.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"

#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(PrimaryGeneratorAction* PG) : partGen(PG)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    //inform the runManager to save random number seed
    //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

    //initialize cumulative quantities
    //
    nInteracting = 0;
    nPassing = 0;

    hist = new TH1F("Energy","Energy deposited in the scintillator",1000,0,5000);
    histDead = new TH1F("EnergyDead","Energy deposited in the dead layer",1000,0,5000);
    histProduced = new TH1F("Produced","Number of photons generated in one event",20000,0,20000);
    histDetected = new TH1F("Detected","Number of photons detected in one event",3000,0,3000);
    photoWaveProduced = new TH1F("waveProduced","Wavelength spectra of produced photons",1000,0,1000);
    photoWaveDetected = new TH1F("waveDetected","Wavelength spectra of detected photons",1000,0,1000);
    time = new TH1F("time", "Time distribution of detected p.e.",1000,0,1000);
    fiber = new TH1F("fiber", "Distribution of hited fibers",30,-15,15);
    std::string fileName = "time";
    std::string fileName2 = "fiber";
    char print[50];
    sprintf(print, "%f%f", partGen->GetX()/cm , partGen->GetY()/cm);
    fileName += print;
    fileName += ".txt";
    fileName2 += print;
    fileName2 += ".txt";
    timeFile.open(fileName.c_str());
    fiberFile.open(fileName2.c_str());
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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

  char print[50];
  sprintf(print, "%.2f %.2f %.2f cm", partGen->GetX()/cm , partGen->GetY()/cm, partGen->GetZ()/cm);
  dimensions->SetString(print);

  f->mkdir(print);
  f->cd(print);
  hist->Write();
  histDead->Write();
  histProduced->Write();
  histDetected->Write();
  photoWaveProduced->Write();
  photoWaveDetected->Write();
  time->Write();
  fiber->Write();
  timeFile.close();
  fiberFile.close();

  //dimensions->Write();

  G4cout<<"Closing file..."<<G4endl;
  f->cd();
  f->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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
    time->Fill(newTime);
    timeFile << newTime << " ";
 }

 void RunAction::fillFiber(int fiberID)
 {
    fiber->Fill(fiberID);
    fiberFile << fiberID << " ";
 }
