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
// $Id: PrimaryGeneratorAction.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04-patch-01 $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(
                                             DetectorConstruction* DC)
:Detector(DC),rndmFlag("off")
{
    G4int n_particle = 1;
    particleGun  = new G4ParticleGun(n_particle);

    //create a messenger for this class
    gunMessenger = new PrimaryGeneratorMessenger(this);

    // default particle kinematic

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle
                    = particleTable->FindParticle(particleName="e-");
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleEnergy(1.0*MeV);

    x = 1.0*cm;
    y = 1.0*cm;
    z = 1.0*cm;

    //G4double x = (-1.0+2.0*G4UniformRand())*20.0*cm;
    //G4double y = (-1.0+2.0*G4UniformRand())*10.0*cm;
    //double x = +15.0*cm;
    //double y = 3.0*mm;
    //particleGun->SetParticlePosition(G4ThreeVector(x,y,1.*cm));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //G4double x = (-1.0+2.0*G4UniformRand())*Detector->GetDetX()/2;
    //G4double x = (-1.0+2.0*G4UniformRand())*2.5*cm + 15.0*cm;
    //G4double y = (-1.0+2.0*G4UniformRand())*Detector->GetDetY()/2;

    particleGun->SetParticlePosition(G4ThreeVector(x,y,z));

    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));

    particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

