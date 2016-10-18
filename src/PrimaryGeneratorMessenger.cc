#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithABool.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun) : Action(Gun)
{
  gunDir = new G4UIdirectory("/myPG/");
  gunDir->SetGuidance("PrimaryGenerator control");

  RndmCmd = new G4UIcmdWithAString("/myPG/rndm",this);
  RndmCmd->SetGuidance("Shoot randomly the incident particle.");
  RndmCmd->SetGuidance("  Choice : on(default), off");
  RndmCmd->SetParameterName("choice",true);
  RndmCmd->SetDefaultValue("on");
  RndmCmd->SetCandidates("on off");
  RndmCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  PositionCmd = new G4UIcmdWith3Vector("/myPG/position", this);
  PositionCmd->SetGuidance("Set the position of the primary particle.");

  PointCmd = new G4UIcmdWithABool("/myPG/point",this);
  WholeDetCmd = new G4UIcmdWithABool("/myPG/wholeDet",this);
  KalabashkyCmd = new G4UIcmdWithABool("/myPG/kalabashky",this);
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete RndmCmd;
  delete gunDir;
  delete PositionCmd;
  delete PointCmd;
  delete WholeDetCmd;
  delete KalabashkyCmd;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if( command == RndmCmd )
    {
        Action->SetRndmFlag(newValue);
    }else if (command == PositionCmd )
    {
        Action->SetX(PositionCmd->GetNew3VectorValue(newValue).getX());
        Action->SetY(PositionCmd->GetNew3VectorValue(newValue).getY());
        Action->SetZ(PositionCmd->GetNew3VectorValue(newValue).getZ());
    }else if (command == PointCmd )
    {
        Action->SetPoint();
    }else if (command == WholeDetCmd )
    {
        Action->SetWholeDet();
    }else if (command == KalabashkyCmd )
    {
        Action->SetKalabashky();
    }
}
