#pragma once

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
