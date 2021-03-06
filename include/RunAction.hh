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
// $Id: RunAction.hh,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TFile.h"
#include "TH1F.h"
#include "TObjString.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class PrimaryGeneratorAction;

class RunAction : public G4UserRunAction
{
    public:
        RunAction(PrimaryGeneratorAction*);
        virtual ~RunAction();

        void BeginOfRunAction(const G4Run*);
        void   EndOfRunAction(const G4Run*);

        void fillPerEvent(int, int, G4double, G4double);

        void fillPhotoWaveProduced(double wavelength);
        void fillPhotoWaveDetected(double wavelength);
        void fillTime(double time);
        void fillFiber(int fiberID);

    private:

        G4int nInteracting;
        G4int nPassing;
        G4double energyDeposited;
        G4double energyDepositedDead;
        TFile *f;
        TH1F *hist;
        TH1F *histDead;
        TH1F *histProduced;
        TH1F *histDetected;
        TH1F *photoWaveProduced;
        TH1F *photoWaveDetected;
        TH1F *timeH;
        TH1F *fiber;

        ofstream timeFile;
        ofstream fiberFile;

        time_t myTime;

        PrimaryGeneratorAction* partGen;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

