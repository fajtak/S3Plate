#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* DC) : Detector(DC), rndmFlag("off")
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

    x = 0.0*cm;
    y = 0.0*cm;
    z = 1.0*cm;

    point = true;
    wholeDet = false;
    kalabashky = false;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    if (point)
    {
        particleGun->SetParticlePosition(G4ThreeVector(x,y,z));
    }

    if (wholeDet)
    {
        double a = (-1.0+2.0*G4UniformRand())*Detector->GetDetX()/2;
        double b = (-1.0+2.0*G4UniformRand())*Detector->GetDetY()/2;
        double c = 1;
        particleGun->SetParticlePosition(G4ThreeVector(a,b,c));
    }

    if (kalabashky)
    {
        double a = x + (-1.0+2.0*G4UniformRand())*2.5*cm;
        double b = (-1.0+2.0*G4UniformRand())*Detector->GetDetY()/2;
        double c = 1;
        particleGun->SetParticlePosition(G4ThreeVector(a,b,c));
    }

    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));
    particleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::SetPoint(void)
{
    point = true;
    wholeDet = false;
    kalabashky = false;
    z = 1.0*cm;
}

void PrimaryGeneratorAction::SetWholeDet(void)
{
    point = false;
    wholeDet = true;
    kalabashky = false;
    z = -0.1*cm;
}

void PrimaryGeneratorAction::SetKalabashky(void)
{
    point = false;
    wholeDet = false;
    kalabashky = true;
    z = 0.1*cm;
}
