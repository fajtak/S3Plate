#pragma once

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWith3Vector;
class G4UIcmdWithABool;

class PrimaryGeneratorMessenger: public G4UImessenger
{
public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
  virtual ~PrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  PrimaryGeneratorAction* Action;
  G4UIdirectory*          gunDir;
  G4UIcmdWithAString*     RndmCmd;
  G4UIcmdWith3Vector*     PositionCmd;
  G4UIcmdWithABool*       PointCmd;
  G4UIcmdWithABool*       WholeDetCmd;
  G4UIcmdWithABool*       KalabashkyCmd;
};
